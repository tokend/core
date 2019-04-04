// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/test/mocks/MockDatabase.h>
#include "ledger/AccountHelperLegacy.h"
#include "LedgerDelta.h"
#include "util/types.h"
#include "StorageHelperImpl.h"
#include "AccountHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void
AccountHelperLegacy::dropAll(Database& db)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getAccountHelper().dropAll();
}

void
AccountHelperLegacy::storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->getAccountHelper().storeAdd(entry);
}

void
AccountHelperLegacy::storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->getAccountHelper().storeChange(entry);
}

void
AccountHelperLegacy::storeDelete(LedgerDelta& delta, Database& db,
        LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->getAccountHelper().storeDelete(key);
}

bool
AccountHelperLegacy::exists(Database& db, LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    return storageHelper->getAccountHelper().exists(key);
}

LedgerKey
AccountHelperLegacy::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.account().accountID = from.data.account().accountID;
    return ledgerKey;
}

EntryFrame::pointer AccountHelperLegacy::storeLoad(LedgerKey const& key, Database& db)
{
    return loadAccount(key.account().accountID, db);
}

EntryFrame::pointer
AccountHelperLegacy::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AccountFrame>(from);
}

uint64_t
AccountHelperLegacy::countObjects(soci::session& sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM accounts;", into(count);
    return count;
}

AccountFrame::pointer
AccountHelperLegacy::loadAccount(AccountID const& accountID, Database& db, LedgerDelta* delta)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, delta);
    return storageHelper->getAccountHelper().loadAccount(accountID);
}

AccountFrame::pointer
AccountHelperLegacy::loadAccount(LedgerDelta& delta, AccountID const& accountID,
        Database& db)
{
    auto a = loadAccount(accountID, db);
    if (a)
    {
        delta.recordEntry(*a);
    }
    return a;
}

AccountFrame::pointer
AccountHelperLegacy::mustLoadAccount(AccountID const& accountID, Database& db)
{
    auto accountFrame = loadAccount(accountID, db);

    if (!accountFrame)
    {
        throw std::runtime_error("Expect account to exist");
    }

    return accountFrame;
}

bool AccountHelperLegacy::exists(AccountID const &rawAccountID, Database &db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    return storageHelper->getAccountHelper().exists(rawAccountID);
}

std::string const
AccountHelperLegacy::getTableName() const
{
    MockDatabase db;
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    return storageHelper->getAccountHelper().getTableName();
}
}