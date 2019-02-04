#pragma once

#include "EntryHelper.h"
#include "AtomicSwapBidFrame.h"

namespace soci
{
    class session;
}

namespace stellar
{

    class StatementContext;

    class AtomicSwapBidHelper : public EntryHelperLegacy
    {
    public:
        AtomicSwapBidHelper(AtomicSwapBidHelper const&) = delete;
        AtomicSwapBidHelper& operator= (AtomicSwapBidHelper const&) = delete;

        static AtomicSwapBidHelper* Instance()
        {
            static AtomicSwapBidHelper singleton;
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

        AtomicSwapBidFrame::pointer
        loadAtomicSwapBid(AccountID const& ownerID, uint64_t bidID,
                          Database& db, LedgerDelta* delta = nullptr);

        AtomicSwapBidFrame::pointer
        loadAtomicSwapBid(uint64_t bidID, Database &db,
                          LedgerDelta *delta = nullptr);

        std::unordered_map<AccountID, std::vector<AtomicSwapBidFrame::pointer>>
        loadAllAtomicSwapBids(Database& db);

    private:
        AtomicSwapBidHelper() { ; }
        ~AtomicSwapBidHelper() { ; }

        void storeUpdateHelper(LedgerDelta& delta, Database& db, bool insert,
                               LedgerEntry const& entry);

        void loadAtomicSwapBids(Database& db, StatementContext& prep,
                                std::function<void(LedgerEntry const&)>
                                        atomicSwapBidProcessor);
    };

}