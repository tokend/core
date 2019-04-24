#pragma once

#include "EntryFrame.h"

namespace stellar
{

class AccountSpecificRuleFrame : public EntryFrame
{
    AccountSpecificRuleEntry& mAccountSpecificRuleEntry;
    AccountSpecificRuleFrame(AccountSpecificRuleFrame const& from);

public:
    typedef std::shared_ptr<AccountSpecificRuleFrame> pointer;

    AccountSpecificRuleFrame();
    AccountSpecificRuleFrame(LedgerEntry const& from);

    AccountSpecificRuleFrame& operator=(AccountSpecificRuleFrame const& other);
    EntryFrame::pointer copy() const override;

    LedgerKey const&
    getKey() const override;

    AccountSpecificRuleEntry&
    getEntry()
    {
        clearCached();
        return mAccountSpecificRuleEntry;
    }

    uint64_t const
    getID() const
    {
        return mAccountSpecificRuleEntry.id;
    }

    bool const
    forbids() const
    {
        return mAccountSpecificRuleEntry.forbids;
    }
};
}
