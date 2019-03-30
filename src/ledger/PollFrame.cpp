#include "PollFrame.h"

namespace stellar
{
PollFrame::PollFrame() : EntryFrame(LedgerEntryType::POLL)
        , mPollEntry(mEntry.data.poll())
{
}

PollFrame::PollFrame(LedgerEntry const& from) : EntryFrame(from)
        , mPollEntry(mEntry.data.poll())
{
}

PollFrame::PollFrame(PollFrame const& from) : PollFrame(from.mEntry)
{
}

PollFrame::pointer
PollFrame::createNew(uint64_t const id, CreatePollRequest request,
                     const AccountID &ownerID)
{
    LedgerEntry entry;
    entry.data.type(LedgerEntryType::POLL);
    auto& poll = entry.data.poll();

    poll.id = id;
    poll.permissionType = request.permissionType;
    poll.numberOfChoices = request.numberOfChoices;
    poll.data = request.data;
    poll.startTime = request.startTime;
    poll.endTime = request.endTime;
    poll.voteConfirmationRequired = request.voteConfirmationRequired;
    poll.resultProviderID = request.resultProviderID;
    poll.ownerID = ownerID;
    poll.details = request.creatorDetails;

    return std::make_shared<PollFrame>(entry);
}

LedgerKey const&
PollFrame::getKey() const
{
    if (!mKeyCalculated)
    {
        mKey = LedgerKey(LedgerEntryType::POLL);
        mKey.poll().id = mPollEntry.id;
        mKeyCalculated = true;
    }

    return mKey;
}
}