#pragma once

#include "EntryHelperLegacy.h"

namespace stellar
{

class EntryHelperLegacyImpl : public EntryHelperLegacy
{
    LedgerEntryType mEntryType;

    EntryHelperLegacyImpl(LedgerEntryType entryType);

public:
    static EntryHelperLegacyImpl *Instance(LedgerEntryType entryType)
    {
        static EntryHelperLegacyImpl singleton(entryType);
        return &singleton;
    }

    void dropAll(Database& db) override;

    void storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
    void storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
    void storeDelete(LedgerDelta& delta, Database& db, LedgerKey const& key) override;
    bool exists(Database& db, LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer fromXDR(LedgerEntry const &from) override;
    EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey, Database &db) override;
    uint64_t countObjects(soci::session& sess) override;
    uint64_t countObjects(Database& db) override;
};
}
