#pragma once

#include "AccountRoleHelper.h"
#include "AccountRoleRulesHelper.h"

namespace soci
{
class session;
}

namespace stellar
{
class StorageHelper;
class Application;
class StatementContext;

class AccountRoleHelperImpl : public AccountRoleHelper, NonCopyable
{
public:
    AccountRoleHelperImpl(StorageHelper& storageHelper);

private:
    void dropAll() override;
    void storeAdd(LedgerEntry const& entry) override;
    void storeChange(LedgerEntry const& entry) override;
    void storeDelete(LedgerKey const& key) override;
    bool exists(LedgerKey const& key) override;
    LedgerKey getLedgerKey(LedgerEntry const& from) override;
    EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
    EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
    uint64_t countObjects() override;

    bool
    exists(uint64 roleID) override;

    Database& getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    AccountRoleFrame::pointer
    loadAccountRole(uint64_t const roleID) override;

    std::vector<uint64_t>
    loadRoleIDsByRule(uint64_t const ruleID) override;

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    void storeUpdate(LedgerEntry const &entry, bool insert);
    StorageHelper& mStorageHelper;
    AccountRoleRulesHelper mAccountRoleRulesHelper;

    const char* mAccountRoleSelector;
};
} // namespace stellar