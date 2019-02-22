#pragma once

#include "util/NonCopyable.h"
#include "AssetHelper.h"

namespace soci
{
class session;
}

namespace stellar
{
class StorageHelper;

class AssetHelperImpl : public AssetHelper, NonCopyable
{

public:
    explicit AssetHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

    void
    addTrailingDigits() override;

    void
    storeAdd(LedgerEntry const& entry) override;

    void
    storeChange(LedgerEntry const& entry) override;

    void
    storeDelete(LedgerKey const& key) override;

    bool
    exists(LedgerKey const& key) override;

    bool
    exists(const AssetCode &code) override;

    LedgerKey
    getLedgerKey(LedgerEntry const& from) override;

    EntryFrame::pointer
    storeLoad(LedgerKey const& key) override;

    EntryFrame::pointer
    fromXDR(LedgerEntry const& from) override;

    uint64_t
    countObjects() override;

    AssetFrame::pointer
    loadAsset(AssetCode assetCode) override;

    AssetFrame::pointer
    mustLoadAsset(AssetCode assetCode) override;

    AssetFrame::pointer
    loadAsset(AssetCode assetCode, AccountID owner) override;

    AssetFrame::pointer
    loadStatsAsset() override;

    void
    loadAssets(StatementContext& prep,
               std::function<void(LedgerEntry const&)> assetProcessor) override;

    std::vector<AssetFrame::pointer>
    loadBaseAssets() override;

    bool
    doesAmountFitAssetPrecision(const AssetCode& assetCode, uint64_t amount) override;

    void
    storeUpdateHelper(bool insert, LedgerEntry const& entry);

    Database&
    getDatabase() override;

    StorageHelper& mStorageHelper;
    const char* mAssetColumnSelector;
};

} // namespace stellar
