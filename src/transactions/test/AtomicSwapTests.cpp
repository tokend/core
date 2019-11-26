#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include <transactions/test/test_helper/CreateASwapAskRequestTestHelper.h>
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/ManageAssetTestHelper.h>
#include <transactions/test/test_helper/ManageBalanceTestHelper.h>
#include <transactions/test/test_helper/ReviewASwapAskRequestTestHelper.h>
#include <transactions/test/test_helper/CancelASwapAskTestHelper.h>
#include <transactions/test/test_helper/CreateASwapBidRequestTestHelper.h>
#include <transactions/test/test_helper/ReviewASwapBidRequestTestHelper.h>
#include <transactions/test/test_helper/ManageKeyValueTestHelper.h>
#include <ledger/BalanceHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "test/test_marshaler.h"
#include "test/test.h"
#include "ledger/StorageHelper.h"

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
    CreateASwapAskRequestHelper aSwapAskRequestHelper(testManager);
    IssuanceRequestHelper issuanceTestHelper(testManager);
    ManageAssetTestHelper manageAssetTestHelper(testManager);
    ManageBalanceTestHelper manageBalanceTestHelper(testManager);
    ReviewASwapAskRequestHelper reviewASwapBidCreationRequestHelper(testManager);
    CancelASwapAskHelper cancelASwapAskHelper(testManager);
    CreateASwapBidRequestTestHelper createASwapBidRequestTestHelper(testManager);
    ReviewASwapBidRequestHelper reviewAswapRequestHelper(testManager);
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

    AccountRuleResource askResource(LedgerEntryType::ATOMIC_SWAP_ASK);
    askResource.atomicSwapAsk().assetCode = baseAsset;
    askResource.atomicSwapAsk().assetType = UINT64_MAX;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, askResource, AccountRuleAction::CREATE, false);
    auto baseAssetASwapBidCreationRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource issueResource(LedgerEntryType::REVIEWABLE_REQUEST);
    issueResource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ISSUANCE);
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, issueResource, AccountRuleAction::CREATE_WITH_TASKS, false);
    auto issuerRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource preIssueResource(LedgerEntryType::REVIEWABLE_REQUEST);
    preIssueResource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_PRE_ISSUANCE);
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, preIssueResource, AccountRuleAction::CREATE, false);
    auto preIssuerRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    AccountRuleResource updateAssetResource(LedgerEntryType::REVIEWABLE_REQUEST);
    updateAssetResource.reviewableRequest().details.requestType(ReviewableRequestType::UPDATE_ASSET);
    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, updateAssetResource, AccountRuleAction::CREATE, false);
    auto updateAssetRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, AccountRuleResource(LedgerEntryType::TRANSACTION), AccountRuleAction::SEND, false);
    auto txSendRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, assetResource, AccountRuleAction::ANY, false);
    auto baseAssetReceiverRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(
            0, AccountRuleResource(LedgerEntryType::BALANCE), AccountRuleAction::CREATE, false);
    auto ownBalanceCreationRuleID = manageAccountRuleTestHelper.applyTx(
            root, ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSellerAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"base_asset_seller"})", {baseAssetOwnerRuleID, ownBalanceCreationRuleID, preIssuerRuleID,
                                                baseAssetASwapBidCreationRuleID, txSendRuleID, issuerRuleID, updateAssetRuleID});
    auto sellerAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createSellerAccountRoleOp).success().roleID;

    auto createReceiverAccountRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            R"({"name":"usd_receiver"})", {baseAssetReceiverRuleID, ownBalanceCreationRuleID, txSendRuleID});
    auto receiverAccountRoleID = manageAccountRoleTestHelper.applyTx(
            root, createReceiverAccountRoleOp).success().roleID;

    // db helpers
    auto& balanceHelper =testManager->getStorageHelper().getBalanceHelper();

    auto createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(sellerPubKey)
            .addBasicSigner()
            .setRoleID(sellerAccountRoleID);
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(firstBuyerPubKey)
            .addBasicSigner()
            .setRoleID(receiverAccountRoleID);
    createAccountHelper.applyTx(createAccountTestBuilder);

    createAccountTestBuilder = CreateAccountTestBuilder()
            .setSource(root)
            .setToPublicKey(secondBuyerPubKey)
            .addBasicSigner()
            .setRoleID(receiverAccountRoleID);
    createAccountHelper.applyTx(createAccountTestBuilder);

    manageKeyValueHelper.assetOpWithoutReview();
    longstring key = ManageKeyValueOpFrame::makeAtomicSwapAskTasksKey();
    manageKeyValueHelper.setKey(key)->setUi32Value(1);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

    // create base asset
    uint64_t  baseAssetAmount = (INT64_MAX - (INT64_MAX % ONE)) / 100;
    issuanceTestHelper.createAssetWithPreIssuedAmount(seller, baseAsset,
                                                      baseAssetAmount, root, 6, 1);
    manageAssetTestHelper.updateAsset(seller, baseAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP));

    // create quote assets
    manageAssetTestHelper.createAsset(root, root.key, firstQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    manageAssetTestHelper.createAsset(root, root.key, secondQuoteAsset, root,
              static_cast<uint32_t>(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP));

    AtomicSwapAskQuoteAsset firstASwapQuoteAsset(firstQuoteAsset, 10 * ONE, LedgerVersion::EMPTY_VERSION);

    AtomicSwapAskQuoteAsset secondASwapQuoteAsset(secondQuoteAsset,
            ((INT64_MAX - (INT64_MAX % ONE)) / 100), LedgerVersion::EMPTY_VERSION);

    std::vector<AtomicSwapAskQuoteAsset> quoteAssets =
            {firstASwapQuoteAsset, secondASwapQuoteAsset};

    // fund seller account
    manageBalanceTestHelper.createBalance(seller, sellerPubKey, baseAsset);
    auto sellerBalance = balanceHelper.loadBalance(sellerPubKey, baseAsset);
    REQUIRE(!!sellerBalance);
    auto sellerBalanceID = sellerBalance->getBalanceID();

    uint32_t issuanceTasks = 0;
    issuanceTestHelper.applyCreateIssuanceRequest(seller, baseAsset,
          baseAssetAmount, sellerBalanceID, "Some reference", &issuanceTasks);

    std::string details = R"({"details":"Tickets for conference"})";

    SECTION("Invalid amount")
    {
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID, 0, details,
                                              quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::INVALID_AMOUNT);
    }

    SECTION("Invalid price")
    {
        quoteAssets.emplace_back("BTC", 0, LedgerVersion::EMPTY_VERSION);
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID, baseAssetAmount,
                                              details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::INVALID_PRICE);
    }

    SECTION("Invalid details")
    {
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID, baseAssetAmount,
                                              "Invalid details", quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::INVALID_DETAILS);
    }

    SECTION("Base asset cannot be swapped")
    {
        manageAssetTestHelper.updateAsset(seller, baseAsset, root, 0);
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID, baseAssetAmount,
                                              details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
    }

    SECTION("Quote asset not found")
    {
        quoteAssets.emplace_back("BTC", ONE, LedgerVersion::EMPTY_VERSION);
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID,
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND);
    }

    SECTION("Quote asset cannot be swapped")
    {
        auto thirdASwapQuoteAsset = AtomicSwapAskQuoteAsset();
        thirdASwapQuoteAsset.quoteAsset = "BTC";
        thirdASwapQuoteAsset.price = ONE;
        quoteAssets.emplace_back(thirdASwapQuoteAsset);
        manageAssetTestHelper.createAsset(root, root.key,
                                          thirdASwapQuoteAsset.quoteAsset,
                                          root, 0);
        manageBalanceTestHelper.createBalance(seller, sellerPubKey,
                                              thirdASwapQuoteAsset.quoteAsset);
        auto request = aSwapAskRequestHelper.
                createASwapAskCreationRequest(sellerBalanceID,
                                              baseAssetAmount,
                                              details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
    }

    SECTION("Base asset not found")
    {
        auto absentBalanceID = SecretKey::random().getPublicKey();
        auto request = aSwapAskRequestHelper.createASwapAskCreationRequest(
                absentBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_NOT_FOUND,
                OperationResultCode::opNO_ENTRY);
    }

    SECTION("Base and quote assets are equal")
    {
        auto sameQuoteAsset = AtomicSwapAskQuoteAsset();
        sameQuoteAsset.quoteAsset = baseAsset;
        sameQuoteAsset.price = ONE;
        quoteAssets.push_back(sameQuoteAsset);
        auto request = aSwapAskRequestHelper.createASwapAskCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::ASSETS_ARE_EQUAL);
    }

    SECTION("Base balance underfunded")
    {
        uint64_t tooBigAmount = baseAssetAmount + 1;
        auto request = aSwapAskRequestHelper.createASwapAskCreationRequest(
                sellerBalanceID, tooBigAmount, details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_UNDERFUNDED);
    }

    SECTION("Invalid quote asset")
    {
        AtomicSwapAskQuoteAsset invalidQuoteAsset;
        invalidQuoteAsset.quoteAsset = "";
        invalidQuoteAsset.price = ONE;
        quoteAssets.push_back(invalidQuoteAsset);
        auto request = aSwapAskRequestHelper.createASwapAskCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller, request,
                CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET);
    }

    SECTION("Atomic swap ask creation request created")
    {
        auto request = aSwapAskRequestHelper.createASwapAskCreationRequest(
                sellerBalanceID, baseAssetAmount, details, quoteAssets);
        auto creationResult = aSwapAskRequestHelper.applyCreateASwapAskCreationRequest(
                seller,
                request);
        auto requestID = creationResult.success().requestID;

        SECTION("Try to remove asset")
        {
            manageAssetTestHelper.applyRemoveAssetTx(
                root, baseAsset, nullptr, RemoveAssetResultCode::HAS_PENDING_MOVEMENTS);
        }

        SECTION("Try review atomic swap ask creation request")
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

            SECTION("Atomic swap ask created (by autoapprove)")
            {
                auto result = reviewASwapBidCreationRequestHelper.applyReviewRequestTxWithTasks(
                        root, requestID, ReviewRequestOpAction::APPROVE, "", 1);

                auto askID = result.success().typeExt.atomicSwapAskExtended().askID;

                SECTION("Try to cancel foreign atomic swap ask")
                {
                    cancelASwapAskHelper.applyCancelASwapBid(root, askID,
                            CancelAtomicSwapAskResultCode::NOT_FOUND);
                }

                SECTION("Cancel ask without any atomic swap requests")
                {
                    auto cancelResult = cancelASwapAskHelper.applyCancelASwapBid(seller, askID);
                    REQUIRE(cancelResult.success().lockedAmount == 0);
                }

                SECTION("Try create swap request for buyers")
                {
                    uint64_t amountToBuy = 5 * ONE;

                    SECTION("Ask not found")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        0, firstQuoteAsset, amountToBuy);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND);
                    }

                    SECTION("Try to create aswap request for own ask")
                    {
                        auto aSwapRequest = createASwapBidRequestTestHelper.createASwapRequestOp(
                                askID, firstQuoteAsset, amountToBuy);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                seller, aSwapRequest,
                                CreateAtomicSwapBidRequestResultCode::SOURCE_ACCOUNT_EQUALS_ASK_OWNER);
                    }

                    SECTION("Invalid base amount")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, firstQuoteAsset, 0);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapBidRequestResultCode::INVALID_BASE_AMOUNT);
                    }

                    SECTION("Invalid quote asset")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, "", amountToBuy);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest, CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET);
                    }

                    SECTION("Ask has not such quote asset")
                    {
                        manageAssetTestHelper.createAsset(root, root.key, "VLT", root, 0);

                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, "VLT", amountToBuy);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND);
                    }

                    SECTION("Atomic swap ask overflow")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, secondQuoteAsset, INT64_MAX);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapBidRequestResultCode::QUOTE_AMOUNT_OVERFLOWS);
                    }

                    SECTION("Ask underfunded")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, firstQuoteAsset, baseAssetAmount + 1);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapBidRequestResultCode::ASK_UNDERFUNDED);
                    }

                    SECTION("Atomic swap tasks not found")
                    {
                        auto aSwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, firstQuoteAsset, amountToBuy);
                        createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                firstBuyer, aSwapRequest,
                                CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND);
                    }

                    SECTION("Atomic swap requests created")
                    {
                        longstring key = ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey("*");
                        manageKeyValueHelper.setKey(key)->setUi32Value(2);
                        manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

                        auto firstBuyerASwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, firstQuoteAsset, amountToBuy);

                        auto firstBuyerASwapRequestID =
                                createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                        firstBuyer, firstBuyerASwapRequest).success().requestID;

                        auto secondBuyerASwapRequest =
                                createASwapBidRequestTestHelper.createASwapRequestOp(
                                        askID, secondQuoteAsset, amountToBuy);

                        auto secondBuyerASwapRequestID =
                                createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                secondBuyer, secondBuyerASwapRequest).success().requestID;

                        SECTION("Try to cancel atomic swap bid with aswap requests")
                        {
                            auto cancelResult = cancelASwapAskHelper.applyCancelASwapBid(seller, askID);
                            REQUIRE(cancelResult.success().lockedAmount == amountToBuy*2);

                            SECTION("Reject all aswap requests")
                            {
                                auto res = reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, firstBuyerASwapRequestID,
                                        ReviewRequestOpAction::PERMANENT_REJECT,
                                        R"({"reason":"invalid aswap request"})");

                                REQUIRE(res.success().typeExt.atomicSwapBidExtended().bidOwnerBaseBalanceID == BalanceID());

                                res = reviewAswapRequestHelper.applyReviewRequestTx(
                                        root, secondBuyerASwapRequestID,
                                        ReviewRequestOpAction::PERMANENT_REJECT,
                                        R"({"reason":"invalid aswap request"})");

                                REQUIRE(res.success().typeExt.atomicSwapBidExtended().bidOwnerBaseBalanceID == BalanceID());

                                SECTION("Bid is removed, cannot create atomic swap request")
                                {
                                    createASwapBidRequestTestHelper.applyCreateASwapRequest(
                                            secondBuyer, secondBuyerASwapRequest,
                                            CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND,
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