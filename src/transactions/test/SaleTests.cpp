#include <ledger/OfferHelper.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/FeesManager.h>
#include <ledger/FeeHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "ledger/AssetHelperLegacy.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/ReviewableRequestHelper.h"
#include "main/test.h"
#include "TxTests.h"
#include "crypto/SHA.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "ledger/BalanceHelperLegacy.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/SaleRequestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "test_helper/ManageSaleTestHelper.h"
#include "test_helper/ParticipateInSaleTestHelper.h"
#include "transactions/dex/OfferManager.h"
#include "ledger/SaleHelper.h"
#include "test_helper/CheckSaleStateTestHelper.h"
#include "test_helper/ReviewAssetRequestHelper.h"
#include "test_helper/ReviewSaleRequestHelper.h"
#include "test_helper/ReviewUpdateSaleDetailsRequestHelper.h"
#include "test_helper/SetFeesTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/ManageAssetPairTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("Sale in several quote assets", "[tx][sale_several_quote]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();

    auto root = Account{ getRoot(), Salt(0) };

    uint32_t zeroTasks = 0;

    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);
    ParticipateInSaleTestHelper participationHelper(testManager);
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

    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueHelper.setKey(saleCreateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring saleUpdateKey = ManageKeyValueOpFrame::makeSaleUpdateTasksKey("*");
    manageKeyValueHelper.setKey(saleUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    AssetCode defaultQuoteAsset = "USD";
    uint64_t quoteMaxIssuance = INT64_MAX;
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    auto assetCreationRequest = assetTestHelper.createAssetCreationRequest(defaultQuoteAsset, root.key.getPublicKey(), "{}", 0,
        uint32_t(AssetPolicy::BASE_ASSET));
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    AssetCode quoteAssetBTC = "BTC";
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAssetBTC, root.key.getPublicKey(), "{}", quoteMaxIssuance,
        uint32_t(AssetPolicy::BASE_ASSET));
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    AssetCode quoteAssetETH = "ETH";
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAssetETH, root.key.getPublicKey(), "{}", quoteMaxIssuance,
        uint32_t(AssetPolicy::BASE_ASSET));
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    uint64_t btcUSDPrice = 10000 * ONE;
    assetPairHelper.applyManageAssetPairTx(root, quoteAssetBTC, defaultQuoteAsset, btcUSDPrice, 0, 0);
    uint64_t ethUSDPrice = 500 * ONE;
    assetPairHelper.applyManageAssetPairTx(root, quoteAssetETH, defaultQuoteAsset, ethUSDPrice, 0, 0);

    auto syndicate = Account{ SecretKey::random(), 0 };
    auto syndicatePubKey = syndicate.key.getPublicKey();

    CreateAccountTestHelper(testManager).applyCreateAccountTx(root, syndicatePubKey, AccountType::SYNDICATE);
    const AssetCode baseAsset = "XAAU";
    const uint64_t maxIssuanceAmount = 2000 * ONE;
    const uint64_t preIssuedAmount = maxIssuanceAmount;
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(baseAsset, syndicate.key.getPublicKey(), "{}",
                                                                      maxIssuanceAmount, 0,
                                                                      nullptr,
                                                                      preIssuedAmount);
    assetTestHelper.createApproveRequest(root, syndicate, assetCreationRequest);

    uint64_t hardCap = 100000000 * ONE;
    uint64 softCap = 50000000 * ONE;

    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    uint64_t xaauUSDPrice = (hardCap / maxIssuanceAmount) * ONE;
    uint64_t xaauBTCPrice = (xaauUSDPrice / btcUSDPrice) * ONE;
    uint64_t xaauETHPrice = (xaauUSDPrice / ethUSDPrice) * ONE;
    auto saleRequest = SaleRequestHelper::createSaleRequest(baseAsset, defaultQuoteAsset, currentTime,
                                                            endTime, softCap, hardCap, "{}",
                                                            {saleRequestHelper.createSaleQuoteAsset(quoteAssetBTC,
                                                                                                        xaauBTCPrice),
                                                                 saleRequestHelper.createSaleQuoteAsset(quoteAssetETH,
                                                                                                        xaauETHPrice)},
                                                            maxIssuanceAmount);

    auto saleCreateResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
    REQUIRE(saleCreateResult.success().fulfilled);
    const uint64_t saleID = saleCreateResult.success().saleID;

    SECTION("Happy path")
    {
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(maxIssuanceAmount/2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(maxIssuanceAmount/2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);
        CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);
    }
    SECTION("Happy path with different precisions")
    {
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(baseAsset, 2);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetBTC, 1);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetETH, 0);

        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(maxIssuanceAmount/2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(maxIssuanceAmount/2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

        CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);
    }
}

TEST_CASE("Sale creation while base asset is on review", "[tx][sale]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);
    ParticipateInSaleTestHelper participationHelper(testManager);
    ManageAssetTestHelper assetTestHelper(testManager);
    ManageSaleTestHelper manageSaleHelper(testManager);
    ReviewSaleRequestHelper saleReviewer(testManager);
    ReviewAssetRequestHelper assetReviewer(testManager);

    auto root = Account{ getRoot(), Salt(0) };
    AssetCode defaultQuoteAsset = "USD";
    uint64_t quoteMaxIssuance = INT64_MAX;

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

    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueHelper.setKey(saleCreateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring saleUpdateKey = ManageKeyValueOpFrame::makeSaleUpdateTasksKey("*");
    manageKeyValueHelper.setKey(saleUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    auto assetCreationRequest = assetTestHelper.createAssetCreationRequest(defaultQuoteAsset, root.key.getPublicKey(), "{}", 0,
                                                                           uint32_t(AssetPolicy::BASE_ASSET), nullptr);
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    AssetCode quoteAssetBTC = "BTC";
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAssetBTC, root.key.getPublicKey(), "{}", quoteMaxIssuance,
                                                                      uint32_t(AssetPolicy::BASE_ASSET), nullptr);
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    AssetCode quoteAssetETH = "ETH";
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAssetETH, root.key.getPublicKey(), "{}", quoteMaxIssuance,
                                                                      uint32_t(AssetPolicy::BASE_ASSET), nullptr);
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    uint64_t btcUSDPrice = 10 * ONE;
    assetPairHelper.applyManageAssetPairTx(root, quoteAssetBTC, defaultQuoteAsset, btcUSDPrice, 0, 0);
    uint64_t ethUSDPrice = 5 * ONE;
    assetPairHelper.applyManageAssetPairTx(root, quoteAssetETH, defaultQuoteAsset, ethUSDPrice, 0, 0);

    AssetCode baseAsset = "UAH";
    uint64_t baseType = 1;
    uint64_t saleTypeInt = 1;

    // create syndicate role
    AccountRuleResource baseAssetResource(LedgerEntryType::ASSET);
    baseAssetResource.asset().assetType = baseType;
    baseAssetResource.asset().assetCode = baseAsset;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            baseAssetResource, "*", false);
    auto baseAssetOwnerRuleID = manageAccountRuleTestHelper.applyTx(root,
            ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource saleResource(LedgerEntryType::REVIEWABLE_REQUEST);
    saleResource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);
    saleResource.reviewableRequest().details.sale().type = saleTypeInt;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            saleResource, "create", false);
    auto saleCreatorRuleID = manageAccountRuleTestHelper.applyTx(root,
            ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            "{}", {baseAssetOwnerRuleID, saleCreatorRuleID});
    auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root,
            createSyndicateRoleOp).success().roleID;

    // basic account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setRecovery(SecretKey::random().getPublicKey());

    auto syndicate = Account{ SecretKey::random(), 0 };
    auto syndicatePubKey = syndicate.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                            .setToPublicKey(syndicatePubKey)
                                            .setRoleID(1));

    const uint64_t maxIssuanceAmount = 2000 * ONE;
    const uint64_t preIssuedAmount = maxIssuanceAmount;
    uint64_t hardCap = 20000 * ONE;
    uint64 softCap = 10000 * ONE;

    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    uint64_t xaauUSDPrice;
    uint64_t xaauBTCPrice;
    uint64_t xaauETHPrice;
    bigDivide(xaauUSDPrice, hardCap, ONE, maxIssuanceAmount, ROUND_UP);
    bigDivide(xaauBTCPrice, xaauUSDPrice, ONE, btcUSDPrice, ROUND_UP);
    bigDivide(xaauETHPrice, xaauUSDPrice, ONE, ethUSDPrice, ROUND_UP);

    uint32_t assetTasks = 1, zeroTasks = 0;
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(baseAsset,
            syndicate.key.getPublicKey(), "{}", maxIssuanceAmount, 0, &assetTasks,
          preIssuedAmount, 6, baseType);
    auto assetResult = assetTestHelper.applyManageAssetTx(syndicate, 0, assetCreationRequest);
    auto saleType = SaleType::FIXED_PRICE;
    auto saleRequest = SaleRequestHelper::createSaleRequest(baseAsset, defaultQuoteAsset,
            currentTime, endTime, softCap, hardCap, "{}",
            { saleRequestHelper.createSaleQuoteAsset(quoteAssetBTC, xaauBTCPrice),
              saleRequestHelper.createSaleQuoteAsset(quoteAssetETH, xaauETHPrice) },
            maxIssuanceAmount, saleType, saleTypeInt);

    auto saleCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
    auto request = ReviewableRequestHelper::Instance()->
            loadRequest(assetResult.success().requestID,
                        testManager->getDB(), nullptr);
    REQUIRE(request);
    auto reviewResult = assetReviewer.applyReviewRequestTxWithTasks(root, request->
                                                                                       getRequestID(),
                                                                               request->getHash(),
                                                                               request->getRequestType(),
                                                                               ReviewRequestOpAction::
                                                                               APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                                               &zeroTasks,
                                                                               &assetTasks);

    auto requestID = saleCreationResult.success().requestID;
    auto saleReviewResult = saleReviewer.applyReviewRequestTx(root, requestID,
                                                 ReviewRequestOpAction::APPROVE, "");
    const auto saleID = saleReviewResult.success().typeExt.saleExtended().saleID;

    SECTION("Happy path")
    {
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(maxIssuanceAmount/2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(maxIssuanceAmount/2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }
    SECTION("Happy path with different precisions")
    {
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(baseAsset, 0);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetBTC, 1);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetETH, 2);

        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(maxIssuanceAmount/2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(maxIssuanceAmount/2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }
}

TEST_CASE("Sale", "[tx][sale]")
{
    struct TestSet
    {
        const AssetCode quoteAsset;
        const AssetCode baseAsset;
        const int trailingDigitsCount;
    };
    const TestSet testSet = GENERATE(
            TestSet { "USD", "BTC", AssetFrame::kMaximumTrailingDigits },
            TestSet { "USDN", "BTCN", 0 } );

    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    Database& db = testManager->getDB();

    auto root = Account{ getRoot(), Salt(0) };

    const AssetCode& baseAsset = testSet.baseAsset;
    uint64_t  baseType = 1;
    const AssetCode& quoteAsset = testSet.quoteAsset;
    uint64_t quoteType = 2;
    const uint64_t precision = AssetFrame::getMinimumAmountFromTrailingDigits(testSet.trailingDigitsCount);
    const uint64_t maxNonDividedAmount = INT64_MAX - (INT64_MAX % precision);

    uint32_t zeroTasks = 0;

    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);
    ManageSaleTestHelper manageSaleTestHelper(testManager);
    ReviewUpdateSaleDetailsRequestTestHelper reviewUpdateSaleDetailsRequestTestHelper(testManager);
    CreateAccountTestHelper accountTestHelper(testManager);
    SetFeesTestHelper setFeesTestHelper(testManager);
    auto saleReviewer = ReviewSaleRequestHelper(testManager);
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    ParticipateInSaleTestHelper participationHelper(testManager);
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

    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueHelper.setKey(saleCreateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring saleUpdateKey = ManageKeyValueOpFrame::makeSaleUpdateTasksKey("*");
    manageKeyValueHelper.setKey(saleUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    auto assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAsset, root.key.getPublicKey(), "{}", maxNonDividedAmount,
                                                                           uint32_t(AssetPolicy::BASE_ASSET), nullptr, 0, testSet.trailingDigitsCount);
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    // create syndicate role
    AccountRuleResource baseAssetResource(LedgerEntryType::ASSET);
    baseAssetResource.asset().assetType = baseType;
    baseAssetResource.asset().assetCode = baseAsset;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            baseAssetResource, "*", false);
    auto baseAssetOwnerRuleID = manageAccountRuleTestHelper.applyTx(root,
            ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            "{}", {baseAssetOwnerRuleID});
    auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root,
            createSyndicateRoleOp).success().roleID;

    // basic account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setRecovery(SecretKey::random().getPublicKey());

    auto syndicate = Account{ SecretKey::random(), 0 };
    auto syndicatePubKey = syndicate.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                            .setToPublicKey(syndicatePubKey)
                                            .setRoleID(1));
    // TODO: for now we need to keep maxIssuance = preIssuance to allow sale creation
    const uint64_t maxIssuanceAmount = 6000 * ONE;
    const uint64_t preIssuedAmount = maxIssuanceAmount;
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(baseAsset,
            syndicate.key.getPublicKey(), "{}", maxIssuanceAmount, 0, nullptr,
            preIssuedAmount, testSet.trailingDigitsCount);
    assetTestHelper.createApproveRequest(root, syndicate, assetCreationRequest);
    const uint64_t price = 2 * ONE;
    auto hardCap = static_cast<const uint64_t>(bigDivide(preIssuedAmount / 2, price, ONE, ROUND_DOWN));
    uint64_t softCap = hardCap / 2;
    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    const auto requiredBaseAssetForHardCap = (hardCap / price) * ONE;
    auto saleRequest = SaleRequestHelper::createSaleRequest(baseAsset, quoteAsset, currentTime,
                                                            endTime, softCap, hardCap, "{}",
                                                            {saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
                                                            requiredBaseAssetForHardCap);

    uint32_t issuanceTasks = 0;
    SECTION("Create sale request with tasks and cancel")
    {
        uint32_t allTasks = 1;
        auto result = saleRequestHelper.applyCreateSaleRequest(syndicate, 0,
                                                               saleRequest, &allTasks);
        auto requestID = result.success().requestID;

        SECTION("Success cancel sale request")
        {
            saleRequestHelper.applyCancelSaleRequest(syndicate, requestID);

            SECTION("Already canceled")
            {
                saleRequestHelper.applyCancelSaleRequest(syndicate, requestID,
                      CancelSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
            }
        }

        auto newSyndicate = Account{ SecretKey::random(), 0 };
        auto newSyndicatePubKey = newSyndicate.key.getPublicKey();

        auto createAccountTestBuilder = CreateAccountTestBuilder()
                .setSource(root)
                .setToPublicKey(newSyndicatePubKey)
                .setType(AccountType::SYNDICATE)
                .setRecovery(SecretKey::random().getPublicKey());

        auto createAccountHelper = CreateAccountTestHelper(testManager);
        createAccountHelper.applyTx(createAccountTestBuilder);

        SECTION("Other user cannot cancel request")
        {
            saleRequestHelper.applyCancelSaleRequest(newSyndicate, requestID,
                CancelSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
        }

        SECTION("Request id cannot be zero")
        {
            saleRequestHelper.applyCancelSaleRequest(newSyndicate, 0,
                CancelSaleCreationRequestResultCode::REQUEST_ID_INVALID);
        }
    }

    SECTION("Non zero balance on sale close"){
        auto sellerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, int64_t(2 * ONE), quoteAsset, &syndicatePubKey, precision);
        auto participantsFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, int64_t(1 * ONE), quoteAsset, nullptr, precision);
        LedgerDeltaImpl delta(testManager->getLedgerManager().getCurrentLedgerHeader(), db);
        EntryHelperProvider::storeAddEntry(delta, db, sellerFeeFrame->mEntry);
        EntryHelperProvider::storeAddEntry(delta, db, participantsFeeFrame->mEntry);

        uint64_t quotePreIssued(0);
        participantsFeeFrame->calculatePercentFee(hardCap, quotePreIssued, ROUND_UP, 1);
        quotePreIssued += hardCap + ONE;
        IssuanceRequestHelper(testManager).authorizePreIssuedAmount(root, root.key, quoteAsset, quotePreIssued, root);

        saleRequestHelper.createApprovedSale(root, syndicate, saleRequest);

        auto sales = SaleHelper::Instance()->loadSalesForOwner(syndicate.key.getPublicKey(), testManager->getDB());
        REQUIRE(sales.size() == 1);
        const auto saleID = sales[0]->getID();


        auto ownBalance = BalanceHelperLegacy::Instance()->loadBalance(syndicatePubKey, baseAsset, testManager->getDB(),
                                                                 nullptr);
        IssuanceRequestHelper(testManager).applyCreateIssuanceRequest(syndicate, baseAsset, 10*ONE, ownBalance->getBalanceID(),
                                                                      syndicate.key.getStrKeyPublic(), &issuanceTasks,
                                                                      CreateIssuanceRequestResultCode::SUCCESS);

        const int numberOfParticipants = 10;
        const uint64_t quoteAmount = softCap / numberOfParticipants;
        uint64_t feeToPay(0);
        participantsFeeFrame->calculatePercentFee(quoteAmount, feeToPay, ROUND_UP, 1);
        const int64_t timeStep = (endTime - currentTime) / numberOfParticipants;
        for (int i = 0; i < numberOfParticipants - 1; i++)
        {
            participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAmount, price, feeToPay);
            testManager->advanceToTime(testManager->getLedgerManager().getCloseTime() + timeStep);
            checkStateHelper.applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
        }

        participantsFeeFrame->calculatePercentFee(quoteAmount, feeToPay, ROUND_UP, 1);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAmount, price, feeToPay);
        testManager->advanceToTime(endTime + 1);
        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }

    SECTION("Simple happy path for test fee")
    {
        auto fee = setFeesTestHelper.createFeeEntry(FeeType::INVEST_FEE, quoteAsset, 0, 1 * ONE,
                nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);
        fee = setFeesTestHelper.createFeeEntry(FeeType::OFFER_FEE, quoteAsset, 0, 1 * ONE,
                                               nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);
        fee = setFeesTestHelper.createFeeEntry(FeeType::CAPITAL_DEPLOYMENT_FEE, quoteAsset, 0, 1 * ONE,
                                               nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);

        saleRequest.hardCap = 200 * ONE;
        saleRequest.softCap = 100 * ONE;

        auto syndicateAccountFrame = std::make_shared<AccountFrame>(syndicatePubKey);
        auto syndicateFee = FeeHelper::Instance()->loadForAccount(FeeType::CAPITAL_DEPLOYMENT_FEE,
                quoteAsset, FeeFrame::SUBTYPE_ANY, syndicateAccountFrame, saleRequest.hardCap, db);
        uint64_t feeToPayBySyndicate = 0;
        REQUIRE(syndicateFee->calculatePercentFee(saleRequest.hardCap, feeToPayBySyndicate, ROUND_UP, 1));

        uint64_t feeToPay(2 * ONE);
        auto result = saleRequestHelper.createApprovedSale(root, syndicate, saleRequest);
        auto saleID = result.success().typeExt.saleExtended().saleID;
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, saleRequest.hardCap, price, feeToPay);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);

        auto commissionBalance = BalanceHelperLegacy::Instance()->loadBalance(app.getAdminID(),  quoteAsset, db, nullptr);
        REQUIRE(!!commissionBalance);
        REQUIRE(commissionBalance->getAmount() == feeToPay + feeToPayBySyndicate);
    }

    SECTION("Happy path")
    {
        //set offer fee for sale owner and participants
        // TODO: use set fees
        auto sellerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, int64_t(2 * ONE), quoteAsset, &syndicatePubKey, precision);
        auto participantsFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, int64_t(1 * ONE), quoteAsset, nullptr, precision);
        LedgerDeltaImpl delta(testManager->getLedgerManager().getCurrentLedgerHeader(), db);
        EntryHelperProvider::storeAddEntry(delta, db, sellerFeeFrame->mEntry);
        EntryHelperProvider::storeAddEntry(delta, db, participantsFeeFrame->mEntry);
        auto fee = setFeesTestHelper.createFeeEntry(FeeType::CAPITAL_DEPLOYMENT_FEE, quoteAsset, 0, 1 * ONE,
                nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);

        uint64_t quotePreIssued(0);
        participantsFeeFrame->calculatePercentFee(hardCap, quotePreIssued, ROUND_UP, 1);
        quotePreIssued += hardCap + ONE;
        IssuanceRequestHelper(testManager).authorizePreIssuedAmount(root, root.key, quoteAsset, quotePreIssued, root);

        saleRequestHelper.createApprovedSale(root, syndicate, saleRequest);

        auto sales = SaleHelper::Instance()->loadSalesForOwner(syndicate.key.getPublicKey(), testManager->getDB());
        REQUIRE(sales.size() == 1);
        const auto saleID = sales[0]->getID();
        SECTION("Create second sale for the same base asset and close both") {
            //autoreview
            auto createSecondSaleRequestResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            sales = SaleHelper::Instance()->loadSalesForOwner(syndicate.key.getPublicKey(), testManager->getDB());
            REQUIRE(sales.size() == 2);

            const uint64_t secondSaleID = sales[1]->getID();

            IssuanceRequestHelper(testManager).authorizePreIssuedAmount(root, root.key, quoteAsset, quotePreIssued, root);

            const int numberOfParticipants = 10;
            const auto quoteAssetAmount = hardCap / numberOfParticipants;
            uint64_t feeToPay(0);
            participantsFeeFrame->calculatePercentFee(quoteAssetAmount, feeToPay, ROUND_UP, 1);

            // first sale reached hard cap
            for (auto i = 0; i < numberOfParticipants; i++)
            {
                participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAssetAmount, price, feeToPay);
                if (i < numberOfParticipants - 1)
                {
                    CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
                }
            }

            CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);

            // second sale reached hard cap
            for (auto i = 0; i < numberOfParticipants; i++)
            {
                participationHelper.addNewParticipant(root, secondSaleID, baseAsset, quoteAsset, quoteAssetAmount, price, feeToPay);
                if (i < numberOfParticipants - 1)
                {
                    CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, secondSaleID, CheckSaleStateResultCode::NOT_READY);
                }
            }

            testManager->advanceToTime(endTime + 1);

            CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, secondSaleID);
        }
        SECTION("Create several sales for the same base asset") {
            //autoreview
            auto createSecondSaleRequestResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            auto createThirdSaleRequestResult =
                    saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                            CreateSaleCreationRequestResultCode::INSUFFICIENT_PREISSUED);

            sales = SaleHelper::Instance()->loadSalesForOwner(syndicate.key.getPublicKey(), testManager->getDB());
            REQUIRE(sales.size() == 2);

            // cancel one of two sales to check that right base amount was unlocked
            auto data = manageSaleTestHelper.createDataForAction(ManageSaleAction::CANCEL);
            manageSaleTestHelper.applyManageSaleTx(syndicate, saleID, data);
        }
        SECTION("Try to cancel sale offer as regular one")
        {
            auto account = Account{ SecretKey::random(), 0 };
            CreateAccountTestHelper(testManager).applyCreateAccountTx(root, account.key.getPublicKey(), AccountType::NOT_VERIFIED);
            uint64_t quoteAssetAmount = hardCap / 2;
            uint64_t feeToPay(0);
            participantsFeeFrame->calculatePercentFee(quoteAssetAmount, feeToPay, ROUND_UP, 1);
            const auto offerID = participationHelper.addNewParticipant(root, account, saleID, baseAsset, quoteAsset, quoteAssetAmount, price, feeToPay);
            auto offer = OfferHelper::Instance()->loadOffer(account.key.getPublicKey(), offerID, testManager->getDB());
            REQUIRE(!!offer);
            const auto offerEntry = offer->getOffer();
            auto manageOfferOp = OfferManager::buildManageOfferOp(offerEntry.baseBalance, offerEntry.quoteBalance,
                true, 0, price, 0, offerEntry.offerID, 0);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(account, manageOfferOp, ManageOfferResultCode::NOT_FOUND);
            manageOfferOp.orderBookID = saleID;
            ParticipateInSaleTestHelper(testManager).applyManageOffer(account, manageOfferOp);

        }
        SECTION("Reached hard cap")
        {
            const int numberOfParticipants = 10;
            const auto quoteAssetAmount = hardCap / numberOfParticipants;
            uint64_t feeToPay(0);
            participantsFeeFrame->calculatePercentFee(quoteAssetAmount, feeToPay, ROUND_UP, 1);
            for (auto i = 0; i < numberOfParticipants; i++)
            {
                participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAssetAmount, price, feeToPay);
                if (i < numberOfParticipants - 1)
                {
                    CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
                }
            }

            CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);
        }

        SECTION("Reached soft cap")
        {
            const int numberOfParticipants = 10;
            const uint64_t quoteAmount = softCap / numberOfParticipants;
            uint64_t feeToPay(0);
            participantsFeeFrame->calculatePercentFee(quoteAmount, feeToPay, ROUND_UP, 1);
            const int64_t timeStep = (endTime - currentTime) / numberOfParticipants;
            for (int i = 0; i < numberOfParticipants - 1; i++)
            {
                participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAmount, price, feeToPay);
                testManager->advanceToTime(testManager->getLedgerManager().getCloseTime() + timeStep);
                checkStateHelper.applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
            }
            // sale is still active
            participantsFeeFrame->calculatePercentFee(2 * quoteAmount, feeToPay, ROUND_UP, 1);
            participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, 2 * quoteAmount, price, feeToPay);
            testManager->advanceToTime(endTime + 1);
            checkStateHelper.applyCheckSaleStateTx(root, saleID);
        }

        SECTION("Canceled")
        {
            const int numberOfParticipants = 10;
            const uint64_t quoteAmount = softCap / numberOfParticipants;
            uint64_t feeToPay(0);
            participantsFeeFrame->calculatePercentFee(quoteAmount, feeToPay, ROUND_UP, 1);
            for (auto i = 0; i < numberOfParticipants - 1; i++)
            {
                participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, quoteAmount, price, feeToPay);
                checkStateHelper.applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
            }
            // softcap is not reached, so no sale to close
            CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::NOT_READY);
            // close ledger after end time
            testManager->advanceToTime(endTime + 1);
            auto checkRes = checkStateHelper.applyCheckSaleStateTx(root, saleID, CheckSaleStateResultCode::SUCCESS);
            REQUIRE(checkRes.success().effect.effect() == CheckSaleStateEffect::CANCELED);
        }

        SECTION("Manage sale")
        {
            SECTION("Update sale details") {
                uint64_t requestID = 0;
                uint32_t tasks = 1;
                std::string newDetails = "{\n \"a\": \"test string\" \n}";
                auto manageSaleData = manageSaleTestHelper.createDataForAction(
                        ManageSaleAction::CREATE_UPDATE_DETAILS_REQUEST, &tasks, &requestID, &newDetails);
                auto manageSaleResult = manageSaleTestHelper.applyManageSaleTx(syndicate, saleID, manageSaleData);

                SECTION("Request already exists") {
                    manageSaleTestHelper.applyManageSaleTx(syndicate, saleID, manageSaleData,
                                                           ManageSaleResultCode::UPDATE_DETAILS_REQUEST_ALREADY_EXISTS);
                }

                SECTION("Sale not found") {
                    manageSaleTestHelper.applyManageSaleTx(syndicate, 42, manageSaleData,
                                                           ManageSaleResultCode::SALE_NOT_FOUND);
                }

                SECTION("Request to update not found") {
                    manageSaleData.updateSaleDetailsData().requestID = 42;
                    manageSaleTestHelper.applyManageSaleTx(syndicate, saleID, manageSaleData,
                                                           ManageSaleResultCode::UPDATE_DETAILS_REQUEST_NOT_FOUND);
                }

                requestID = manageSaleResult.success().response.requestID();

                SECTION("reject and successful update") {
                    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
                    REQUIRE(!!request);
                    reviewUpdateSaleDetailsRequestTestHelper.applyReviewRequestTx(root, requestID,
                                                                                           request->getHash(),
                                                                                           ReviewableRequestType::UPDATE_SALE_DETAILS,
                                                                                           ReviewRequestOpAction::REJECT, "because",
                                                                                           ReviewRequestResultCode::SUCCESS);
                    manageSaleData.updateSaleDetailsData().requestID = requestID;
                    manageSaleData.updateSaleDetailsData().newDetails = "{\n \"a\": \"updated string\" \n}";
                    manageSaleData.updateSaleDetailsData().allTasks = nullptr;
                    manageSaleTestHelper.applyManageSaleTx(syndicate, saleID, manageSaleData);
                }

                auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
                REQUIRE(!!request);
                uint32_t toAdd = 0, toRemove = 1;
                reviewUpdateSaleDetailsRequestTestHelper.applyReviewRequestTxWithTasks(root, requestID,
                                                                              request->getHash(),
                                                                              ReviewableRequestType::UPDATE_SALE_DETAILS,
                                                                              ReviewRequestOpAction::APPROVE, "",
                                                                              ReviewRequestResultCode::SUCCESS,
                                                                              &toAdd, &toRemove);
            }
        }
    }

    SECTION("Create sale with predefined required base asset amount for hard cap") {
        auto basicSaleType = SaleType::BASIC_SALE;
        SECTION("Insufficient preissued") {
            auto requiredBaseAssetForHardCap = maxIssuanceAmount + (5 * ONE);
            hardCap = static_cast<const uint64_t>(bigDivide(requiredBaseAssetForHardCap, price, ONE, ROUND_DOWN));
            softCap = hardCap / 2;
            saleRequest = saleRequestHelper.createSaleRequest(baseAsset, quoteAsset, currentTime,
                                                              endTime, softCap, hardCap, "{}",
                                                              { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
                                                              requiredBaseAssetForHardCap);
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            saleReviewer.applyReviewRequestTx(root, requestCreationResult.success().requestID,
                                              ReviewRequestOpAction::APPROVE, "",
                                              ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP);
        }
        SECTION("Success") {
            auto requiredBaseAssetForHardCap = maxIssuanceAmount - (5 * ONE);
            hardCap = static_cast<const uint64_t>(bigDivide(requiredBaseAssetForHardCap, price, ONE, ROUND_DOWN));
            softCap = hardCap / 2;
            saleRequest = saleRequestHelper.createSaleRequest(baseAsset, quoteAsset, currentTime,
                                                              endTime, softCap, hardCap, "{}",
                                                              { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
                                                              requiredBaseAssetForHardCap);
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            REQUIRE(requestCreationResult.success().fulfilled);
        }
    }

    SECTION("Create SaleCreationRequest")
    {
        SECTION("Try to create sale with zero price")
        {
            saleRequest.quoteAssets[0].price = 0;
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::INVALID_PRICE);
        }
        SECTION("Try to create sale that's ends before begins")
        {
            saleRequest.endTime = saleRequest.startTime;
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::START_END_INVALID);
        }
        SECTION("Try to create sale with hardCap less than softCap")
        {
            saleRequest.hardCap = saleRequest.softCap - 1;
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::INVALID_CAP);
        }
        SECTION("Try to update not existent request")
        {
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 42, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::REQUEST_NOT_FOUND);
        }
        SECTION("Base asset not found")
        {
            saleRequest.baseAsset = "GSC";
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::BASE_ASSET_OR_ASSET_REQUEST_NOT_FOUND);
        }
        SECTION("Quote asset not found")
        {
            saleRequest.quoteAssets[0].quoteAsset = "GSC";
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                                  CreateSaleCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        }
        SECTION("Try to create request that's already exists")
        {
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
        }
        SECTION("Trying to create sale with boundary start time and end time")
        {
            saleRequest.startTime = 0;
            saleRequest.endTime = INT64_MAX;
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
        }
    }

    SECTION("Review SaleCreationRequest with tasks")
    {
        uint32_t allTasks = 1;
        auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, &allTasks);
        auto requestID = requestCreationResult.success().requestID;

        SECTION("Check new review sale request result")
        {
            uint32_t toAdd = 0, toRemove = 1;
            auto reviewSaleRequestResult = saleReviewer.applyReviewRequestTxWithTasks(root, requestID,
                                                                             ReviewRequestOpAction::APPROVE, "",
                                                                             ReviewRequestResultCode::SUCCESS,
                                                                             &toAdd, &toRemove);
            REQUIRE(reviewSaleRequestResult.success().fulfilled);
            REQUIRE(reviewSaleRequestResult.success().typeExt.requestType() ==
                    ReviewableRequestType::CREATE_SALE);
            REQUIRE(reviewSaleRequestResult.success().typeExt.saleExtended().saleID != 0);
        }
        SECTION("Max issuance or preissued amount is less then hard cap")
        {
            const AssetCode asset = "GSC";

            // Create asset creation request with max issuance 2000 * ONE
            assetCreationRequest = assetTestHelper.createAssetCreationRequest(asset, syndicatePubKey, "{}",
                                                                              900*ONE, 0,
                                                                              nullptr,
                                                                              500*ONE);
            auto assetRequestCreationResult = assetTestHelper.applyManageAssetTx(syndicate, 0, assetCreationRequest);
            auto assetRequestID = assetRequestCreationResult.success().requestID;

            // Create sale creation request with hardCap 1000 * ONE
            saleRequest = saleRequestHelper.createSaleRequest(asset, quoteAsset, currentTime, currentTime + 1000, softCap, hardCap, "{}",
            { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)}, preIssuedAmount*2);
            auto saleRequestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
            auto saleRequestID = saleRequestCreationResult.success().requestID;

            SECTION("Hard cap will exceed max issuance")
            {
                //Try to approve sale creation request
                saleReviewer.applyReviewRequestTx(root, saleRequestID, ReviewRequestOpAction::APPROVE, "",
                                                  ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP);
            }
            SECTION("Preissued amount of base asset is not enough for hard cap")
            {
                //Try to approve sale creation request
                saleReviewer.applyReviewRequestTx(root, saleRequestID, ReviewRequestOpAction::APPROVE, "",
                                                  ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP);
            }
        }
    }
    SECTION("Try to steal token by creating sale for stranger asset")
    {
        uint32_t tasks = 1, zeroTasks = 0;
        auto ownerSyndicate = Account{ SecretKey::random(), 0 };
        auto ownerSyndicatePubKey = ownerSyndicate.key.getPublicKey();
        CreateAccountTestHelper(testManager).applyCreateAccountTx(root, ownerSyndicatePubKey, AccountType::SYNDICATE);

        auto thiefSyndicate = Account{ SecretKey::random(), 0 };
        auto thiefSyndicatePubKey = thiefSyndicate.key.getPublicKey();
        CreateAccountTestHelper(testManager).applyCreateAccountTx(root, thiefSyndicatePubKey, AccountType::SYNDICATE);

        const AssetCode asset = "GSC";
        const uint64_t assetMaxIssuanceAmount = 2000 * ONE;
        const uint64_t assetPreIssuedAmount = 1000 * ONE;

        // Owner creates asset creation request
        assetCreationRequest = assetTestHelper.createAssetCreationRequest(asset, ownerSyndicatePubKey, "{}",
                                                                          assetMaxIssuanceAmount,0,
                                                                          &tasks,
                                                                          assetPreIssuedAmount);
        auto ownerRequestCreationResult = assetTestHelper.applyManageAssetTx(ownerSyndicate, 0, assetCreationRequest);
        auto ownerAssetRequestID = ownerRequestCreationResult.success().requestID;

        // Thief creates asset creation request
        assetCreationRequest = assetTestHelper.createAssetCreationRequest(asset, thiefSyndicatePubKey, "{}",
                                                                          assetMaxIssuanceAmount,0,
                                                                          &tasks,
                                                                          assetPreIssuedAmount);
        auto thiefRequestCreationResult = assetTestHelper.applyManageAssetTx(thiefSyndicate, 0, assetCreationRequest);
        auto thiefAssetRequestID = thiefRequestCreationResult.success().requestID;

        // Thief creates sale creation request
        auto thiefSaleRequest = SaleRequestHelper::
                createSaleRequest(asset, quoteAsset, currentTime, currentTime + 1000,
                                         softCap, hardCap, "{}",
                                         {saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
                                         assetMaxIssuanceAmount);

        auto thiefSaleRequestCreationResult = saleRequestHelper.applyCreateSaleRequest(thiefSyndicate, 0, thiefSaleRequest,
                                                                                        &tasks);
        auto thiefSaleRequestID = thiefSaleRequestCreationResult.success().requestID;

        auto assetReviewer = ReviewAssetRequestHelper(testManager);

        // Reviewer approves owner's asset creation request
        auto request = ReviewableRequestHelper::Instance()->
                loadRequest(ownerAssetRequestID,
                            testManager->getDB(), nullptr);
        REQUIRE(request);
        auto reviewResult = assetReviewer.applyReviewRequestTxWithTasks(root, request->
                                                                                           getRequestID(),
                                                                                   request->getHash(),
                                                                                   request->getRequestType(),
                                                                                   ReviewRequestOpAction::
                                                                                   APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                                                   &zeroTasks,
                                                                                   &tasks);

        // Reviewer approves thief's sale creation request
        auto reviewSaleRequestResult = saleReviewer.applyReviewRequestTxWithTasks(root, thiefSaleRequestID,
                                                                                  ReviewRequestOpAction::APPROVE, "",
                                                                                  ReviewRequestResultCode::BASE_ASSET_DOES_NOT_EXISTS,
                                                                                  &zeroTasks, &tasks);
    }
    SECTION("Try to create sale, which is already started")
    {
        uint32_t allTasks = 1, toAdd = 0, toRemove = 1;
        testManager->advanceToTime(2000);
        saleRequest.endTime = testManager->getLedgerManager().getCloseTime() + 1000;
        auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, &allTasks);
        auto requestID = requestCreationResult.success().requestID;
        saleReviewer.applyReviewRequestTxWithTasks(root, requestID, ReviewRequestOpAction::APPROVE, "",
                ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);
    }
    SECTION("Try to create sale, which is already ended")
    {
        testManager->advanceToTime(2000);
        auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                                              CreateSaleCreationRequestResultCode::INVALID_END);
    }

    SECTION("Participation")
    {
        ParticipateInSaleTestHelper participateHelper(testManager);

        // create sale owner
        Account owner = Account{ SecretKey::random(), Salt(0) };
        createAccountTestHelper.applyCreateAccountTx(root, owner.key.getPublicKey(), AccountType::SYNDICATE);

        // create base asset
        const AssetCode baseAsset = "ETH";
        uint64_t maxIssuanceAmount = 10 * ONE;
        auto baseAssetRequest = assetTestHelper.createAssetCreationRequest(baseAsset, owner.key.getPublicKey(), "{}",
                                                                           maxIssuanceAmount, 0,
                                                                           nullptr,
                                                                           maxIssuanceAmount);
        assetTestHelper.createApproveRequest(root, owner, baseAssetRequest);

        // create participant
        Account participant = Account{ SecretKey::random(), Salt(0) };
        AccountID participantID = participant.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, participantID, AccountType::GENERAL);

        // create base balance for participant:
        auto manageBalanceRes = ManageBalanceTestHelper(testManager).applyManageBalanceTx(participant, participantID, baseAsset);
        BalanceID baseBalance = manageBalanceRes.success().balanceID;
        BalanceID quoteBalance = BalanceHelperLegacy::Instance()->loadBalance(participantID, quoteAsset, db,
                                                                        nullptr)->getBalanceID();

        // pre-issue quote amount
        const uint64_t quotePreIssued = maxNonDividedAmount - precision;
        issuanceHelper.authorizePreIssuedAmount(root, root.key, quoteAsset, quotePreIssued, root);

        SECTION("malformed manage offer")
        {
            // create sale to participate in:
            uint64_t startTime = testManager->getLedgerManager().getCloseTime() + 1000;
            uint64_t endTime = startTime + 1000;
            uint64_t price = 2 * ONE;
            int64_t hardCap = bigDivide(maxIssuanceAmount, price, ONE, ROUND_UP);
            auto saleRequest = saleRequestHelper.createSaleRequest(baseAsset, quoteAsset, startTime, endTime,
                                                                   hardCap/2, hardCap, "{}", { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price) }, maxIssuanceAmount);
            saleRequestHelper.createApprovedSale(root, owner, saleRequest);
            auto sales = SaleHelper::Instance()->loadSalesForOwner(owner.key.getPublicKey(), db);
            uint64_t saleID = sales[0]->getID();

            // fund participant with quote asset
            uint64_t quoteBalanceAmount = saleRequest.hardCap;
            issuanceHelper.applyCreateIssuanceRequest(root, quoteAsset, quoteBalanceAmount, quoteBalance,
                                                      SecretKey::random().getStrKeyPublic(), &issuanceTasks);

            // buy a half of sale in order to keep it active
            int64_t baseAmount = bigDivide(saleRequest.hardCap/2, ONE, saleRequest.quoteAssets[0].price, ROUND_UP);
            auto manageOffer = OfferManager::buildManageOfferOp(baseBalance, quoteBalance, true, baseAmount,
                saleRequest.quoteAssets[0].price, 0, 0, saleID);

            SECTION("try to participate in not started sale")
            {
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::SALE_IS_NOT_STARTED_YET);
            }

            // close ledger on start time
            testManager->advanceToTime(startTime);

            SECTION("successfully create participation then delete it")
            {
                participateHelper.applyManageOffer(participant, manageOffer);

                auto offers = OfferHelper::Instance()->loadOffersWithFilters(baseAsset, quoteAsset, &saleID, nullptr, db);
                REQUIRE(offers.size() == 1);

                manageOffer.amount = 0;
                manageOffer.offerID = offers[0]->getOfferID();
                participateHelper.applyManageOffer(participant, manageOffer);
            }
            SECTION("try to sell base asset being participant")
            {
                manageOffer.isBuy = false;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::MALFORMED);
            }
            SECTION("try to participate with negative amount")
            {
                manageOffer.amount = -1;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::INVALID_AMOUNT);
            }
            SECTION("try to participate with zero price")
            {
                manageOffer.price = 0;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::PRICE_IS_INVALID);
            }
            SECTION("overflow quote amount")
            {
                manageOffer.amount = bigDivide(INT64_MAX, ONE, manageOffer.price, ROUND_UP) + 1;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::OFFER_OVERFLOW);
            }
            SECTION("negative fee")
            {
                manageOffer.fee = -1;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::INVALID_PERCENT_FEE);
            }
            SECTION("base balance == quote balance")
            {
                manageOffer.baseBalance = manageOffer.quoteBalance;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE);
            }
            SECTION("base balance doesn't exist")
            {
                BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
                manageOffer.baseBalance = nonExistingBalance;
                participateHelper.applyManageOffer(participant, manageOffer,
                                                   ManageOfferResultCode::BALANCE_NOT_FOUND,
                                                   OperationResultCode::opNO_BALANCE);
            }
            SECTION("quote balance doesn't exist")
            {
                BalanceID nonExistingBalance = SecretKey::random().getPublicKey();
                manageOffer.quoteBalance = nonExistingBalance;
                participateHelper.applyManageOffer(participant, manageOffer,
                                                   ManageOfferResultCode::BALANCE_NOT_FOUND,
                                                   OperationResultCode::opNO_BALANCE);
            }
            SECTION("base and quote balances mixed up")
            {
                manageOffer.baseBalance = quoteBalance;
                manageOffer.quoteBalance = baseBalance;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS);
            }
            SECTION("try participate in non-existing sale")
            {
                uint64_t nonExistingSaleID = saleID + 1;
                manageOffer.orderBookID = nonExistingSaleID;
                participateHelper.applyManageOffer(participant, manageOffer,
                                                   ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS,
                                                   OperationResultCode::opNO_SALE);
            }
            SECTION("base and quote balances are in the same asset")
            {
                //create one more balance in base asset:
                auto opRes = ManageBalanceTestHelper(testManager).applyManageBalanceTx(participant, participantID, baseAsset);
                auto baseBalanceID = opRes.success().balanceID;
                manageOffer.quoteBalance = baseBalanceID;

                // can't find a sale from base to base
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS);
            }
            SECTION("price doesn't match sales price")
            {
                manageOffer.price = saleRequest.quoteAssets[0].price + 1;
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::PRICE_DOES_NOT_MATCH);
            }
            SECTION("try to participate in own sale")
            {
                // load balances for owner
                auto quoteBalanceID = BalanceHelperLegacy::Instance()->loadBalance(owner.key.getPublicKey(), quoteAsset, db,
                                                                             nullptr)->getBalanceID();
                AccountID ownerID = owner.key.getPublicKey();
                auto baseBalanceID = ManageBalanceTestHelper(testManager).applyManageBalanceTx(owner, ownerID, baseAsset)
                                                                         .success().balanceID;
                manageOffer.baseBalance = baseBalanceID;
                manageOffer.quoteBalance = quoteBalanceID;
                participateHelper.applyManageOffer(owner, manageOffer, ManageOfferResultCode::CANT_PARTICIPATE_OWN_SALE);
            }
            SECTION("amount exceeds hard cap")
            {
                // fund account
                issuanceHelper.applyCreateIssuanceRequest(root, quoteAsset, 2 * ONE, quoteBalance,
                                                          SecretKey::random().getStrKeyPublic(), &issuanceTasks);
                SECTION("by more than ONE")
                {
                    int64_t baseAssetAmount = bigDivide(hardCap + 2 * ONE, ONE, price, ROUND_DOWN);
                    manageOffer.amount = baseAssetAmount;
                    participateHelper.applyManageOffer(participant, manageOffer,
                                                       ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP);
                }
            }
            /*SECTION("try to buy asset which requires KYC being NOT_VERIFIED")
            {
                Account notVerified = Account{SecretKey::random(), Salt(0)};
                AccountID notVerifiedID = notVerified.key.getPublicKey();
                createAccountTestHelper.applyCreateAccountTx(root, notVerifiedID, AccountType::NOT_VERIFIED);

                // create base balance
                auto baseBalanceID = ManageBalanceTestHelper(testManager).applyManageBalanceTx(notVerified, notVerifiedID,
                                                                                               baseAsset).success().balanceID;

                // fund with quote asset
                auto quoteBalanceID = BalanceHelperLegacy::Instance()->loadBalance(notVerifiedID, quoteAsset, db, nullptr)->getBalanceID();
                issuanceHelper.applyCreateIssuanceRequest(root, quoteAsset, quoteBalanceAmount, quoteBalanceID,
                                                          SecretKey::random().getStrKeyPublic(), &issuanceTasks);

                manageOffer.baseBalance = baseBalanceID;
                manageOffer.quoteBalance = quoteBalanceID;

                participateHelper.applyManageOffer(notVerified, manageOffer, ManageOfferResultCode::REQUIRES_KYC);
            }*/
            SECTION("delete participation")
            {
                // create sale participation:
                int64_t initialAmount = manageOffer.amount;
                participateHelper.applyManageOffer(participant, manageOffer);
                auto offers = OfferHelper::Instance()->loadOffersWithFilters(baseAsset, quoteAsset, &saleID, nullptr, db);
                REQUIRE(offers.size() == 1);
                uint64_t offerID = offers[0]->getOfferID();

                //delete offer
                manageOffer.amount = 0;
                manageOffer.offerID = offerID;

                SECTION("try to delete non-existing offer")
                {
                    //switch to non-existing offerID
                    manageOffer.offerID++;
                    participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::NOT_FOUND);
                }
                SECTION("try to delete from non-existing orderBook")
                {
                    uint64_t nonExistingOrderBookID = saleID + 1;
                    manageOffer.orderBookID = nonExistingOrderBookID;
                    participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::NOT_FOUND);
                }
                SECTION("try to delete offer from closed sale")
                {
                    //participate again in order to close sale
                    int64_t baseHardCap = bigDivide(hardCap, ONE, price, ROUND_DOWN);
                    manageOffer.amount = baseHardCap - initialAmount;
                    manageOffer.offerID = 0;
                    participateHelper.applyManageOffer(participant, manageOffer);

                    //try to delete offer
                    manageOffer.offerID = offerID;
                    manageOffer.amount = 0;
                    participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::SALE_IS_NOT_ACTIVE);
                }
            }
            SECTION("try to participate after end time")
            {
                testManager->advanceToTime(endTime + 1);
                participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::SALE_ALREADY_ENDED);
            }
            SECTION("Invalid offer amount precision")
            {
                if (testSet.baseAsset == "USDN")
                {
                    manageOffer.amount = 1;
                    participateHelper.applyManageOffer(participant, manageOffer, ManageOfferResultCode::INCORRECT_AMOUNT_PRECISION);
                }
            }
        }

        SECTION("With tasks")
        {
            uint32_t allTasks = 1;
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, &allTasks);
            auto requestID = requestCreationResult.success().requestID;

            SECTION("Approve")
            {
                uint32_t toAdd = 0, toRemove = 1;
                auto reviewSaleRequestResult = saleReviewer.applyReviewRequestTxWithTasks(root, requestID,
                                                                                          ReviewRequestOpAction::APPROVE, "",
                                                                                          ReviewRequestResultCode::SUCCESS,
                                                                                          &toAdd, &toRemove);
                REQUIRE(reviewSaleRequestResult.success().fulfilled);
                REQUIRE(reviewSaleRequestResult.success().typeExt.requestType() ==
                        ReviewableRequestType::CREATE_SALE);
                REQUIRE(reviewSaleRequestResult.success().typeExt.saleExtended().saleID != 0);
            }

            SECTION("Reject")
            {
                auto reviewSaleRequestResult = saleReviewer.applyReviewRequestTxWithTasks(root, requestID,
                                                                                          ReviewRequestOpAction::PERMANENT_REJECT,
                                                                                          "very important reason",
                                                                                          ReviewRequestResultCode::SUCCESS);
            }
        }
    }
}

