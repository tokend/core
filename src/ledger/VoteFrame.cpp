#include "VoteFrame.h"

namespace stellar
{
VoteFrame::VoteFrame() : EntryFrame(LedgerEntryType::POLL)
        , mVoteEntry(mEntry.data.vote())
{
}

VoteFrame::VoteFrame(LedgerEntry const& from) : EntryFrame(from)
        , mVoteEntry(mEntry.data.vote())
{
}

VoteFrame::VoteFrame(VoteFrame const& from) : VoteFrame(from.mEntry)
{
}

LedgerKey const&
VoteFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::VOTE);
        mKey.vote().pollID = mVoteEntry.pollID;
        mKey.vote().voterID = mVoteEntry.voterID;
        mKeyCalculated = true;
    }

    return mKey;
}
}
