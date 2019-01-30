#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryFrame.h"
#include "map"
#include "xdr/Stellar-ledger-entries-account.h"
#include <functional>
#include <unordered_map>

namespace soci
{
class session;
namespace details
{
class prepare_temp_type;
}
} // namespace soci

namespace stellar
{
class LedgerManager;

class AccountFrame : public EntryFrame
{
    AccountEntry& mAccountEntry;

    AccountFrame(AccountFrame const& from);

  public:
    typedef std::shared_ptr<AccountFrame> pointer;

    AccountFrame();
    AccountFrame(LedgerEntry const& from);
    AccountFrame(AccountID const& id);

    // builds an accountFrame for the sole purpose of authentication
    static AccountFrame::pointer makeAuthOnlyAccount(AccountID const& id);

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new AccountFrame(*this));
    }

    bool isBlocked() const;
    void setBlockReasons(uint32 reasonsToAdd, uint32 reasonsToRemove);
    AccountID const& getID() const;

    AccountEntry const&
    getAccount() const
    {
        return mAccountEntry;
    }

    AccountEntry&
    getAccount()
    {
        clearCached();
        return mAccountEntry;
    }

    uint32
    getBlockReasons() const
    {
        return mAccountEntry.blockReasons;
    }

    LedgerKey const&
    getKey() const override;

    AccountID
    getRecoveryID() const
    {
        CLOG(ERROR, "FIXME!!!!!!!!!!!!") << "RECOVERY will be implemented on signer level (getter)";
        return PubKeyUtils::random();
    }

    void
    setRecoveryID(const AccountID& recovery)
    {
        CLOG(ERROR, "FIXME!!!!!!!!!!!!") << "RECOVERY will be implemented on signer level";
    }

    uint64_t getAccountRole() const;
    void setAccountRole(uint64_t accountRoleID);

    // compare signers, ignores weight
    static bool signerCompare(Signer const& s1, Signer const& s2);
};
} // namespace stellar
