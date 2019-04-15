#pragma once

#include "EntryFrame.h"

namespace stellar
{

class PollFrame : public EntryFrame
{
    PollEntry& mPollEntry;

    PollFrame(PollFrame const& from);

public:
    typedef std::shared_ptr<PollFrame> pointer;

    PollFrame();
    PollFrame(LedgerEntry const& from);

    static pointer
    createNew(uint64_t id, CreatePollRequest request, AccountID const& ownerID);

    LedgerKey const&
    getKey() const override;

    EntryFrame::pointer
    copy() const override
    {
        return EntryFrame::pointer(new PollFrame(*this));
    }

    PollEntry const&
    getEntry() const
    {
        return mPollEntry;
    }

    PollEntry&
    getEntry()
    {
        clearCached();
        return mPollEntry;
    }

    AccountID&
    getOwner()
    {
        return mPollEntry.ownerID;
    }

    AccountID&
    getResultProvider()
    {
        return mPollEntry.resultProviderID;
    }
};
}
