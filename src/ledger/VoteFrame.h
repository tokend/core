#pragma once

#include "EntryFrame.h"

namespace stellar
{

class VoteFrame : public EntryFrame
{
    VoteEntry& mVoteEntry;

    VoteFrame(VoteFrame const& from);

public:
    typedef std::shared_ptr<VoteFrame> pointer;

    VoteFrame();
    VoteFrame(LedgerEntry const& from);

    LedgerKey const&
    getKey() const override;

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new VoteFrame(*this));
    }

    VoteEntry const&
    getEntry() const
    {
        return mVoteEntry;
    }

    VoteEntry&
    getEntry()
    {
        clearCached();
        return mVoteEntry;
    }

};
}
