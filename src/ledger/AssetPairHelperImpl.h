#include "AssetPairHelper.h"
#include "StorageHelper.h"

namespace soci
{
    class session;
}

namespace stellar {
class StatementContext;


class AssetPairHelperImpl : public AssetPairHelper
{
public:
    explicit AssetPairHelperImpl(StorageHelper &storageHelper);

    AssetPairHelperImpl(AssetPairHelperImpl const&) = delete;

    AssetPairHelperImpl& operator=(AssetPairHelperImpl const&) = delete;

    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    uint64_t countObjects() override;
    Database& getDatabase() override;
    LedgerDelta* getLedgerDelta() override;
    bool exists(AssetCode base, AssetCode quote) override;
    bool existsForAsset(AssetCode code) override;
    AssetPairFrame::pointer loadAssetPair(AssetCode base, AssetCode quote) override;
    AssetPairFrame::pointer
    mustLoadAssetPair(AssetCode base, AssetCode quote) override;
    AssetPairFrame::pointer
    tryLoadAssetPairForAssets(AssetCode code1, AssetCode code2) override;
    bool convertAmount(const AssetPairFrame::pointer& assetPair,
                       const AssetCode& destCode, uint64_t amount,
                       Rounding rounding, uint64_t& result) override;
    void
    loadAssetPairs(StatementContext& prep,
                   std::function<void(LedgerEntry const&)> AssetPairProcessor);
    void storeUpdateHelper(bool insert, LedgerEntry const& entry);

private:
    StorageHelper& mStorageHelper;
    const char* mAssetPairColumnSelector;

};

}