// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <ledger/AccountHelperLegacy.h>
#include <ledger/FeeHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <transactions/test/test_helper/ManageLimitsTestHelper.h>
#include "main/test.h"
#include "crypto/SHA.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "ledger/BalanceHelperLegacy.h"
#include "test_helper/WithdrawRequestHelper.h"
#include "test_helper/ReviewWithdrawalRequestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("Withdraw", "[tx][withdraw]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto root = Account{ getRoot(), Salt(0) };
    auto issuanceHelper = IssuanceRequestHelper(testManager);
    auto assetHelper = ManageAssetTestHelper(testManager);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    auto reviewWithdrawHelper = ReviewWithdrawRequestHelper(testManager);
    auto withdrawRequestHelper = WithdrawRequestHelper(testManager);
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    ManageLimitsTestHelper manageLimitsTestHelper(testManager);

    //Default tasks
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
    longstring assetCreate = ManageKeyValueOpFrame::makeAssetCreateTasksKey();
    manageKeyValueHelper.setKey(assetCreate)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring assetUpdate = ManageKeyValueOpFrame::makeAssetUpdateTasksKey();
    manageKeyValueHelper.setKey(assetUpdate)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring preissuanceKey = ManageKeyValueOpFrame::makePreIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(preissuanceKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring issuanceKey = ManageKeyValueOpFrame::makeIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(issuanceKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    // create asset and make it withdrawable
    const AssetCode asset = "USD";
    const uint64_t preIssuedAmount = 10000 * ONE;
    issuanceHelper.createAssetWithPreIssuedAmount(root, asset, preIssuedAmount, root);
    assetHelper.updateAsset(root, asset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) | static_cast<uint32_t>(AssetPolicy::WITHDRAWABLE));

    //create stats asset and stats asset pair
    const AssetCode statsAsset = "UAH";
    assetHelper.createAsset(root, root.key, statsAsset, root, static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));
    const uint64_t statsPricePerUnit = 25;
    const uint64_t statsPrice = 25 * ONE;
    assetPairHelper.createAssetPair(root, asset, statsAsset, statsPrice);

    // create account which will withdraw
    auto withdrawerKP = SecretKey::random();
    createAccountTestHelper.applyCreateAccountTx(root, withdrawerKP.getPublicKey(), AccountType::GENERAL);
    auto withdrawer = Account{ withdrawerKP, Salt(0) };
    auto withdrawerBalance = BalanceHelperLegacy::Instance()->loadBalance(withdrawerKP.getPublicKey(), asset, testManager->getDB(), nullptr);
    REQUIRE(!!withdrawerBalance);
    issuanceHelper.applyCreateIssuanceRequest(root, asset, preIssuedAmount, withdrawerBalance->getBalanceID(),
                                              "RANDOM ISSUANCE REFERENCE");

    //create limitsV2
    ManageLimitsOp manageLimitsOp;
    manageLimitsOp.details.action(ManageLimitsAction::CREATE);
    manageLimitsOp.details.limitsCreateDetails().accountID.activate() = withdrawer.key.getPublicKey();
    manageLimitsOp.details.limitsCreateDetails().assetCode = "UAH";
    manageLimitsOp.details.limitsCreateDetails().statsOpType = StatsOpType::WITHDRAW;
    manageLimitsOp.details.limitsCreateDetails().isConvertNeeded = true;
    manageLimitsOp.details.limitsCreateDetails().dailyOut = 200000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().weeklyOut = 400000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().monthlyOut = 800000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().annualOut = 2000000 * ONE;
    manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

    SECTION("Happy path")
    {
        // create asset to withdraw to
        const AssetCode withdrawDestAsset = "BTC";
        assetHelper.createAsset(root, root.key, withdrawDestAsset, root, 0);
        const uint64_t price = 2000 * ONE;
        assetPairHelper.createAssetPair(root, withdrawDestAsset, asset, price);

        //create withdraw request
        uint64_t amountToWithdraw = 1000 * ONE;
        withdrawerBalance = BalanceHelperLegacy::Instance()->loadBalance(withdrawerKP.getPublicKey(), asset, testManager->getDB(), nullptr);
        REQUIRE(withdrawerBalance->getAmount() >= amountToWithdraw);
        const uint64_t expectedAmountInDestAsset = 0.5 * ONE;

        Fee zeroFee;
        zeroFee.fixed = 0;
        zeroFee.percent = 0;


        SECTION("Default tasks") {
            longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
            manageKeyValueHelper.setKey(key)->setUi32Value(2048);
            manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
            auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                               amountToWithdraw,
                                                                               zeroFee, "{}");

            auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);

            uint32_t toAdd = 0;
            uint32_t toRemove = 2048;
            auto reviewResult = reviewWithdrawHelper.applyReviewRequestTxWithTasks(root,
                                                                                   withdrawResult.success().requestID,
                                                                                   ReviewRequestOpAction::APPROVE,
                                                                                   "",
                                                                                   ReviewRequestResultCode::SUCCESS,
                                                                                   &toAdd,
                                                                                   &toRemove
            );

            REQUIRE(reviewResult.success().fulfilled);
        }

        SECTION("Set tasks on request creation") {
            longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
            manageKeyValueHelper.setKey(key)->setUi32Value(2048);
            manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
            auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                               amountToWithdraw,
                                                                               zeroFee, "{}");


            uint32_t allTasks = 1024;
            auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, &allTasks,
                                                                                   CreateWithdrawalRequestResultCode::NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS);
        }


        SECTION("lower bound")
        {
            //create withdraw request
            uint64_t amountToWithdraw = 100 * ONE;
            auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(), amountToWithdraw,
                                                                               zeroFee, "{}");

            longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
            manageKeyValueHelper.setKey(key)->setUi32Value(1);
            manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);

            SECTION("exceeded")
            {
                uint64 lowerLimits = ONE;
                manageKeyValueHelper.setKey("WithdrawLowerBound:USD");
                manageKeyValueHelper.setUi64Value(lowerLimits);
                manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
                withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest);
            }
            SECTION("lower bound not set")
            {
                withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest);
            }
        }
    }

    SECTION("create withdraw request hard path")
    {
        // create asset to withdraw to
        const AssetCode withdrawDestAsset = "CZK";
        assetHelper.createAsset(root, root.key, withdrawDestAsset, root, 0);
        const uint64_t pricePerUnit = 20;
        const uint64_t price = pricePerUnit * ONE;
        assetPairHelper.createAssetPair(root, asset, withdrawDestAsset, price);

        //create withdraw request
        uint64_t amountToWithdraw = 1000 * ONE;
        withdrawerBalance = BalanceHelperLegacy::Instance()->loadBalance(withdrawerKP.getPublicKey(), asset, testManager->getDB(), nullptr);
        REQUIRE(withdrawerBalance->getAmount() >= amountToWithdraw);
        const uint64_t expectedAmountInDestAsset = pricePerUnit * amountToWithdraw;

        Fee zeroFee;
        zeroFee.fixed = 0;
        zeroFee.percent = 0;
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(), amountToWithdraw,
                                                                           zeroFee, "{}");
        longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
        manageKeyValueHelper.setKey(key)->setUi32Value(1);
        manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);

        SECTION("lower bound")
        {

            SECTION("Reject")
            {
                uint64 lowerLimits = 2000 * ONE;
                manageKeyValueHelper.setKey(ManageKeyValueOpFrame::makeWithdrawLowerBoundKey("USD"));
                manageKeyValueHelper.setUi64Value(lowerLimits);
                manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
                withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest,
                                                                 nullptr,
                                                                 CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED);
            }
        }
        SECTION("zero tasks") {
            longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
            manageKeyValueHelper.setKey(key)->setUi32Value(0);
            manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
            auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest,
                                                                                   nullptr,
                                                                                   CreateWithdrawalRequestResultCode::WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED);
        }
        SECTION("successful application")
        {
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
        }

        SECTION("Try to withdraw zero amount")
        {
            withdrawRequest.amount = 0;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr, CreateWithdrawalRequestResultCode::INVALID_AMOUNT);
        }

        SECTION("too long external details")
        {
            uint64 maxLength = testManager->getApp().getWithdrawalDetailsMaxLength();
            std::string longExternalDetails(maxLength + 1, 'x');
            withdrawRequest.creatorDetails = longExternalDetails;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::INVALID_EXTERNAL_DETAILS);
        }

        SECTION("invalid external details json")
        {
            //missed colon
            std::string invalidExternalDetails = "{ \"key\" \"value\" }";
            withdrawRequest.creatorDetails = invalidExternalDetails;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::INVALID_EXTERNAL_DETAILS);
        }

        SECTION("try to review with invalid external details")
        {
            longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
            manageKeyValueHelper.setKey(key)->setUi32Value(1);
            manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);

            auto opRes = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
            uint64_t requestID = opRes.success().requestID;

            auto requestFrame = ReviewableRequestHelper::Instance()->loadRequest(requestID, testManager->getDB());
            REQUIRE(!!requestFrame);

            Operation op;
            op.body.type(OperationType::REVIEW_REQUEST);
            auto& reviewWithdraw = op.body.reviewRequestOp();
            reviewWithdraw.requestID = requestID;
            reviewWithdraw.action = ReviewRequestOpAction::APPROVE;
            reviewWithdraw.reason = "";
            reviewWithdraw.requestHash = requestFrame->getHash();
            reviewWithdraw.requestDetails.requestType(ReviewableRequestType::CREATE_WITHDRAW);
            reviewWithdraw.requestDetails.withdrawal().externalDetails = "{\"key\"}";

            TxHelper txHelper(testManager);
            auto txFrame = txHelper.txFromOperation(root, op);
            testManager->applyCheck(txFrame);

            auto opResCode = txFrame->getResult().result.results()[0].tr().reviewRequestResult().code();
            REQUIRE(opResCode == ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        }

        SECTION("non-zero universal amount")
        {
            withdrawRequest.universalAmount = ONE;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::INVALID_UNIVERSAL_AMOUNT);
        }

        SECTION("try to withdraw from non-existing balance")
        {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            withdrawRequest.balance = nonExistingBalance;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND,
                                                             OperationResultCode::opNO_ENTRY);
        }

        SECTION("try to withdraw from not my balance")
        {
            //create another account
            auto newAccountKP = SecretKey::random();
            createAccountTestHelper.applyCreateAccountTx(root, newAccountKP.getPublicKey(), AccountType::GENERAL);
            Account newAccount = Account{newAccountKP, Salt(0)};

            withdrawRequestHelper.applyCreateWithdrawRequest(newAccount, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND);
        }

        SECTION("try to withdraw non-withdrawable asset")
        {
            // make asset non-withdrawable by updating policies
            assetHelper.updateAsset(root, asset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET));
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::ASSET_IS_NOT_WITHDRAWABLE);
        }

        SECTION("fee doesn't match")
        {
            Fee newFee;
            newFee.fixed = ONE;
            newFee.percent = ONE;
            withdrawRequest.fee = newFee;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::FEE_MISMATCHED);
        }

        SECTION("overflow statistics")
        {
            uint32_t allTasks = 0;
            //issue some amount to withdrawer
            uint64_t enoughToOverflow = UINT64_MAX/pricePerUnit - 1;
            REQUIRE(statsPricePerUnit > pricePerUnit);
            issuanceHelper.authorizePreIssuedAmount(root, root.key, asset, enoughToOverflow, root);
            issuanceHelper.applyCreateIssuanceRequest(root, asset, enoughToOverflow, withdrawerBalance->getBalanceID(),
                                                      SecretKey::random().getStrKeyPublic(), &allTasks);
            withdrawRequest.amount = enoughToOverflow;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::STATS_OVERFLOW);
        }

        SECTION("exceed limits")
        {
            manageLimitsOp.details.limitsCreateDetails().dailyOut = amountToWithdraw - 1;
            manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest,
                                                             nullptr,
                                                             CreateWithdrawalRequestResultCode::LIMITS_EXCEEDED);
        }

    }

}
