#include <ledger/BalanceHelperLegacy.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <transactions/test/test_helper/PaymentTestHelper.h>
#include <transactions/test/test_helper/SetFeesTestHelper.h>
#include <transactions/test/test_helper/ManageLimitsTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test/test_marshaler.h"
#include "test/test.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("payment v2", "[tx][payment_v2]") {
    struct TestSet
    {
        const AssetCode paymentAsset;
        const int trailingDigitsCount;
    };
    const TestSet testSet = GENERATE(
            TestSet { "USD", AssetFrame::kMaximumTrailingDigits },
            TestSet { "USDN", 0 } );

    Config const &cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application &app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);
    auto testManager = TestManager::make(app);
    Database &db = testManager->getDB();

    // test helpers
    auto createAccountTestHelper = CreateAccountTestHelper(testManager);
    auto issuanceTestHelper = IssuanceRequestHelper(testManager);
    auto manageAssetTestHelper = ManageAssetTestHelper(testManager);
    auto manageAssetPairTestHelper = ManageAssetPairTestHelper(testManager);
    auto paymentV2TestHelper = PaymentTestHelper(testManager);
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
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring preissuanceKey = ManageKeyValueOpFrame::makePreIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(preissuanceKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring assetUpdateKey = ManageKeyValueOpFrame::makeAssetUpdateTasksKey();
    manageKeyValueHelper.setKey(assetUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring key = ManageKeyValueOpFrame::makeIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(key)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    const AssetCode& paymentAsset = testSet.paymentAsset;
    const uint64_t precision = AssetFrame::getMinimumAmountFromTrailingDigits(testSet.trailingDigitsCount);
    const uint64_t preIssuedAmount = INT64_MAX - (INT64_MAX % precision);

    // create asset
    uint64_t assetType = 1;
    issuanceTestHelper.createAssetWithPreIssuedAmount(root, paymentAsset, preIssuedAmount, root, testSet.trailingDigitsCount, assetType);
    manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));

    // create policy (just entry)
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = assetType;
    assetResource.asset().assetCode = paymentAsset;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, assetResource, AccountRuleAction::ANY, false);
    // write this entry to DB
    auto createSenderRuleResult = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, assetResource, AccountRuleAction::ANY, false);
    // write this entry to DB
    auto createReceiverRuleResult = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, AccountRuleResource(LedgerEntryType::TRANSACTION), AccountRuleAction::SEND, false);
    // write this entry to DB
    auto sendTxRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    // create account role using root as source
    auto createSenderAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_sender"})", {createSenderRuleResult.success().ruleID, sendTxRuleID});

    auto senderAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createSenderAccountRoleOp).success().roleID;

    // create account role using root as source
    auto createReceiverAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_receiver"})", {createReceiverRuleResult.success().ruleID, sendTxRuleID});

    auto recipientAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createReceiverAccountRoleOp).success().roleID;

    payer = Account{SecretKey::random(), Salt(1)};
    recipient = Account{SecretKey::random(), Salt(1)};

    createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                            .setSource(root)
                                            .setToPublicKey(payer.key.getPublicKey())
                                            .addBasicSigner()
                                            .setRoleID(senderAccountRoleID));

    createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                            .setSource(root)
                                            .setToPublicKey(recipient.key.getPublicKey())
                                            .addBasicSigner()
                                            .setRoleID(recipientAccountRoleID));

    //create limits
    ManageLimitsOp manageLimitsOp;
    manageLimitsOp.details.action(ManageLimitsAction::CREATE);
    manageLimitsOp.details.limitsCreateDetails().accountID.activate() = payer.key.getPublicKey();
    manageLimitsOp.details.limitsCreateDetails().assetCode = testSet.paymentAsset;
    manageLimitsOp.details.limitsCreateDetails().statsOpType = StatsOpType::PAYMENT_OUT;
    manageLimitsOp.details.limitsCreateDetails().isConvertNeeded = false;
    manageLimitsOp.details.limitsCreateDetails().dailyOut = 20000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().weeklyOut = 40000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().monthlyOut = 80000 * ONE;
    manageLimitsOp.details.limitsCreateDetails().annualOut = 200000 * ONE;
    manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);

    // create fee charging rules for incoming and outgoing payments
    auto incomingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 0, nullptr, nullptr,
                                                        static_cast<int64_t>(PaymentFeeType::INCOMING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &incomingFee, false);

    auto outgoingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 5 * ONE, nullptr, nullptr,
                                                        static_cast<int64_t>(PaymentFeeType::OUTGOING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

    // find payer
    auto payerBalance = balanceHelper->loadBalance(payer.key.getPublicKey(), paymentAsset, db, nullptr);
    REQUIRE(payerBalance);

    int64_t paymentAmount = 100 * ONE;
    auto emissionAmount = 3 * paymentAmount;

    uint32_t issuanceTasks = 0;

    issuanceTestHelper.applyCreateIssuanceRequest(root, paymentAsset, emissionAmount, payerBalance->getBalanceID(),
                                                  SecretKey::random().getStrKeyPublic(), &issuanceTasks);

    // create destination and feeData for further tests
    auto destination = paymentV2TestHelper.createDestinationForAccount(recipient.key.getPublicKey());

    // maxPaymnetFee more in five times because fee in ETH, payment in USD, exchange rates 1:5
    auto sourceFeeData = paymentV2TestHelper.createFeeData(outgoingFee.fixedFee, outgoingFee.percentFee);
    auto destFeeData = paymentV2TestHelper.createFeeData(incomingFee.fixedFee, incomingFee.percentFee);
    auto paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);

    if (testSet.paymentAsset == "USD") {
        SECTION("Malformed") {
            SECTION("Reference longer than 64") {
                auto invalidReference = "VECUCAORAHYCZKCAWHIJYYQZAAUWHDRNJZZLBZWCZIOQJADHWMAANUWWQNXQLSHPR";
                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "",
                                                     invalidReference, nullptr,
                                                     PaymentResultCode::MALFORMED);
            }

            SECTION("Too much signs"){
                auto invalidSubject = "1111аааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааа";
                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                      paymentAmount, paymentFeeData, invalidSubject,
                                                      "", nullptr,
                                                     PaymentResultCode::TOO_MUCH_SIGNS);

            }

            SECTION("Send to self by balance") {
                auto balanceDestination = paymentV2TestHelper.createDestinationForBalance(payerBalance->getBalanceID());
                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                     balanceDestination, paymentAmount, paymentFeeData,
                                                     "", "", nullptr,
                                                     PaymentResultCode::MALFORMED);
            }
            SECTION("Send to self by account") {
                auto accountDestination = paymentV2TestHelper.createDestinationForAccount(payer.key.getPublicKey());
                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                     accountDestination, paymentAmount, paymentFeeData,
                                                     "", "", nullptr,
                                                     PaymentResultCode::MALFORMED);
            }
        }
        SECTION("Amount is less than destination fee") {
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 destination, 3, paymentFeeData, "", "", nullptr,
                                                 PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
        }
        SECTION("Payer underfunded") {
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount * 4, paymentFeeData, "", "",
                                                 nullptr, PaymentResultCode::UNDERFUNDED);
        }
        SECTION("Destination account not found") {
            AccountID nonExistingAccount = SecretKey::random().getPublicKey();
            auto accountDestination = paymentV2TestHelper.createDestinationForAccount(nonExistingAccount);
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 accountDestination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND,
                                                 OperationResultCode::opNO_ENTRY);
        }
        SECTION("Destination balance not found") {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            auto balanceDestination = paymentV2TestHelper.createDestinationForBalance(nonExistingBalance);
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 balanceDestination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND,
                                                 OperationResultCode::opNO_ENTRY);
        }
        SECTION("Source balance not found") {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            paymentV2TestHelper.applyPaymentTx(payer, nonExistingBalance,
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::SRC_BALANCE_NOT_FOUND,
                                                 OperationResultCode::opNO_ENTRY);
        }
        SECTION("Not allowed by asset policy")
        {
            manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET));
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY);

            manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                        static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                        static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));
            assetResource.asset().assetCode = "XRP";

            ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
                    createSenderRuleResult.success().ruleID, assetResource, AccountRuleAction::SEND, false);
            // write this entry to DB
            manageAccountRuleTestHelper.applyTx(root, ruleEntry, ManageAccountRuleAction::UPDATE);
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY,
                                                 OperationResultCode::opNO_ROLE_PERMISSION);
        }

        SECTION("Insufficient fee amount") {
            paymentFeeData.sourceFee.fixed = static_cast<uint64>(outgoingFee.fixedFee - 1);
            paymentFeeData.sourceFee.percent = static_cast<uint64>(outgoingFee.percentFee - 1);
            paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentResultCode::INSUFFICIENT_FEE_AMOUNT);
        }
    }
    SECTION("Limits exceeded") {
        manageLimitsOp.details.limitsCreateDetails().dailyOut = paymentAmount - 1;
        manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);
        paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                             destination, paymentAmount, paymentFeeData, "", "",
                                             nullptr, PaymentResultCode::LIMITS_EXCEEDED);
    }
    SECTION("Dest fee amount overflows UINT64_MAX") {
        paymentFeeData.destinationFee.fixed = UINT64_MAX;
        paymentFeeData.destinationFee.percent = 1;
        paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(),
                                             destination, paymentAmount, paymentFeeData, "", "",
                                             nullptr, PaymentResultCode::INVALID_DESTINATION_FEE);
    }

    SECTION("Single asset payment") {
        setFeesTestHelper.applySetFeesTx(root, &outgoingFee, true);
        outgoingFee.asset = paymentAsset;
        setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

        SECTION("Source pays for destination success") {
            paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, true);

            SECTION("Happy path") {
                // create paymentDelta to check balances amounts
                PaymentDelta paymentV2Delta;

                auto totalFee = outgoingFee.fixedFee + outgoingFee.percentFee + incomingFee.fixedFee +
                                incomingFee.percentFee;

                paymentV2Delta.source.push_back(BalanceDelta{paymentAsset, (paymentAmount + totalFee) * -1});
                paymentV2Delta.destination.push_back(BalanceDelta{paymentAsset, paymentAmount});
                paymentV2Delta.commission.push_back(BalanceDelta{paymentAsset, totalFee});

                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "",
                                                     &paymentV2Delta);
            }

            SECTION("Happy path using account rule and rules")
            {
                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "");
            }

            SECTION("Incorrect amount precision") {
                if (testSet.paymentAsset == "USDN") {
                    paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                         paymentAmount - 1, paymentFeeData, "", "",
                                                         nullptr, PaymentResultCode::INCORRECT_AMOUNT_PRECISION);
                }
            }
        }
        SECTION("Destination pays") {
            paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);

            SECTION("Happy path") {
                // create paymentDelta to check balances amounts
                PaymentDelta paymentV2Delta;

                auto totalFee = outgoingFee.fixedFee + outgoingFee.percentFee + incomingFee.fixedFee +
                                incomingFee.percentFee;

                paymentV2Delta.source.push_back(
                        BalanceDelta{paymentAsset, (paymentAmount + outgoingFee.fixedFee + outgoingFee.percentFee) * -1});
                paymentV2Delta.destination.push_back(
                        BalanceDelta{paymentAsset, paymentAmount - (incomingFee.fixedFee + incomingFee.percentFee)});
                paymentV2Delta.commission.push_back(BalanceDelta{paymentAsset, totalFee});

                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "ref",
                                                     &paymentV2Delta);

                paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "ref",
                                                     &paymentV2Delta, PaymentResultCode::REFERENCE_DUPLICATION);
            }
            SECTION("Incorrect amount precision") {
                if (testSet.paymentAsset == "USDN") {
                    paymentV2TestHelper.applyPaymentTx(payer, payerBalance->getBalanceID(), destination,
                                                         paymentAmount - 1, paymentFeeData, "", "",
                                                         nullptr, PaymentResultCode::INCORRECT_AMOUNT_PRECISION);
                }

            }
        }
    }
}