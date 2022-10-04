#include <ledger/LiquidityPoolHelper.h>

namespace stellar
{

    class MockLiquidityPoolHelper : public LiquidityPoolHelper
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
        MOCK_METHOD1(exists, bool(uint64_t poolID));
        MOCK_METHOD1(exists, bool(AssetCode const& lpTokenAsset));
        MOCK_METHOD2(exists, bool(AssetCode const& firstAsset, AssetCode const& secondAsset));
        MOCK_METHOD1(loadPool, LiquidityPoolFrame::pointer(uint64_t poolID));
        MOCK_METHOD1(loadPool, LiquidityPoolFrame::pointer(AssetCode const& lpTokenAsset));
    };

} // namespace stellar
