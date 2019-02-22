#include "AccountFrame.h"

namespace stellar
{
using xdr::operator<;

AccountFrame::AccountFrame()
    : EntryFrame(LedgerEntryType::ACCOUNT), mAccountEntry(mEntry.data.account())
{
}

AccountFrame::AccountFrame(LedgerEntry const& from)
    : EntryFrame(from), mAccountEntry(mEntry.data.account())
{
}

AccountFrame::AccountFrame(AccountFrame const& from) : AccountFrame(from.mEntry)
{
}

AccountFrame::AccountFrame(AccountID const& id) : AccountFrame()
{
    mAccountEntry.accountID = id;
}

LedgerKey const&
AccountFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::ACCOUNT);
        mKey.account().accountID = getID();
        mKeyCalculated = true;
    }

    return mKey;
}

AccountFrame::pointer
AccountFrame::makeAuthOnlyAccount(AccountID const& id)
{
    AccountFrame::pointer ret = std::make_shared<AccountFrame>(id);
    return ret;
}

AccountID const&
AccountFrame::getID() const
{
    return (mAccountEntry.accountID);
}

uint64_t
AccountFrame::getAccountRole() const
{
    return mAccountEntry.roleID;
}
void
AccountFrame::setAccountRole(uint64_t accountRoleID)
{
   mAccountEntry.roleID = accountRoleID;
}

} // namespace stellar
