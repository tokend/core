// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include "main/Config.h"
#include "overlay/LoopbackPeer.h"
#include "test/test.h"
#include "TxTests.h"
#include "test_helper/TestManager.h"
#include "transactions/test/test_helper/ManageAssetTestHelper.h"
#include "test_helper/ReviewAssetRequestHelper.h"
#include "test_helper/IssuanceRequestHelper.h"
#include "test_helper/ReviewPreIssuanceRequestHelper.h"
#include "test_helper/ManageKeyValueTestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

void testAuthPreissuedAssetHappyPath(TestManager::pointer testManager, Account& account, Account& root) {
	auto preissuedSigner = SecretKey::random();
	AssetCode assetCode = "EUR";
	auto manageAssetHelper = ManageAssetTestHelper(testManager);
    manageAssetHelper.createAsset(account, preissuedSigner, assetCode, root, 0);
	auto issuanceRequestHelper = IssuanceRequestHelper(testManager);
	auto reviewPreIssuanceRequestHelper = ReviewPreIssuanceRequestHelper(testManager);
        auto& assetHelper = testManager->getStorageHelper().getAssetHelper();
	auto asset = assetHelper.loadAsset(assetCode);
	const uint64_t amountToIssue = 10000;
	const int issueTimes = 3;
    bool isMaster = account.key == getRoot();
	for (int i = 0; i < issueTimes; i++) {
		auto preIssuanceResult = issuanceRequestHelper.applyCreatePreIssuanceRequest(account, preissuedSigner, assetCode, amountToIssue,
			SecretKey::random().getStrKeyPublic());
        if (!isMaster)
            reviewPreIssuanceRequestHelper.applyReviewRequestTx(root, preIssuanceResult.success().requestID,
                                                                ReviewRequestOpAction::APPROVE, "");
	}
	asset = assetHelper.loadAsset(assetCode);
	REQUIRE(asset->getAvailableForIssuance() == amountToIssue * issueTimes);
}

TEST_CASE("Authorize pre issued asset", "[tx][auth_preissued_asset]")
{
	Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);
	VirtualClock clock;
	Application::pointer appPtr = Application::create(clock, cfg);
	Application& app = *appPtr;
	app.start();
	auto testManager = TestManager::make(app);

	ManageAssetTestHelper manageAssetHelper(testManager);
	IssuanceRequestHelper issuanceRequestHelper(testManager);
	ReviewPreIssuanceRequestHelper reviewPreIssuanceRequestHelper(testManager);
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


	auto root = Account{ getRoot(), Salt(0) };
	SECTION("Root happy path")
	{
		testAuthPreissuedAssetHappyPath(testManager, root, root);
	}
	SECTION("Create two pre issuance requests with max issuance amount, try approve them")
	{
		preissuanceKey = ManageKeyValueOpFrame::makePreIssuanceTasksKey("*");
		manageKeyValueHelper.setKey(preissuanceKey)->setUi32Value(1);
		manageKeyValueHelper.doApply(testManager->getApp(), ManageKVAction::PUT, true);

		AssetCode assetCode("PLN");
		uint64_t maxIssuance(10*ONE);
		manageAssetHelper.createAsset(root, root.key, assetCode, root, 0,
									  nullptr, 6, 1, maxIssuance);

		auto firstRequestID = issuanceRequestHelper.applyCreatePreIssuanceRequest(
				root, root.key, assetCode, maxIssuance,
				SecretKey::random().getStrKeyPublic()).success().requestID;

		auto secondRequestID = issuanceRequestHelper.applyCreatePreIssuanceRequest(
				root, root.key, assetCode, maxIssuance,
				SecretKey::random().getStrKeyPublic()).success().requestID;

		reviewPreIssuanceRequestHelper.applyReviewRequestTxWithTasks(root, firstRequestID,
													ReviewRequestOpAction::APPROVE, "", 1);
		reviewPreIssuanceRequestHelper.applyReviewRequestTxWithTasks(root, secondRequestID,
													ReviewRequestOpAction::APPROVE, "", 1,
												 ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED);
	}
}