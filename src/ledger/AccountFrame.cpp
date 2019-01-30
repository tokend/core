// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "AccountFrame.h"
#include "LedgerDelta.h"
#include "database/Database.h"
#include "ledger/AccountTypeLimitsFrame.h"
#include "lib/util/format.h"
#include "util/basen.h"
#include "util/types.h"

using namespace soci;
using namespace std;

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
    AccountFrame::pointer ret = make_shared<AccountFrame>(id);
    return ret;
}

bool
AccountFrame::signerCompare(Signer const& s1, Signer const& s2)
{
    return s1.pubKey < s2.pubKey;
}

bool
AccountFrame::isBlocked() const
{
    return mAccountEntry.blockReasons > 0;
}

void
AccountFrame::setBlockReasons(uint32 reasonsToAdd, uint32 reasonsToRemove)
{
    mAccountEntry.blockReasons |= reasonsToAdd;
    mAccountEntry.blockReasons &= ~reasonsToRemove;
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
