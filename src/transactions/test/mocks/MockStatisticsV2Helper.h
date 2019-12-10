#include "ledger/StatisticsV2Helper.h"

namespace stellar
{

class MockStatisticsV2Helper : public StatisticsV2Helper
{
public:
    MOCK_METHOD0(dropAll, void());
    MOCK_METHOD1(storeAdd, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeChange, void(LedgerEntry const& entry));
    MOCK_METHOD1(storeDelete, void(LedgerKey const& key));
    MOCK_METHOD1(exists, bool(LedgerKey const& key));
    MOCK_METHOD1(getLedgerKey, LedgerKey(LedgerEntry const& from));
    MOCK_METHOD1(fromXDR, EntryFrame::pointer(LedgerEntry const& from));
    MOCK_METHOD1(storeLoad, EntryFrame::pointer(LedgerKey const& ledgerKey));
    MOCK_METHOD0(countObjects, uint64_t());
    MOCK_METHOD0(getDatabase, Database&());
    MOCK_METHOD0(getLedgerDelta, LedgerDelta*());
    MOCK_METHOD1(loadStatistics, StatisticsV2Frame::pointer(uint64_t id));
    MOCK_METHOD4(loadStatistics, StatisticsV2Frame::pointer(AccountID& accountID, StatsOpType statsOpType,
            AssetCode const& assetCode, bool isConvertNeeded));
    MOCK_METHOD1(mustLoadStatistics, StatisticsV2Frame::pointer(uint64_t id));
    MOCK_METHOD4(mustLoadStatistics, StatisticsV2Frame::pointer(AccountID& accountID, StatsOpType statsOpType,
            AssetCode const& assetCode, bool isConvertNeeded));
    MOCK_METHOD2(loadStatistics, void(StatementContext& prep, std::function<void(LedgerEntry const&)> processor));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
};

}  // namespace stellar