#pragma once
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
    virtual void restrictUpdateDelete() = 0;
    virtual std::vector<PendingStatisticsFrame::pointer> loadPendingStatistics(uint64_t& requestID0) = 0;
    virtual PendingStatisticsFrame::pointer loadPendingStatistics(uint64_t& requestID, uint64_t& statsID) = 0;

private:
    virtual void storeUpdateHelper(bool insert, const LedgerEntry &entry) = 0;
    virtual void load(StatementContext &prep, std::function<void(LedgerEntry const&)> processor) = 0;
};

}