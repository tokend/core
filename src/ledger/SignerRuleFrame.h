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

    SignerRuleFrame();
    SignerRuleFrame(LedgerEntry const& from);


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

    std::string const
    getAction() const
    {
        return mSignerRuleEntry.action;
    }
};
}