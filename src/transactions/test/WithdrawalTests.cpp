// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <ledger/AccountHelper.h>
#include <ledger/FeeHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/test/test_helper/ManageAccountTestHelper.h>
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

TEST_CASE("Withdraw with tasks", "[tx][withdraw][tasks]")
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
    auto manageAccountTestHelper = ManageAccountTestHelper(testManager);
    ManageLimitsTestHelper manageLimitsTestHelper(testManager);
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
    uint32_t allTasks = 0;
    issuanceHelper.applyCreateIssuanceRequest(root, asset, preIssuedAmount, withdrawerBalance->getBalanceID(),
                                              "RANDOM ISSUANCE REFERENCE", &allTasks);

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


    // create asset to withdraw to
    const AssetCode withdrawDestAsset = "BTC";
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);

    assetHelper.createAsset(root, root.key, withdrawDestAsset, root, 0);
    const uint64_t price = 2000 * ONE;
    assetPairHelper.createAssetPair(root, withdrawDestAsset, asset, price);

    //create withdraw request
    uint64_t amountToWithdraw = 1000 * ONE;
    withdrawerBalance = BalanceHelperLegacy::Instance()->loadBalance(withdrawerKP.getPublicKey(), asset,
                                                                     testManager->getDB(), nullptr);
    REQUIRE(withdrawerBalance->getAmount() >= amountToWithdraw);
    const uint64_t expectedAmountInDestAsset = 0.5 * ONE;

    Fee zeroFee;
    zeroFee.fixed = 0;
    zeroFee.percent = 0;
    SECTION("No tasks") {
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                           amountToWithdraw,
                                                                           zeroFee, "{}", withdrawDestAsset,
                                                                           expectedAmountInDestAsset);

        auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);

        auto reviewResult = reviewWithdrawHelper.applyReviewRequestTx(root, withdrawResult.success().requestID, ReviewRequestOpAction::APPROVE, "");


        REQUIRE(withdrawResult.code() == CreateWithdrawalRequestResultCode::SUCCESS);
    }

    SECTION("Default tasks") {
        longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
        manageKeyValueHelper.setKey(key)->setUi32Value(2048);
        manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                           amountToWithdraw,
                                                                           zeroFee, "{}", withdrawDestAsset,
                                                                           expectedAmountInDestAsset);

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


        REQUIRE(withdrawResult.code() == CreateWithdrawalRequestResultCode::SUCCESS);
        REQUIRE(reviewResult.success().extendedResult.fulfilled);
    }

    SECTION("Set tasks on request creation") {
        longstring key = ManageKeyValueOpFrame::makeWithdrawalTasksKey("*");
        manageKeyValueHelper.setKey(key)->setUi32Value(2048);
        manageKeyValueHelper.doApply(app, ManageKVAction::PUT, true);
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                           amountToWithdraw,
                                                                           zeroFee, "{}", withdrawDestAsset,
                                                                           expectedAmountInDestAsset);


        uint32_t allTasks = 1024;
        auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, &allTasks,
                                                                               CreateWithdrawalRequestResultCode::NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS);
    }

}


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
    auto manageAccountTestHelper = ManageAccountTestHelper(testManager);
    ManageLimitsTestHelper manageLimitsTestHelper(testManager);

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
    uint32_t allTasks = 0;
    issuanceHelper.applyCreateIssuanceRequest(root, asset, preIssuedAmount, withdrawerBalance->getBalanceID(),
                                              "RANDOM ISSUANCE REFERENCE", &allTasks);

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
        auto withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(), amountToWithdraw,
                                                                           zeroFee, "{}", withdrawDestAsset,
                                                                           expectedAmountInDestAsset);

        auto withdrawResult = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
        SECTION("Approve")
        {
            reviewWithdrawHelper.applyReviewRequestTx(root, withdrawResult.success().requestID, ReviewRequestOpAction::APPROVE, "");
        }
        SECTION("Reject")
        {
            reviewWithdrawHelper.applyReviewRequestTx(root, withdrawResult.success().requestID, ReviewRequestOpAction::PERMANENT_REJECT,
                "Invalid external details");
        }
        SECTION("Set withdrawal fee and approve")
        {
            uint64_t percentFee = 1 * ONE;
            uint64_t fixedFee = amountToWithdraw/2;
            AccountID account = withdrawerBalance->getAccountID();
            auto feeEntry = createFeeEntry(FeeType::WITHDRAWAL_FEE, fixedFee, percentFee, asset, &account, nullptr);
            applySetFees(testManager->getApp(), root.key, root.getNextSalt(), &feeEntry, false);

            auto accountFrame = AccountHelper::Instance()->loadAccount(account, testManager->getDB());
            auto feeFrame = FeeHelper::Instance()->loadForAccount(FeeType::WITHDRAWAL_FEE, asset, FeeFrame::SUBTYPE_ANY,
                                                                  accountFrame, preIssuedAmount, testManager->getDB());
            REQUIRE(feeFrame);

            Fee fee;
            fee.fixed = fixedFee;
            REQUIRE(feeFrame->calculatePercentFee(amountToWithdraw, fee.percent, ROUND_UP, 1));
            auto withdrawWithFeeRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                                      amountToWithdraw, fee, "{}",
                                                                                      withdrawDestAsset, expectedAmountInDestAsset);
            auto result = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawWithFeeRequest, nullptr);

            //approve request
            reviewWithdrawHelper.applyReviewRequestTx(root, result.success().requestID, ReviewRequestOpAction::APPROVE, "");
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
                                                                           zeroFee, "{}", withdrawDestAsset,
                                                                           expectedAmountInDestAsset);

        SECTION("successful application")
        {
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
        }

        SECTION("Account with block reason 'WITHDRAWAL' not allowed")
        {
            manageAccountTestHelper.applyManageAccount(root, withdrawer.key.getPublicKey(), AccountType::GENERAL,
                                                       {BlockReasons::WITHDRAWAL}, {});
            auto createWithdrawRequestTx = withdrawRequestHelper.createWithdrawalRequestTx(withdrawer, withdrawRequest, nullptr);
            REQUIRE(!testManager->applyCheck(createWithdrawRequestTx));
            auto opResult = getFirstResultCode(*createWithdrawRequestTx);
            REQUIRE(opResult == OperationResultCode::opACCOUNT_BLOCKED);
        }
        SECTION("Try to withdraw zero amount")
        {
            withdrawRequest.amount = 0;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr, CreateWithdrawalRequestResultCode::INVALID_AMOUNT);
        }

        SECTION("Try to withdraw in same asset") {
            withdrawRequest = withdrawRequestHelper.createWithdrawRequest(withdrawerBalance->getBalanceID(),
                                                                          amountToWithdraw,
                                                                          zeroFee, "{}", asset, amountToWithdraw);

            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr);
        }

        SECTION("too long external details")
        {
            uint64 maxLength = testManager->getApp().getWithdrawalDetailsMaxLength();
            std::string longExternalDetails(maxLength + 1, 'x');
            withdrawRequest.externalDetails = longExternalDetails;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::INVALID_EXTERNAL_DETAILS);
        }

        SECTION("invalid external details json")
        {
            //missed colon
            std::string invalidExternalDetails = "{ \"key\" \"value\" }";
            withdrawRequest.externalDetails = invalidExternalDetails;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::INVALID_EXTERNAL_DETAILS);
        }

        SECTION("try to review with invalid external details")
        {
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
            reviewWithdraw.requestDetails.requestType(ReviewableRequestType::WITHDRAW);
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
                                                             CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND);
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

        SECTION("try to withdraw in non-existing asset")
        {
            AssetCode nonExistingAsset = "BYN";
            withdrawRequest.details.autoConversion().destAsset = nonExistingAsset;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::CONVERSION_PRICE_IS_NOT_AVAILABLE);
        }

        SECTION("overflow converted amount")
        {
            withdrawRequest.amount = UINT64_MAX/pricePerUnit + 1;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::CONVERSION_OVERFLOW);
        }

        SECTION("mismatch conversion amount")
        {
            withdrawRequest.details.autoConversion().expectedAmount = expectedAmountInDestAsset + 1;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::CONVERTED_AMOUNT_MISMATCHED);
        }

        SECTION("underfunded")
        {
            withdrawRequest.amount = preIssuedAmount + 1;
            uint64_t convertedAmount = pricePerUnit * withdrawRequest.amount;
            withdrawRequest.details.autoConversion().expectedAmount = convertedAmount;

            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::UNDERFUNDED);
        }

        SECTION("overflow statistics")
        {
            //issue some amount to withdrawer
            uint64_t enoughToOverflow = UINT64_MAX/pricePerUnit - 1;
            REQUIRE(statsPricePerUnit > pricePerUnit);
            issuanceHelper.authorizePreIssuedAmount(root, root.key, asset, enoughToOverflow, root);
            issuanceHelper.applyCreateIssuanceRequest(root, asset, enoughToOverflow, withdrawerBalance->getBalanceID(),
                                                      SecretKey::random().getStrKeyPublic(), &allTasks);
            withdrawRequest.amount = enoughToOverflow;
            withdrawRequest.details.autoConversion().expectedAmount = enoughToOverflow * pricePerUnit;
            withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr,
                                                             CreateWithdrawalRequestResultCode::STATS_OVERFLOW);
        }

        SECTION("try to review withdrawal request of blocked user")
        {
            // successfully create withdraw request
            auto requestID = withdrawRequestHelper.applyCreateWithdrawRequest(withdrawer, withdrawRequest, nullptr).success().requestID;

            // block withdrawer
            manageAccountTestHelper.applyManageAccount(root, withdrawerKP.getPublicKey(), AccountType::GENERAL,
                                                       {BlockReasons::SUSPICIOUS_BEHAVIOR}, {});

            // try to review withdrawal request
            reviewWithdrawHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::APPROVE, "",
                                                      ReviewRequestResultCode::REQUESTOR_IS_BLOCKED);

            // unlock withdrawer
            manageAccountTestHelper.applyManageAccount(root, withdrawerKP.getPublicKey(), AccountType::GENERAL, {},
                                                       {BlockReasons::SUSPICIOUS_BEHAVIOR});

            // and now everything is ok
            reviewWithdrawHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::APPROVE, "");
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
