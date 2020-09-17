#include "TxTests.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test.h"
#include "test/test_marshaler.h"
#include "test_helper/CancelCloseDeferredPaymentRequestHelper.h"
#include "test_helper/CancelCreateDeferredPaymentRequestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/CreateCloseDeferredPaymentRequestTestHelper.h"
#include "test_helper/CreateDeferredPaymentCreationRequestTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageAccountRoleTestHelper.h"
#include "test_helper/ManageAccountRuleTestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/ReviewCloseDeferredPaymentRequestHelper.h"
#include "test_helper/ReviewCreateDeferredPaymentRequestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("DeferredPayment", "[tx][deferred_payment]")
{
    struct TestSet
    {
        const AssetCode paymentAsset;
        const int trailingDigitsCount;
    };
    const TestSet testSet =
        GENERATE(TestSet{"USD", AssetFrame::kMaximumTrailingDigits});

    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();

    auto root = Account{getRoot(), Salt(0)};

    // helpers
    CreateDeferredPaymentCreationTestHelper
        createDeferredPaymentCreationTestHelper(testManager);
    CreateCloseDeferredPaymentTestHelper createCloseDeferredPaymentTestHelper(
        testManager);
    ReviewCreateDeferredPaymentRequestTestHelper
        reviewCreateDeferredPaymentHelper(testManager);
    ReviewCloseDeferredPaymentRequestTestHelper
        reviewCloseDeferredPaymentHelper(testManager);
    ManageAssetTestHelper manageAssetTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);
    IssuanceRequestHelper issuanceTestHelper(testManager);
    CancelCloseDeferredPaymentRequestHelper
        cancelCloseDeferredPaymentRequestHelper(testManager);
    CancelCreateDeferredPaymentRequestHelper
        cancelCreateDeferredPaymentRequestHelper(testManager);

    auto& balanceHelper = testManager->getStorageHelper().getBalanceHelper();
    auto& requestHelper =
        testManager->getStorageHelper().getReviewableRequestHelper();

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

    auto payer = Account{SecretKey::random(), Salt(1)};
    auto recipient = Account{SecretKey::random(), Salt(1)};

    createAccountTestHelper.applyTx(
        CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(payer.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(1));

    createAccountTestHelper.applyTx(
        CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(recipient.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(1));

    const AssetCode& deferredPaymentAsset = testSet.paymentAsset;
    const uint64_t preIssuedAmount = 10000 * ONE;

    // create asset
    uint64_t assetType = 1;
    issuanceTestHelper.createAssetWithPreIssuedAmount(
        root, deferredPaymentAsset, preIssuedAmount, root,
        testSet.trailingDigitsCount, assetType);
    manageAssetTestHelper.updateAsset(
        root, deferredPaymentAsset, root,
        static_cast<uint32_t>(AssetPolicy::BASE_ASSET) |
            static_cast<uint32_t>(AssetPolicy::TRANSFERABLE) |
            static_cast<uint32_t>(AssetPolicy::STATS_QUOTE_ASSET));

    uint32_t zeroTasks = 0;
    uint32_t allTasks = 1;

    AccountID sourceAccountID = payer.key.getPublicKey();
    AccountID destAccountID = recipient.key.getPublicKey();

    auto sourceBalance =
        manageBalanceTestHelper
            .applyManageBalanceTx(root, sourceAccountID, testSet.paymentAsset,
                                  ManageBalanceAction::CREATE)
            .success()
            .balanceID;

    issuanceTestHelper.applyCreateIssuanceRequest(
        root, testSet.paymentAsset, 10 * ONE, sourceBalance,
        "deferred_pmnt_test", nullptr);
    auto destBalance =
        manageBalanceTestHelper
            .applyManageBalanceTx(root, destAccountID, testSet.paymentAsset,
                                  ManageBalanceAction::CREATE)
            .success()
            .balanceID;

    CreateDeferredPaymentRequest request;
    request.amount = 1000;
    request.creatorDetails = R"({"test": "a"})";
    request.sourceBalance = sourceBalance;
    request.destination = destAccountID;

    SECTION("empty reason is not allowed")
    {
        request.creatorDetails = R"({"test": "a")";
        createDeferredPaymentCreationTestHelper
            .applyCreateDeferredPaymentCreationRequest(
                payer, request, 0, &allTasks, OperationResultCode::opINNER,
                CreateDeferredPaymentCreationRequestResultCode::
                    INVALID_CREATOR_DETAILS);
    }
    SECTION("zero amount is not allowed")
    {
        request.amount = 0;
        createDeferredPaymentCreationTestHelper
            .applyCreateDeferredPaymentCreationRequest(
                payer, request, 0, &allTasks, OperationResultCode::opINNER,
                CreateDeferredPaymentCreationRequestResultCode::INVALID_AMOUNT);
    }

    SECTION("destination not found")
    {
        auto dest = Account{SecretKey::random(), Salt(1)};

        request.destination = dest.key.getPublicKey();
        createDeferredPaymentCreationTestHelper
            .applyCreateDeferredPaymentCreationRequest(
                payer, request, 0, &allTasks, OperationResultCode::opNO_ENTRY);
    }

    SECTION("underfunded")
    {
        auto dest = Account{SecretKey::random(), Salt(1)};

        request.amount = 12 * ONE;
        createDeferredPaymentCreationTestHelper
            .applyCreateDeferredPaymentCreationRequest(
                payer, request, 0, &allTasks, OperationResultCode::opINNER,
                CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED);
    }

    SECTION("Success")
    {
        auto result = createDeferredPaymentCreationTestHelper
                          .applyCreateDeferredPaymentCreationRequest(
                              payer, request, 0, &zeroTasks,
                              OperationResultCode::opINNER);
        REQUIRE(result.success().fulfilled);

        SECTION("Close")
        {
            CloseDeferredPaymentRequest closeDeferredPaymentRequest;
            closeDeferredPaymentRequest.creatorDetails = R"({"test": "ab"})";
            closeDeferredPaymentRequest.destinationBalance = destBalance;
            closeDeferredPaymentRequest.deferredPaymentID =
                result.success().deferredPaymentID;
            closeDeferredPaymentRequest.amount = 500;

            createCloseDeferredPaymentTestHelper
                .applyCreateCloseDeferredPaymentRequest(
                    recipient, closeDeferredPaymentRequest, 0, &allTasks);
        }

        SECTION("create Close & cancel")
        {
            CloseDeferredPaymentRequest closeDeferredPaymentRequest;
            closeDeferredPaymentRequest.creatorDetails = R"({"test": "ab"})";
            closeDeferredPaymentRequest.destinationBalance = destBalance;
            closeDeferredPaymentRequest.deferredPaymentID =
                result.success().deferredPaymentID;
            closeDeferredPaymentRequest.amount = 500;

            auto createCloseRes =
                createCloseDeferredPaymentTestHelper
                    .applyCreateCloseDeferredPaymentRequest(
                        recipient, closeDeferredPaymentRequest, 0, &allTasks);

            cancelCloseDeferredPaymentRequestHelper
                .applyCancelCloseDeferredPaymentRequest(
                    recipient, createCloseRes.success().requestID);
        }
    }

    SECTION("Create & cancel")
    {
        auto result =
            createDeferredPaymentCreationTestHelper
                .applyCreateDeferredPaymentCreationRequest(
                    payer, request, 0, &allTasks, OperationResultCode::opINNER);
        REQUIRE_FALSE(result.success().fulfilled);

        cancelCreateDeferredPaymentRequestHelper
            .applyCancelCreateDeferredPaymentRequest(
                payer, result.success().requestID);
    }
}