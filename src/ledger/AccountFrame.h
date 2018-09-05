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
    bool mUpdateSigners;

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

    void normalize();

    bool isValid();

    static bool
    isLimitsValid(Limits const& limits)
    {
        if (limits.dailyOut < 0)
            return false;
        return limits.dailyOut <= limits.weeklyOut &&
               limits.weeklyOut <= limits.monthlyOut &&
               limits.monthlyOut <= limits.annualOut;
    }

    void
    setUpdateSigners(bool updateSigners)
    {
        normalize();
        mUpdateSigners = updateSigners;
    }

    void
    initLoaded(bool updateSigners)
    {
        setUpdateSigners(updateSigners);
        assert(isValid());
        clearCached();
    }

    bool isBlocked() const;
    void setBlockReasons(uint32 reasonsToAdd, uint32 reasonsToRemove);
    AccountID const& getID() const;

    bool
    checkPolicy(AccountPolicies policy) const
    {
        auto policyValue = static_cast<int32_t>(policy);
        return (mAccountEntry.policies & policyValue) == policyValue;
    }

    uint32_t getMasterWeight() const;
    uint32_t getHighThreshold() const;
    uint32_t getMediumThreshold() const;
    uint32_t getLowThreshold() const;

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

    bool
    getUpdateSigners() const
    {
        return mUpdateSigners;
    }

    AccountType
    getAccountType() const
    {
        return mAccountEntry.accountType;
    }

    uint32
    getBlockReasons() const
    {
        return mAccountEntry.blockReasons;
    }

    void
    setAccountType(AccountType accountType)
    {
        mAccountEntry.accountType = accountType;
    }

    void
    setReferrer(AccountID referrer)
    {
        mAccountEntry.referrer.activate() = referrer;
    }

    AccountID*
    getReferrer() const
    {
        return mAccountEntry.referrer.get();
    }

    AccountID
    getRecoveryID() const
    {
        return mAccountEntry.recoveryID;
    }

    void
    setRecoveryID(const AccountID& recovery)
    {
        mAccountEntry.recoveryID = recovery;
    }

    int32_t
    getPolicies() const
    {
        return mAccountEntry.policies;
    }
    uint32
    getKYCLevel() const
    {
        if (mAccountEntry.ext.v() == LedgerVersion::USE_KYC_LEVEL)
        {
            return mAccountEntry.ext.kycLevel();
        }
        else if (mAccountEntry.ext.v() ==
                 LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES)
        {
            return mAccountEntry.ext.ext_0().kycLevel;
        }
        else
        {
            return 0;
        }
    }
    void
    setKYCLevel(uint32 kycLevel)
    {
        if (mAccountEntry.ext.v() == LedgerVersion::USE_KYC_LEVEL)
        {
            mAccountEntry.ext.kycLevel() = kycLevel;
        }
        else if (mAccountEntry.ext.v() ==
                 LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES)
        {
            mAccountEntry.ext.ext_0().kycLevel = kycLevel;
        }
        else if (kycLevel != 0)
        {
            throw std::runtime_error("Could not read KYC Level");
        }
    }
    uint32
    getAccountRole() const
    {
        if (mAccountEntry.ext.v() ==
                 LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES)
        {
            return mAccountEntry.ext.ext_0().accountRole;
        }
        else
        {
            return 0;
        }
    }
    void
    setAccountRole(uint32 accountRole)
    {
        if (mAccountEntry.ext.v() ==
                 LedgerVersion::REPLACE_ACCOUNT_TYPES_WITH_POLICIES)
        {
            mAccountEntry.ext.ext_0().accountRole = accountRole;
        }
        else if (accountRole != 0)
        {
            throw std::runtime_error("Could not read account role");
        }
    }
    // compare signers, ignores weight
    static bool signerCompare(Signer const& s1, Signer const& s2);
};
} // namespace stellar
