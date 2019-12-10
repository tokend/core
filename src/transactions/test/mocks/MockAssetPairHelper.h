#include "ledger/AssetPairHelper.h"

namespace stellar
{

class MockAssetPairHelper : public AssetPairHelper
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
    MOCK_METHOD1(existsForAsset, bool(AssetCode code));
    MOCK_METHOD2(exists, bool(AssetCode base, AssetCode quote));
    MOCK_METHOD2(loadAssetPair, AssetPairFrame::pointer(AssetCode base, AssetCode quote));
    MOCK_METHOD2(mustLoadAssetPair, AssetPairFrame::pointer(AssetCode base, AssetCode quote));
    MOCK_METHOD2(tryLoadAssetPairForAssets, AssetPairFrame::pointer(AssetCode code1, AssetCode code2));
    MOCK_METHOD2(loadAssetPairs, void((StatementContext& prep,
                  std::function<void(LedgerEntry const&)> AssetPairProcessor)));
    MOCK_METHOD2(storeUpdateHelper, void(bool insert, LedgerEntry const& entry));
    MOCK_METHOD5(convertAmount, bool(const AssetPairFrame::pointer& assetPair,
                  const AssetCode& destCode, uint64_t amount,
                    Rounding rounding, uint64_t& result));
};

}  // namespace stellar