// Copyright 2017 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CacheIsConsistentWithDatabase.h"
#include "ledger/LedgerDelta.h"
#include "ledger/EntryHelper.h"
#include "lib/util/format.h"
#include "xdrpp/printer.h"
#include "ledger/StorageHelperImpl.h"

namespace stellar
{

    CacheIsConsistentWithDatabase::CacheIsConsistentWithDatabase(
            Database &db) : Invariant(true), mDb{db}
    {
    }

    CacheIsConsistentWithDatabase::
    ~CacheIsConsistentWithDatabase() = default;

    std::string
    CacheIsConsistentWithDatabase::getName() const {
        return "cache is consistent with database";
    }

    std::string
    CacheIsConsistentWithDatabase::check(LedgerDelta const &delta) const {
        StorageHelperImpl storageHelperImpl(mDb, nullptr);
        StorageHelper& storageHelper = storageHelperImpl;
        for (auto const &l : delta.getLiveEntries()) {
            checkAgainstDatabase(l);
        }

        for (auto const &d : delta.getDeadEntries()) {
            if (storageHelper.getHelper(d.type())->exists(d)) {
                return fmt::format("Inconsistent state; entry should not exist in database: {}",
                                   xdr::xdr_to_string(d));
            }
        }

        return {};
    }

    std::string CacheIsConsistentWithDatabase::checkAgainstDatabase(LedgerEntry const &entry) const{
        StorageHelperImpl storageHelperImpl(mDb, nullptr);
        StorageHelper& storageHelper = storageHelperImpl;
        LedgerKey key = storageHelper.getHelper(entry.data.type())->getLedgerKey(entry);
        auto legacyHelper = storageHelper.getHelper(entry.data.type()); // helper existing handled above
        legacyHelper->flushCachedEntry(key);
        EntryFrame::pointer fromDb = legacyHelper->storeLoad(key);

        if (!fromDb || !(fromDb->mEntry == entry))
        {
            std::string s;
            s = "Inconsistent state between objects: ";
            s += !!fromDb ? xdr::xdr_to_string(fromDb->mEntry, "db") : "db: nullptr\n";
            s += xdr::xdr_to_string(entry, "live");
            throw std::runtime_error(s);
        }
        return {};
    }
}