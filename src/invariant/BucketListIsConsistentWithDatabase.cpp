// Copyright 2017 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "invariant/BucketListIsConsistentWithDatabase.h"
#include "bucket/Bucket.h"
#include "bucket/BucketInputIterator.h"
#include "crypto/Hex.h"
#include "invariant/InvariantManager.h"
#include "ledger/LedgerRange.h"
//#include "ledger/LedgerTxn.h"
//#include "ledger/LedgerTxnEntry.h"
#include "lib/util/format.h"
#include "main/Application.h"
#include "xdrpp/printer.h"
#include "ledger/EntryHelperLegacy.h"

namespace stellar
{

static std::string
checkAgainstDatabase(Database& db, LedgerEntry const& entry)
{
    LedgerKey key = LedgerEntryKey(entry);
    auto legacyHelper = EntryHelperProvider::getHelper(entry.data.type()); // helper existing handled above
    legacyHelper->flushCachedEntry(key, db);
    EntryFrame::pointer fromDb = legacyHelper->storeLoad(key, db);

    if (!fromDb)
    {
        std::string s{
            "Inconsistent state between objects (not found in database): "};
        s += xdr::xdr_to_string(entry, "live");
        return s;
    }

    if (fromDb->mEntry == entry)
    {
        return {};
    }
    else
    {
        std::string s{"Inconsistent state between objects: "};
        s += xdr::xdr_to_string(fromDb->mEntry, "db");
        s += xdr::xdr_to_string(entry, "live");
        return s;
    }
}

static std::string
checkAgainstDatabase(Database& db, LedgerKey const& key)
{
    auto legacyHelper = EntryHelperProvider::getHelper(key.type()); // helper existing handled above
    legacyHelper->flushCachedEntry(key, db);
    EntryFrame::pointer fromDb = legacyHelper->storeLoad(key, db);
    if (!fromDb)
    {
        return {};
    }

    std::string s = "Entry with type DEADENTRY found in database ";
    s += xdr::xdr_to_string(fromDb->mEntry, "db");
    return s;
}

std::shared_ptr<Invariant>
BucketListIsConsistentWithDatabase::registerInvariant(Application& app)
{
    return app.getInvariantManager()
        .registerInvariant<BucketListIsConsistentWithDatabase>(app);
}

BucketListIsConsistentWithDatabase::BucketListIsConsistentWithDatabase(
    Application& app)
    : Invariant(true), mApp(app)
{
}

std::string
BucketListIsConsistentWithDatabase::getName() const
{
    return "BucketListIsConsistentWithDatabase";
}

std::string
BucketListIsConsistentWithDatabase::checkOnBucketApply(
    std::shared_ptr<Bucket const> bucket, uint32_t oldestLedger,
    uint32_t newestLedger)
{
    Database& db = mApp.getDatabase();

    bool hasPreviousEntry = false;
    BucketEntry previousEntry;
    for (BucketInputIterator iter(bucket); iter; ++iter)
    {
        auto const& e = *iter;
        if (hasPreviousEntry && !BucketEntryIdCmp{}(previousEntry, e))
        {
            std::string s = "Bucket has out of order entries: ";
            s += xdr::xdr_to_string(previousEntry, "previous");
            s += xdr::xdr_to_string(e, "current");
            return s;
        }
        previousEntry = e;
        hasPreviousEntry = true;

        switch (e.type())
        {
            case  BucketEntryType::LIVEENTRY:
            {
                auto s = checkAgainstDatabase(db, e.liveEntry());
                if (!s.empty())
                {
                    return s;
                }
            }
            case BucketEntryType::DEADENTRY:
            {
                auto s = checkAgainstDatabase(db, e.deadEntry());
                if (!s.empty())
                {
                    return s;
                }
            }
        }
    }

    return {};
}
}
