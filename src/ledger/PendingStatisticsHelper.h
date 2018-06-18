#pragma once
// Created by artem on 11.06.18.
//

#include "LedgerDelta.h"
#include "EntryHelper.h"
#include "PendingStatisticsFrame.h"

namespace soci
{
    class session;
}

namespace stellar
{
    class StatementContext;

class PendingStatisticsHelper : public EntryHelper {

public:

    static PendingStatisticsHelper *Instance() {
        static PendingStatisticsHelper singleton;
        return &singleton;
    }

    void dropAll(Database &db) override;
    void storeAdd(LedgerDelta &delta, Database &db, LedgerEntry const &entry) override;
    void storeChange(LedgerDelta &delta, Database &db, LedgerEntry const &entry) override;
    void storeDelete(LedgerDelta &delta, Database &db, LedgerKey const &key) override;
    bool exists(Database& db, LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& key, Database& db) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects(soci::session& sess) override;

    std::vector<PendingStatisticsFrame::pointer> loadPendingStatistics(uint64_t& requestID, Database& db,
                                                                       LedgerDelta& delta);

    PendingStatisticsFrame::pointer loadPendingStatistics(uint64_t& requestID, uint64_t& statsID, Database& db,
                                                          LedgerDelta* delta = nullptr);

private:
    void storeUpdateHelper(LedgerDelta &delta, Database &db, bool insert, const LedgerEntry &entry);

    void load(StatementContext &prep, std::function<void(LedgerEntry const&)> processor);
};

}