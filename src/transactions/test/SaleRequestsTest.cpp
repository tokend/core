#include <ledger/OfferHelper.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/managers/FeeManager.h>
#include <ledger/FeeHelper.h>
#include <transactions/test/test_helper/ManageAccountRuleTestHelper.h>
#include <transactions/test/test_helper/ManageAccountRoleTestHelper.h>
#include "ledger/AssetHelperLegacy.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test.h"
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


TEST_CASE("Sale Requests", "[tx][sale_requests]")
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
            baseAssetResource, AccountRuleAction::ANY, false);
    auto baseAssetOwnerRuleID = manageAccountRuleTestHelper.applyTx(root,
            ruleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

    auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp(
            "{}", {baseAssetOwnerRuleID});
    auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root,
            createSyndicateRoleOp).success().roleID;

    // basic account builder
    auto createAccountBuilder = CreateAccountTestBuilder()
            .setSource(root);

    auto syndicate = Account{ SecretKey::random(), 0 };
    auto syndicatePubKey = syndicate.key.getPublicKey();
    createAccountTestHelper.applyTx(createAccountBuilder
                                            .setToPublicKey(syndicatePubKey)
                                            .addBasicSigner()
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
        SECTION("Update sale request")
        {
            saleRequest.endTime++;
            saleRequestHelper.applyCreateSaleRequest(syndicate, requestID, saleRequest, nullptr);
            // sale request must endup with higher sequence
            saleRequest.sequenceNumber++;
            auto requestAfterUpdate =
                ReviewableRequestHelperLegacy::Instance()->loadRequest(requestID, db,
                                                                 nullptr);
            REQUIRE(requestAfterUpdate);
            REQUIRE(requestAfterUpdate->getRequestEntry()
                        .body.saleCreationRequest() == saleRequest);
        }
        SECTION("Success cancel sale request")
        {
            saleRequestHelper.applyCancelSaleRequest(syndicate, requestID);

            SECTION("Already canceled")
            {
                saleRequestHelper.applyCancelSaleRequest(syndicate, requestID,
                      CancelSaleCreationRequestResultCode::REQUEST_NOT_FOUND,
                      OperationResultCode::opNO_ENTRY);
            }
        }

        auto newSyndicate = Account{ SecretKey::random(), 0 };
        auto newSyndicatePubKey = newSyndicate.key.getPublicKey();

        auto createAccountTestBuilder = CreateAccountTestBuilder()
                .setSource(root)
                .setToPublicKey(newSyndicatePubKey)
                .addBasicSigner();

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
        auto participantsFeeFrame = FeeFrame::create(FeeType::INVEST_FEE, 0, int64_t(1 * ONE), quoteAsset, nullptr, precision);
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
        auto fee = setFeesTestHelper.createFeeEntry(FeeType::INVEST_FEE, quoteAsset, 0, 2 * ONE,
                nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);
        fee = setFeesTestHelper.createFeeEntry(FeeType::CAPITAL_DEPLOYMENT_FEE, quoteAsset, 0, 1 * ONE,
                                               nullptr, nullptr, FeeFrame::SUBTYPE_ANY, 0, maxNonDividedAmount);
        setFeesTestHelper.applySetFeesTx(root, &fee, false);

        saleRequest.hardCap = 200 * ONE;
        saleRequest.softCap = 100 * ONE;
        uint64_t feeToPayBySyndicate(2 * ONE);
        uint64_t feeToPay(4 * ONE);

        auto result = saleRequestHelper.createApprovedSale(root, syndicate, saleRequest);
        auto saleID = result.success().typeExt.saleExtended().saleID;
        participationHelper.addNewParticipant(root, saleID, baseAsset, quoteAsset, saleRequest.hardCap, price, feeToPay);

        checkStateHelper.applyCheckSaleStateTx(root, saleID);

        auto commissionBalance = BalanceHelperLegacy::Instance()->loadBalance(app.getAdminID(),  quoteAsset, db, nullptr);
        REQUIRE(!!commissionBalance);
        REQUIRE(commissionBalance->getAmount() == feeToPay + feeToPayBySyndicate);
    }

    SECTION("Create sale with predefined required base asset amount for hard cap") {
        auto basicSaleType = SaleType::BASIC_SALE;
        SECTION("Insufficient max issaunce") {
            auto requiredBaseAssetForHardCap = maxIssuanceAmount + (5 * ONE);
            hardCap = static_cast<const uint64_t>(bigDivide(requiredBaseAssetForHardCap, price, ONE, ROUND_DOWN));
            softCap = hardCap / 2;
            saleRequest = saleRequestHelper.createSaleRequest(baseAsset, quoteAsset, currentTime,
                                                              endTime, softCap, hardCap, "{}",
                                                              { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)},
                                                              requiredBaseAssetForHardCap);
            auto requestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr, 
                CreateSaleCreationRequestResultCode::INSUFFICIENT_MAX_ISSUANCE);
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
        SECTION("Global rule required")
        {
            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_REQUIRED);
        }
        SECTION("EXCEEDED MAX RULES SIZE, using default max length")
        {
            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequest.ext.saleRules() = xdr::xvector<CreateAccountSaleRuleData>(
                    app.getMaxSaleRulesLength() + 1, CreateAccountSaleRuleData());
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::EXCEEDED_MAX_RULES_SIZE);
        }
        SECTION("EXCEEDED MAX RULES SIZE, using max length from key value")
        {
            uint32_t maxRuleLength(10);
            longstring rulesKey = ManageKeyValueOpFrame::makeMaxSaleRulesNumberKey();
            manageKeyValueHelper.setKey(rulesKey)->setUi32Value(maxRuleLength);
            manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequest.ext.saleRules() = xdr::xvector<CreateAccountSaleRuleData>(
                    maxRuleLength + 1, CreateAccountSaleRuleData());
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::EXCEEDED_MAX_RULES_SIZE);
        }
        SECTION("GLOBAL SPECIFIC RULE DUPLICATION")
        {
            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequest.ext.saleRules() = xdr::xvector<CreateAccountSaleRuleData>(
                    2, CreateAccountSaleRuleData());
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::GLOBAL_SPECIFIC_RULE_DUPLICATION);
        }
        SECTION("Account not found")
        {
            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequest.ext.saleRules() = xdr::xvector<CreateAccountSaleRuleData>(
                    2, CreateAccountSaleRuleData(new AccountID(), false, LedgerVersion::EMPTY_VERSION));;
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::ACCOUNT_NOT_FOUND);
        }
        SECTION("ACCOUNT SPECIFIC RULE DUPLICATION")
        {
            saleRequest.ext.v(LedgerVersion::ADD_SALE_WHITELISTS);
            saleRequest.ext.saleRules() = xdr::xvector<CreateAccountSaleRuleData>(
                    2, CreateAccountSaleRuleData(new AccountID(syndicatePubKey), false, LedgerVersion::EMPTY_VERSION));
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                    CreateSaleCreationRequestResultCode::ACCOUNT_SPECIFIC_RULE_DUPLICATION);
        }
        SECTION("Trying to create sale for reversed pair")
        {
            auto assetPairTestHelper = ManageAssetPairTestHelper(testManager);
            assetPairTestHelper.createAssetPair(root, saleRequest.defaultQuoteAsset, saleRequest.baseAsset, 2);
            saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest, nullptr,
                                                     CreateSaleCreationRequestResultCode::INVALID_ASSET_PAIR);
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

            // Create asset creation request with max issuance 2000 * ONE - 
            assetCreationRequest = assetTestHelper.createAssetCreationRequest(asset, syndicatePubKey, "{}",
                                                                              900*ONE, 0,
                                                                              nullptr,
                                                                              500*ONE);
            auto assetRequestCreationResult = assetTestHelper.applyManageAssetTx(syndicate, 0, assetCreationRequest);
            auto assetRequestID = assetRequestCreationResult.success().requestID;

            // Create sale creation request with hardCap 1000 * ONE
            saleRequest = saleRequestHelper.createSaleRequest(asset, quoteAsset, currentTime, currentTime + 1000, softCap, hardCap, "{}",
            { saleRequestHelper.createSaleQuoteAsset(quoteAsset, price)}, 900*ONE);
            auto saleRequestCreationResult = saleRequestHelper.applyCreateSaleRequest(syndicate, 0, saleRequest,
                &zeroTasks, CreateSaleCreationRequestResultCode::AUTO_REVIEW_FAILED);
            REQUIRE(
                saleRequestCreationResult.autoReviewFailed()
                    .reviewRequestRequest.code() ==
                ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP);
        }
    }
    SECTION("Try to steal token by creating sale for stranger asset")
    {
        uint32_t tasks = 1, zeroTasks = 0;
        auto ownerSyndicate = Account{ SecretKey::random(), 0 };
        auto ownerSyndicatePubKey = ownerSyndicate.key.getPublicKey();
        CreateAccountTestHelper(testManager).applyCreateAccountTx(root, ownerSyndicatePubKey, 1);

        auto thiefSyndicate = Account{ SecretKey::random(), 0 };
        auto thiefSyndicatePubKey = thiefSyndicate.key.getPublicKey();
        CreateAccountTestHelper(testManager).applyCreateAccountTx(root, thiefSyndicatePubKey, 1);

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
        auto request = ReviewableRequestHelperLegacy::Instance()->
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
}

