#pragma once 

#include "DataHelper.h"

namespace stellar
{
class StorageHelper;
class StatementContext;
class DataHelperImpl : public DataHelper, NonCopyable
{
    void
    dropAll() override;

    void
    createIfNotExists() override;

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

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    DataFrame::pointer 
    loadData(uint64_t id) override;

    StorageHelper& mStorageHelper;
    const char* mDataColumnSelector;

public:
    DataHelperImpl(StorageHelper& storageHelper);
};
} // namespace stellar
