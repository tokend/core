#include "ledger/AtomicSwapAskHelper.h"

namespace stellar
{

class MockAtomicSwapAskHelper : public AtomicSwapAskHelper
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
    MOCK_METHOD2(loadAtomicSwapAsk, AtomicSwapAskFrame::pointer(
                         AccountID const& ownerID, uint64_t bidID));
    MOCK_METHOD1(loadAtomicSwapAsk, AtomicSwapAskFrame::pointer(uint64_t bidID));
    MOCK_METHOD0(loadAllAtomicSwapAsks, std::unordered_map<AccountID, std::vector<AtomicSwapAskFrame::pointer>>());
    MOCK_METHOD1(existForAsset, bool(const AssetCode& code));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
    MOCK_METHOD2(loadAtomicSwapAsks, void(StatementContext& prep,
                             std::function<void(LedgerEntry const&)>
                               atomicSwapBidProcessor));
};

}  // namespace stellar