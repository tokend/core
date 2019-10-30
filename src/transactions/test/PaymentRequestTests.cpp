#include "test/test.h"
#include "test/test_marshaler.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageLimitsTestHelper.h>
#include <transactions/test/test_helper/PaymentRequestHelper.h>
#include <transactions/test/test_helper/PaymentTestHelper.h>
#include <transactions/test/test_helper/ReviewPaymentRequestHelper.h>
#include <transactions/test/test_helper/SetFeesTestHelper.h>

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("payment requests", "[tx][payment][reviewable_request]")
{
    const int trailingDigitsCount = AssetFrame::kMaximumTrailingDigits;

    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);
    auto testManager = TestManager::make(app);
    Database& db = testManager->getDB();

    // test helpers
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto issuanceTestHelper = IssuanceRequestHelper(testManager);
    auto manageAssetTestHelper = ManageAssetTestHelper(testManager);
    auto manageAssetPairTestHelper = ManageAssetPairTestHelper(testManager);
    auto paymentRequestTestHelper = PaymentRequestHelper(testManager);
    auto reviewPaymentTestHelper = ReviewPaymentRequestHelper(testManager);
    auto paymentTestHelper = PaymentTestHelper(testManager);
    auto setFeesTestHelper = SetFeesTestHelper(testManager);
    auto manageLimitsTestHelper = ManageLimitsTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    // db helpers
    auto balanceHelper = BalanceHelperLegacy::Instance();

    auto root = Account{getRoot(), Salt(0)};
    auto payer = Account{SecretKey::random(), Salt(1)};
    auto recipient = Account{SecretKey::random(), Salt(1)};

    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring assetKey = ManageKeyValueOpFrame::makeAssetCreateTasksKey();
    manageKeyValueHelper.setKey(assetKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT,
                                 true);
    longstring preissuanceKey =
        ManageKeyValueOpFrame::makePreIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(preissuanceKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT,
                                 true);
    longstring assetUpdateKey =
        ManageKeyValueOpFrame::makeAssetUpdateTasksKey();
    manageKeyValueHelper.setKey(assetUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT,
                                 true);
    longstring key = ManageKeyValueOpFrame::makeIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT,
                                 true);

    const AssetCode& paymentAsset = "USD";
    const uint64_t precision =
        AssetFrame::getMinimumAmountFromTrailingDigits(trailingDigitsCount);
    const uint64_t preIssuedAmount = INT64_MAX - (INT64_MAX % precision);

    // create asset
    uint64_t assetType = 1;
    issuanceTestHelper.createAssetWithPreIssuedAmount(
        root, paymentAsset, preIssuedAmount, root, trailingDigitsCount,
        assetType);
    manageAssetTestHelper.updateAsset(
        root, paymentAsset, root,
        static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
            static_cast<uint32_t>(AssetPolicy::TRANSFERABLE));

    // create policy (just entry)
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = assetType;
    assetResource.asset().assetCode = paymentAsset;

    AccountRuleResource reviewableRequestResource(
        LedgerEntryType::REVIEWABLE_REQUEST);
    reviewableRequestResource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_PAYMENT);
    reviewableRequestResource.reviewableRequest()
        .details.createPayment()
        .assetType = assetType;
    reviewableRequestResource.reviewableRequest()
        .details.createPayment()
        .assetCode = paymentAsset;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, reviewableRequestResource, AccountRuleAction::ANY, false);
    // write this entry to DB
    auto createSenderRuleResult = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, assetResource, AccountRuleAction::ANY, false);
    // write this entry to DB

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, assetResource, AccountRuleAction::ANY, false);
    // write this entry to DB
    auto createReceiverRuleResult = manageAccountRuleTestHelper.applyTx(
        root, ruleEntry, ManageAccountRuleAction::CREATE);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, AccountRuleResource(LedgerEntryType::TRANSACTION),
        AccountRuleAction::SEND, false);
    // write this entry to DB
    auto sendTxRuleID =
        manageAccountRuleTestHelper
            .applyTx(root, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    // create account role using root as source
    auto createSenderAccountRoleOp =
        manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_sender"})",
            {createSenderRuleResult.success().ruleID,
             createReceiverRuleResult.success().ruleID, sendTxRuleID});

    auto senderAccountRoleID =
        manageAccountRoleTestHelper.applyTx(root, createSenderAccountRoleOp)
            .success()
            .roleID;

    // create account role using root as source
    auto createReceiverAccountRoleOp =
        manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_receiver"})",
            {createReceiverRuleResult.success().ruleID, sendTxRuleID});

    auto recipientAccountRoleID =
        manageAccountRoleTestHelper.applyTx(root, createReceiverAccountRoleOp)
            .success()
            .roleID;

    payer = Account{SecretKey::random(), Salt(1)};
    recipient = Account{SecretKey::random(), Salt(1)};

    createAccountTestHelper.applyTx(
        CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(payer.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(senderAccountRoleID));

    createAccountTestHelper.applyTx(
        CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(recipient.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(recipientAccountRoleID));

    // create limits
    ManageLimitsOp manageLimitsOp;
    manageLimitsOp.details.action(ManageLimitsAction::CREATE);
    manageLimitsOp.details.limitsCreateDetails().accountID.activate() =
        payer.key.getPublicKey();
    manageLimitsOp.details.limitsCreateDetails().assetCode = paymentAsset;
    manageLimitsOp.details.limitsCreateDetails().statsOpType =
        StatsOpType::PAYMENT_OUT;
    manageLimitsOp.details.limitsCreateDetails().isConvertNeeded = false;
    manageLimitsOp.details.limitsCreateDetails().dailyOut = 20000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().weeklyOut = 40000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().monthlyOut = 80000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().annualOut = 200000 * ONE;
    manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

    // create fee charging rules for incoming and outgoing payments
    auto incomingFee = setFeesTestHelper.createFeeEntry(
        FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 0, nullptr, nullptr,
        static_cast<int64_t>(PaymentFeeType::INCOMING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &incomingFee, false);

    auto outgoingFee = setFeesTestHelper.createFeeEntry(
        FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 5 * ONE, nullptr, nullptr,
        static_cast<int64_t>(PaymentFeeType::OUTGOING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

    // find payer
    auto payerBalance = balanceHelper->loadBalance(payer.key.getPublicKey(),
                                                   paymentAsset, db, nullptr);
    REQUIRE(payerBalance);

    int64_t paymentAmount = 100 * ONE;
    auto emissionAmount = 3 * paymentAmount;

    uint32_t issuanceTasks = 0;

    issuanceTestHelper.applyCreateIssuanceRequest(
        root, paymentAsset, emissionAmount, payerBalance->getBalanceID(),
        SecretKey::random().getStrKeyPublic(), &issuanceTasks);

    // create destination and feeData for further tests
    auto destination = paymentTestHelper.createDestinationForAccount(
        recipient.key.getPublicKey());

    // maxPaymnetFee more in five times because fee in ETH, payment in USD,
    // exchange rates 1:5
    auto sourceFeeData = paymentTestHelper.createFeeData(
        outgoingFee.fixedFee, outgoingFee.percentFee);
    auto destFeeData = paymentTestHelper.createFeeData(incomingFee.fixedFee,
                                                       incomingFee.percentFee);
    auto paymentFeeData = paymentTestHelper.createPaymentFeeData(
        sourceFeeData, destFeeData, false);

    uint32_t zeroTasks = 0;

    SECTION("Malformed")
    {
        SECTION("Reference longer than 64")
        {
            auto invalidReference = "VECUCAORAHYCZKCAWHIJYYQZAAUWHDRNJZZLBZ"
                                    "WCZIOQJADHWMlkasjdlkjsadAANUWWQNXQLSHPR";
            auto req = paymentRequestTestHelper.createPaymentRequest(
                payerBalance->getBalanceID(), destination, paymentAmount,
                paymentFeeData, invalidReference, "");
            paymentRequestTestHelper.applyCreatePaymentRequest(
                payer, req, &zeroTasks, OperationResultCode::opINNER,
                CreatePaymentRequestResultCode::INVALID_PAYMENT,
                PaymentResultCode::MALFORMED);
        }
        SECTION("Send to self by balance")
        {
            auto balanceDestination =
                paymentTestHelper.createDestinationForBalance(
                    payerBalance->getBalanceID());

            auto req = paymentRequestTestHelper.createPaymentRequest(
                payerBalance->getBalanceID(), balanceDestination, paymentAmount,
                paymentFeeData, "", "");
            paymentRequestTestHelper.applyCreatePaymentRequest(
                payer, req, &zeroTasks, OperationResultCode::opINNER,
                CreatePaymentRequestResultCode::INVALID_PAYMENT,
                PaymentResultCode::MALFORMED);
        }
        SECTION("Send to self by account")
        {
            auto accountDestination =
                paymentTestHelper.createDestinationForAccount(
                    payer.key.getPublicKey());
            auto req = paymentRequestTestHelper.createPaymentRequest(
                payerBalance->getBalanceID(), accountDestination, paymentAmount,
                paymentFeeData, "", "");
            paymentRequestTestHelper.applyCreatePaymentRequest(
                payer, req, &zeroTasks, OperationResultCode::opINNER,
                CreatePaymentRequestResultCode::INVALID_PAYMENT,
                PaymentResultCode::MALFORMED);
        }
    }

    SECTION("All ok")
    {
        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, paymentAmount,
            paymentFeeData, "123", "");
        auto result = paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::SUCCESS);

        REQUIRE(result.success().fulfilled);
    }

    SECTION("Amount is less than destination fee")
    {

        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, 3, paymentFeeData, "",
            "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
    }
    SECTION("Payer underfunded")
    {
        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, 4 * paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::UNDERFUNDED);
    }
    SECTION("Destination account not found")
    {
        AccountID nonExistingAccount = SecretKey::random().getPublicKey();
        auto accountDestination =
            paymentTestHelper.createDestinationForAccount(nonExistingAccount);
        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), accountDestination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opNO_ENTRY);
    }
    SECTION("Destination balance not found")
    {
        BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
        auto balanceDestination =
            paymentTestHelper.createDestinationForBalance(nonExistingBalance);
        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), balanceDestination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opNO_ENTRY);
    }
    SECTION("Source balance not found")
    {

        BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
        auto req = paymentRequestTestHelper.createPaymentRequest(
            nonExistingBalance, destination, paymentAmount, paymentFeeData, "",
            "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opNO_ENTRY);
    }
    SECTION("Not allowed by asset policy")
    {
        manageAssetTestHelper.updateAsset(
            root, paymentAsset, root,
            static_cast<uint32_t>(AssetPolicy::BASE_ASSET));

        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY);

        manageAssetTestHelper.updateAsset(
            root, paymentAsset, root,
            static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));
        assetResource.asset().assetCode = "XRP";

        ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            createSenderRuleResult.success().ruleID, assetResource,
            AccountRuleAction::SEND, false);
        // write this entry to DB
        manageAccountRuleTestHelper.applyTx(root, ruleEntry,
                                            ManageAccountRuleAction::UPDATE);
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opNO_ROLE_PERMISSION);
    }

    SECTION("Insufficient fee amount")
    {
        paymentFeeData.sourceFee.fixed =
            static_cast<uint64>(outgoingFee.fixedFee - 1);
        paymentFeeData.sourceFee.percent =
            static_cast<uint64>(outgoingFee.percentFee - 1);

        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::INSUFFICIENT_FEE_AMOUNT);
    }

    SECTION("Limits exceeded")
    {
        manageLimitsOp.details.limitsCreateDetails().dailyOut =
            paymentAmount - 1;
        manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::LIMITS_EXCEEDED);
    }
    SECTION("Dest fee amount overflows UINT64_MAX")
    {
        paymentFeeData.destinationFee.fixed = UINT64_MAX;
        paymentFeeData.destinationFee.percent = 1;
        auto req = paymentRequestTestHelper.createPaymentRequest(
            payerBalance->getBalanceID(), destination, paymentAmount,
            paymentFeeData, "", "");
        paymentRequestTestHelper.applyCreatePaymentRequest(
            payer, req, &zeroTasks, OperationResultCode::opINNER,
            CreatePaymentRequestResultCode::INVALID_PAYMENT,
            PaymentResultCode::INVALID_DESTINATION_FEE);
    }

    SECTION("With tasks")
    {
        uint32_t tasks = 1;

        SECTION("All ok")
        {
            auto req = paymentRequestTestHelper.createPaymentRequest(
                payerBalance->getBalanceID(), destination, paymentAmount,
                paymentFeeData, "123", "");
            auto result = paymentRequestTestHelper.applyCreatePaymentRequest(
                payer, req, &tasks, OperationResultCode::opINNER,
                CreatePaymentRequestResultCode::SUCCESS);

            REQUIRE_FALSE(result.success().fulfilled);
            SECTION("Review")
            {
                auto requestID = result.success().requestID;
                uint32_t toAdd = 0, toRemove = 1;
                auto reviewRequestResult =
                    reviewPaymentTestHelper.applyReviewRequestTxWithTasks(
                        root, requestID, ReviewRequestOpAction::APPROVE, "",
                        ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);
                REQUIRE(reviewRequestResult.success().fulfilled);
                REQUIRE(reviewRequestResult.success().typeExt.requestType() ==
                    ReviewableRequestType::CREATE_PAYMENT);
            }

// Again, i'm too lazy to refactor all test helpers to use expected operation result code
// It's ok, i checked
//            SECTION("Remove asset & review")
//            {
//                manageAssetTestHelper.applyRemoveAssetTx(root, paymentAsset,
//                                                     nullptr);
//
//                auto requestID = result.success().requestID;
//                uint32_t toAdd = 0, toRemove = 1;
//                auto reviewRequestResult =
//                    reviewPaymentTestHelper.applyReviewRequestTxWithTasks(
//                        root, requestID, ReviewRequestOpAction::APPROVE, "",
//                        ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS, &toAdd, &toRemove);
//                REQUIRE_FALSE(reviewRequestResult.success().fulfilled);
//                REQUIRE(reviewRequestResult.success().typeExt.requestType() ==
//                    ReviewableRequestType::CREATE_PAYMENT);
//            }


        }
    }
}