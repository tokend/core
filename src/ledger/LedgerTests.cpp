// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/Timer.h"
#include "main/Application.h"
#include "main/test.h"
#include "database/Database.h"
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/LedgerManager.h"
#include "ledger/EntryHelperLegacy.h"
#include "ledger/AccountFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include <xdrpp/autocheck.h>
#include "LedgerTestUtils.h"
#include "test/test_marshaler.h"

using namespace stellar;

TEST_CASE("Ledger entry db lifecycle", "[ledger]")
{
    Config cfg(getTestConfig());
    VirtualClock clock;
    Application::pointer app = Application::create(clock, cfg);
    app->start();
    LedgerDeltaImpl delta(app->getLedgerManager().getCurrentLedgerHeader(),
                          app->getDatabase());
    auto& db = app->getDatabase();
    for (size_t i = 0; i < 1000; ++i)
    {
        auto le = LedgerTestUtils::generateValidLedgerEntry(3);
        CHECK(!EntryHelperProvider::existsEntry(db, LedgerEntryKey(le)));
		EntryHelperProvider::storeAddOrChangeEntry(delta, db, le);
        CHECK(EntryHelperProvider::existsEntry(db, LedgerEntryKey(le)));
		CHECK(EntryHelperProvider::storeLoadEntry(LedgerEntryKey(le), db));
		EntryHelperProvider::storeDeleteEntry(delta, db, LedgerEntryKey(le));
        CHECK(!EntryHelperProvider::existsEntry(db, LedgerEntryKey(le)));
		CHECK(!EntryHelperProvider::storeLoadEntry(LedgerEntryKey(le), db));
    }
}

TEST_CASE("single ledger entry insert SQL", "[singlesql][entrysql]")
{
    Config::TestDbMode mode = Config::TESTDB_ON_DISK_SQLITE;
#ifdef USE_POSTGRES
    if (!force_sqlite)
        mode = Config::TESTDB_POSTGRESQL;
#endif

    VirtualClock clock;
    Application::pointer app =
        Application::create(clock, getTestConfig(0, mode));
    app->start();

    LedgerDeltaImpl delta(app->getLedgerManager().getCurrentLedgerHeader(),
                          app->getDatabase());
    auto& db = app->getDatabase();
    auto le = LedgerTestUtils::generateValidLedgerEntry(3);
    auto ctx = db.captureAndLogSQL("ledger-insert");
	EntryHelperProvider::storeAddOrChangeEntry(delta, db, le);
}

TEST_CASE("DB cache interaction with transactions", "[ledger][dbcache]")
{
    Config::TestDbMode mode = Config::TESTDB_ON_DISK_SQLITE;
#ifdef USE_POSTGRES
    if (!force_sqlite)
        mode = Config::TESTDB_POSTGRESQL;
#endif

    VirtualClock clock;
    Application::pointer app =
        Application::create(clock, getTestConfig(0, mode));
    app->start();

    auto& db = app->getDatabase();
    auto& session = db.getSession();

    LedgerEntry le;
    do
    {
        le = LedgerTestUtils::generateValidLedgerEntry(3);
    } while (le.data.type() != LedgerEntryType::ACCOUNT);

    auto key = LedgerEntryKey(le);

    {
        LedgerDeltaImpl delta(app->getLedgerManager().getCurrentLedgerHeader(),
                              app->getDatabase());
        soci::transaction sqltx(session);
        EntryHelperProvider::storeAddOrChangeEntry(delta, db, le);
        sqltx.commit();
    }

    // The write should have removed it from the cache.
	auto accountHelper = AccountHelperLegacy::Instance();
    REQUIRE(!accountHelper->cachedEntryExists(key, db));

    uint64_t accountType0, accountType1;

    {
        soci::transaction sqltx(session);
        LedgerDeltaImpl delta(app->getLedgerManager().getCurrentLedgerHeader(),
                              app->getDatabase());

        auto acc = accountHelper->loadAccount(key.account().accountID, db);
        REQUIRE(accountHelper->cachedEntryExists(key, db));

        accountType0 = acc->getAccount().roleID;
        acc->getAccount().roleID = 1;
        accountType1 = acc->getAccount().roleID;

        EntryHelperProvider::storeChangeEntry(delta, db, acc->mEntry);
        // Write should flush cache, put balance1 in DB _pending commit_.
        REQUIRE(!accountHelper->cachedEntryExists(key, db));

        acc = accountHelper->loadAccount(key.account().accountID, db);
        // Read should have populated cache.
        REQUIRE(accountHelper->cachedEntryExists(key, db));

        // Read-back value should be balance1
        REQUIRE(acc->getAccount().roleID == accountType1);

        LOG(INFO) << "accountType0: " << static_cast<int32_t >(accountType0);
        LOG(INFO) << "accountType1: " << static_cast<int32_t >(accountType1);

        // Scope-end will rollback sqltx and delta
    }

    // Rollback should have evicted changed value from cache.
    CHECK(!accountHelper->cachedEntryExists(key, db));

    auto acc = accountHelper->loadAccount(key.account().accountID, db);
    // Read should populate cache
    CHECK(accountHelper->cachedEntryExists(key, db));
    LOG(INFO) << "cached accountType: " << static_cast<int32_t >(acc->getAccount().roleID);

    CHECK(accountType0 == acc->getAccount().roleID);
}
