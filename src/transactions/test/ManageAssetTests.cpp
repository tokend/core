// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include "transactions/test/test_helper/IssuanceRequestHelper.h"
#include "transactions/test/test_helper/CreateAccountTestHelper.h"
#include "transactions/test/test_helper/ManageSignerTestHelper.h"
#include "test/test.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/test/test_helper/ManageAssetTestHelper.h"
#include "test_helper/ReviewAssetRequestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/manage_asset/ManageAssetOpFrame.h"
#include "transactions/test/test_helper/ManageAccountRuleTestHelper.h"
#include "transactions/test/test_helper/ManageAccountRoleTestHelper.h"

using namespace stellar;
using namespace txtest;

void testManageAssetHappyPath(TestManager::pointer testManager,
                              Account& account, Account& root);

TEST_CASE("manage asset", "[tx][manage_asset]")
{
    auto cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    auto updateMaxIssuanceTxHash = "1096aef9c1847621e7ce3e6e1c1568932a65ec1b91ba6532086d8e98193ed63d";
    cfg.TX_SKIP_SIG_CHECK.emplace(updateMaxIssuanceTxHash);
    VirtualClock clock;
    const auto appPtr = Application::create(clock, cfg);
    auto& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);


    //Helpers
    auto& storageHelper = testManager->getStorageHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    ManageKeyValueTestHelper manageKeyValueHelper(testManager);
    longstring preissuanceKey = ManageKeyValueOpFrame::makePreIssuanceTasksKey("*");
    manageKeyValueHelper.setKey(preissuanceKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring assetUpdateKey = ManageKeyValueOpFrame::makeAssetUpdateTasksKey();
    manageKeyValueHelper.setKey(assetUpdateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    longstring assetCreateKey = ManageKeyValueOpFrame::makeAssetCreateTasksKey();
    manageKeyValueHelper.setKey(assetCreateKey)->setUi32Value(0);
    manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);
    uint32_t zeroTasks = 0;

    auto root = Account{getRoot(), Salt(0)};

    CreateAccountTestHelper createAccountTestHelper(testManager);

    SECTION("Given valid asset")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        auto assetCode = "USD681";
        auto request = manageAssetHelper.createAssetCreationRequest(assetCode, root.key.getPublicKey(), "{}", UINT64_MAX, 0, &zeroTasks);
        auto creationResult = manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                                   ManageAssetResultCode::SUCCESS);
        REQUIRE(creationResult.success().fulfilled);

        auto assetFrame = assetHelper.loadActiveAsset(assetCode);
        REQUIRE(!!assetFrame);

        SECTION("Able to change max issuance with fork")
        {
            auto maxIssuanceAmount = 0;
            auto updateIssuanceRequest = manageAssetHelper.updateMaxAmount(assetCode, maxIssuanceAmount);
            auto txFrame = manageAssetHelper.createManageAssetTx(root, 0, updateIssuanceRequest);

            std::string txIDString(binToHex(txFrame->getContentsHash()));
            CLOG(INFO, Logging::OPERATION_LOGGER) << "tx must go throug even with invalid sigs: " << txIDString;
            REQUIRE(updateMaxIssuanceTxHash == txIDString);
            LedgerDeltaImpl delta(app.getLedgerManager().getCurrentLedgerHeader(),
                                  app.getDatabase());
            applyCheck(txFrame, delta, app);

            assetFrame = assetHelper.loadActiveAsset(assetCode);
            REQUIRE(!!assetFrame);
            REQUIRE(assetFrame->getMaxIssuanceAmount() == maxIssuanceAmount);
        }
    }
    SECTION("Syndicate happy path")
    {
        auto syndicate = Account{SecretKey::random(), Salt(0)};
        createAccountTestHelper.applyCreateAccountTx(root, syndicate.key.getPublicKey(), 1);
        testManageAssetHappyPath(testManager, syndicate, root);
    }
    SECTION("Cancel asset request")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        SECTION("Invalid ID")
        {
            manageAssetHelper.applyManageAssetTx(root, 0,
                                                 manageAssetHelper.
                                                     createCancelRequest(),
                                                 ManageAssetResultCode::
                                                 REQUEST_NOT_FOUND);
        }
        SECTION("Request not found")
        {
            manageAssetHelper.applyManageAssetTx(root, 12,
                                                 manageAssetHelper.
                                                     createCancelRequest(),
                                                 ManageAssetResultCode::
                                                 REQUEST_NOT_FOUND,
                                                 OperationResultCode::opNO_ENTRY);
        }
        SECTION("Request has invalid type")
        {
            // 1. create asset
            // 2. create pre issuance request for it
            // 3. try to cancel it with asset request
            const AssetCode asset = "USDT";
            manageAssetHelper.createAsset(root, root.key, asset, root, 0, &zeroTasks);
            auto issuanceHelper = IssuanceRequestHelper(testManager);
            auto requestResult = issuanceHelper.
                applyCreatePreIssuanceRequest(root, root.key, asset, 10000,
                                              SecretKey::random().
                                                  getStrKeyPublic());
            const auto cancelRequest = manageAssetHelper.createCancelRequest();
            manageAssetHelper.
                applyManageAssetTx(root, requestResult.success().requestID,
                                   cancelRequest,
                                   ManageAssetResultCode::REQUEST_NOT_FOUND,
                                   OperationResultCode::opNO_ENTRY);
        }
    }
    SECTION("Asset creation request")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        SECTION("Invalid asset code")
        {
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USD S",
                                           root.key.getPublicKey(), "{}", 100,
                                           0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 INVALID_CODE);
        }
        SECTION("Invalid policies")
        {
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USDS",
                                           root.key.getPublicKey(), "{}", 100,
                                           UINT32_MAX);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 INVALID_POLICIES);
        }
        SECTION("Inital pre issuance amount exceeds max issuance")
        {
            const uint64_t maxIssuanceAmount = 100;
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USDS",
                                           root.key.getPublicKey(), "{}", maxIssuanceAmount,
                                           0, &zeroTasks, maxIssuanceAmount + 1);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE);
        }
        SECTION("Trying to update non existing request")
        {
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USDS",
                                           root.key.getPublicKey(), "{}", 100,
                                           0);
            manageAssetHelper.applyManageAssetTx(root, 1, request,
                                                 ManageAssetResultCode::
                                                 REQUEST_NOT_FOUND);
        }
        SECTION("Trying to create request for same asset twice")
        {
            const AssetCode assetCode = "EURT";
            const auto request = manageAssetHelper.
                createAssetCreationRequest(assetCode,
                                           root.key.getPublicKey(), "{}", 100,
                                           0, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, request);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_ALREADY_EXISTS);
        }
        SECTION("Trying to create asset which is already exist")
        {
            const AssetCode assetCode = "EUR";
            manageAssetHelper.createAsset(root, root.key, assetCode, root, 0, &zeroTasks);
            const auto request = manageAssetHelper.
                createAssetCreationRequest(assetCode,
                                           root.key.getPublicKey(), "{}", 100,
                                           0, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_ALREADY_EXISTS);
        }
        SECTION("Trying to create asset with invalid details")
        {
            const AssetCode assetCode = "USD";
            // missed value
            const std::string invalidDetails = "{\"key\"}";

            const auto request = manageAssetHelper.createAssetCreationRequest(assetCode, root.key.getPublicKey(),
                                                                              invalidDetails, 100, 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_CREATOR_DETAILS);
        }
        /*SECTION("Try to review manage asset request from blocked syndicate")
        {
            uint32_t tasks = 1;
            Account syndicate = Account{SecretKey::random(), Salt(0)};
            createAccountTestHelper.applyCreateAccountTx(root, syndicate.key.getPublicKey(), AccountType::SYNDICATE);

            // create asset creation request
            auto request = manageAssetHelper.createAssetCreationRequest("USD", syndicate.key.getPublicKey(), "{}", UINT64_MAX, 0, &tasks);
            auto requestID = manageAssetHelper.applyManageAssetTx(syndicate, 0, request).success().requestID;

            // block syndicate
            ManageAccountTestHelper(testManager).applyManageAccount(root, syndicate.key.getPublicKey(), AccountType::SYNDICATE,
                                                                    {BlockReasons::SUSPICIOUS_BEHAVIOR}, {});

            auto reviewHelper = ReviewAssetRequestHelper(testManager);
            reviewHelper.applyReviewRequestTx(root, requestID, ReviewRequestOpAction::APPROVE, "",
                                              ReviewRequestResultCode::REQUESTOR_IS_BLOCKED);
        }*/
    }
    SECTION("Asset update request")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        const AssetCode assetCode = "USD";
        manageAssetHelper.createAsset(root, root.key, assetCode, root, 0, &zeroTasks);

        SECTION("Invalid asset code")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest("USD S", "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_CODE);
        }
        SECTION("Invalid asset policies")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest("USDS", "{}", UINT32_MAX);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_POLICIES);
        }
        SECTION("Trying to update non existing request")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest(assetCode, "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 12, request, ManageAssetResultCode::REQUEST_NOT_FOUND);
        }
        SECTION("Trying to update not my asset")
        {
            // create asset by syndicate
            auto syndicate = Account{SecretKey::random(), Salt(0)};
            createAccountTestHelper.applyCreateAccountTx(root, syndicate.key.getPublicKey(), 1);
            const AssetCode assetCode = "BTC";
            manageAssetHelper.createAsset(syndicate, syndicate.key, assetCode, root, 0, &zeroTasks);
            // try to update with root
            const auto request = manageAssetHelper.
                createAssetUpdateRequest(assetCode, "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_NOT_FOUND);
        }
        SECTION("Trying to update asset's details to invalid")
        {
            const std::string invalidDetails = "{\"key\"}";
            const auto request = manageAssetHelper.createAssetUpdateRequest(assetCode, invalidDetails, 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_CREATOR_DETAILS);
        }
        SECTION("Tasks permissions")
        {
            ManageAccountRuleTestHelper manageAccountRuleTestHelper(testManager);
            ManageAccountRoleTestHelper manageAccountRoleTestHelper(testManager);

            AccountRuleResource txResource(LedgerEntryType::TRANSACTION);
            auto txRuleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                                  txResource, AccountRuleAction::SEND, false);
            auto txRuleId = manageAccountRuleTestHelper.applyTx(root,
                                                                txRuleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

            AccountRuleResource assetResource(LedgerEntryType::ASSET);
            assetResource.asset().assetType = 0;
            assetResource.asset().assetCode = "*";
            auto assetRuleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                                     assetResource, AccountRuleAction::ANY, false);
            auto assetRuleId = manageAccountRuleTestHelper.applyTx(root,
                                                                   assetRuleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

            AccountRuleResource reviewableRequestResource(LedgerEntryType::REVIEWABLE_REQUEST);
            reviewableRequestResource.reviewableRequest().details.requestType(ReviewableRequestType::ANY);
            auto revReqRuleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
                                                                                      reviewableRequestResource, AccountRuleAction::CREATE, false);
            auto revReqRuleId = manageAccountRuleTestHelper.applyTx(root,
                                                                    revReqRuleEntry, ManageAccountRuleAction::CREATE).success().ruleID;

            auto createSyndicateRoleOp = manageAccountRoleTestHelper.buildCreateRoleOp("{}",
                                                                                       {assetRuleId, revReqRuleId,
                                                                                        txRuleId});
            auto syndicateRoleID = manageAccountRoleTestHelper.applyTx(root, createSyndicateRoleOp).success().roleID;

            auto createAccountBuilder = CreateAccountTestBuilder()
                .setSource(root);

            auto syndicate = Account{SecretKey::random(), 0};
            auto syndicatePubKey = syndicate.key.getPublicKey();
            createAccountTestHelper.applyTx(createAccountBuilder
                                                .setToPublicKey(syndicatePubKey)
                                                .addBasicSigner()
                                                .setRoleID(syndicateRoleID));

            const AssetCode assetCode = "AST";
            auto createRequest = manageAssetHelper.createAssetCreationRequest(assetCode,
                                                                              syndicatePubKey, "{}", UINT64_MAX, 0, &zeroTasks);
            auto creationResult = manageAssetHelper.applyManageAssetTx(syndicate, 0, createRequest,
                                                                       ManageAssetResultCode::SUCCESS);

            SECTION("Set tasks without permission")
            {
                const auto request = manageAssetHelper.createAssetUpdateRequest(assetCode, "{}", 0, &zeroTasks);
                manageAssetHelper.applyManageAssetTx(syndicate, 0, request,
                                                     ManageAssetResultCode::SUCCESS, // No check of inner permission
                                                     OperationResultCode::opNO_ROLE_PERMISSION);
            }
            SECTION("Without setting tasks")
            {
                const auto request = manageAssetHelper.createAssetUpdateRequest(assetCode, "{}", 0);
                manageAssetHelper.applyManageAssetTx(syndicate, 0, request, ManageAssetResultCode::SUCCESS);
            }
        }
    }
    SECTION("create base asset")
    {
        uint32 baseAssetPolicy = static_cast<uint32>(AssetPolicy::BASE_ASSET);
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        auto preissuedSigner = SecretKey::random();

        SECTION("create base asset")
        {
            AssetCode baseAsset = "ILS";
            auto assetCreationRequest = manageAssetHelper.
                createAssetCreationRequest(baseAsset, SecretKey::random().getPublicKey(),
                                           "{}",
                                           UINT64_MAX, baseAssetPolicy, &zeroTasks, 10203);
            auto creationResult = manageAssetHelper.applyManageAssetTx(root, 0, assetCreationRequest);
        }

        SECTION("create asset then make it base by updating policies")
        {
            AssetCode assetCode = "UAH";
            manageAssetHelper.createAsset(root, preissuedSigner, assetCode, root, 0, &zeroTasks);

            auto assetUpdateRequest = manageAssetHelper.
                createAssetUpdateRequest(assetCode, "{}", baseAssetPolicy, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, assetUpdateRequest);
        }

        SECTION("remove base asset by updating policies")
        {
            AssetCode assetCode = "ILS";
            manageAssetHelper.createAsset(root, preissuedSigner, assetCode, root,
                                          static_cast<uint32_t>(AssetPolicy::BASE_ASSET), &zeroTasks);

            auto assetUpdateRequest = manageAssetHelper.
                createAssetUpdateRequest(assetCode, "{}", 0, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, assetUpdateRequest);
            auto baseAssets = assetHelper.loadBaseAssets();
            REQUIRE(baseAssets.empty());
        }
    }

    SECTION("create stats asset")
    {
        ManageAssetTestHelper manageAssetHelper(testManager);
        uint32 statsPolicy = static_cast<uint32>(AssetPolicy::STATS_QUOTE_ASSET);
        SECTION("create stats asset")
        {
            AssetCode statsAsset = "BYN";
            SecretKey preissuedSigner = SecretKey::random();
            auto createAssetRequest = manageAssetHelper.
                createAssetCreationRequest(statsAsset, preissuedSigner.getPublicKey(), "{}",
                                           UINT64_MAX, statsPolicy, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, createAssetRequest);
        }

        SECTION("attempt to create several stats assets")
        {
            AssetCode statsAsset = "BYN";
            SecretKey preissuedSigner = SecretKey::random();
            auto createFirst = manageAssetHelper.
                createAssetCreationRequest(statsAsset, preissuedSigner.getPublicKey(), "{}",
                                           UINT64_MAX, statsPolicy, &zeroTasks);
            manageAssetHelper.applyManageAssetTx(root, 0, createFirst);

            auto createSecond = manageAssetHelper.
                createAssetCreationRequest("CZK", preissuedSigner.getPublicKey(), "{}", UINT64_MAX, statsPolicy);
            manageAssetHelper.applyManageAssetTx(root, 0, createSecond,
                                                 ManageAssetResultCode::STATS_ASSET_ALREADY_EXISTS);
        }
    }
}


void testManageAssetHappyPath(TestManager::pointer testManager,
                              Account& account, Account& root)
{
    auto preissuedSigner = SecretKey::random();
    auto manageAssetHelper = ManageAssetTestHelper(testManager);
    ManageSignerTestHelper manageSignerTestHelper(testManager);
    const AssetCode assetCode = "EURT";
    const uint64_t maxIssuance = 102030;
    const auto initialPreIssuedAmount = maxIssuance;
    uint32_t zeroTasks = 0;
    uint32_t tasks = 1;

    auto& storageHelper = testManager->getStorageHelper();
    auto& assetHelper = storageHelper.getAssetHelper();


    SECTION("Can create asset")
    {

        auto creationRequest = manageAssetHelper.
            createAssetCreationRequest(assetCode,
                                       preissuedSigner.getPublicKey(),
                                       "{}", maxIssuance, 0, &tasks, initialPreIssuedAmount);
        auto creationResult = manageAssetHelper.applyManageAssetTx(account, 0,
                                                                   creationRequest);

        manageSignerTestHelper.applyCreateOperationalSigner(account, preissuedSigner.getPublicKey());

        auto& storageHelper = testManager->getStorageHelper();
        auto& requestHelper = storageHelper.getReviewableRequestHelper();
        auto& assetHelper = storageHelper.getAssetHelper();

        SECTION("Can cancel creation request")
        {
            manageAssetHelper.applyManageAssetTx(account,
                                                 creationResult.success().
                                                     requestID,
                                                 manageAssetHelper.
                                                     createCancelRequest());
        }
        SECTION("Can update pending request")
        {
            creationRequest.createAssetCreationRequest().createAsset.code = "USDT";
            auto requestID = creationResult.success().requestID;
            auto requestBefore = requestHelper.loadRequest(
                requestID, account.key.getPublicKey(),
                ReviewableRequestType::CREATE_ASSET);
            REQUIRE(requestBefore);
            creationRequest.createAssetCreationRequest().allTasks = nullptr;
            manageAssetHelper.applyManageAssetTx(account,
                                                 requestID,
                                                 creationRequest);
            auto requestAfter = requestHelper.loadRequest(
                requestID, account.key.getPublicKey(),
                ReviewableRequestType::CREATE_ASSET);
            REQUIRE(requestAfter);
            auto seqBefore = requestBefore->getRequestEntry()
                .body.assetCreationRequest()
                .sequenceNumber;
            auto seqAfter = requestAfter->getRequestEntry()
                .body.assetCreationRequest()
                .sequenceNumber;
            REQUIRE(seqBefore + 1 == seqAfter);

        }
        SECTION("Given approved asset")
        {
            auto approvingRequest = requestHelper.
                loadRequest(creationResult.success().requestID);
            REQUIRE(approvingRequest);
            auto reviewRequetHelper = ReviewAssetRequestHelper(testManager);
            reviewRequetHelper.applyReviewRequestTxWithTasks(root, approvingRequest->
                                                                 getRequestID(),
                                                             approvingRequest->getHash(),
                                                             approvingRequest->getType(),
                                                             ReviewRequestOpAction::
                                                             APPROVE, "",
                                                             ReviewRequestResultCode::SUCCESS,
                                                             &zeroTasks, &tasks);

            SECTION("Can change asset pre issuance signer")
            {
                auto newPreIssuanceSigner = SecretKey::random();
                auto preissuedSignerAccount = Account{preissuedSigner, 0};
                auto changePreIssuanceSigner = manageAssetHelper.createChangeSignerRequest(
                    preissuedSignerAccount, assetCode, newPreIssuanceSigner.getPublicKey());
                auto txFrame = manageAssetHelper.createManageAssetTx(account, 0, changePreIssuanceSigner);
                txFrame->getEnvelope().signatures.clear();
                txFrame->addSignature(preissuedSigner);
                testManager->applyCheck(txFrame);
                auto txResult = txFrame->getResult();
                const auto opResult = txResult.result.results()[0];
                auto actualResultCode = ManageAssetOpFrame::getInnerCode(opResult);
                REQUIRE(actualResultCode == ManageAssetResultCode::SUCCESS);
                auto assetFrame = assetHelper.loadActiveAsset(assetCode);
                REQUIRE(assetFrame->getPreIssuedAssetSigner() == newPreIssuanceSigner.getPublicKey());
                SECTION("Owner is not able to change signer")
                {
                    changePreIssuanceSigner = manageAssetHelper.createChangeSignerRequest(account, assetCode, preissuedSigner.getPublicKey());
                    txFrame = manageAssetHelper.createManageAssetTx(account, 0, changePreIssuanceSigner);
                    testManager->applyCheck(txFrame);
                    auto txResult = txFrame->getResult();
                    const auto opResult = txResult.result.results()[0];
                    REQUIRE(opResult.code() == OperationResultCode::opINNER);
                    REQUIRE(opResult.tr().manageAssetResult().code() == ManageAssetResultCode::INVALID_SIGNATURE);
                }
            }
            SECTION("Can update asset")
            {

                const auto updateRequestBody = manageAssetHelper.
                    createAssetUpdateRequest(assetCode,
                                             "{}", 0, &zeroTasks);
                auto updateResult = manageAssetHelper.
                    applyManageAssetTx(account, 0, updateRequestBody);
                REQUIRE(updateResult.success().fulfilled);
            }
        }
    }

    SECTION("With tasks")
    {
        uint32_t allTasks = 2;
        uint32_t tasksToAdd = 0, tasksToRemove = 2;

        auto creationRequest = manageAssetHelper.
            createAssetCreationRequest(assetCode,
                                       preissuedSigner.getPublicKey(),
                                       "{}", maxIssuance, 0, &allTasks, initialPreIssuedAmount);
        auto creationResult = manageAssetHelper.applyManageAssetTx(account, 0,
                                                                   creationRequest);


        REQUIRE_FALSE(creationResult.success().fulfilled);

        auto& requestHelper = testManager->getStorageHelper().getReviewableRequestHelper();
        auto reviewAssetRequestHelper = ReviewAssetRequestHelper(testManager);

        SECTION("Can update rejected request")
        {
            auto request = requestHelper.
                loadRequest(creationResult.success().requestID);
            REQUIRE(request);
            auto reviewResult = reviewAssetRequestHelper.applyReviewRequestTxWithTasks(root, request->
                                                                                           getRequestID(),
                                                                                       request->getHash(),
                                                                                       request->getRequestType(),
                                                                                       ReviewRequestOpAction::
                                                                                       REJECT, "Because", ReviewRequestResultCode::SUCCESS,
                                                                                       &tasksToAdd,
                                                                                       &zeroTasks);
            auto secondCreationRequest = manageAssetHelper.
                createAssetCreationRequest(assetCode,
                                           preissuedSigner.getPublicKey(),
                                           "{}", maxIssuance * 2, 0, nullptr, initialPreIssuedAmount);

            auto secondCreationResult = manageAssetHelper.applyManageAssetTx(account, request->getRequestID(),
                                                                             secondCreationRequest);
            REQUIRE_FALSE(secondCreationResult.success().fulfilled);
            request = requestHelper.
                loadRequest(creationResult.success().requestID);
            REQUIRE(request);
            auto secondReviewResult = reviewAssetRequestHelper.applyReviewRequestTxWithTasks(root, request->
                                                                                                 getRequestID(),
                                                                                             request->getHash(),
                                                                                             request->getRequestType(),
                                                                                             ReviewRequestOpAction::
                                                                                             APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                                                             &zeroTasks,
                                                                                             &tasksToRemove);

        }
        SECTION("Valid")
        {

            auto request = requestHelper.
                loadRequest(creationResult.success().requestID);
            REQUIRE(request);
            auto reviewResult = reviewAssetRequestHelper.applyReviewRequestTxWithTasks(root, request->
                                                                                           getRequestID(),
                                                                                       request->getHash(),
                                                                                       request->getRequestType(),
                                                                                       ReviewRequestOpAction::
                                                                                       APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                                                       &tasksToAdd,
                                                                                       &tasksToRemove);
            REQUIRE(reviewResult.success().fulfilled);

            SECTION("Update")
            {
                const auto updateRequestBody = manageAssetHelper.
                    createAssetUpdateRequest(assetCode,
                                             "{}", 0, &allTasks);
                auto updateResult = manageAssetHelper.
                    applyManageAssetTx(account, 0, updateRequestBody);

                REQUIRE_FALSE(updateResult.success().fulfilled);

                auto request = requestHelper.
                    loadRequest(updateResult.success().requestID);
                REQUIRE(request);
                auto updateReviewResult = reviewAssetRequestHelper.
                    applyReviewRequestTxWithTasks(root, request->
                                                      getRequestID(),
                                                  request->getHash(),
                                                  request->getRequestType(),
                                                  ReviewRequestOpAction::
                                                  APPROVE, "", ReviewRequestResultCode::SUCCESS,
                                                  &tasksToAdd,
                                                  &tasksToRemove);
                REQUIRE(updateReviewResult.success().fulfilled);
            }

            SECTION("Remove asset")
            {
                manageAssetHelper.applyRemoveAssetTx(root, assetCode,
                                                   nullptr);

                REQUIRE(assetHelper.exists(assetCode));
                REQUIRE_FALSE(assetHelper.existActive(assetCode));

                SECTION("Create again")
                {
                    auto req = manageAssetHelper.
                        createAssetCreationRequest(assetCode,
                                                   preissuedSigner.getPublicKey(),
                                                   "{}", maxIssuance, 0, &tasks, initialPreIssuedAmount);
                    manageAssetHelper.applyManageAssetTx(account, 0,
                                                                               req, ManageAssetResultCode::ASSET_ALREADY_EXISTS);
                }

            }

        }

    }
}
