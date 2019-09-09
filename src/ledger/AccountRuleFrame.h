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

    AccountRuleFrame& operator=(AccountRuleFrame const& other);

    AccountRuleEntry const&
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

    AccountRuleAction const
    getAction() const
    {
        return mAccountRuleEntry.action;
    }

    bool const
    forbids() const
    {
        return mAccountRuleEntry.forbids;
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
