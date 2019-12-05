#include "ledger/PendingStatisticsHelper.h"

namespace stellar
{

class MockPendingStatisticsHelper : public PendingStatisticsHelper
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
    MOCK_METHOD1(loadPendingStatistics, std::vector<PendingStatisticsFrame::pointer>(uint64_t& requestID));
    MOCK_METHOD2(loadPendingStatistics, PendingStatisticsFrame::pointer(uint64_t& requestID, uint64_t& statsID));
    MOCK_METHOD0(restrictUpdateDelete, void());
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, const LedgerEntry &entry));
    MOCK_METHOD2(load, void(StatementContext &prep, std::function<void(LedgerEntry const&)> processor));
};

}  // namespace stellar