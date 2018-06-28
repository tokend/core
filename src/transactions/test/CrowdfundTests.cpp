// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include <ledger/AssetPairHelper.h>
#include <transactions/FeesManager.h>
#include "main/Application.h"
#include "main/test.h"
#include "TxTests.h"
#include "test_helper/TestManager.h"
#include "test_helper/Account.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/SaleRequestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/CheckSaleStateTestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/SaleHelper.h"
#include "test_helper/ManageAssetPairTestHelper.h"
#include "ledger/BalanceHelper.h"
#include "test_helper/ManageBalanceTestHelper.h"
#include "transactions/dex/OfferManager.h"
#include "test_helper/ParticipateInSaleTestHelper.h"
#include "test_helper/ManageSaleTestHelper.h"
#include "test_helper/ReviewPromotionUpdateRequestTestHelper.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Crowdfunding", "[tx][crowdfunding]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    const Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto root = Account{ getRoot(), Salt(0) };

    const AssetCode defaultQuoteAsset = "USD";
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    auto assetCreationRequest = assetTestHelper.createAssetCreationRequest(defaultQuoteAsset, root.key.getPublicKey(), "{}", INT64_MAX,
                                                                           uint32_t(AssetPolicy::BASE_ASSET));
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    const AssetCode quoteAsset = "ETH";
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(quoteAsset, root.key.getPublicKey(), "{}", INT64_MAX,
        uint32_t(AssetPolicy::BASE_ASSET));
    assetTestHelper.applyManageAssetTx(root, 0, assetCreationRequest);

    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    int64_t quoteDefaultQuotePrice = ONE;
    assetPairHelper.applyManageAssetPairTx(root, quoteAsset, defaultQuoteAsset, quoteDefaultQuotePrice, 0, 0);

    CreateAccountTestHelper createAccountTestHelper(testManager);
    SaleRequestHelper saleRequestHelper(testManager);
    IssuanceRequestHelper issuanceHelper(testManager);
    CheckSaleStateHelper checkStateHelper(testManager);
    ManageSaleTestHelper manageSaleHelper(testManager);
    ReviewPromotionUpdateRequestHelper reviewPromotionUpdateHelper(testManager);

    auto syndicate = Account{ SecretKey::random(), 0 };
    const auto syndicatePubKey = syndicate.key.getPublicKey();

    CreateAccountTestHelper(testManager).applyCreateAccountTx(root, syndicatePubKey, AccountType::SYNDICATE);
    const AssetCode baseAsset = "XAU";
    // TODO: for now we need to keep maxIssuance = preIssuance to allow sale creation
    const uint64_t maxIssuanceAmount = 2000 * ONE;
    const auto preIssuedAmount = maxIssuanceAmount;
    assetCreationRequest = assetTestHelper.createAssetCreationRequest(baseAsset, syndicate.key.getPublicKey(), "{}",
                                                                      maxIssuanceAmount,0, preIssuedAmount);
    assetTestHelper.createApproveRequest(root, syndicate, assetCreationRequest);
    const auto hardCap = 10000 * ONE;
    const uint64_t softCap = hardCap / 2;
    const auto currentTime = testManager->getLedgerManager().getCloseTime();
    const auto endTime = currentTime + 1000;
    SaleType saleType = SaleType::CROWD_FUNDING;
    SECTION("Price must be 1")
    {
        const auto saleRequest = saleRequestHelper.createSaleRequest(baseAsset, defaultQuoteAsset, currentTime,
            endTime, softCap, hardCap, "{}", { saleRequestHelper.createSaleQuoteAsset(quoteAsset, ONE + 1) }, &saleType);
        saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest,
            CreateSaleCreationRequestResultCode::INVALID_PRICE);
    }
    SECTION("Given valid crowdfund")
    {
        const auto saleRequest = saleRequestHelper.createSaleRequest(baseAsset, defaultQuoteAsset, currentTime,
            endTime, softCap, hardCap, "{}", { saleRequestHelper.createSaleQuoteAsset(quoteAsset, ONE) }, &saleType, &preIssuedAmount, SaleState::PROMOTION);
        saleRequestHelper.createApprovedSale(root, syndicate, saleRequest);
        auto sales = SaleHelper::Instance()->loadSalesForOwner(syndicate.key.getPublicKey(), testManager->getDB());
        REQUIRE(sales.size() == 1);
        const auto saleID = sales[0]->getID();

        // create participant
        Account participant = Account{ SecretKey::random(), Salt(0) };
        AccountID participantID = participant.key.getPublicKey();
        createAccountTestHelper.applyCreateAccountTx(root, participantID, AccountType::GENERAL);

        // create base balance for participant:
        auto manageBalanceRes = ManageBalanceTestHelper(testManager).applyManageBalanceTx(participant, participantID, baseAsset);
        BalanceID baseBalance = manageBalanceRes.success().balanceID;
        Database& db = testManager->getDB();
        BalanceID quoteBalance = BalanceHelper::Instance()->loadBalance(participantID, quoteAsset, db,
            nullptr)->getBalanceID();

        // pre-issue quote amount
        issuanceHelper.authorizePreIssuedAmount(root, root.key, quoteAsset, INT64_MAX, root);

        // fund participant with quote asset
        uint64_t quoteBalanceAmount = INT64_MAX;
        issuanceHelper.applyCreateIssuanceRequest(root, quoteAsset, quoteBalanceAmount, quoteBalance,
            SecretKey::random().getStrKeyPublic());

        SECTION("Participation amount is too small")
        {
            auto saleTestHelper = ManageSaleTestHelper(testManager);
            auto saleStateData = saleTestHelper.setSaleState(SaleState::NONE);
            saleTestHelper.applyManageSaleTx(root, saleID, saleStateData);
            // able to invest 10^-6 when price for quote and default quote is 1
            auto quoteBalanceBeforeTx = BalanceHelper::Instance()->loadBalance(quoteBalance, db);
            quoteDefaultQuotePrice = 1000 * ONE;
            assetPairHelper.applyManageAssetPairTx(root, quoteAsset, defaultQuoteAsset, quoteDefaultQuotePrice, 0, 0, 0, ManageAssetPairAction::UPDATE_PRICE);
            auto manageOffer = OfferManager::buildManageOfferOp(baseBalance, quoteBalance, true, 1,
                ONE, 0, 0, saleID);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer);
            // exchange rate for quote asset changed, so now amount to recieve is 0
            quoteDefaultQuotePrice = 1;
            assetPairHelper.applyManageAssetPairTx(root, quoteAsset, defaultQuoteAsset, quoteDefaultQuotePrice, 0, 0, 0, ManageAssetPairAction::UPDATE_PRICE);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer, ManageOfferResultCode::INVALID_AMOUNT);
            // buy whole sale
            const auto hardCapInQuoteAsset = bigDivide(hardCap, ONE, quoteDefaultQuotePrice, ROUND_UP);
            manageOffer = OfferManager::buildManageOfferOp(baseBalance, quoteBalance, true, hardCapInQuoteAsset,
                ONE, 0, 0, saleID);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer);
            // now we should have two rders
            auto quoteBalanceAfterTx = BalanceHelper::Instance()->loadBalance(quoteBalance, db);
            REQUIRE(quoteBalanceAfterTx->getAmount() == quoteBalanceBeforeTx->getAmount() - hardCapInQuoteAsset - 1);
            // Check state and make sure first order was canceled
            CheckSaleStateHelper(testManager).applyCheckSaleStateTx(root, saleID);
            // we had two offers one with amount so small that base amount is 0, so it should have been canceled
            // so quote balance should be charged with only second order
            quoteBalanceAfterTx = BalanceHelper::Instance()->loadBalance(quoteBalance, db);
            REQUIRE(quoteBalanceAfterTx->getAmount() == quoteBalanceBeforeTx->getAmount() - hardCapInQuoteAsset);
        }
        SECTION("Not able to invest into sale in voting state")
        {
            auto saleTestHelper = ManageSaleTestHelper(testManager);
            auto saleStateData = saleTestHelper.setSaleState(SaleState::VOTING);
            saleTestHelper.applyManageSaleTx(root, saleID, saleStateData);

            // able to invest 10^-6 when price for quote and default quote is 1
            auto quoteBalanceBeforeTx = BalanceHelper::Instance()->loadBalance(quoteBalance, db);
            quoteDefaultQuotePrice = 1000 * ONE;
            assetPairHelper.applyManageAssetPairTx(root, quoteAsset, defaultQuoteAsset, quoteDefaultQuotePrice, 0, 0, 0, ManageAssetPairAction::UPDATE_PRICE);
            auto manageOffer = OfferManager::buildManageOfferOp(baseBalance, quoteBalance, true, 1,
                ONE, 0, 0, saleID);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer, ManageOfferResultCode::SALE_IS_NOT_STARTED_YET);

            // reset back
            saleStateData = saleTestHelper.setSaleState(SaleState::NONE);
            saleTestHelper.applyManageSaleTx(root, saleID, saleStateData);

            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer);
        }
        SECTION("Not able to invest into sale in promotion state")
        {
            // able to invest 10^-6 when price for quote and default quote is 1
            auto quoteBalanceBeforeTx = BalanceHelper::Instance()->loadBalance(quoteBalance, db);
            quoteDefaultQuotePrice = 1000 * ONE;
            assetPairHelper.applyManageAssetPairTx(root, quoteAsset, defaultQuoteAsset, quoteDefaultQuotePrice, 0, 0, 0, ManageAssetPairAction::UPDATE_PRICE);
            auto manageOffer = OfferManager::buildManageOfferOp(baseBalance, quoteBalance, true, 1,
                ONE, 0, 0, saleID);
            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer, ManageOfferResultCode::SALE_IS_NOT_STARTED_YET);

            // reset back
            auto saleTestHelper = ManageSaleTestHelper(testManager);
            auto saleStateData = saleTestHelper.setSaleState(SaleState::NONE);
            saleTestHelper.applyManageSaleTx(root, saleID, saleStateData);

            ParticipateInSaleTestHelper(testManager).applyManageOffer(participant, manageOffer);
        }
        SECTION("Update sale in promotion state")
        {
            uint64_t requestID = 0;
            const auto newPromotionData = SaleRequestHelper::createSaleRequest(baseAsset, defaultQuoteAsset,
                                                                               currentTime,
                                                                               endTime, softCap * 2, hardCap * 2, "{}",
                                                                               {saleRequestHelper.createSaleQuoteAsset
                                                                                       (quoteAsset, ONE)},
                                                                               &saleType, &preIssuedAmount,
                                                                               SaleState::NONE);

            auto manageSaleData = manageSaleHelper.createPromotionUpdateRequest(requestID, newPromotionData);

            auto manageSaleResult = manageSaleHelper.applyManageSaleTx(syndicate, saleID, manageSaleData);

            requestID = manageSaleResult.success().response.promotionUpdateRequestID();

            reviewPromotionUpdateHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::APPROVE, "");
        }
    }
}
