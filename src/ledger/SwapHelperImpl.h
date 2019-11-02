#pragma once

#include "SwapHelper.h"
#include "util/NonCopyable.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class SwapHelperImpl : public SwapHelper, NonCopyable
{
public:
    SwapHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

    void
    storeAdd(LedgerEntry const& entry) override;

    void
    storeChange(LedgerEntry const& entry) override;

    void
    storeDelete(LedgerKey const& key) override;

    bool
    exists(LedgerKey const& key) override;

    LedgerKey
    getLedgerKey(LedgerEntry const& key) override;

    EntryFrame::pointer
    fromXDR(LedgerEntry const& entry) override;

    EntryFrame::pointer
    storeLoad(LedgerKey const& key) override;

    uint64_t
    countObjects() override;

    Database&
    getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    SwapFrame::pointer
    loadSwap(uint64_t id) override;

    SwapFrame::pointer
    mustLoadSwap(uint64_t id) override;

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    bool
    existForAsset(const AssetCode& assetCode) override;

    bool
    exists(uint64_t swapID) override;

    StorageHelper& mStorageHelper;
    const char* mSwapColumnSelector;
};

}
