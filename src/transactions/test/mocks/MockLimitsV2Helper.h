#include "ledger/LimitsV2Helper.h"

namespace stellar
{

class MockLimitsV2Helper : public LimitsV2Helper
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
    MOCK_METHOD1(flushCachedEntry, void(LedgerKey const& key));
    MOCK_METHOD1(cachedEntryExists, bool(LedgerKey const& key));
    MOCK_METHOD4(loadLimits, std::vector<LimitsV2Frame::pointer>(
                 std::vector<StatsOpType> statsOpTypes,
                 AssetCode assetCode, xdr::pointer<AccountID> accountID,
                 uint64_t* accountType));
    MOCK_METHOD5(loadLimits, LimitsV2Frame::pointer(StatsOpType statsOpType, AssetCode assetCode,
                 xdr::pointer<AccountID> accountID, uint64_t* accountType,
                 bool isConvertNeeded));
    MOCK_METHOD1(loadLimits, LimitsV2Frame::pointer(uint64_t id));
    MOCK_METHOD2(loadLimitsForAsset,std::vector<LimitsV2Frame::pointer>(Database& db, AssetCode const& code));
    MOCK_METHOD1(obtainSqlStatsOpTypesString, std::string(std::vector<StatsOpType> stats));
};

}  // namespace stellar