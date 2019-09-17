#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test.h"
#include "test/test_marshaler.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "transactions/test/test_helper/CloseSwapHelper.h"
#include "transactions/test/test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/IssuanceRequestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "transactions/test/test_helper/ManageAssetTestHelper.h"
#include "transactions/test/test_helper/ManageBalanceTestHelper.h"
#include "transactions/test/test_helper/OpenSwapHelper.h"
#include "transactions/test/test_helper/SetFeesTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("swap", "[tx][swap]")
{
    struct TestSet
    {
        const AssetCode swapAsset;
        const int trailingDigitsCount;
    };
    const TestSet testSet = GENERATE(
        TestSet{"USD", AssetFrame::kMaximumTrailingDigits}, TestSet{"USDN", 0});

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
    auto openSwapHelper = OpenSwapTestHelper(testManager);
    auto closeSwapHelper = CloseSwapTestHelper(testManager);
    auto setFeesTestHelper = SetFeesTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    auto& balanceHelper = testManager->getStorageHelper().getBalanceHelper();

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

    const AssetCode& swapAsset = testSet.swapAsset;
    const uint64_t precision = AssetFrame::getMinimumAmountFromTrailingDigits(
        testSet.trailingDigitsCount);
    const uint64_t preIssuedAmount = INT64_MAX - (INT64_MAX % precision);

    // create asset
    uint64_t assetType = 1;
    issuanceTestHelper.createAssetWithPreIssuedAmount(
        root, swapAsset, preIssuedAmount, root, testSet.trailingDigitsCount,
        assetType);
    manageAssetTestHelper.updateAsset(
        root, swapAsset, root,
        static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
            static_cast<uint32_t>(AssetPolicy::SWAPPABLE) |
            static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));

    // create policy (just entry)
    AccountRuleResource swapResource(LedgerEntryType::SWAP);
    swapResource.swap().assetType = assetType;
    swapResource.swap().assetCode = swapAsset;

    // create policy (just entry)
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = assetType;
    assetResource.asset().assetCode = swapAsset;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, assetResource, AccountRuleAction::ANY, false);
    // write this entry to DB
    auto assetRuleID =
        manageAccountRuleTestHelper
            .applyTx(root, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, swapResource, AccountRuleAction::EXCHANGE, false);
    // write this entry to DB
    auto swapRuleID =
        manageAccountRuleTestHelper
            .applyTx(root, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

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
            {swapRuleID, assetRuleID, sendTxRuleID});

    auto senderAccountRoleID =
        manageAccountRoleTestHelper.applyTx(root, createSenderAccountRoleOp)
            .success()
            .roleID;

    // create account role using root as source
    auto createReceiverAccountRoleOp =
        manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_receiver"})",
            {swapRuleID, assetRuleID, sendTxRuleID});

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

    // create fee charging rules for incoming and outgoing swaps
    auto incomingFee = setFeesTestHelper.createFeeEntry(
        FeeType::SWAP_FEE, swapAsset, 5 * ONE, 0, nullptr, nullptr,
        static_cast<int64_t>(PaymentFeeType::INCOMING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &incomingFee, false);

    auto outgoingFee = setFeesTestHelper.createFeeEntry(
        FeeType::SWAP_FEE, swapAsset, 5 * ONE, 5 * ONE, nullptr, nullptr,
        static_cast<int64_t>(PaymentFeeType::OUTGOING), 0, preIssuedAmount);
    setFeesTestHelper.applySetFeesTx(root, &outgoingFee, false);

    // find payer
    auto payerBalance =
        balanceHelper.loadBalance(payer.key.getPublicKey(), swapAsset);
    REQUIRE(payerBalance);

    int64_t swapAmount = 100 * ONE;
    auto emissionAmount = 3 * swapAmount;

    uint32_t issuanceTasks = 0;

    issuanceTestHelper.applyCreateIssuanceRequest(
        root, swapAsset, emissionAmount, payerBalance->getBalanceID(),
        SecretKey::random().getStrKeyPublic(), &issuanceTasks);

    // create destination and feeData for further tests
    auto destination = openSwapHelper.createDestinationForAccount(
        recipient.key.getPublicKey());

    auto asset = testManager->getStorageHelper().getAssetHelper().loadAsset(
        testSet.swapAsset);

    // maxPaymnetFee more in five times because fee in ETH, swap in USD,
    // exchange rates 1:5
    auto sourceFeeData = openSwapHelper.createFeeData(
        swapAmount, outgoingFee.fixedFee, outgoingFee.percentFee,
        asset->getMinimumAmount());
    auto destFeeData = openSwapHelper.createFeeData(
        swapAmount, incomingFee.fixedFee, incomingFee.percentFee,
        asset->getMinimumAmount());
    auto swapFeeData =
        openSwapHelper.createPaymentFeeData(sourceFeeData, destFeeData, false);

    auto details = "{\"very_important\": \"details\"}";
    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto lockTime = currentTime + 1000;

    auto secret = HashUtils::random();
    auto secretHash = sha256(secret);
    SECTION("Invalid")
    {
        if (testSet.swapAsset == "USD")
        {
            SECTION("Malformed")
            {
                SECTION("Send to self by balance")
                {
                    auto balanceDestination =
                        openSwapHelper.createDestinationForBalance(
                            payerBalance->getBalanceID());
                    openSwapHelper.applyOpenSwapTx(
                        payer, payerBalance->getBalanceID(), balanceDestination,
                        swapAmount, swapFeeData, details, secretHash, lockTime,
                        OpenSwapResultCode::MALFORMED);
                }
                SECTION("Send to self by account")
                {
                    auto accountDestination =
                        openSwapHelper.createDestinationForAccount(
                            payer.key.getPublicKey());
                    openSwapHelper.applyOpenSwapTx(
                        payer, payerBalance->getBalanceID(), accountDestination,
                        swapAmount, swapFeeData, details, secretHash, lockTime,
                        OpenSwapResultCode::MALFORMED);
                }
            }
        }
        if (testSet.swapAsset == "USDN")
        {
            SECTION("Incorrect precision")
            {
                openSwapHelper.applyOpenSwapTx(
                    payer, payerBalance->getBalanceID(), destination,
                    swapAmount - 1, swapFeeData, details, secretHash, lockTime,
                    OpenSwapResultCode::INCORRECT_AMOUNT_PRECISION);
            }
        }
        SECTION("Amount is less than destination fee")
        {
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), destination, 3,
                swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE);
        }
        SECTION("Payer underfunded")
        {
            swapAmount = 4 * swapAmount;
            auto sourceFeeData = openSwapHelper.createFeeData(
                swapAmount, outgoingFee.fixedFee, outgoingFee.percentFee,
                asset->getMinimumAmount());
            auto destFeeData = openSwapHelper.createFeeData(
                swapAmount, incomingFee.fixedFee, incomingFee.percentFee,
                asset->getMinimumAmount());
            auto swapFeeData = openSwapHelper.createPaymentFeeData(
                sourceFeeData, destFeeData, false);

            //
            openSwapHelper.applyOpenSwapTx(payer, payerBalance->getBalanceID(),
                                           destination, swapAmount, swapFeeData,
                                           details, secretHash, lockTime,
                                           OpenSwapResultCode::UNDERFUNDED);
        }
        SECTION("Destination account not found")
        {
            AccountID nonExistingAccount = SecretKey::random().getPublicKey();
            auto accountDestination =
                openSwapHelper.createDestinationForAccount(nonExistingAccount);
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), accountDestination,
                swapAmount, swapFeeData, details, secretHash, lockTime,

                OpenSwapResultCode::MALFORMED, OperationResultCode::opNO_ENTRY);
        }
        SECTION("Assets mismatched")
        {
            auto account = Account{SecretKey::random(), 0};
            createAccountTestHelper.applyCreateAccountTx(
                root, account.key.getPublicKey(), 1);
            auto accountID = account.key.getPublicKey();
            AssetCode someAsset = "EUR";

            auto preissuedSigner = SecretKey::random();
            manageAssetTestHelper.createAsset(root, preissuedSigner, someAsset,
                                              root, 1);
            ManageBalanceTestHelper manageBalanceTestHelper(testManager);
            auto createBalanceResult =
                manageBalanceTestHelper.applyManageBalanceTx(
                    root, accountID, someAsset,
                    ManageBalanceAction::CREATE_UNIQUE);

            auto balanceDestination =
                openSwapHelper.createDestinationForBalance(
                    createBalanceResult.success().balanceID);
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), balanceDestination,
                swapAmount, swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::BALANCE_ASSETS_MISMATCHED);
        }

        SECTION("Destination balance not found")
        {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            auto balanceDestination =
                openSwapHelper.createDestinationForBalance(nonExistingBalance);
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), balanceDestination,
                swapAmount, swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::MALFORMED, OperationResultCode::opNO_ENTRY);
        }
        SECTION("Source balance not found")
        {
            BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
            openSwapHelper.applyOpenSwapTx(
                payer, nonExistingBalance, destination, swapAmount, swapFeeData,
                details, secretHash, lockTime, OpenSwapResultCode::MALFORMED,
                OperationResultCode::opNO_ENTRY);
        }
        SECTION("Not allowed by asset policy")
        {
            manageAssetTestHelper.updateAsset(
                root, swapAsset, root,
                static_cast<uint32_t>(AssetPolicy::BASE_ASSET));
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), destination, swapAmount,
                swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        }

        SECTION("Insufficient fee amount")
        {
            swapFeeData.sourceFee.fixed =
                static_cast<uint64>(outgoingFee.fixedFee - 1);
            swapFeeData.sourceFee.percent =
                static_cast<uint64>(outgoingFee.percentFee - 1);
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), destination, swapAmount,
                swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT);
        }
        SECTION("Dest fee amount overflows UINT64_MAX")
        {
            swapFeeData.destinationFee.fixed = UINT64_MAX;
            swapFeeData.destinationFee.percent = 1;
            openSwapHelper.applyOpenSwapTx(
                payer, payerBalance->getBalanceID(), destination, swapAmount,
                swapFeeData, details, secretHash, lockTime,
                OpenSwapResultCode::INVALID_DESTINATION_FEE);
        }

        SECTION("Invalid details")
        {
            swapFeeData.destinationFee.fixed = UINT64_MAX;
            swapFeeData.destinationFee.percent = 1;
            auto invalidDetails = "{\"very_important\": \"details\"";

            openSwapHelper.applyOpenSwapTx(payer, payerBalance->getBalanceID(),
                                           destination, swapAmount, swapFeeData,
                                           invalidDetails, secretHash, lockTime,
                                           OpenSwapResultCode::INVALID_DETAILS);
        }
    }

    SECTION("Valid swap")
    {

        auto result = openSwapHelper.applyOpenSwapTx(
            payer, payerBalance->getBalanceID(), destination, swapAmount,
            swapFeeData, details, secretHash, lockTime);

        auto swapID = result.success().swapID;

        SECTION("Try cancel too early")
        {
            closeSwapHelper.applyCloseSwapTx(
                payer, swapID, nullptr, nullptr,
                CloseSwapResultCode::NOT_AUTHORIZED);
        }

        SECTION("Try close with wrong secret")
        {
            auto wrongSecret = HashUtils::random();
            closeSwapHelper.applyCloseSwapTx(
                recipient, swapID, &wrongSecret, nullptr,
                CloseSwapResultCode::INVALID_SECRET);
        }

        SECTION("Try close too late")
        {
            testManager->advanceToTime(lockTime + 10);
            closeSwapHelper.applyCloseSwapTx(recipient, swapID, &secret,
                                             nullptr,
                                             CloseSwapResultCode::SWAP_EXPIRED);
        }

        SECTION("Try cancel by admin too early")
        {
            // admin is allowed to cancel swap on swap expiration
            closeSwapHelper.applyCloseSwapTx(
                root, swapID, nullptr, nullptr,
                CloseSwapResultCode::NOT_AUTHORIZED);
        }

        SECTION("Close")
        {

            SECTION("Payer cancel")
            {
                testManager->advanceToTime(lockTime + 10);
                closeSwapHelper.applyCloseSwapTx(payer, swapID, nullptr,
                                                 nullptr);
            }

            SECTION("Admin cancel")
            {
                testManager->advanceToTime(lockTime + 10);
                closeSwapHelper.applyCloseSwapTx(root, swapID, nullptr,
                                                 nullptr);
            }

            SECTION("Receiver close")
            {
                closeSwapHelper.applyCloseSwapTx(recipient, swapID, &secret,
                                                 nullptr);
            }
        }
    }
}