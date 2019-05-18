#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/CreateASwapBidCreationRequestTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageBalanceTestHelper.h>
#include <transactions/test/test_helper/ReviewASwapBidCreationRequestTestHelper.h>
#include <transactions/test/test_helper/CancelASwapBidTestHelper.h>
#include <transactions/test/test_helper/CreateASwapReviewableRequestTestHelper.h>
#include <transactions/test/test_helper/ReviewAswapRequestTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "test/test_marshaler.h"
#include "test/test.h"

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
    ReviewASwapBidCreationRequestHelper reviewASwapBidCreationRequestHelper(testManager);
    CancelASwapBidHelper cancelASwapBidHelper(testManager);
    CreateASwapReviewableRequestTestHelper createASwapReviewableRequestTestHelper(testManager);
    ReviewASwapRequestHelper reviewAswapRequestHelper(testManager);
    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);

    // create seller and buyer accounts
    auto root = Account{getRoot(), Salt(0)};
    auto seller = Account{SecretKey::random(), Salt(1)};
    auto firstBuyer = Account{SecretKey::random(), Salt(1)};
    auto secondBuyer = Account{SecretKey::random(), Salt(1)};
    auto sellerPubKey = seller.key.getPublicKey();
    auto firstBuyerPubKey = firstBuyer.key.getPublicKey();
    auto secondBuyerPubKey = secondBuyer.key.getPublicKey();

    AssetCode baseAsset = "DL0TICKETS";
    AssetCode firstQuoteAsset = "XRP";
    AssetCode secondQuoteAsset = "LTC";

    // create roles and rules
    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetCode = baseAsset;
    assetResource.asset().assetType = UINT64_MAX;

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, assetResource, AccountRuleAction::ANY, false);
    auto baseAssetOwnerRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource bidResource(LedgerEntryType::ATOMIC_SWAP_BID);
    bidResource.atomicSwapBid().assetCode = baseAsset;
    bidResource.atomicSwapBid().assetType = UINT64_MAX;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, bidResource, AccountRuleAction::CREATE, false);
    auto baseAssetASwapBidCreationRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, assetResource, AccountRuleAction::RECEIVE_ISSUANCE, false);
    auto baseAssetReceiverRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, AccountRuleResource(LedgerEntryType::BALANCE), AccountRuleAction::CREATE, false);
    auto ownBalanceCreationRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSellerAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"base_asset_seller"})", {baseAssetOwnerRuleID, ownBalanceCreationRuleID, baseAssetASwapBidCreationRuleID});
    auto sellerAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createSellerAccountRoleOp).success().roleID;

    auto createReceiverAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_receiver"})", {baseAssetReceiverRuleID, ownBalanceCreationRuleID});
    auto receiverAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createReceiverAccountRoleOp).success().roleID;

    // db helpers
    auto balanceHelper = BalanceHelperLegacy::Instance();

    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(sellerPubKey)
            .addBasicSigner()
            .setRoleID(1);
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(firstBuyerPubKey)
            .addBasicSigner()
            .setRoleID(1);
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(secondBuyerPubKey)
            .addBasicSigner()
            .setRoleID(1);
    createAccountHelper.applyTx(createAccountTestBuilder);

    manageKeyValueHelper.assetOpWithoutReview();
    longstring key = ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey();
    manageKeyValueHelper.setKey(key)->setUi32Value(1);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    // create base asset
    uint64_t  baseAssetAmount = INT64_MAX - (INT64_MAX % ONE);
    issuanceTestHelper.createAssetWithPreIssuedAmount(seller, baseAsset,
                                                      baseAssetAmount, root, 6, 1);
    manageAssetTestHelper.updateAsset(seller, baseAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP));

    // create quote assets
    manageAssetTestHelper.createAsset(root, root.key, firstQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    manageAssetTestHelper.createAsset(root, root.key, secondQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    auto firstASwapQuoteAsset = AtomicSwapBidQuoteAsset();
    firstASwapQuoteAsset.quoteAsset = firstQuoteAsset;
    firstASwapQuoteAsset.price = 10 * ONE;

    auto secondASwapQuoteAsset = AtomicSwapBidQuoteAsset();
    secondASwapQuoteAsset.quoteAsset = secondQuoteAsset;
    secondASwapQuoteAsset.price = (INT64_MAX - (INT64_MAX % ONE)) / 100;

    std::vector<AtomicSwapBidQuoteAsset> quoteAssets =
            {firstASwapQuoteAsset, secondASwapQuoteAsset};

    // fund seller account
    manageBalanceTestHelper.createBalance(seller, sellerPubKey, baseAsset);
    auto sellerBalance = balanceHelper->loadBalance(sellerPubKey, baseAsset,
                                                    db, nullptr);
    REQUIRE(!!sellerBalance);
    auto sellerBalanceID = sellerBalance->getBalanceID();

    uint32_t issuanceTasks = 0;
    issuanceTestHelper.applyCreateIssuanceRequest(seller, baseAsset,
          baseAssetAmount, sellerBalanceID, "Some reference", &issuanceTasks);

    std::string details = R"({"details":"Tickets for conference"})";

    SECTION("Invalid amount")
    {
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, 0, details,
                                              quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::INVALID_AMOUNT);
    }

    SECTION("Invalid price")
    {
        auto thirdASwapQuoteAsset = AtomicSwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = 0;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::INVALID_PRICE);
    }

    SECTION("Invalid details")
    {
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                              "Invalid details", quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::INVALID_DETAILS);
    }

    SECTION("Base asset cannot be swapped")
    {
        manageAssetTestHelper.updateAsset(seller, baseAsset, root, 0);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID, baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
    }

    SECTION("Quote asset not found")
    {
        auto thirdASwapQuoteAsset = AtomicSwapBidQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = ONE;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.
                createASwapBidCreationRequest(sellerBalanceID,
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND);
    }

    SECTION("Quote asset cannot be swapped")
    {
        auto thirdASwapQuoteAsset = AtomicSwapBidQuoteAsset();
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
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
    }

    SECTION("Base asset not found")
    {
        auto absentBalanceID = SecretKey::random().getPublicKey();
        auto request = aSwapBidCreationRequestHelper.createASwapBidCreationRequest(
                absentBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::BASE_BALANCE_NOT_FOUND,
                OperationResultCode::opNO_ENTRY);
    }

    SECTION("Base and quote assets are equal")
    {
        auto sameQuoteAsset = AtomicSwapBidQuoteAsset();
        sameQuoteAsset.quoteAsset = baseAsset;
        sameQuoteAsset.price = ONE;
        quoteAssets.push_back(sameQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.createASwapBidCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::ASSETS_ARE_EQUAL);
    }

    SECTION("Base balance underfunded")
    {
        uint64_t tooBigAmount = baseAssetAmount + 1;
        auto request = aSwapBidCreationRequestHelper.createASwapBidCreationRequest(
                sellerBalanceID, tooBigAmount, details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::BASE_BALANCE_UNDERFUNDED);
    }

    SECTION("Invalid quote asset")
    {
        AtomicSwapBidQuoteAsset invalidQuoteAsset;
        invalidQuoteAsset.quoteAsset = "";
        invalidQuoteAsset.price = ONE;
        quoteAssets.push_back(invalidQuoteAsset);
        auto request = aSwapBidCreationRequestHelper.createASwapBidCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(
                seller, request,
                CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET);
    }

    SECTION("Atomic swap bid creation request created")
    {
        auto request = aSwapBidCreationRequestHelper.createASwapBidCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        auto creationResult = aSwapBidCreationRequestHelper.applyCreateASwapBidCreationRequest(seller,
                                                                                               request);
        auto requestID = creationResult.success().requestID;

        SECTION("Try review atomic swap bid creation request")
        {
            SECTION("Base asset can not be swapped anymore")
            {
                manageAssetTestHelper.updateAsset(seller, baseAsset, root, 0);
                reviewASwapBidCreationRequestHelper.applyReviewRequestTxWithTasks(
                        root, requestID, ReviewRequestOpAction::APPROVE, "", 1,
                        ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
            }

            SECTION("Reject atomic swap bid creation request")
            {
                reviewASwapBidCreationRequestHelper.applyReviewRequestTx(
                        root, requestID, ReviewRequestOpAction::PERMANENT_REJECT,
                        R"({"reason":"bad BTC address"})");
            }

            SECTION("Atomic swap bid created (by autoapprove)")
            {
                auto result = reviewASwapBidCreationRequestHelper.applyReviewRequestTxWithTasks(
                        root, requestID, ReviewRequestOpAction::APPROVE, "", 1);

                auto bidID = result.success().typeExt.atomicSwapBidExtended().bidID;

                SECTION("Try to cancel foreign atomic swap bid")
                {
                    cancelASwapBidHelper.applyCancelASwapBid(root, bidID,
                                                             CancelAtomicSwapBidResultCode::NOT_FOUND);
                }

                SECTION("Cancel bid without any atomic swap requests")
                {
                    auto cancelResult = cancelASwapBidHelper.applyCancelASwapBid(seller, bidID);
                    REQUIRE(cancelResult.success().lockedAmount == 0);
                }

                SECTION("Try create swap request for buyers")
                {
                    uint64_t amountToBuy = 5 * ONE;

                    SECTION("Bid not found")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        0, firstQuoteAsset, amountToBuy);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapAskRequestResultCode::BID_NOT_FOUND);
                    }

                    SECTION("Try to create aswap request for own bid")
                    {
                        auto aSwapRequest = createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                bidID, firstQuoteAsset, amountToBuy);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                seller, aSwapRequest,
                                CreateAtomicSwapAskRequestResultCode::SOURCE_ACCOUNT_EQUALS_BID_OWNER);
                    }

                    SECTION("Invalid base amount")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, firstQuoteAsset, 0);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapAskRequestResultCode::INVALID_BASE_AMOUNT);
                    }

                    SECTION("Invalid quote asset")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, "", amountToBuy);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET);
                    }

                    SECTION("Bid has not such quote asset")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, "VLT", amountToBuy);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND);
                    }

                    SECTION("Atomic swap bid overflow")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, secondQuoteAsset, INT64_MAX);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapAskRequestResultCode::QUOTE_AMOUNT_OVERFLOWS);
                    }

                    SECTION("Bid underfunded")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, firstQuoteAsset, baseAssetAmount + 1);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapAskRequestResultCode::BID_UNDERFUNDED);
                    }

                    SECTION("Atomic swap tasks not found")
                    {
                        auto aSwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, firstQuoteAsset, amountToBuy);
                        createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND);
                    }

                    SECTION("Atomic swap requests created")
                    {
                        longstring key = ManageKeyValueOpFrame::makeAtomicSwapTasksKey();
                        manageKeyValueHelper.setKey(key)->setUi32Value(2);
                        manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

                        auto firstBuyerASwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, firstQuoteAsset, amountToBuy);

                        auto firstBuyerASwapRequestID =
                                createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                        firstBuyer, firstBuyerASwapRequest).success().requestID;

                        auto secondBuyerASwapRequest =
                                createASwapReviewableRequestTestHelper.createASwapRequestOp(
                                        bidID, secondQuoteAsset, amountToBuy);

                        auto secondBuyerASwapRequestID =
                                createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                secondBuyer, secondBuyerASwapRequest).success().requestID;

                        SECTION("Try to cancel atomic swap bid with aswap requests")
                        {
                            auto cancelResult = cancelASwapBidHelper.applyCancelASwapBid(seller, bidID);
                            REQUIRE(cancelResult.success().lockedAmount == amountToBuy*2);

                            SECTION("Reject all aswap requests")
                            {
                                reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, firstBuyerASwapRequestID,
                                        ReviewRequestOpAction::PERMANENT_REJECT,
                                        R"({"reason":"invalid aswap request"})");
                                reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, secondBuyerASwapRequestID,
                                        ReviewRequestOpAction::PERMANENT_REJECT,
                                        R"({"reason":"invalid aswap request"})");

                                SECTION("Bid is removed, cannot create atomic swap request")
                                {
                                    createASwapReviewableRequestTestHelper.applyCreateASwapRequest(
                                            secondBuyer, secondBuyerASwapRequest,
                                            CreateAtomicSwapAskRequestResultCode::BID_NOT_FOUND,
                                            OperationResultCode::opNO_ENTRY);
                                }
                            }

                            SECTION("Approve all aswap requests")
                            {
                                reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, firstBuyerASwapRequestID,
                                        ReviewRequestOpAction::APPROVE,
                                        "");
                                reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, secondBuyerASwapRequestID,
                                        ReviewRequestOpAction::APPROVE,
                                        "");
                            }
                        }
                    }
                }
            }
        }
    }

}