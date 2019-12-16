#include "test_helper/ManageAccountRoleTestHelper.h"
#include "test_helper/ManageAccountRuleTestHelper.h"
#include "test_helper/ManageRedemptionTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ReviewWithdrawalRequestHelper.h"
#include "test_helper/ReviewRedemptionRequestTestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "TxTests.h"
#include "test/test.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Redemption", "[tx][redemption]") {
    struct TestSet {
        const AssetCode paymentAsset;
        const int trailingDigitsCount;
    };
    const TestSet testSet = GENERATE(TestSet{"USD", AssetFrame::kMaximumTrailingDigits});

    Config const &cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application &app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database &db = testManager->getDB();

    auto root = Account{getRoot(), Salt(0)};

    // helpers
    ManageRedemptionTestHelper redemptionHelper(testManager);
    ReviewRedemptionRequestTestHelper reviewRedemptionHelper(testManager);
    ManageAssetTestHelper manageAssetTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);
    IssuanceRequestHelper issuanceTestHelper(testManager);

    auto &balanceHelper = testManager->getStorageHelper().getBalanceHelper();
    auto& requestHelper = testManager->getStorageHelper().getReviewableRequestHelper();

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

    const AssetCode &redemptionAsset = testSet.paymentAsset;
    const uint64_t preIssuedAmount = 10000 * ONE;

    // create asset
    uint64_t assetType = 1;
    issuanceTestHelper.createAssetWithPreIssuedAmount(root, redemptionAsset, preIssuedAmount, root,
                                                      testSet.trailingDigitsCount, assetType);
    manageAssetTestHelper.updateAsset(root, redemptionAsset, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
                                                                   static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
                                                                   static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));


    // create policy (just entry)
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = assetType;
    assetResource.asset().assetCode = redemptionAsset;

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

    auto payer = Account{SecretKey::random(), Salt(1)};
    auto recipient = Account{SecretKey::random(), Salt(1)};

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

    uint32_t allTasks = 1;
    uint32_t zeroTasks = 0;

    SECTION("empty reason is not allowed") {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 0, "", "", &allTasks,
                                               CreateRedemptionRequestResultCode::INVALID_CREATOR_DETAILS);
    }
    SECTION("zero amount is not allowed") {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 0, "Inalid", "", &allTasks,
                                               CreateRedemptionRequestResultCode::INVALID_AMOUNT);
    }
    SECTION("src balance does not exist") {
        BalanceID srcBalanceID;
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalanceID, dstAccountID, 10, "Inalid", "", &allTasks,
                                               CreateRedemptionRequestResultCode::SOURCE_BALANCE_NOT_EXIST,
                                               OperationResultCode::opNO_ENTRY);
    }
    auto srcBalance = balanceHelper.loadBalance(payer.key.getPublicKey(), redemptionAsset);
    SECTION("dst account does not exist") {
        AccountID dstAccountID;
        redemptionHelper.applyCreateRedemption(root, srcBalance->getBalanceID(), dstAccountID, 10, "Inalid", "",
                                               &allTasks, CreateRedemptionRequestResultCode::DST_ACCOUNT_NOT_FOUND,
                                               OperationResultCode::opNO_ENTRY);
    }

    auto reference = "Random reference";
    SECTION("Given valid accounts with balances") {
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
        srcBalance = balanceHelper.loadBalance(payer.key.getPublicKey(), redemptionAsset);
        REQUIRE(!!srcBalance);

        uint32_t issuanceTasks = 0;
        issuanceTestHelper.applyCreateIssuanceRequest(root, redemptionAsset, preIssuedAmount,
                                                      srcBalance->getBalanceID(),
                                                      "RANDOM ISSUANCE REFERENCE AWARWAWRWARAWR", &issuanceTasks);
        SECTION("zero tasks not allowed") {
            redemptionHelper.applyCreateRedemption(root, srcBalance->getBalanceID(), recipient.key.getPublicKey(),
                                                   preIssuedAmount - 10, "because", reference, &zeroTasks,
                                                   CreateRedemptionRequestResultCode::REDEMPTION_ZERO_TASKS_NOT_ALLOWED);
        }
        SECTION("Underfunded") {
            REQUIRE(srcBalance->getAmount() == 0);
            redemptionHelper.applyCreateRedemption(root, srcBalance->getBalanceID(), recipient.key.getPublicKey(),
                                                   preIssuedAmount + 10, "because", reference, &allTasks,
                                                   CreateRedemptionRequestResultCode::UNDERFUNDED);
        }
        SECTION("Mismatching balance precision and amount") {
            manageAssetTestHelper.changeAssetTrailingDigits(redemptionAsset, 0);
            redemptionHelper.applyCreateRedemption(root, srcBalance->getBalanceID(), recipient.key.getPublicKey(),
                                                   preIssuedAmount - 10, "just because", reference, &allTasks,
                                                   CreateRedemptionRequestResultCode::INCORRECT_PRECISION);
        }
        SECTION("create and approve request")
        {
            auto result = redemptionHelper.applyCreateRedemption(root, srcBalance->getBalanceID(),
                                                                 recipient.key.getPublicKey(),
                                                                 preIssuedAmount / 2, "because i can", reference, &allTasks,
                                                                 CreateRedemptionRequestResultCode::SUCCESS);
            SECTION("OK but not fulfilled because only admin can fulfill")
            {
                REQUIRE(!result.redemptionResponse().fulfilled);
            }

            SECTION("approve & fulfill request")
            {
                auto request = requestHelper.loadRequest(result.redemptionResponse().requestID);
                REQUIRE(request->getReviewer() == app.getAdminID());
                uint32_t tasksToRemove = 1;
                auto reviewResult = reviewRedemptionHelper.applyReviewRequestTxWithTasks(root,
                        request->getRequestID(), ReviewRequestOpAction::APPROVE, "",
                        ReviewRequestResultCode::SUCCESS, &zeroTasks, &tasksToRemove);
                REQUIRE(reviewResult.success().fulfilled);
            }
        }

    }
}