#pragma once

#include <unordered_map>
#include "EntryHelperLegacy.h"
#include "AtomicSwapAskFrame.h"

namespace soci
{
class session;
}

namespace stellar
{

class StatementContext;

class AtomicSwapAskHelper : public EntryHelperLegacy
{
public:
    AtomicSwapAskHelper(AtomicSwapAskHelper const&) = delete;
    AtomicSwapAskHelper& operator= (AtomicSwapAskHelper const&) = delete;

    static AtomicSwapAskHelper* Instance()
    {
        static AtomicSwapAskHelper singleton;
        return &singleton;
    }

    void dropAll(Database& db) override;

    void storeAdd(LedgerDelta& delta, Database& db,
                  LedgerEntry const& entry) override;

    void storeChange(LedgerDelta& delta, Database& db,
                     LedgerEntry const& entry) override;

    void storeDelete(LedgerDelta& delta, Database& db,
                     LedgerKey const& key) override;

    bool exists(Database& db, LedgerKey const& key) override;

    LedgerKey getLedgerKey(LedgerEntry const& from) override;

    EntryFrame::pointer storeLoad(LedgerKey const& key,
                                  Database& db) override;

    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;

    uint64_t countObjects(soci::session& sess) override;

    AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(AccountID const& ownerID, uint64_t bidID,
                      Database& db, LedgerDelta* delta = nullptr);

    AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(uint64_t bidID, Database &db,
                      LedgerDelta *delta = nullptr);

    std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>>
    loadAllAtomicSwapAsks(Database& db);

    bool
    existForAsset(Database& db, const AssetCode& code);

private:
    AtomicSwapAskHelper() { ; }
    ~AtomicSwapAskHelper() { ; }

    void storeUpdateHelper(LedgerDelta& delta, Database& db, bool insert,
                           LedgerEntry const& entry);

    void loadAtomicSwapAsks(Database& db, StatementContext& prep,
                            std::function<void(LedgerEntry const&)>
                                    atomicSwapBidProcessor);
};

}