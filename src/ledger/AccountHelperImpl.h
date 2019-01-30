#pragma once

#include "AccountHelper.h"
#include "util/NonCopyable.h"

namespace stellar
{
class StorageHelper;

class AccountHelperImpl : public AccountHelper, NonCopyable
{
public:
    AccountHelperImpl(StorageHelper& storageHelper);

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

    AccountFrame::pointer
    loadAccount(AccountID const& accountID) override;

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    bool
    exists(AccountID const &rawAccountID);

    StorageHelper& mStorageHelper;
    const char* mAccountColumnSelector;
};

}
