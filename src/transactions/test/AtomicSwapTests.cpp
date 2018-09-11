#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/CreateASwapBidCreationRequestTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <ledger/BalanceHelper.h>
#include <transactions/test/test_helper/ManageBalanceTestHelper.h>
#include "test_helper/TxHelper.h"
#include "test/test_marshaler.h"
#include "main/test.h"
#include "TxTests.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("atomic swap", "[tx][atomic_swap]")
{
    Config const &cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application &app = *appPtr;
    app.start();
    TestManager::upgradeToCurrentLedgerVersion(app);
    auto testManager = TestManager::make(app);
    Database &db = testManager->getDB();

    // test helpers
    CreateAccountTestHelper createAccountHelper(testManager);
    CreateASwapBidCreationRequestHelper aSwapBidCreationRequestHelper(testManager);
    IssuanceRequestHelper issuanceTestHelper(testManager);
    ManageAssetTestHelper manageAssetTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);

    // db helpers
    auto balanceHelper = BalanceHelper::Instance();

    // create seller and buyer accounts
    auto root = Account{getRoot(), Salt(0)};
    auto seller = Account{SecretKey::random(), Salt(1)};
    auto firstBuyer = Account{SecretKey::random(), Salt(1)};
    auto secondBuyer = Account{SecretKey::random(), Salt(1)};
    auto sellerPubKey = seller.key.getPublicKey();
    auto firstBuyerPubKey = firstBuyer.key.getPublicKey();
    auto secondBuyerPubKey = secondBuyer.key.getPublicKey();

    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(sellerPubKey)
            .setType(AccountType::SYNDICATE)
            .setRecovery(SecretKey::random().getPublicKey());
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(firstBuyerPubKey)
            .setType(AccountType::NOT_VERIFIED)
            .setRecovery(SecretKey::random().getPublicKey());
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(secondBuyerPubKey)
            .setType(AccountType::NOT_VERIFIED)
            .setRecovery(SecretKey::random().getPublicKey());
    createAccountHelper.applyTx(createAccountTestBuilder);

    // create base asset
    AssetCode baseAsset = "DL0TICKETS";
    issuanceTestHelper.createAssetWithPreIssuedAmount(seller, baseAsset,
                                                      INT64_MAX, root);
    manageAssetTestHelper.updateAsset(seller, baseAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP));

    // create quote assets
    AssetCode firstQuoteAsset = "XRP";
    manageAssetTestHelper.createAsset(root, root.key, firstQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    AssetCode secondQuoteAsset = "LTC";
    manageAssetTestHelper.createAsset(root, root.key, secondQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    auto firstASwapQuoteAsset = ASwapBidQuoteAsset();
    firstASwapQuoteAsset.quoteAsset = firstQuoteAsset;
    firstASwapQuoteAsset.price = 10 * ONE;

    auto secondASwapQuoteAsset = ASwapBidQuoteAsset();
    secondASwapQuoteAsset.quoteAsset = secondQuoteAsset;
    secondASwapQuoteAsset.price = 20 * ONE;

    std::vector<ASwapBidQuoteAsset> quoteAssets =
            {firstASwapQuoteAsset, secondASwapQuoteAsset};

    // fund seller account
    manageBalanceTestHelper.createBalance(seller, sellerPubKey, baseAsset);
    auto sellerBalance = balanceHelper->loadBalance(sellerPubKey, baseAsset,
                                                    db, nullptr);
    REQUIRE(!!sellerBalance);
    auto sellerBalanceID = sellerBalance->getBalanceID();

    uint32_t issuanceTasks = 0;
    uint64_t  baseAssetAmount = 10 * ONE;
    issuanceTestHelper.applyCreateIssuanceRequest(seller, baseAsset,
          baseAssetAmount, sellerBalanceID, "Some reference", &issuanceTasks);

    std::string details = "{\"details\":\"Tickets for conference\"}";

    SECTION("Invalid amount")
    {
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, 0, details,
                                              quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
             request, CreateASwapBidCreationRequestResultCode::INVALID_AMOUNT);
    }

    SECTION("Invalid price")
    {
        auto thirdASwapQuoteAsset = ASwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = 0;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                     details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
             request, CreateASwapBidCreationRequestResultCode::INVALID_PRICE);
    }

    SECTION("Invalid details")
    {
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                              "Invalid details", quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
             request, CreateASwapBidCreationRequestResultCode::INVALID_DETAILS);
    }

    SECTION("Atomic swap bid overflow")
    {
        auto thirdASwapQuoteAsset = ASwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = INT64_MAX;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
            request,
            CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW);
    }

    SECTION("Only asset owner can create bid")
    {
        AssetCode fakeBaseAsset = "FAKE0TICKETS";
        manageAssetTestHelper.createAsset(root, root.key, fakeBaseAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP));
        manageBalanceTestHelper.createBalance(seller, sellerPubKey,
                                              fakeBaseAsset);
        auto fakeSellerBalance = balanceHelper->loadBalance(sellerPubKey,
                fakeBaseAsset, db, nullptr);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(fakeSellerBalance->getBalanceID(),
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
         request,
         CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND);
    }

    SECTION("Base asset cannot be swapped")
    {
        AssetCode fakeBaseAsset = "FAKE0TICKETS";
        manageAssetTestHelper.createAsset(seller, root.key, fakeBaseAsset,
                                          root, 0);
        manageBalanceTestHelper.createBalance(seller, sellerPubKey,
                                              fakeBaseAsset);
        auto fakeSellerBalance = balanceHelper->loadBalance(sellerPubKey,
                                                            fakeBaseAsset, db,
                                                            nullptr);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(fakeSellerBalance->getBalanceID(),
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
         request,
         CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
    }

    SECTION("Quote asset not found")
    {
        auto thirdASwapQuoteAsset = ASwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = ONE;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID,
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
         request,
         CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND);
    }

    SECTION("Quote asset cannot be swapped")
    {
        auto thirdASwapQuoteAsset = ASwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = ONE;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        manageAssetTestHelper.createAsset(root, root.key,
                                          thirdASwapQuoteAsset.quoteAsset,
                                          root, 0);
        manageBalanceTestHelper.createBalance(seller, sellerPubKey,
                                              thirdASwapQuoteAsset.quoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID,
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
        request,
        CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
    }
}