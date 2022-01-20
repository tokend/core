#pragma once

#include "EntryHelper.h"
#include "StorageHelper.h"
#include "LiquidityPoolHelper.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class LiquidityPoolHelperImpl : public LiquidityPoolHelper, NonCopyable
{
public:
    explicit LiquidityPoolHelperImpl(StorageHelper &storageHelper);

    void dropAll() override;
    void createIfNotExists() override;
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

    bool exists(uint64_t poolID) override;
    bool exists(AssetCode const& lpTokenAsset) override;
    bool exists(AssetCode const& firstAsset, AssetCode const& secondAsset) override;

    LiquidityPoolFrame::pointer loadPool(uint64_t poolID, AccountID accountID) override;
    LiquidityPoolFrame::pointer loadPool(uint64_t poolID) override;
    LiquidityPoolFrame::pointer loadPool(uint64_t poolID, AssetCode const& first, AssetCode const& second) override;
    LiquidityPoolFrame::pointer loadPool(AssetCode const& first, AssetCode const& second) override;

    void loadPools(StatementContext& prep, const std::function<void(LedgerEntry const&)>& lpProcessor) const;

private:
    StorageHelper& mStorageHelper;
    const char* mLPColumnSelector;

    void storeUpdateHelper(bool insert, LedgerEntry const& entry);
};

}
