#pragma once

#include "PollHelper.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class PollHelperImpl : public PollHelper, NonCopyable
{
public:
    PollHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

    void
    createIfNotExists() override;

    void
    permissionTypeMigration() override;

    Database&
    getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

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

    PollFrame::pointer
    loadPoll(uint64_t id) override;

    PollFrame::pointer
    mustLoadPoll(uint64_t id) override;

    bool
    exists(uint64_t id) override;

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    std::string
    getTableSchema();

    StorageHelper& mStorageHelper;
    const char* mPollColumnSelector;

};

}
