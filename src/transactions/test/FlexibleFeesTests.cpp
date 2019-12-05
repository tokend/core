// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the ISC License. See the COPYING file at the top-level directory of
// this distribution or at http://opensource.org/licenses/ISC

#include "main/Application.h"
#include "test/test.h"
#include "ledger/FeeHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "TxTests.h"
#include "crypto/SHA.h"
#include "test_helper/TestManager.h"
#include "test/test_marshaler.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;


TEST_CASE("Flexible fees", "[!hide][dep_tx][flexible_fees]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;

    app.start();

    auto testManager = TestManager::make(app);
    TestManager::upgradeToCurrentLedgerVersion(app);

    auto& assetHelper = testManager->getStorageHelper().getAssetHelper();

    // set up world
    SecretKey root = getRoot();
    AccountID rootPK = root.getPublicKey();
    SecretKey issuance = getIssuanceKey();
    Salt rootSeq = 1;
	closeLedgerOn(app, 3, 1, 7, 2014);
	applySetFees(app, root, rootSeq, nullptr, false, nullptr);
	closeLedgerOn(app, 4, 1, 7, 2014);

	auto& feeHelper = testManager->getStorageHelper().getFeeHelper();

        auto baseAssets = assetHelper.loadBaseAssets();
        REQUIRE(!baseAssets.empty());
        auto asset = baseAssets[0];

	SECTION("Set global, set for account check global")
	{
		auto globalFee = createFeeEntry(FeeType::OFFER_FEE, 0, 10 * ONE, asset->getCode(), nullptr, nullptr);
		applySetFees(app, root, rootSeq++, &globalFee, false, nullptr);

		auto a = SecretKey::random();
		auto aPubKey = a.getPublicKey();
		applyCreateAccountTx(app, root, a, rootSeq++);
		auto accountFee = createFeeEntry(FeeType::OFFER_FEE, 0, 10 * ONE, asset->getCode(), &aPubKey, nullptr);
		applySetFees(app, root, rootSeq++, &accountFee, false, nullptr);

		auto globalFeeFrame = feeHelper.loadFee(FeeType::OFFER_FEE, asset->getCode(), nullptr, nullptr, 0, 0, INT64_MAX);
		REQUIRE(globalFeeFrame);
		REQUIRE(globalFeeFrame->getFee() == globalFee);

		auto accountFeeFrame = feeHelper.loadFee(FeeType::OFFER_FEE, asset->getCode(), &aPubKey, nullptr, 0, 0, INT64_MAX);
		REQUIRE(accountFeeFrame);
		REQUIRE(accountFeeFrame->getFee() == accountFee);
	}
}
