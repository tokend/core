#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <map>
#include <set>
#include "ledger/EntryFrame.h"
#include "ledger/LedgerHeaderFrame.h"
#include "bucket/LedgerCmp.h"
#include "xdrpp/marshal.h"

namespace stellar
{
class Application;
class Database;

class LedgerDelta
{
public:
    typedef std::map<LedgerKey, EntryFrame::pointer, LedgerEntryIdCmp>
        KeyEntryMap;
private:
    LedgerDelta*
        mOuterDelta;       // set when this delta is nested inside another delta
    LedgerHeader* mHeader; // LedgerHeader to commit changes to

    // objects to keep track of changes
    // ledger header itself
    LedgerHeaderFrame mCurrentHeader;
    LedgerHeader mPreviousHeaderValue;
    // ledger entries
    KeyEntryMap mNew;
    KeyEntryMap mMod;
    std::set<LedgerKey, LedgerEntryIdCmp> mDelete;

    // all created/changed ledger entries:
    LedgerEntryChanges mAllChanges;

    KeyEntryMap mPrevious;

    Database& mDb; // Used strictly for rollback of db entry cache.

    bool mUpdateLastModified;

    void checkState();
    void addEntry(EntryFrame::pointer entry);
    void deleteEntry(EntryFrame::pointer entry);
    void modEntry(EntryFrame::pointer entry);
    void recordEntry(EntryFrame::pointer entry);

    // merge "other" into current ledgerDelta
    void mergeEntries(LedgerDelta& other);

    // helper method that adds a meta entry to "changes"
    // with the previous value of an entry if needed
    void addCurrentMeta(LedgerEntryChanges& changes,
                        LedgerKey const& key) const;

  public:
    // keeps an internal reference to the outerDelta,
    // will apply changes to the outer scope on commit
    explicit LedgerDelta(LedgerDelta& outerDelta);

    // keeps an internal reference to ledgerHeader,
    // will apply changes to ledgerHeader on commit,
    // will clear db entry cache on rollback.
    // updateLastModified: if true, revs the lastModified field
    LedgerDelta(LedgerHeader& ledgerHeader, Database& db,
                bool updateLastModified = true);

    ~LedgerDelta();

    LedgerHeader& getHeader();
    LedgerHeader const& getHeader() const;
    LedgerHeaderFrame& getHeaderFrame();

    // methods to register changes in the ledger entries
    void addEntry(EntryFrame const& entry);
    void deleteEntry(EntryFrame const& entry);
    void deleteEntry(LedgerKey const& key);
    void modEntry(EntryFrame const& entry);
    void recordEntry(EntryFrame const& entry);

    // commits this delta into outer delta
    void commit();
    // aborts any changes pending, flush db cache entries
    void rollback();

    bool updateLastModified() const;

    void markMeters(Application& app) const;

    std::vector<LedgerEntry> getLiveEntries() const;
    std::vector<LedgerKey> getDeadEntries() const;

    LedgerEntryChanges getChanges() const;
    LedgerEntryChanges getAllChanges() const;

    // performs sanity checks against the local state
    void checkAgainstDatabase(Application& app) const;

    KeyEntryMap getState() const
    {
        return mPrevious;
    }
};
}
