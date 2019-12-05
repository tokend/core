#pragma once
#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include <functional>
#include <unordered_map>
#include "StatisticsV2Frame.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class StatisticsV2Helper : public EntryHelper
{
public:
    virtual StatisticsV2Frame::pointer loadStatistics(uint64_t id) = 0;
    virtual StatisticsV2Frame::pointer loadStatistics(AccountID& accountID, StatsOpType statsOpType,
                                              AssetCode const& assetCode, bool isConvertNeeded) = 0;

    virtual StatisticsV2Frame::pointer mustLoadStatistics(uint64_t id) = 0;
    virtual StatisticsV2Frame::pointer mustLoadStatistics(AccountID& accountID, StatsOpType statsOpType,
                                                  AssetCode const& assetCode, bool isConvertNeeded) = 0;
};
}