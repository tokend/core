#pragma once

#include "SignerRuleHelper.h"

namespace stellar
{
class StorageHelper;
class StatementContext;

class SignerRuleHelperImpl : public SignerRuleHelper, NonCopyable
{
public:
    SignerRuleHelperImpl(StorageHelper& storageHelper);

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

    std::vector<SignerRuleFrame::pointer>
    loadSignerRules(std::vector<uint64_t> const ruleIDs);

    SignerRuleFrame::pointer
    loadSignerRule(uint64_t const ruleID);

    bool
    exists(uint64_t const ruleID);

    std::vector<uint64_t>
    loadDefaultRuleIDs() override;

    void
    storeUpdate(LedgerEntry const& entry, bool insert);

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    StorageHelper& mStorageHelper;
    const char* mSignerRuleColumnSelector;
};
}

