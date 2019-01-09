#pragma once

#include "ledger/EntryFrame.h"

namespace stellar
{
class AccountRuleFrame : public EntryFrame
{
    AccountRuleEntry& mAccountRuleEntry;
    AccountRuleFrame(AccountRuleFrame const& from);

  public:
    AccountRuleFrame();
    explicit AccountRuleFrame(LedgerEntry const& from);

    typedef std::shared_ptr<AccountRuleFrame> pointer;

    AccountRuleEntry&
    getRuleEntry() const
    {
        return mAccountRuleEntry;
    }

    uint64_t const
    getID() const
    {
        return mAccountRuleEntry.id;
    }

    AccountRuleResource const
    getResource() const
    {
        return mAccountRuleEntry.resource;
    }

    std::string const
    getAction() const
    {
        return mAccountRuleEntry.action;
    }

    bool const
    isForbid() const
    {
        return mAccountRuleEntry.isForbid;
    }

    std::string const
    getDetails() const
    {
        return mAccountRuleEntry.details;
    }

    EntryFrame::pointer copy() const override;

    static void ensureValid(const AccountRuleEntry& entry);
    void ensureValid() const;
};

} // namespace stellar
