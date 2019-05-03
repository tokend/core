#include "AccountRuleFrame.h"

namespace stellar
{

AccountRuleFrame::AccountRuleFrame()
    : EntryFrame(LedgerEntryType::ACCOUNT_RULE)
    , mAccountRuleEntry(mEntry.data.accountRule())
{
}

AccountRuleFrame::AccountRuleFrame(LedgerEntry const& from)
    : EntryFrame(from)
    , mAccountRuleEntry(mEntry.data.accountRule())
{
}

AccountRuleFrame::AccountRuleFrame(
    AccountRuleFrame const& from)
    : AccountRuleFrame(from.mEntry)
{
}

void
AccountRuleFrame::ensureValid(const AccountRuleEntry& entry)
{
}

void
AccountRuleFrame::ensureValid() const
{
    ensureValid(mAccountRuleEntry);
}

EntryFrame::pointer
AccountRuleFrame::copy() const
{
    return EntryFrame::pointer(new AccountRuleFrame(*this));
}

AccountRuleFrame&
AccountRuleFrame::operator=(const AccountRuleFrame& other)
{
    if (&other != this)
    {
        mAccountRuleEntry = other.mAccountRuleEntry;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}
} // namespace stellar
