#include "AccountSpecificRuleFrame.h"

namespace stellar
{

AccountSpecificRuleFrame::AccountSpecificRuleFrame()
        : EntryFrame(LedgerEntryType::ACCOUNT_SPECIFIC_RULE)
        , mAccountSpecificRuleEntry(mEntry.data.accountSpecificRule())
{
}

AccountSpecificRuleFrame::AccountSpecificRuleFrame(LedgerEntry const& from)
        : EntryFrame(from)
        , mAccountSpecificRuleEntry(mEntry.data.accountSpecificRule())
{
}

AccountSpecificRuleFrame::AccountSpecificRuleFrame(
        AccountSpecificRuleFrame const& from)
        : AccountSpecificRuleFrame(from.mEntry)
{
}

AccountSpecificRuleFrame::AccountSpecificRuleFrame(uint64_t const id,
        CreateAccountSpecificRuleData const& data) : AccountSpecificRuleFrame()
{
    mAccountSpecificRuleEntry.id = id;
    mAccountSpecificRuleEntry.ledgerKey = data.ledgerKey;
    mAccountSpecificRuleEntry.accountID = data.accountID;
    mAccountSpecificRuleEntry.forbids = data.forbids;
}

AccountSpecificRuleFrame&
AccountSpecificRuleFrame::operator=(const AccountSpecificRuleFrame& other)
{
    if (&other != this)
    {
        mAccountSpecificRuleEntry = other.mAccountSpecificRuleEntry;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

EntryFrame::pointer
AccountSpecificRuleFrame::copy() const
{
    return EntryFrame::pointer(new AccountSpecificRuleFrame(*this));
}

LedgerKey const&
AccountSpecificRuleFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);
        mKey.accountSpecificRule().id = getID();
        mKeyCalculated = true;
    }

    return mKey;
}

}