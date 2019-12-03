#pragma once

#include "SignerRoleHelper.h"
#include "SignerRoleRulesHelper.h"

namespace stellar
{
class StorageHelper;

class SignerRoleHelperImpl : public SignerRoleHelper, NonCopyable
{
public:
    SignerRoleHelperImpl(StorageHelper& storageHelper);

private:
    void
    dropAll() override;

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

    SignerRoleFrame::pointer
    loadSignerRole(uint64_t const roleID) override;

    bool
    exists(uint64_t const roleID);

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    StorageHelper& mStorageHelper;
    SignerRoleRulesHelper mSignerRoleRulesHelper;
    const char* mSignerRoleColumnSelector;
};
}