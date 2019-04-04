#pragma once

#include "AccountRuleFrame.h"
#include "ledger/AccountRuleHelper.h"
#include "ledger/StorageHelper.h"
#include "xdr/Stellar-types.h"

namespace stellar
{
class LedgerManager;
class StatementContext;

class AccountRuleHelperImpl : public AccountRuleHelper, NonCopyable
{
  public:
    explicit AccountRuleHelperImpl(StorageHelper& storageHelper);

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

    Database& getDatabase() override;

    LedgerDelta*
    getLedgerDelta() override;

    std::string const
    getTableName() const override;

    std::vector<AccountRuleFrame::pointer>
    loadAccountRules(std::vector<uint64_t> const ruleIDs) override;

    void
    load(StatementContext& prep, std::function<void(LedgerEntry const&)> processor);

    void storeUpdate(LedgerEntry const& entry, bool insert);

    Database& mDb;
    LedgerDelta* mLedgerDelta{nullptr};

    const char* mAccountRuleSelector;
    const char* mTableName;
};

} // namespace stellar
