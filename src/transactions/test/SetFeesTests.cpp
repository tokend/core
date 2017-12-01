// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the ISC License. See the COPYING file at the top-level directory of
// this distribution or at http://opensource.org/licenses/ISC

#include "main/Application.h"
#include "overlay/LoopbackPeer.h"
#include "util/make_unique.h"
#include "main/test.h"
#include "lib/catch.hpp"

#include "TxTests.h"
#include "ledger/LedgerDelta.h"
#include "transactions/SetFeesOpFrame.h"

#include "crypto/SHA.h"

using namespace stellar;
using namespace stellar::txtest;

typedef std::unique_ptr<Application> appPtr;

TEST_CASE("Set fee", "[dep_tx][setfee]")
{
    Config const& cfg = getTestConfig(0, Config::TESTDB_POSTGRESQL);

    VirtualClock clock;
    Application::pointer appPtr = Application::create(clock, cfg);
    Application& app = *appPtr;

    app.start();
    closeLedgerOn(app, 2, 1, 7, 2014);
	LedgerDelta delta(app.getLedgerManager().getCurrentLedgerHeader(),
		app.getDatabase());

    // set up world
    SecretKey root = getRoot();
    Salt rootSeq = 1;

    SECTION("Only Master account with admin signer can set fee")
    {
		auto tx = createSetFees(app.getNetworkID(), root, 0, nullptr, false);
		tx->checkValid(app);
		auto op = tx->getOperations()[0];
		op->checkValid(app, &delta);
		auto sourceAccountDetials = op->getSourceAccountDetails({});
		REQUIRE(sourceAccountDetials.mNeededSignedClass == static_cast<int32_t>(SignerType::ASSET_MANAGER));
		auto allowedSource = sourceAccountDetials.mAllowedSourceAccountTypes;
		REQUIRE(allowedSource.size() == 1);
		REQUIRE(allowedSource[0] == AccountType::MASTER);
    }
	SECTION("Invalid asset")
	{
		auto fee = createFeeEntry(FeeType::PAYMENT_FEE, 0, 0, "");
		applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_ASSET);
	}
	SECTION("Invalid fee type")
	{
		auto fee = createFeeEntry(FeeType(123), 0, 0, app.getBaseAsset());
		applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_FEE_TYPE);
	}
	SECTION("Asset not found")
	{
		auto fee = createFeeEntry(FeeType::PAYMENT_FEE, 0, 0, "AETH");
		applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::ASSET_NOT_FOUND);
	}
	SECTION("AccountID is set")
	{
        auto a = SecretKey::random();
        auto aPubKey = a.getPublicKey();
        applyCreateAccountTx(app, root, a, rootSeq++, AccountType::GENERAL);
        auto accountFrame = loadAccount(a, app);
        auto accountFee = FeeFrame::loadForAccount(FeeType::PAYMENT_FEE, app.getBaseAsset(), FeeFrame::SUBTYPE_ANY,
            accountFrame, 0, app.getDatabase());

        REQUIRE(!accountFee);

        auto feeEntry = createFeeEntry(FeeType::PAYMENT_FEE, 1, 2, app.getBaseAsset(), &aPubKey);
		applySetFees(app, root, rootSeq++, &feeEntry, false, nullptr);
        accountFee = FeeFrame::loadForAccount(FeeType::PAYMENT_FEE, app.getBaseAsset(), FeeFrame::SUBTYPE_ANY,
            accountFrame, 0, app.getDatabase());

        REQUIRE(accountFee->getFee() == feeEntry);
	}
	SECTION("AccountType is set")
	{
        auto accountType = AccountType::GENERAL;
        auto a = SecretKey::random();
        applyCreateAccountTx(app, root, a, rootSeq++, AccountType::GENERAL);
        auto accountFrame = loadAccount(a, app);
        auto accountFee = FeeFrame::loadForAccount(FeeType::PAYMENT_FEE, app.getBaseAsset(), FeeFrame::SUBTYPE_ANY,
            accountFrame, 0, app.getDatabase());

        REQUIRE(!accountFee);

        auto feeEntry = createFeeEntry(FeeType::PAYMENT_FEE, 10, 20, app.getBaseAsset(), nullptr, &accountType);
		applySetFees(app, root, rootSeq++, &feeEntry, false, nullptr);
        accountFee = FeeFrame::loadForAccount(FeeType::PAYMENT_FEE, app.getBaseAsset(), FeeFrame::SUBTYPE_ANY,
            accountFrame, 0, app.getDatabase());

        REQUIRE(accountFee->getFee() == feeEntry);
	}

	SECTION("Both cannot be set")
	{
		auto account = SecretKey::random();
		auto accountID = account.getPublicKey();
        auto accountType = AccountType::GENERAL;
		applyCreateAccountTx(app, root, account, 0, AccountType::GENERAL);
        auto feeEntry = createFeeEntry(FeeType::PAYMENT_FEE, 0, 0, app.getBaseAsset(), &accountID, &accountType);
		applySetFees(app, root, rootSeq++, &feeEntry, false, nullptr, SetFeesResultCode::MALFORMED);
	}


	SECTION("Payment fee")
	{
		SECTION("Success")
		{
			auto fee = createFeeEntry(FeeType::PAYMENT_FEE, 2, 2 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
		}
		SECTION("Success zero")
		{
			auto fee = createFeeEntry(FeeType::PAYMENT_FEE, 0, 0, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
		}
		SECTION("Invalid percent fee fee")
		{
			auto fee = createFeeEntry(FeeType::PAYMENT_FEE, 0, 101 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_AMOUNT);
		}
	}
	SECTION("Offer fee")
	{
		SECTION("Success")
		{
			auto fee = createFeeEntry(FeeType::OFFER_FEE, 0, 2 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
		}
		SECTION("Success zero")
		{
			auto fee = createFeeEntry(FeeType::OFFER_FEE, 0, 0, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
		}
		SECTION("Invalid fixed fee")
		{
			auto fee = createFeeEntry(FeeType::OFFER_FEE, 1, 2 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_AMOUNT);
		}
		SECTION("Invalid percent fee")
		{
			auto fee = createFeeEntry(FeeType::OFFER_FEE, 0, 101 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_AMOUNT);
		}
	}
	SECTION("forfeit fee")
	{
		SECTION("Success")
		{
			auto fee = createFeeEntry(FeeType::FORFEIT_FEE, 1, 2 * ONE, app.getBaseAsset(), nullptr, nullptr, 1);
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
            SECTION("update existing")
            {
				auto fee = createFeeEntry(FeeType::FORFEIT_FEE, 0, 0, app.getBaseAsset(), nullptr, nullptr, 1);
                applySetFees(app, root, rootSeq++, &fee, false, nullptr);
            }
			SECTION("Can delete")
			{
				auto fee = createFeeEntry(FeeType::FORFEIT_FEE, 0, 0, app.getBaseAsset(), nullptr, nullptr, 1);
				applySetFees(app, root, rootSeq++, &fee, true, nullptr);
			}
            
		}
		SECTION("Success zero")
		{
			auto fee = createFeeEntry(FeeType::FORFEIT_FEE, 0, 0, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr);
		}
		SECTION("Invalid percent fee")
		{
			auto fee = createFeeEntry(FeeType::FORFEIT_FEE, 0, 101 * ONE, app.getBaseAsset());
			applySetFees(app, root, rootSeq++, &fee, false, nullptr, SetFeesResultCode::INVALID_AMOUNT);
		}
	}

}