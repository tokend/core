#pragma once

#include "ledger/EntryFrame.h"

namespace stellar
{

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

    LedgerKey const&
    getKey() const override;

    AccountID*
    getReferrer() const
    {
        mAccountEntry.referrer.get();
    }

    void
    setReferrer(AccountID const& referrer)
    {
        mAccountEntry.referrer.activate() = referrer;
    }

    uint64_t
    getAccountRole() const;

    void
    setAccountRole(uint64_t roleID);
};
} // namespace stellar
