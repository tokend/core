#include <ledger/BalanceHelperLegacy.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageAssetPairTestHelper.h>
#include <transactions/test/test_helper/PaymentV2TestHelper.h>
#include <transactions/test/test_helper/SetFeesTestHelper.h>
#include <transactions/test/test_helper/ManageLimitsTestHelper.h>
#include "test_helper/TxHelper.h"
#include "test/test_marshaler.h"
#include "main/test.h"
#include "TxTests.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("payment v2", "[tx][payment_v2]") {
    struct TestSet
    {
        const AssetCode paymentAsset;
        //const AssetCode feeAsset;
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
    auto paymentV2TestHelper = PaymentV2TestHelper(testManager);
    auto setFeesTestHelper = SetFeesTestHelper(testManager);
    auto manageLimitsTestHelper = ManageLimitsTestHelper(testManager);

    // db helpers
    auto balanceHelper = BalanceHelperLegacy::Instance();

    auto root = Account{getRoot(), Salt(0)};
    auto payer = Account{SecretKey::random(), Salt(1)};
    auto recipient = Account{SecretKey::random(), Salt(1)};

    const AssetCode& paymentAsset = testSet.paymentAsset;
    //const AssetCode& feeAsset = testSet.feeAsset;
    const uint64_t precision = AssetFrame::getMinimumAmountFromTrailingDigits(testSet.trailingDigitsCount);
    const uint64_t preIssuedAmount = INT64_MAX - (INT64_MAX % precision);

    // create two assets
    issuanceTestHelper.createAssetWithPreIssuedAmount(root, paymentAsset, preIssuedAmount, root, testSet.trailingDigitsCount);
    manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));
    issuanceTestHelper.createAssetWithPreIssuedAmount(root, paymentAsset, preIssuedAmount, root, testSet.trailingDigitsCount);
    manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                            static_cast<uint32_t>(AssetPolicy::TRANSFERABLE));

    // create payment participants
    createAccountTestHelper.applyCreateAccountTx(root, payer.key.getPublicKey(), AccountType::GENERAL);
    createAccountTestHelper.applyCreateAccountTx(root, recipient.key.getPublicKey(), AccountType::GENERAL);

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

    // exchange rates ETH USD
    auto exchangeRatesETH_USD = 5;

    // create asset pair
    manageAssetPairTestHelper.createAssetPair(root, paymentAsset, paymentAsset, exchangeRatesETH_USD * ONE);

    // create fee charging rules for incoming and outgoing payments
    auto incomingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 0, nullptr, nullptr,
                                                        static_cast<int64_t>(PaymentFeeType::INCOMING), 0, preIssuedAmount,
                                                        &paymentAsset);
    setFeesTestHelper.applySetFeesTx(root, &incomingFee, false);

    auto outgoingFee = setFeesTestHelper.createFeeEntry(FeeType::PAYMENT_FEE, paymentAsset, 5 * ONE, 5 * ONE, nullptr, nullptr,
                                                        static_cast<int64_t>(PaymentFeeType::OUTGOING), 0, preIssuedAmount,
                                                        &paymentAsset);
    setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

    // fund payer
    auto payerBalance = balanceHelper->loadBalance(payer.key.getPublicKey(), paymentAsset, db, nullptr);
    REQUIRE(payerBalance);

    auto payerFeeBalance = balanceHelper->loadBalance(payer.key.getPublicKey(), paymentAsset, db, nullptr);
    REQUIRE(payerFeeBalance);

    int64_t paymentAmount = 100 * ONE;
    auto emissionAmount = 3 * paymentAmount;

    uint32_t issuanceTasks = 0;

    issuanceTestHelper.applyCreateIssuanceRequest(root, paymentAsset, emissionAmount, payerBalance->getBalanceID(),
                                                  SecretKey::random().getStrKeyPublic(), &issuanceTasks);
    issuanceTestHelper.applyCreateIssuanceRequest(root, paymentAsset, emissionAmount, payerFeeBalance->getBalanceID(),
                                                  SecretKey::random().getStrKeyPublic(), &issuanceTasks);

    // create destination and feeData for further tests
    auto destination = paymentV2TestHelper.createDestinationForAccount(recipient.key.getPublicKey());

    // maxPaymnetFee more in five times because fee in ETH, payment in USD, exchange rates 1:5
    auto sourceFeeData = paymentV2TestHelper.createFeeData(outgoingFee.fixedFee, outgoingFee.percentFee * exchangeRatesETH_USD,
                                                           outgoingFee.ext.feeAsset());
    auto destFeeData = paymentV2TestHelper.createFeeData(incomingFee.fixedFee, incomingFee.percentFee,
                                                         incomingFee.ext.feeAsset());
    auto paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);

    if (testSet.paymentAsset == "USD") {
        SECTION("Malformed") {
            SECTION("Reference longer than 64") {
                auto invalidReference = "VECUCAORAHYCZKCAWHIJYYQZAAUWHDRNJZZLBZWCZIOQJADHWMAANUWWQNXQLSHPR";
                paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "",
                                                     invalidReference, nullptr,
                                                     PaymentV2ResultCode::MALFORMED);
            }
            SECTION("Send to self by balance") {
                auto balanceDestination = paymentV2TestHelper.createDestinationForBalance(payerBalance->getBalanceID());
                paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                     balanceDestination, paymentAmount, paymentFeeData,
                                                     "", "", nullptr,
                                                     PaymentV2ResultCode::MALFORMED);
            }
            SECTION("Send to self by account") {
                auto accountDestination = paymentV2TestHelper.createDestinationForAccount(payer.key.getPublicKey());
                paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                     accountDestination, paymentAmount, paymentFeeData,
                                                     "", "", nullptr,
                                                     PaymentV2ResultCode::MALFORMED);
            }
        }
        SECTION("Amount is less than destination fee") {
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 destination, 3, paymentFeeData, "", "", nullptr,
                                                 PaymentV2ResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
        }
        SECTION("Payer underfunded") {
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount * 4, paymentFeeData, "", "",
                                                 nullptr, PaymentV2ResultCode::UNDERFUNDED);
        }
        SECTION("Destination account not found") {
            AccountID nonExistingAccount = SecretKey::random().getPublicKey();
            auto accountDestination = paymentV2TestHelper.createDestinationForAccount(nonExistingAccount);
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 accountDestination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
        }
        SECTION("Destination balance not found") {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            auto balanceDestination = paymentV2TestHelper.createDestinationForBalance(nonExistingBalance);
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 balanceDestination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::DESTINATION_BALANCE_NOT_FOUND);
        }
        SECTION("Payment between different assets are not supported") {
            auto balanceDestination = paymentV2TestHelper.createDestinationForBalance(payerFeeBalance->getBalanceID());
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 balanceDestination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::BALANCE_ASSETS_MISMATCHED);
        }
        SECTION("Source balance not found") {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            paymentV2TestHelper.applyPaymentV2Tx(payer, nonExistingBalance,
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::SRC_BALANCE_NOT_FOUND);
        }
        SECTION("Not allowed by asset policy") {
            manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET));
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::NOT_ALLOWED_BY_ASSET_POLICY);

            manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                        static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                        static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET) |
                                                                        static_cast<uint32_t>(AssetPolicy::REQUIRES_VERIFICATION));
            auto newPayer = Account{SecretKey::random(), Salt(1)};
            createAccountTestHelper.applyCreateAccountTx(root, newPayer.key.getPublicKey(), AccountType::NOT_VERIFIED);
            payerBalance = balanceHelper->loadBalance(newPayer.key.getPublicKey(), paymentAsset, db, nullptr);
            REQUIRE(!!payerBalance);
            paymentV2TestHelper.applyPaymentV2Tx(newPayer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::NOT_ALLOWED_BY_ASSET_POLICY);

            manageAssetTestHelper.updateAsset(root, paymentAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                        static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                        static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET) |
                                                                        static_cast<uint32_t>(AssetPolicy::REQUIRES_KYC));
            paymentV2TestHelper.applyPaymentV2Tx(newPayer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::NOT_ALLOWED_BY_ASSET_POLICY);

            newPayer = Account{SecretKey::random(), Salt(1)};
            createAccountTestHelper.applyCreateAccountTx(root, newPayer.key.getPublicKey(), AccountType::VERIFIED);
            payerBalance = balanceHelper->loadBalance(newPayer.key.getPublicKey(), paymentAsset, db, nullptr);
            REQUIRE(!!payerBalance);
            paymentV2TestHelper.applyPaymentV2Tx(newPayer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        }

        SECTION("Insufficient fee amount") {
            paymentFeeData.sourceFee.fee.fixed = static_cast<uint64>(outgoingFee.fixedFee - 1);
            paymentFeeData.sourceFee.fee.percent = static_cast<uint64>(outgoingFee.percentFee - 1);
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::INSUFFICIENT_FEE_AMOUNT);
        }
        SECTION("Balance to charge fee from not found") {
            auto eur = "EUR";
            issuanceTestHelper.createAssetWithPreIssuedAmount(root, eur, INT64_MAX, root);
            //paymentFeeData.sourceFee.feeAsset = eur;
            manageAssetPairTestHelper.createAssetPair(root, eur, paymentAsset, 2 * ONE);
            setFeesTestHelper.applySetFeesTx(root, &outgoingFee, true);
            outgoingFee.ext.feeAsset() = eur;
            setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);
            paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                                 destination, paymentAmount, paymentFeeData, "",
                                                 "", nullptr,
                                                 PaymentV2ResultCode::BALANCE_TO_CHARGE_FEE_FROM_NOT_FOUND);
        }
    }
    SECTION("Limits exceeded") {
        manageLimitsOp.details.limitsCreateDetails().dailyOut = paymentAmount - 1;
        manageLimitsTestHelper.applyManageLimitsTx(root, manageLimitsOp);
        paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                             destination, paymentAmount, paymentFeeData, "", "",
                                             nullptr, PaymentV2ResultCode::LIMITS_EXCEEDED);
    }
    SECTION("Dest fee amount overflows UINT64_MAX") {
        paymentFeeData.destinationFee.fee.fixed = UINT64_MAX;
        paymentFeeData.destinationFee.fee.percent = 1;
        paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(),
                                             destination, paymentAmount, paymentFeeData, "", "",
                                             nullptr, PaymentV2ResultCode::INVALID_DESTINATION_FEE);
    }

    SECTION("Single asset payment") {
        setFeesTestHelper.applySetFeesTx(root, &outgoingFee, true);
        outgoingFee.ext.feeAsset() = paymentAsset;
        setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

        SECTION("Source pays for destination success") {
            paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, true);

            SECTION("Happy path") {
                // create paymentDelta to check balances amounts
                PaymentV2Delta paymentV2Delta;

                auto totalFee = outgoingFee.fixedFee + outgoingFee.percentFee + incomingFee.fixedFee +
                                incomingFee.percentFee;

                paymentV2Delta.source.push_back(BalanceDelta{paymentAsset, (paymentAmount + totalFee) * -1});
                paymentV2Delta.destination.push_back(BalanceDelta{paymentAsset, paymentAmount});
                paymentV2Delta.commission.push_back(BalanceDelta{paymentAsset, totalFee});

                paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "",
                                                     &paymentV2Delta);
            }
            SECTION("Incorrect amount precision") {
                if (testSet.paymentAsset == "USDN") {
                    paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(), destination,
                                                         paymentAmount - 1, paymentFeeData, "", "",
                                                         nullptr, PaymentV2ResultCode::INCORRECT_AMOUNT_PRECISION);
                }
            }
        }
        SECTION("Destination pays") {
            paymentFeeData = paymentV2TestHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);
//            paymentFeeData.sourceFee.feeAsset = paymentAsset;

            SECTION("Happy path") {
                // create paymentDelta to check balances amounts
                PaymentV2Delta paymentV2Delta;

                auto totalFee = outgoingFee.fixedFee + outgoingFee.percentFee + incomingFee.fixedFee +
                                incomingFee.percentFee;

                paymentV2Delta.source.push_back(
                        BalanceDelta{paymentAsset, (paymentAmount + outgoingFee.fixedFee + outgoingFee.percentFee) * -1});
                paymentV2Delta.destination.push_back(
                        BalanceDelta{paymentAsset, paymentAmount - (incomingFee.fixedFee + incomingFee.percentFee)});
                paymentV2Delta.commission.push_back(BalanceDelta{paymentAsset, totalFee});

                paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(), destination,
                                                     paymentAmount, paymentFeeData, "", "",
                                                     &paymentV2Delta);
            }
            SECTION("Incorrect amount precision") {
                if (testSet.paymentAsset == "USDN") {
                    paymentV2TestHelper.applyPaymentV2Tx(payer, payerBalance->getBalanceID(), destination,
                                                         paymentAmount - 1, paymentFeeData, "", "",
                                                         nullptr, PaymentV2ResultCode::INCORRECT_AMOUNT_PRECISION);
                }
            }
        }
    }
}