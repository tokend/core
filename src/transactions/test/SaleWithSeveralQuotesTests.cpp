#include <ledger/OfferHelper.h>
#include <transactions/managers/FeeManager.h>
#include <ledger/FeeHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "ledger/ReviewableRequestHelper.h"
#include "test/test.h"
#include "TxTests.h"
#include "crypto/SHA.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "ledger/StorageHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/SaleRequestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageSaleTestHelper.h"
#include "test_helper/ParticipateInSaleTestHelper.h"
#include "ledger/SaleHelper.h"
#include "test_helper/CheckSaleStateTestHelper.h"
#include "test_helper/ReviewAssetRequestHelper.h"
#include "test_helper/ReviewSaleRequestHelper.h"
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

    auto root = Account{getRoot(), Salt(0)};

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

    auto syndicate = Account{SecretKey::random(), 0};
    auto syndicatePubKey = syndicate.key.getPublicKey();

    CreateAccountTestHelper(testManager).applyCreateAccountTx(root, syndicatePubKey, 1);
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
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(
            maxIssuanceAmount / 2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(
            maxIssuanceAmount / 2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);
        CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);
    }
    SECTION("Happy path with different precisions")
    {
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(baseAsset, 2);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetBTC, 1);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetETH, 0);

        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(
            maxIssuanceAmount / 2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(
            maxIssuanceAmount / 2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

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

    auto root = Account{getRoot(), Salt(0)};
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

    uint32_t defaultSaleTasks = 1;
    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueHelper.setKey(saleCreateKey)->setUi32Value(defaultSaleTasks);
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
                                                                        baseAssetResource, AccountRuleAction::ANY, false);
    auto baseAssetOwnerRuleID = manageAccountRuleTestHelper.applyTx(root,
                                                                    ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource saleResource(LedgerEntryType::REVIEWABLE_REQUEST);
    saleResource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);
    saleResource.reviewableRequest().details.createSale().type = saleTypeInt;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                   saleResource, AccountRuleAction::CREATE, false);
    auto saleCreatorRuleID = manageAccountRuleTestHelper.applyTx(root,
                                                                 ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
        "{}", {baseAssetOwnerRuleID, saleCreatorRuleID});
    auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root,
                                                               createSyndicateRoleOp).success().roleID;

    // basic account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
        .setSource(root);

    auto syndicate = Account{SecretKey::random(), 0};
    auto syndicatePubKey = syndicate.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                        .setToPublicKey(syndicatePubKey)
                                        .addBasicSigner()
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
                                                            {saleRequestHelper.createSaleQuoteAsset(quoteAssetBTC, xaauBTCPrice),
                                                             saleRequestHelper.createSaleQuoteAsset(quoteAssetETH, xaauETHPrice)},
                                                            maxIssuanceAmount, saleType, saleTypeInt);

    auto saleCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest);
    auto request = testManager->getStorageHelper().getReviewableRequestHelper().
        loadRequest(assetResult.success().requestID);
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
    auto saleReviewResult = saleReviewer.applyReviewRequestTxWithTasks(
        root, requestID,
        ReviewRequestOpAction::APPROVE, "",
        ReviewRequestResultCode::SUCCESS, &zeroTasks, &defaultSaleTasks);
    const auto saleID = saleReviewResult.success().typeExt.saleExtended().saleID;

    SECTION("Happy path")
    {
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(
            maxIssuanceAmount / 2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(
            maxIssuanceAmount / 2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }
    SECTION("Happy path with different precisions")
    {
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(baseAsset, 0);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetBTC, 1);
        ManageAssetTestHelper(testManager).changeAssetTrailingDigits(quoteAssetETH, 2);

        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetBTC, bigDivide(
            maxIssuanceAmount / 2, xaauBTCPrice, ONE, ROUND_UP), xaauBTCPrice, 0);
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAssetETH, bigDivide(
            maxIssuanceAmount / 2, xaauETHPrice, ONE, ROUND_UP), xaauETHPrice, 0);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);
    }
}
