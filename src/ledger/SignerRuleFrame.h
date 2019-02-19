#pragma once

#include "EntryFrame.h"

namespace stellar
{

class SignerRuleFrame : public EntryFrame
{
    SignerRuleEntry& mSignerRuleEntry;

    SignerRuleFrame(SignerRuleFrame const& from);

public:
    typedef std::shared_ptr<SignerRuleFrame> pointer;

    static const uint32_t threshold = 1000;

    SignerRuleFrame();
    SignerRuleFrame(LedgerEntry const& from);
    SignerRuleFrame(uint64_t const ruleID, AccountID ownerID,
                    CreateSignerRuleData const data);

    LedgerKey const&
    getKey() const override;

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new SignerRuleFrame(*this));
    }

    SignerRuleEntry const&
    getEntry() const
    {
        return mSignerRuleEntry;
    }

    SignerRuleEntry&
    getEntry()
    {
        clearCached();
        return mSignerRuleEntry;
    }

    SignerRuleResource const&
    getResource() const
    {
        return mSignerRuleEntry.resource;
    }

    bool const
    isForbid() const
    {
        return mSignerRuleEntry.isForbid;
    }

    bool const
    isDefault() const
    {
        return mSignerRuleEntry.isDefault;
    }

    SignerRuleAction const
    getAction() const
    {
        return mSignerRuleEntry.action;
    }

    AccountID const&
    getOwnerID() const
    {
        return mSignerRuleEntry.ownerID;
    }

    uint64_t const
    getID() const
    {
        return mSignerRuleEntry.id;
    }
};
}