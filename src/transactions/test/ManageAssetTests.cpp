// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include <transactions/test/test_helper/IssuanceRequestHelper.h>
#include <transactions/test/test_helper/CreateAccountTestHelper.h>
#include "main/test.h"
#include "ledger/AssetHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "TxTests.h"
#include "transactions/test/test_helper/ManageAssetTestHelper.h"
#include "test_helper/ReviewAssetRequestHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace txtest;

void testManageAssetHappyPath(TestManager::pointer testManager,
                              Account& account, Account& root);


TEST_CASE("manage asset", "[tx][manage_asset]")
{
    auto const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
    VirtualClock clock;
    const auto appPtr = Application::create(clock, cfg);
    auto& app = *appPtr;
    app.start();
    auto testManager = TestManager::make(app);

    auto root = Account{getRoot(), Salt(0)};

	auto assetHelper = AssetHelper::Instance();
    CreateAccountTestHelper createAccountTestHelper(testManager);

    SECTION("Syndicate happy path")
    {
        auto syndicate = Account{SecretKey::random(), Salt(0)};
        createAccountTestHelper.applyCreateAccountTx(root, syndicate.key.getPublicKey(), AccountType::SYNDICATE);
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
                                                 REQUEST_NOT_FOUND);
        }
        SECTION("Request has invalid type")
        {
            // 1. create asset
            // 2. create pre issuance request for it
            // 3. try to cancel it with asset request
            const AssetCode asset = "USDT";
            manageAssetHelper.createAsset(root, root.key, asset, root, 0);
            auto issuanceHelper = IssuanceRequestHelper(testManager);
            auto requestResult = issuanceHelper.
                applyCreatePreIssuanceRequest(root, root.key, asset, 10000,
                                              SecretKey::random().
                                              getStrKeyPublic());
            const auto cancelRequest = manageAssetHelper.createCancelRequest();
            manageAssetHelper.
                applyManageAssetTx(root, requestResult.success().requestID,
                                   cancelRequest,
                                   ManageAssetResultCode::REQUEST_NOT_FOUND);
        }
    }
    SECTION("Asset creation request")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        SECTION("Invalid asset code")
        {
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USD S",
                                           root.key.getPublicKey(), "{}",100,
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
                    0, maxIssuanceAmount + 1);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                ManageAssetResultCode::INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE);
        }
        SECTION("Trying to update non existsing request")
        {
            const auto request = manageAssetHelper.
                createAssetCreationRequest("USDS",
                                           root.key.getPublicKey(), "{}",100,
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
                                           root.key.getPublicKey(), "{}",100,
                                           0);
            manageAssetHelper.applyManageAssetTx(root, 0, request);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_ALREADY_EXISTS);
        }
        SECTION("Trying to create asset which is already exist")
        {
            const AssetCode assetCode = "EUR";
            manageAssetHelper.createAsset(root, root.key, assetCode, root, 0);
            const auto request = manageAssetHelper.
                createAssetCreationRequest(assetCode,
                                           root.key.getPublicKey(), "{}",100,
                                           0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_ALREADY_EXISTS);
        }
        SECTION("Trying to create asset with invalid details")
        {
            const AssetCode assetCode = "USD";
            // missed value
            std::string invalidDetails = "{\"key\"}";

            const auto request = manageAssetHelper.createAssetCreationRequest(assetCode, root.key.getPublicKey(),
                                                                              invalidDetails, 100, 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_DETAILS);
        }
    }
    SECTION("Asset update request")
    {
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        SECTION("Invalid asset code")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest("USD S", "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 INVALID_CODE);
        }
        SECTION("Invalid asset policies")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest("USDS", "{}", UINT32_MAX);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 INVALID_POLICIES);
        }
        SECTION("Trying to update non existsing request")
        {
            const auto request = manageAssetHelper.
                createAssetUpdateRequest("USDS", "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 12, request, ManageAssetResultCode::REQUEST_NOT_FOUND);
        }
        SECTION("Trying to update not my asset")
        {
            // create asset by syndicate
            auto syndicate = Account{SecretKey::random(), Salt(0)};
            createAccountTestHelper.applyCreateAccountTx(root, syndicate.key.getPublicKey(), AccountType::SYNDICATE);
            const AssetCode assetCode = "BTC";
            manageAssetHelper.createAsset(syndicate, syndicate.key, assetCode, root, 0);
            // try to update with root
            const auto request = manageAssetHelper.
                createAssetUpdateRequest(assetCode, "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::
                                                 ASSET_NOT_FOUND);
        }
        SECTION("Trying to update asset's details to invalid")
        {
            const AssetCode assetCode = "USD";
            manageAssetHelper.createAsset(root, root.key, assetCode, root, 0);

            std::string invalidDetails = "{\"key\"}";
            auto request = manageAssetHelper.createAssetUpdateRequest(assetCode, invalidDetails, 0);
            manageAssetHelper.applyManageAssetTx(root, 0, request,
                                                 ManageAssetResultCode::INVALID_DETAILS);
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
                                               UINT64_MAX, baseAssetPolicy, 10203);
            auto creationResult = manageAssetHelper.applyManageAssetTx(root, 0, assetCreationRequest);
        }

        SECTION("create asset then make it base by updating policies")
        {
            AssetCode assetCode = "UAH";
            manageAssetHelper.createAsset(root, preissuedSigner, assetCode, root, 0);

            auto assetUpdateRequest = manageAssetHelper.
                    createAssetUpdateRequest(assetCode, "{}", baseAssetPolicy);
            manageAssetHelper.applyManageAssetTx(root, 0, assetUpdateRequest);
        }

        SECTION("remove base asset by updating policies")
        {
            AssetCode assetCode = "ILS";
            manageAssetHelper.createAsset(root, preissuedSigner, assetCode, root, static_cast<uint32_t>(AssetPolicy::BASE_ASSET));

            auto assetUpdateRequest = manageAssetHelper.
                    createAssetUpdateRequest(assetCode, "{}", 0);
            manageAssetHelper.applyManageAssetTx(root, 0, assetUpdateRequest);
            std::vector<AssetFrame::pointer> baseAssets;
			assetHelper->loadBaseAssets(baseAssets, testManager->getDB());
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
                    createAssetCreationRequest(statsAsset, preissuedSigner.getPublicKey(), "{}", UINT64_MAX, statsPolicy);
            manageAssetHelper.applyManageAssetTx(root, 0, createAssetRequest);
        }

        SECTION("attempt to create several stats assets")
        {
            AssetCode statsAsset = "BYN";
            SecretKey preissuedSigner = SecretKey::random();
            auto createFirst = manageAssetHelper.
                    createAssetCreationRequest(statsAsset, preissuedSigner.getPublicKey(), "{}", UINT64_MAX, statsPolicy);
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
    SECTION("Can create asset")
    {
        auto preissuedSigner = SecretKey::random();
        auto manageAssetHelper = ManageAssetTestHelper(testManager);
        const AssetCode assetCode = "EURT";
        const uint64_t maxIssuance = 102030;
        const auto initialPreIssuedAmount = maxIssuance;
        auto creationRequest = manageAssetHelper.
            createAssetCreationRequest(assetCode,
                                       preissuedSigner.getPublicKey(),
                                       "{}", maxIssuance, 0, initialPreIssuedAmount);
        auto creationResult = manageAssetHelper.applyManageAssetTx(account, 0,
                                                                   creationRequest);

		auto reviewableRequestHelper = ReviewableRequestHelper::Instance();

        SECTION("Can cancel creation request")
        {
            manageAssetHelper.applyManageAssetTx(account,
                                                 creationResult.success().
                                                                requestID,
                                                 manageAssetHelper.
                                                 createCancelRequest());
        }
        SECTION("Can update existing request")
        {
            creationRequest.createAsset().code = "USDT";
            auto updateResult = manageAssetHelper.applyManageAssetTx(account,
                                                                     creationResult
                                                                     .success().
                                                                      requestID,
                                                                     creationRequest);
            REQUIRE(updateResult.success().requestID == creationResult.success()
                .requestID);
        }
        SECTION("Given approved asset")
        {
            auto& delta = testManager->getLedgerDelta();
            auto approvingRequest = reviewableRequestHelper->
				loadRequest(creationResult.success().requestID,
                            testManager->getDB(), &delta);
            REQUIRE(approvingRequest);
            auto reviewRequetHelper = ReviewAssetRequestHelper(testManager);
            reviewRequetHelper.applyReviewRequestTx(root, approvingRequest->
                                                    getRequestID(),
                                                    approvingRequest->getHash(),
                                                    approvingRequest->getType(),
                                                    ReviewRequestOpAction::
                                                    APPROVE, "");
            SECTION("Can update asset")
            {
                const auto updateRequestBody = manageAssetHelper.
                    createAssetUpdateRequest(assetCode,
                                             "{}", 0);
                auto updateResult = manageAssetHelper.
                    applyManageAssetTx(account, 0, updateRequestBody);
                approvingRequest = reviewableRequestHelper->
                    loadRequest(updateResult.success().requestID,
                                testManager->getDB(), &delta);
                REQUIRE(approvingRequest);
                reviewRequetHelper.applyReviewRequestTx(root, approvingRequest->
                                                        getRequestID(),
                                                        approvingRequest->
                                                        getHash(),
                                                        approvingRequest->
                                                        getType(),
                                                        ReviewRequestOpAction::
                                                        APPROVE, "");
            }
        }
    }
}
