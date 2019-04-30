#pragma once

#include "AccountSpecificRuleHelper.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class AccountSpecificRuleHelperImpl : public AccountSpecificRuleHelper, NonCopyable
{
public:
    explicit AccountSpecificRuleHelperImpl(StorageHelper& storageHelper);

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

    void
    deleteRulesForEntry(LedgerKey const& key) override;

    bool
    exists(LedgerKey const& key) override;

    LedgerKey
    getLedgerKey(LedgerEntry const& entry) override;

    EntryFrame::pointer
    fromXDR(LedgerEntry const& entry) override;

    EntryFrame::pointer
    storeLoad(LedgerKey const& key) override;

    uint64_t
    countObjects() override;

    AccountSpecificRuleFrame::pointer
    loadRule(uint64_t id) override;

    AccountSpecificRuleFrame::pointer
    loadRule(const LedgerKey &ledgerKey, AccountID const* accountID, bool exact) override;

    AccountSpecificRuleFrame::pointer
    mustLoadRule(uint64_t id) override;

    bool
    exists(uint64_t id) override;

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    StorageHelper& mStorageHelper;
    const char* mRuleColumnSelector;
};
}
