#pragma once

#include "VoteHelper.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class VoteHelperImpl : public VoteHelper, NonCopyable
{
public:
    VoteHelperImpl(StorageHelper& storageHelper);
    virtual void storeChange(LedgerEntry const& entry);

private:
    void
    dropAll() override;

    void
    createIfNotExists() override;

    Database&
    getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    void
    storeAdd(LedgerEntry const& entry) override;

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

    VoteFrame::pointer
    loadVote(uint64_t pollID, AccountID voterID) override;

    bool
    exists(uint64_t const pollID, AccountID voterID) override;

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    void
    deleteForPoll(uint64_t pollID) override;

    void handleDeletedDelta(uint64_t pollID);

    std::string
    getTableSchema();

    StorageHelper& mStorageHelper;
    const char* mVoteColumnSelector;

};

}
