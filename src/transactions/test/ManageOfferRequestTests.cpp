#include "ledger/BalanceHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test.h"
#include "test/test_marshaler.h"
#include "test_helper/CreateAccountTestHelper.h"
#include "test_helper/CreateManageOfferRequestTestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ManageAMLAlertTestHelper.h"
#include "test_helper/ManageAccountRoleTestHelper.h"
#include "test_helper/ManageAccountRuleTestHelper.h"
#include "test_helper/ManageAssetPairTestHelper.h"
#include "test_helper/ManageAssetTestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test_helper/ManageOfferTestHelper.h"
#include "test_helper/ReviewManageOfferTestHelper.h"
#include "transactions/dex/OfferExchange.h"

using namespace stellar;
using namespace stellar::txtest;

// Try setting each option to make sure it works
// try setting all at once
// try setting high threshold ones without the correct sigs
// make sure it doesn't allow us to add signers when we don't have the
// minbalance
TEST_CASE("manage offer request", "[tx][manage_offer_request]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    // set up world
    SecretKey root = getRoot();
    Salt rootSeq = 1;
    auto rootAccount = Account{root, rootSeq};

    // test helpers
    auto assetTestHelper = ManageAssetTestHelper(testManager);
    auto assetPairHelper = ManageAssetPairTestHelper(testManager);
    auto issuanceHelper = IssuanceRequestHelper(testManager);
    auto offerTestHelper = ManageOfferTestHelper(testManager);
    auto amlAlertHelper = ManageAMLAlertTestHelper(testManager);
    CreateAccountTestHelper createAccountTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    CreateManageOfferRequestTestHelper manageOfferRequestTestHelper(
        testManager);
    ReviewManageOfferRequestHelper reviewManageOfferRequestHelper(testManager);

    manageKeyValueHelper.assetOpWithoutReview();

    AssetCode base = "BTC";
    uint64_t baseType = 1;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, base, rootAccount,
                                int32(AssetPolicy::BASE_ASSET), nullptr, 6,
                                baseType);
    AssetCode quote = "USD";
    uint64_t quoteType = 2;
    assetTestHelper.createAsset(rootAccount, rootAccount.key, quote,
                                rootAccount, int32(AssetPolicy::BASE_ASSET),
                                nullptr, 6, quoteType);

    assetPairHelper.applyManageAssetPairTx(
        rootAccount, base, quote, 1, 0, 0,
        int32(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET));

    AccountRuleResource requestResource(LedgerEntryType::REVIEWABLE_REQUEST);
    requestResource.reviewableRequest().details.requestType(
        ReviewableRequestType::MANAGE_OFFER);
    requestResource.reviewableRequest().details.manageOffer().baseAssetCode =
        base;
    requestResource.reviewableRequest().details.manageOffer().baseAssetType =
        baseType;
    requestResource.reviewableRequest().details.manageOffer().quoteAssetCode =
        quote;
    requestResource.reviewableRequest().details.manageOffer().quoteAssetType =
        quoteType;
    requestResource.reviewableRequest().details.manageOffer().manageAction =
        UINT32_MAX;
    requestResource.reviewableRequest().details.manageOffer().isBuy = true;
    requestResource.reviewableRequest().details.manageOffer().orderBookID = 0;

    // buyer
    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, requestResource, AccountRuleAction::ANY, false);
    auto buyerRuleID =
        manageAccountRuleTestHelper
            .applyTx(rootAccount, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    // seller
    requestResource.reviewableRequest().details.manageOffer().isBuy = false;
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, requestResource, AccountRuleAction::ANY, false);
    auto sellerRuleID =
        manageAccountRuleTestHelper
            .applyTx(rootAccount, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    AccountRuleResource baseAssetResource(LedgerEntryType::ASSET);
    baseAssetResource.asset().assetType = baseType;
    baseAssetResource.asset().assetCode = base;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, baseAssetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
    auto baseRuleID =
        manageAccountRuleTestHelper
            .applyTx(rootAccount, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    AccountRuleResource txResource(LedgerEntryType::TRANSACTION);

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, txResource, AccountRuleAction::ANY, false);
    auto txRuleID =
        manageAccountRuleTestHelper
            .applyTx(rootAccount, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    AccountRuleResource quoteAssetResource(LedgerEntryType::ASSET);
    quoteAssetResource.asset().assetType = quoteType;
    quoteAssetResource.asset().assetCode = quote;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
        0, quoteAssetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
    auto quoteRuleID =
        manageAccountRuleTestHelper
            .applyTx(rootAccount, ruleEntry, ManageAccountRuleAction::CREATE)
            .success()
            .ruleID;

    auto createExchangeRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
        "{}", {txRuleID, buyerRuleID, sellerRuleID, baseRuleID, quoteRuleID});
    auto exchangeRoleID =
        manageAccountRoleTestHelper.applyTx(rootAccount, createExchangeRoleOp)
            .success()
            .roleID;
    // basic create account builder
    auto createAccountBuilder =
        CreateAccountTestBuilder().setSource(rootAccount).setRoleID(1);

    auto& balanceHelper = testManager->getStorageHelper().getBalanceHelper();
    auto& offerHelper = testManager->getStorageHelper().getOfferHelper();

    auto buyer = Account{SecretKey::random(), 0};
    createAccountTestHelper.applyTx(
        createAccountBuilder.setToPublicKey(buyer.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(exchangeRoleID));
    auto baseBuyerBalance =
        balanceHelper.loadBalance(buyer.key.getPublicKey(), base);
    REQUIRE(baseBuyerBalance);
    auto quoteBuyerBalance =
        balanceHelper.loadBalance(buyer.key.getPublicKey(), quote);
    REQUIRE(quoteBuyerBalance);

    auto quoteAssetAmount = 1000 * ONE;

    auto baseAssetAmount = 100 * ONE;

    auto price = bigDivide(quoteAssetAmount, ONE, baseAssetAmount, ROUND_UP);

    issuanceHelper.authorizePreIssuedAmount(rootAccount, rootAccount.key, quote,
                                            quoteAssetAmount, rootAccount);
    issuanceHelper.applyCreateIssuanceRequest(
        rootAccount, quote, quoteAssetAmount, quoteBuyerBalance->getBalanceID(),
        SecretKey::random().getStrKeyPublic());

    auto seller = Account{SecretKey::random(), 0};
    createAccountTestHelper.applyTx(
        createAccountBuilder.setToPublicKey(seller.key.getPublicKey())
            .addBasicSigner()
            .setRoleID(exchangeRoleID));
    auto baseSellerBalance =
        balanceHelper.loadBalance(seller.key.getPublicKey(), base);
    REQUIRE(baseSellerBalance);
    auto quoteSellerBalance =
        balanceHelper.loadBalance(seller.key.getPublicKey(), quote);
    REQUIRE(quoteSellerBalance);

    issuanceHelper.authorizePreIssuedAmount(rootAccount, rootAccount.key, base,
                                            baseAssetAmount, rootAccount);
    issuanceHelper.applyCreateIssuanceRequest(
        rootAccount, base, baseAssetAmount, baseSellerBalance->getBalanceID(),
        SecretKey::random().getStrKeyPublic());

    auto buyOp = offerTestHelper.manageOfferOp(
        0, baseBuyerBalance->getBalanceID(), quoteBuyerBalance->getBalanceID(),
        baseAssetAmount, price, true, 0);
    auto sellOp = offerTestHelper.manageOfferOp(
        0, baseSellerBalance->getBalanceID(),
        quoteSellerBalance->getBalanceID(), baseAssetAmount, price, false, 0);

    SECTION("Zero tasks")
    {
        uint32_t allTasks = 0;
        SECTION("All ok")
        {
            manageOfferRequestTestHelper.applyTx(buyer, buyOp, &allTasks);
            quoteBuyerBalance =
                loadBalance(quoteBuyerBalance->getBalanceID(), app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            baseBuyerBalance =
                loadBalance(baseBuyerBalance->getBalanceID(), app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == 0);

            manageOfferRequestTestHelper.applyTx(seller, sellOp, &allTasks);

            baseBuyerBalance =
                loadBalance(baseBuyerBalance->getBalanceID(), app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == baseAssetAmount);
        }
        SECTION("Invalid creator details")
        {

            longstring validDetails = "{ldkfjglkfdg}";

            auto result = manageOfferRequestTestHelper.applyTx(
                buyer, buyOp, &allTasks, &validDetails,
                CreateManageOfferRequestResultCode::INVALID_CREATOR_DETAILS);
        }

        SECTION("Valid creator details")
        {
            longstring validDetails = "{}";

            manageOfferRequestTestHelper.applyTx(buyer, buyOp, &allTasks,
                                                 &validDetails);
            quoteBuyerBalance =
                loadBalance(quoteBuyerBalance->getBalanceID(), app);
            REQUIRE(quoteBuyerBalance->getLocked() == quoteAssetAmount);
            REQUIRE(quoteBuyerBalance->getAmount() == 0);

            baseBuyerBalance =
                loadBalance(baseBuyerBalance->getBalanceID(), app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == 0);

            manageOfferRequestTestHelper.applyTx(seller, sellOp, &allTasks);

            baseBuyerBalance =
                loadBalance(baseBuyerBalance->getBalanceID(), app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == baseAssetAmount);
        }
    }

    SECTION("With tasks")
    {
        uint32_t allTasks = 1;
        uint32_t toAdd = 0, toRemove = 1;

        auto result =
            manageOfferRequestTestHelper.applyTx(buyer, buyOp, &allTasks);
        auto buyerRequestID = result.success().requestID;

        quoteBuyerBalance = loadBalance(quoteBuyerBalance->getBalanceID(), app);
        REQUIRE(quoteBuyerBalance->getLocked() == 0);
        REQUIRE(quoteBuyerBalance->getAmount() == quoteAssetAmount);

        result =
            manageOfferRequestTestHelper.applyTx(seller, sellOp, &allTasks);
        auto sellerRequestID = result.success().requestID;

        baseSellerBalance = loadBalance(baseSellerBalance->getBalanceID(), app);
        REQUIRE(baseSellerBalance->getLocked() == 0);
        REQUIRE(baseSellerBalance->getAmount() == baseAssetAmount);

        SECTION("All ok")
        {

            auto reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, buyerRequestID, ReviewRequestOpAction::APPROVE,
                    "", ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);

            REQUIRE(reviewResult.success().fulfilled);
            REQUIRE(reviewResult.success().typeExt.requestType() ==
                    ReviewableRequestType::MANAGE_OFFER);

            reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, sellerRequestID,
                    ReviewRequestOpAction::APPROVE, "",
                    ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);

            REQUIRE(reviewResult.success().fulfilled);
            REQUIRE(reviewResult.success().typeExt.requestType() ==
                    ReviewableRequestType::MANAGE_OFFER);

            //
            baseBuyerBalance =
                loadBalance(baseBuyerBalance->getBalanceID(), app);
            REQUIRE(baseBuyerBalance->getLocked() == 0);
            REQUIRE(baseBuyerBalance->getAmount() == baseAssetAmount);
        }

        SECTION("Delete offer")
        {
            quoteBuyerBalance =
                loadBalance(quoteBuyerBalance->getBalanceID(), app);
            REQUIRE(quoteBuyerBalance->getLocked() == 0);
            REQUIRE(quoteBuyerBalance->getAmount() == quoteAssetAmount);

            auto reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, buyerRequestID, ReviewRequestOpAction::APPROVE,
                    "", ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);

            auto offerID = reviewResult.success()
                               .typeExt.manageOfferResult()
                               .success()
                               .offer.offer()
                               .offerID;

            auto offer =
                testManager->getStorageHelper().getOfferHelper().loadOffer(
                    buyer.key.getPublicKey(), offerID,
                    ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID);
            REQUIRE(offer->getOffer().baseAmount == baseAssetAmount);

            buyOp.offerID = offerID;
            buyOp.amount = 0;

            result =
                manageOfferRequestTestHelper.applyTx(buyer, buyOp, &allTasks);
            buyerRequestID = result.success().requestID;

            reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, buyerRequestID, ReviewRequestOpAction::APPROVE,
                    "", ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);

            REQUIRE(reviewResult.success()
                        .typeExt.manageOfferResult()
                        .success()
                        .offer.effect() == ManageOfferEffect::DELETED);
        }

        SECTION("One of the requests is invalid")
        {

            auto reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, buyerRequestID, ReviewRequestOpAction::APPROVE,
                    "", ReviewRequestResultCode::SUCCESS, &toAdd, &toRemove);

            REQUIRE(reviewResult.success().fulfilled);
            REQUIRE(reviewResult.success().typeExt.requestType() ==
                    ReviewableRequestType::MANAGE_OFFER);

            amlAlertHelper.applyCreateAmlAlert(
                rootAccount, baseSellerBalance->getBalanceID(), baseAssetAmount,
                "Inalid", "", &toAdd);

            reviewResult =
                reviewManageOfferRequestHelper.applyReviewRequestTxWithTasks(
                    rootAccount, sellerRequestID,
                    ReviewRequestOpAction::APPROVE, "",
                    ReviewRequestResultCode::MANAGE_OFFER_FAILED, &toAdd,
                    &toRemove);

            REQUIRE(reviewResult.manageOfferCode() ==
                    ManageOfferResultCode::UNDERFUNDED);
        }
    }
}