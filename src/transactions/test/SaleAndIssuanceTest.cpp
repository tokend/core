#include "test/test_marshaler.h"
#include "test/test.h"
#include "TxTests.h"
#include "test_helper/SaleRequestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ParticipateInSaleTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/CheckSaleStateTestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/BalanceHelper.h"

using namespace stellar;
using namespace stellar::txtest;

// This test case check exceeding of max issuance amount of asset
TEST_CASE("Sale and issuance", "[tx][sale][issuance]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    StorageHelperImpl storageHelperImpl(app.getDatabase(), nullptr);
    StorageHelper& storageHelper = storageHelperImpl;

    ManageAssetTestHelper assetTestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    ParticipateInSaleTestHelper participateHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueTestHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);

    manageKeyValueTestHelper.assetOpWithoutReview();
    longstring saleCreateKey = ManageKeyValueOpFrame::makeSaleCreateTasksKey("*");
    manageKeyValueTestHelper.setKey(saleCreateKey)->setUi32Value(0);
    manageKeyValueTestHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    auto root = Account{ getRoot(), Salt(0) };

    AssetCode baseAsset("BASE0ASSET");
    AssetCode quoteAsset("QUOTE0ASSET");
    uint32_t zeroTasks(0);
    uint64_t preIssuedAmount(3*ONE);

    issuanceHelper.createAssetWithPreIssuedAmount(root, baseAsset, preIssuedAmount/3*2, root, 6, 1, preIssuedAmount);
    issuanceHelper.createAssetWithPreIssuedAmount(root, quoteAsset, preIssuedAmount, root, 6, 1);

    const uint64_t price = ONE;
    auto hardCap = preIssuedAmount / 3;
    uint64_t softCap = hardCap / 2;
    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    const auto requiredBaseAssetForHardCap = ONE * hardCap / price;
    auto saleRequest = SaleRequestHelper::createSaleRequest(baseAsset, quoteAsset,
            currentTime, endTime, softCap, hardCap, "{}",
            {saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
            requiredBaseAssetForHardCap);
    auto firstSaleID = saleRequestHelper.createApprovedSale(root, root, saleRequest)
            .success().typeExt.saleExtended().saleID;

    issuanceHelper.applyCreatePreIssuanceRequest(root, root.key, baseAsset, preIssuedAmount, "reference",
                                                 CreatePreIssuanceRequestResultCode::EXCEEDED_MAX_AMOUNT);

    saleRequest.hardCap = preIssuedAmount / 3 * 2;
    saleRequest.softCap = saleRequest.hardCap / 2;
    saleRequest.requiredBaseAssetForHardCap = ONE * saleRequest.hardCap / price;
    auto result = saleRequestHelper.applyCreateSaleRequest(root, 0, saleRequest, nullptr,
                                             CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED);

    REQUIRE(result.autoReviewFailed().reviewRequestRequest.code() ==
            ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP);

    issuanceHelper.applyCreatePreIssuanceRequest(root, root.key, baseAsset, preIssuedAmount/3, "reference");

    auto secondSaleID = saleRequestHelper.createApprovedSale(root, root, saleRequest)
            .success().typeExt.saleExtended().saleID;

    participateHelper.addNewParticipant(root, firstSaleID, baseAsset, quoteAsset, hardCap, ONE, 0);
    checkStateHelper.applyCheckSaleStateTx(root, firstSaleID);

    auto balance = storageHelper.getBalanceHelper().loadBalance(root.key.getPublicKey(), baseAsset);
    issuanceHelper.applyCreateIssuanceRequest(root, baseAsset, preIssuedAmount, balance->getBalanceID(), "reference0",
                                              nullptr, CreateIssuanceRequestResultCode::EXCEEDS_MAX_ISSUANCE_AMOUNT);

    participateHelper.addNewParticipant(root, secondSaleID, baseAsset, quoteAsset, saleRequest.hardCap, ONE, 0);
    checkStateHelper.applyCheckSaleStateTx(root, secondSaleID);
}
