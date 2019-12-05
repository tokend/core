// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "overlay/LoopbackPeer.h"
#include "test/test.h"
#include "transactions/dex/OfferExchange.h"
#include "ledger/BalanceHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/AssetPairHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageAssetPairTestHelper.h"
#include "test_helper/ManageOfferTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/StorageHelperImpl.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

// Try setting each option to make sure it works
// try setting all at once
// try setting high threshold ones without the correct sigs
// make sure it doesn't allow us to add signers when we don't have the
// minbalance
TEST_CASE("manage offer", "[tx][offer]")
{
    using xdr::operator==;

    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);
    auto& db = testManager->getDB();

    // set up world
    SecretKey root = getRoot();
    auto rootAccount = Account{ root, 0 };

    Salt rootSeq = 1;

    // test helpers
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    auto issuanceHelper = IssuanceRequestHelper(testManager);
    auto offerTestHelper = ManageOfferTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
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

    AssetCode base = "BTC";
    uint64_t baseType = 1;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, base, rootAccount, 
                                int32(AssetPolicy::BASE_ASSET), nullptr, 6, baseType);
    AssetCode quote = "USD";
    uint64_t quoteType = 2;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, quote, rootAccount,
                                int32(AssetPolicy::BASE_ASSET), nullptr, 6, quoteType);

    assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote, 1, 0, 0, 
                                           int32(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET));

    // create roles for token exchanging
    AccountRuleResource offerResource(LedgerEntryType::OFFER_ENTRY);
    offerResource.offer().baseAssetCode = base;
    offerResource.offer().baseAssetType = baseType;
    offerResource.offer().quoteAssetCode = quote;
    offerResource.offer().quoteAssetType = quoteType;
    
    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            offerResource, AccountRuleAction::CREATE, false);
    auto offerRuleID = manageAccountRuleTestHelper.applyTx(rootAccount, ruleEntry,
            ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource baseAssetResource(LedgerEntryType::ASSET);
    baseAssetResource.asset().assetType = baseType;
    baseAssetResource.asset().assetCode = base;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            baseAssetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
    auto baseRuleID = manageAccountRuleTestHelper.applyTx(rootAccount, ruleEntry,
            ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource quoteAssetResource(LedgerEntryType::ASSET);
    quoteAssetResource.asset().assetType = quoteType;
    quoteAssetResource.asset().assetCode = quote;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            quoteAssetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
    auto quoteRuleID = manageAccountRuleTestHelper.applyTx(rootAccount, ruleEntry,
            ManageAccountRuleAction::CREATE).success().ruleID;

    auto createExchangeRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            "{}", {offerRuleID, baseRuleID, quoteRuleID});
    auto exchangeRoleID = manageAccountRoleTestHelper.applyTx(rootAccount,
            createExchangeRoleOp).success().roleID;


    // basic create account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(rootAccount)
            .setRoleID(1);

    auto fundAccount = [&issuanceHelper, &rootAccount](AssetCode code, uint64_t amount, BalanceID receiver)
    {
        issuanceHelper.authorizePreIssuedAmount(rootAccount, rootAccount.key, code, amount, rootAccount);
        issuanceHelper.applyCreateIssuanceRequest(rootAccount, code, amount, receiver, SecretKey::random().getStrKeyPublic());
    };

    auto& balanceHelper = testManager->getStorageHelper().getBalanceHelper();
    auto& offerHelper = testManager->getStorageHelper().getOfferHelper();

    SECTION("basics")
    {
        auto buyer = Account{ SecretKey::random() , 0};
        createAccountTestHelper.applyTx(createAccountBuilder
                                    .setToPublicKey(buyer.key.getPublicKey())
                                    .addBasicSigner());
        auto baseBuyerBalance = balanceHelper.loadBalance(buyer.key.getPublicKey(), base);

        REQUIRE(baseBuyerBalance);
        auto quoteBuyerBalance = balanceHelper.
            loadBalance(buyer.key.getPublicKey(), quote);
        REQUIRE(quoteBuyerBalance);
        auto quoteAssetAmount = 1000 * ONE;
        fundAccount(quote, quoteAssetAmount, quoteBuyerBalance->getBalanceID());
        auto seller = Account{ SecretKey::random() , 0};
        createAccountTestHelper.applyTx(CreateAccountTestBuilder()
                                    .setSource(rootAccount)
                                    .setRoleID(1)
                                    .setToPublicKey(seller.key.getPublicKey())
                                    .addBasicSigner());
        auto baseSellerBalance = balanceHelper.
            loadBalance(seller.key.getPublicKey(), base);
        REQUIRE(baseBuyerBalance);
        auto quoteSellerBalance = balanceHelper.
            loadBalance(seller.key.getPublicKey(), quote);
        REQUIRE(quoteSellerBalance);
        auto baseAssetAmount = 200 * ONE;
        fundAccount(base, baseAssetAmount, baseSellerBalance->getBalanceID());
        SECTION("Place two offers")
        {
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(),
                               baseAssetAmount / 2, 5 * ONE, true, 0);
            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount / 2);
            REQUIRE(quoteBuyerBalance->getAmount() == quoteAssetAmount / 2);

            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(),
                               baseAssetAmount / 2, 5 * ONE, true, 0);
            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            SECTION("Try to delete assets")
            {
                assetTestHelper.applyRemoveAssetTx(rootAccount, quote, nullptr, RemoveAssetResultCode::HAS_ACTIVE_OFFERS);
                assetTestHelper.applyRemoveAssetTx(rootAccount, base, nullptr, RemoveAssetResultCode::HAS_ACTIVE_OFFERS);
            }
        }
        SECTION("Current price restrictions not met")
        {
            offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             baseAssetAmount / 2, 5 * ONE, true, 0);

            offerTestHelper.applyManageOffer(seller, 0,
                                             baseSellerBalance->getBalanceID(),
                                             quoteSellerBalance->getBalanceID(),
                                             baseAssetAmount / 2, 5 * ONE, false, 0);

            StorageHelperImpl storageHelperImpl(db, nullptr);
            StorageHelper& storageHelper = storageHelperImpl;
            auto assetPair = storageHelper.getAssetPairHelper().loadAssetPair(base, quote);

            REQUIRE(assetPair->getCurrentPrice() == 5 * ONE);

            //update policies
            auto maxPriceStep = ONE;
            auto policies = static_cast<int32_t>(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET) |
                       static_cast<int32_t>(AssetPairPolicy::
                       CURRENT_PRICE_RESTRICTION);
            assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote,
                                                       0,
                                                       0,
                                                       maxPriceStep,
                                                       policies,
                                                       ManageAssetPairAction
                                                       ::UPDATE_POLICIES);


            offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             baseAssetAmount / 2, 6 * ONE, true, 0,
                                             ManageOfferResultCode::CURRENT_PRICE_RESTRICTION);

            offerTestHelper.applyManageOffer(seller, 0,
                                             baseSellerBalance->getBalanceID(),
                                             quoteSellerBalance->getBalanceID(),
                                             baseAssetAmount / 2, 6 * ONE, false, 0,
                                             ManageOfferResultCode::CURRENT_PRICE_RESTRICTION);

        }

        SECTION("Current price restrictions met")
        {
            auto maxPriceStep = ONE;
            auto policies = static_cast<int32_t>(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET) |
                       static_cast<int32_t>(AssetPairPolicy::
                       CURRENT_PRICE_RESTRICTION);
            assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote,
                                                       ONE,
                                                       0,
                                                       maxPriceStep,
                                                       policies,
                                                       ManageAssetPairAction
                                                       ::UPDATE_POLICIES);

            assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote,
                                                       5 * ONE,
                                                       0,
                                                       maxPriceStep,
                                                       policies,
                                                       ManageAssetPairAction
                                                       ::UPDATE_PRICE);


            offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             baseAssetAmount / 2, int64_t(4.95 * ONE), true, 0);

            offerTestHelper.applyManageOffer(seller, 0,
                                             baseSellerBalance->getBalanceID(),
                                             quoteSellerBalance->getBalanceID(),
                                             baseAssetAmount / 2, int64_t(5.05 * ONE), false, 0);

        }

        SECTION("Physical price restriction")
        {
            auto policies = static_cast<int32_t>(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET) |
                       static_cast<int32_t>(AssetPairPolicy::
                       PHYSICAL_PRICE_RESTRICTION);
            assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote,
                                                       2*ONE,
                                                       100 * ONE,
                                                       ONE,
                                                       policies,
                                                       ManageAssetPairAction
                                                       ::UPDATE_POLICIES);

            assetPairHelper.applyManageAssetPairTx(rootAccount, base, quote,
                                                       2*ONE,
                                                       ONE,
                                                       ONE,
                                                       policies,
                                                       ManageAssetPairAction
                                                       ::UPDATE_PRICE);


            offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             baseAssetAmount, int64_t(1.99 * ONE), true, 0,
                                             ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION);

            offerTestHelper.applyManageOffer(seller, 0,
                                             baseSellerBalance->getBalanceID(),
                                             quoteSellerBalance->getBalanceID(),
                                             baseAssetAmount, int64_t(2.00 * ONE), false, 0);

        }

        SECTION("Place and delete offer")
        {
            auto result = offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             baseAssetAmount, 5 * ONE, true, 0);
            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            // delete
            offerTestHelper.applyManageOffer(buyer,
                               result.success().offer.offer().offerID,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(), 0, 5 * ONE,
                               true, 0);
            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == 0);
            REQUIRE(quoteBuyerBalance->getAmount() == quoteAssetAmount);
        }
        SECTION("base*price = quote")
        {
            auto buyerAccountID = buyer.key.getPublicKey();
            auto offerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0,
                                                  int64_t(0.2 * ONE), quote,
                                                  &buyerAccountID);
            auto offerFee = offerFeeFrame->getFee();

            applySetFees(app, root, rootSeq, &offerFee, false, nullptr);

            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               int64_t(0.5 * ONE), int64_t(45.11 * ONE), false, 0);
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               int64_t(0.1 * ONE), int64_t(45.12 * ONE), false, 0);
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(), ONE,
                               int64_t(45.13 * ONE), false, 0);

            int64_t fee = 0;
            OfferExchange::setFeeToPay(fee, int64_t(45.13 * ONE),
                                       int64_t(0.2 * ONE));
            auto result = offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             ONE, int64_t(45.13 * ONE), true,
                                             fee);
            baseBuyerBalance = loadBalance(baseBuyerBalance->getBalanceID(),
                                           app);
            for (ClaimOfferAtom claimed : result.success().offersClaimed)
            {
                int64_t expectedQuote = 0;
                REQUIRE(bigDivide(expectedQuote, claimed.baseAmount, claimed.
                    currentPrice, ONE, ROUND_UP));
                REQUIRE(expectedQuote == claimed.quoteAmount);
            }
        }
        SECTION("3 taken by one")
        {
            auto buyerAccountID = buyer.key.getPublicKey();
            auto offerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0,
                                                  0.2 * ONE, quote,
                                                  &buyerAccountID);
            auto offerFee = offerFeeFrame->getFee();

            applySetFees(app, root, rootSeq, &offerFee, false, nullptr);

            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               int64_t(0.5 * ONE), int64_t(45.11 * ONE), false, 0);
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               int64_t(0.1 * ONE), int64_t(45.12 * ONE), false, 0);
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(), ONE,
                               int64_t(45.13 * ONE), false, 0);

            int64_t fee = 0;
            OfferExchange::setFeeToPay(fee, 45.13 * ONE, 0.2 * ONE);
            // round up to 2 digits
            fee = bigDivide(fee, 1, 100, ROUND_UP) * 100;
            auto result = offerTestHelper.applyManageOffer(buyer, 0,
                                             baseBuyerBalance->getBalanceID(),
                                             quoteBuyerBalance->getBalanceID(),
                                             ONE, int64_t(45.13 * ONE), true,
                                             fee);
            baseBuyerBalance = loadBalance(baseBuyerBalance->getBalanceID(),
                                           app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == ONE);
        }
        SECTION("1 to 0.5")
        {
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(),
                               baseAssetAmount, 5 * ONE, true, 0);
            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               baseAssetAmount, 5 * ONE, false, 0);

            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == 0);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            baseBuyerBalance = loadBalance(baseBuyerBalance->getBalanceID(),
                                           app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == baseAssetAmount);

            baseSellerBalance = loadBalance(baseSellerBalance->getBalanceID(),
                                            app);
            REQUIRE(baseSellerBalance->getLocked() == 0);
            REQUIRE(baseSellerBalance->getAmount() == 0);

            quoteSellerBalance = loadBalance(quoteSellerBalance->getBalanceID(),
                                             app);
            REQUIRE(quoteSellerBalance->getLocked() == 0);
            REQUIRE(quoteSellerBalance->getAmount() == quoteAssetAmount);
        }
        SECTION("0.5 to 1")
        {
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               baseAssetAmount, 1 * ONE, false, 0);
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(),
                               baseAssetAmount - 1, 5 * ONE, true, 0);
            int64_t matchAmount = baseAssetAmount - 1;

            quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(),
                                            app);
            REQUIRE(quoteBuyerBalance->getLocked() == 0);
            int64_t matchQuoteAmount = matchAmount;
            REQUIRE(quoteBuyerBalance->getAmount() == (quoteAssetAmount -
                matchQuoteAmount));

            baseBuyerBalance = loadBalance(baseBuyerBalance->getBalanceID(),
                                           app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == matchAmount);

            baseSellerBalance = loadBalance(baseSellerBalance->getBalanceID(),
                                            app);
            REQUIRE(baseSellerBalance->getLocked() == 1);
            REQUIRE(baseSellerBalance->getAmount() == 0);

            quoteSellerBalance = loadBalance(quoteSellerBalance->getBalanceID(),
                                             app);
            REQUIRE(quoteSellerBalance->getLocked() == 0);
            REQUIRE(quoteSellerBalance->getAmount() == matchQuoteAmount);
        }
        SECTION("Asset pair is not tradable")
        {
            auto assetPairTestHelper = ManageAssetPairTestHelper(testManager);
            assetPairTestHelper.applyManageAssetPairTx(rootAccount, base, quote, 100 * ONE,
                                   0, 0,
                                   static_cast<int32_t>(AssetPairPolicy::
                                       TRADEABLE_SECONDARY_MARKET),
                                   ManageAssetPairAction::UPDATE_POLICIES);
            auto offerResult = offerTestHelper.applyManageOffer(seller, 0,
                                                  baseSellerBalance->
                                                  getBalanceID(),
                                                  quoteSellerBalance->
                                                  getBalanceID(),
                                                  baseAssetAmount, 95 * ONE,
                                                  false, 0);
            assetPairTestHelper.applyManageAssetPairTx(rootAccount, base, quote, 101 * ONE,
                                   0, 0, 0,
                                   ManageAssetPairAction::UPDATE_POLICIES);
            // offer was deleted
            auto offer = testManager->getStorageHelper().getOfferHelper().loadOffer(seller.key.getPublicKey(),
                              offerResult.success().offer.offer().offerID);
            REQUIRE(!offer);
            // can place offer
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(),
                               baseAssetAmount, 95 * ONE, false, 0,
                               ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE);
        }
        SECTION(
            "Seller can receive more then we expected based on base amount and price"
        )
        {
            int64_t sellPrice = int64_t(45.76 * ONE);
            int64_t buyPrice = int64_t(45.77 * ONE);
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(), ONE, buyPrice,
                               true, 0);
            auto offerMatch = offerTestHelper.applyManageOffer(seller, 0,
                                                 baseSellerBalance->
                                                 getBalanceID(),
                                                 quoteSellerBalance->
                                                 getBalanceID(), ONE, sellPrice,
                                                 false, 0);
            int64_t baseAmount = ONE;
            int64_t quoteAmount = buyPrice;
            REQUIRE(offerMatch.success().offersClaimed[0].baseAmount ==
                baseAmount);
            REQUIRE(offerMatch.success().offersClaimed[0].quoteAmount ==
                quoteAmount);
        }
        SECTION("buy amount == sell amount - buy price")
        {
            int64_t buyAmount = baseAssetAmount;
            int64_t sellAmount = buyAmount;
            int64_t buyPrice = 3 * ONE;
            int64_t sellPrice = ONE;
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(), buyAmount,
                               buyPrice, true, 0);
            auto offerMatch = offerTestHelper.applyManageOffer(seller, 0,
                                                 baseSellerBalance->
                                                 getBalanceID(),
                                                 quoteSellerBalance->
                                                 getBalanceID(), sellAmount,
                                                 sellPrice, false, 0);
            REQUIRE(offerMatch.success().offersClaimed[0].currentPrice ==
                buyPrice);
        }
        SECTION("buy amount > sell amount - buy price")
        {
            int64_t buyAmount = baseAssetAmount;
            int64_t sellAmount = buyAmount - 1;
            int64_t buyPrice = 3 * ONE;
            int64_t sellPrice = ONE;
            offerTestHelper.applyManageOffer(buyer, 0,
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(), buyAmount,
                               buyPrice, true, 0);
            auto offerMatch = offerTestHelper.applyManageOffer(seller, 0,
                                                 baseSellerBalance->
                                                 getBalanceID(),
                                                 quoteSellerBalance->
                                                 getBalanceID(), sellAmount,
                                                 sellPrice, false, 0);
            REQUIRE(offerMatch.success().offersClaimed[0].currentPrice ==
                buyPrice);
        }
        SECTION("buy amount < sell amount - sell price")
        {
            int64_t sellAmount = baseAssetAmount;
            int64_t buyAmount = sellAmount - 1;
            int64_t buyPrice = 3 * ONE;
            int64_t sellPrice = ONE;
            offerTestHelper.applyManageOffer(seller, 0,
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(), sellAmount,
                               sellPrice, false, 0);
            auto offerMatch = offerTestHelper.applyManageOffer(buyer, 0,
                                                 baseBuyerBalance->
                                                 getBalanceID(),
                                                 quoteBuyerBalance->
                                                 getBalanceID(), buyAmount,
                                                 buyPrice, true, 0);
            REQUIRE(offerMatch.success().offersClaimed[0].currentPrice ==
                sellPrice);
        }
        SECTION("Offer fees")
        {
            auto offerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, ONE,
                                                  quote);
            auto offerFee = offerFeeFrame->getFee();

            applySetFees(app, root, rootSeq, &offerFee, false, nullptr);
            SECTION("Try to spend all quote")
            {
                int64_t offerPrice = 5 * ONE;
                int64_t feeToPay = 0;
                REQUIRE(OfferExchange::setFeeToPay(feeToPay, quoteAssetAmount,
                    ONE));
                offerTestHelper.applyManageOffer(buyer, 0,
                                   baseBuyerBalance->getBalanceID(),
                                   quoteBuyerBalance->getBalanceID(),
                                   quoteAssetAmount / offerPrice * ONE,
                                   offerPrice, true, feeToPay,
                                   ManageOfferResultCode::UNDERFUNDED);
            }
            SECTION("Not 0 percent fee")
            {
                offerTestHelper.applyManageOffer(seller, 0,
                                   baseSellerBalance->getBalanceID(),
                                   quoteSellerBalance->getBalanceID(),
                                   baseAssetAmount, 1 * ONE, false, 0,
                                   ManageOfferResultCode::MALFORMED);
            }
            SECTION("Success")
            {
                auto buyerAccountID = baseBuyerBalance->getAccountID();
                offerFeeFrame = FeeFrame::create(FeeType::OFFER_FEE, 0, 2 * ONE,
                                                 quote, &buyerAccountID);
                offerFee = offerFeeFrame->getFee();
                applySetFees(app, root, rootSeq, &offerFee, false, nullptr);
                int64_t matchAmount = baseAssetAmount;
                int64_t matchPrice = 4 * ONE;
                int64_t quoteAssetMatchAmount = matchAmount * matchPrice / ONE;

                int64_t sellerMatchFee, buyerOfferFeeToLock, sellerOfferFee;
                REQUIRE(OfferExchange::setFeeToPay(sellerMatchFee,
                    quoteAssetMatchAmount, ONE));
                REQUIRE(OfferExchange::setFeeToPay(sellerOfferFee,
                    baseAssetAmount, ONE));
                REQUIRE(OfferExchange::setFeeToPay(buyerOfferFeeToLock,
                    baseAssetAmount * 4, offerFee.percentFee));
                offerTestHelper.applyManageOffer(seller, 0,
                                   baseSellerBalance->getBalanceID(),
                                   quoteSellerBalance->getBalanceID(),
                                   baseAssetAmount, ONE, false, sellerOfferFee);
                auto offerMatch = offerTestHelper.applyManageOffer(buyer, 0,
                                                     baseBuyerBalance->
                                                     getBalanceID(),
                                                     quoteBuyerBalance->
                                                     getBalanceID(),
                                                     baseAssetAmount,
                                                     matchPrice, true,
                                                     buyerOfferFeeToLock);
                REQUIRE(offerMatch.success().offersClaimed[0].quoteAmount ==
                    quoteAssetMatchAmount);
                REQUIRE(offerMatch.success().offersClaimed[0].bFeePaid ==
                    sellerMatchFee);
                int64_t buyerOfferFee = 0;
                REQUIRE(OfferExchange::setFeeToPay(buyerOfferFee,
                    quoteAssetMatchAmount, offerFee.percentFee));
                REQUIRE(offerMatch.success().offersClaimed[0].aFeePaid ==
                    buyerOfferFee);
                REQUIRE(offerMatch.success().offersClaimed.size() == 1);

                quoteBuyerBalance =
                    loadBalance(quoteBuyerBalance->getBalanceID(), app);
                REQUIRE(quoteBuyerBalance->getLocked() == 0);
                REQUIRE(quoteBuyerBalance->getAmount() == (quoteAssetAmount -
                    quoteAssetMatchAmount - buyerOfferFee));

                baseBuyerBalance = loadBalance(baseBuyerBalance->getBalanceID(),
                                               app);
                REQUIRE(baseBuyerBalance->getLocked() == 0);
                REQUIRE(baseBuyerBalance->getAmount() == baseAssetAmount);

                baseSellerBalance =
                    loadBalance(baseSellerBalance->getBalanceID(), app);
                REQUIRE(baseSellerBalance->getLocked() == 0);
                REQUIRE(baseSellerBalance->getAmount() == 0);

                quoteSellerBalance =
                    loadBalance(quoteSellerBalance->getBalanceID(), app);
                REQUIRE(quoteSellerBalance->getLocked() == 0);
                REQUIRE(quoteSellerBalance->getAmount() == quoteAssetMatchAmount
                    - sellerMatchFee);

                auto commissionQuoteBalance = balanceHelper.
                    loadBalance(app.getAdminID(), quote);
                REQUIRE(commissionQuoteBalance);
                REQUIRE(commissionQuoteBalance->getAmount() == buyerOfferFee +
                    sellerMatchFee);
            }
        }
    }
    SECTION("Random tests")
    {
        int64_t fee = int64_t(0.75 * ONE);
        auto offerFeeFrame = FeeFrame::
            create(FeeType::OFFER_FEE, 0, fee, quote);
        auto offerFee = offerFeeFrame->getFee();
        applySetFees(app, root, rootSeq, &offerFee, false, nullptr);

        auto buyer = Account{ SecretKey::random(), 0 };
        createAccountTestHelper.applyTx(createAccountBuilder
                                    .setToPublicKey(buyer.key.getPublicKey())
                                    .addBasicSigner());
        auto baseBuyerBalance = balanceHelper.loadBalance(buyer.key.getPublicKey(),
                                                           base);
        REQUIRE(baseBuyerBalance);
        auto quoteBuyerBalance = balanceHelper.
            loadBalance(buyer.key.getPublicKey(), quote);
        REQUIRE(quoteBuyerBalance);
        auto quoteAssetAmount = 10000 * ONE;
        fundAccount(quote, quoteAssetAmount, quoteBuyerBalance->getBalanceID());

        auto seller = Account{ SecretKey::random() , 0};
        createAccountTestHelper.applyTx(createAccountBuilder
                                    .setToPublicKey(seller.key.getPublicKey())
                                    .addBasicSigner());
        auto baseSellerBalance = balanceHelper.
            loadBalance(seller.key.getPublicKey(), base);
        REQUIRE(baseSellerBalance);
        auto quoteSellerBalance = balanceHelper.
            loadBalance(seller.key.getPublicKey(), quote);
        REQUIRE(quoteSellerBalance);
        auto baseAssetAmount = 1000 * ONE;
        fundAccount(base, baseAssetAmount, baseSellerBalance->getBalanceID());

        auto randomPrice = [&base, &quote, &testManager](bool isBuy)
        {
            std::vector<OfferFrame::pointer> offers;
            const int maxOrders = 10;
            testManager->getStorageHelper().getOfferHelper().loadBestOffers(maxOrders, 0, base, quote, 0, !isBuy, offers);
            if (offers.size() == maxOrders)
            {
                return offers[offers.size() - 1]->getPrice();
            }
            // to ensure that quote amount is >= 1
            return (rand() % INT16_MAX + ONE);
        };

        auto randomAmount = []()
        {
            // to ensure that base amount > 1;
            return (rand() % INT16_MAX + 1);
        };

        int64_t matchesLeft = 1000;

        // buyer and seller are placing ramdom orders untill one of them runs out of money
        while (matchesLeft > 0)
        {
            int64_t buyerAmount = randomAmount();
            int64_t buyerPrice = randomPrice(true);
            quoteBuyerBalance = balanceHelper.loadBalance(buyer.key.getPublicKey(),
                                                           quote);
            int64_t buyerOfferAmount = buyerAmount * buyerPrice;
            assert(buyerOfferAmount > 0);

            int64_t buyerFee = 0;
            REQUIRE(OfferExchange::setFeeToPay(buyerFee, bigDivide(buyerPrice,
                buyerAmount, int64_t(ONE), ROUND_UP), fee));

            if (quoteBuyerBalance->getAmount() < buyerOfferAmount + buyerFee)
            {
                quoteAssetAmount += buyerOfferAmount + buyerFee;
                assert(quoteAssetAmount > 0);
                fundAccount(quote, buyerOfferAmount + buyerFee, quoteBuyerBalance->getBalanceID());
            }

            auto offerResult = offerTestHelper.applyManageOffer(buyer, 0, baseBuyerBalance->
                getBalanceID(),
                quoteBuyerBalance->
                getBalanceID(), buyerAmount,
                buyerPrice, true, buyerFee);
            matchesLeft -= offerResult.success().offersClaimed.size();

            int64_t sellerAmount = randomAmount();
            baseSellerBalance = balanceHelper.
                loadBalance(seller.key.getPublicKey(), base);
            if (baseSellerBalance->getAmount() < sellerAmount)
            {
                baseAssetAmount += sellerAmount;
                assert(baseAssetAmount > 0);
                fundAccount(base, sellerAmount, baseSellerBalance->getBalanceID());
            }

            // to ensure that quote amount is >= 1
            int64_t sellerPrice = randomPrice(false);
            int64_t sellerFee = 0;
            REQUIRE(OfferExchange::setFeeToPay(sellerFee, bigDivide(sellerAmount
                , sellerPrice, int64_t(ONE), ROUND_UP), fee));
            offerResult = offerTestHelper.applyManageOffer(seller, 0,
                baseSellerBalance->getBalanceID(),
                quoteSellerBalance->getBalanceID(),
                sellerAmount, sellerPrice, false,
                sellerFee);
            matchesLeft -= offerResult.success().offersClaimed.size();
            LOG(INFO) << "matches left: " << matchesLeft;
        }

        auto offersByAccount = offerHelper.loadAllOffers();
        // delete all buyers offers
        auto buyersOffers = offersByAccount[buyer.key.getPublicKey()];
        for (auto buyerOffer : buyersOffers)
        {
            offerTestHelper.applyManageOffer(buyer, buyerOffer->getOfferID(),
                               baseBuyerBalance->getBalanceID(),
                               quoteBuyerBalance->getBalanceID(), 0, 1, true, 0);
        }

        // delete all seller offers
        auto sellerOffers = offersByAccount[seller.key.getPublicKey()];
        for (auto sellerOffer : sellerOffers)
        {
            offerTestHelper.applyManageOffer(seller, sellerOffer->getOfferID(),
                               baseSellerBalance->getBalanceID(),
                               quoteSellerBalance->getBalanceID(), 0, 1, false, 0);
        }

        offersByAccount = offerHelper.loadAllOffers();
        REQUIRE(offersByAccount.size() == 0);

        baseBuyerBalance = balanceHelper.loadBalance(buyer.key.getPublicKey(),
                                                      base);
        // there must be matches
        REQUIRE(baseBuyerBalance->getAmount() != 0);
        REQUIRE(baseBuyerBalance->getLocked() == 0);

        quoteBuyerBalance = balanceHelper.loadBalance(buyer.key.getPublicKey(),
                                                       quote);
        REQUIRE(quoteBuyerBalance->getLocked() == 0);

        baseSellerBalance = balanceHelper.loadBalance(seller.key.getPublicKey(),
                                                       base);
        REQUIRE(baseSellerBalance->getLocked() == 0);

        quoteSellerBalance = balanceHelper.loadBalance(seller.key.getPublicKey(),
                                                        quote);
        // there must be matches
        REQUIRE(quoteSellerBalance->getAmount() != 0);
        REQUIRE(quoteSellerBalance->getLocked() == 0);

        REQUIRE(baseBuyerBalance->getAmount() + baseSellerBalance->getAmount()
            == baseAssetAmount);

        auto comissionAccount = balanceHelper.
            loadBalance(app.getAdminID(), quote);
        REQUIRE(comissionAccount);
        REQUIRE(comissionAccount->getAmount() + quoteBuyerBalance->getAmount() +
            quoteSellerBalance->getAmount() == quoteAssetAmount);
    }
}
