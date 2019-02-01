#pragma once

#include "EntryFrame.h"

namespace stellar
{

class SignerRoleFrame : public EntryFrame
{
    SignerRoleEntry& mSignerRoleEntry;

    SignerRoleFrame(SignerRoleFrame const& from);

public:
    typedef std::shared_ptr<SignerRoleFrame> pointer;

    SignerRoleFrame();
    SignerRoleFrame(LedgerEntry const& from);

    LedgerKey const&
    getKey() const override;

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new SignerRoleFrame(*this));
    }

    SignerRoleEntry const&
    getEntry() const
    {
        return mSignerRoleEntry;
    }

    SignerRoleEntry&
    getEntry()
    {
        clearCached();
        return mSignerRoleEntry;
    }

    std::vector<uint64_t> const
    getRuleIDs() const
    {
        return mSignerRoleEntry.ruleIDs;
    }
};
}