#pragma once

#include "EntryHelper.h"
#include "VoteFrame.h"

namespace stellar
{

class VoteHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

    virtual VoteFrame::pointer
    loadVote(uint64_t pollID, AccountID voterID) = 0;

    virtual bool
    exists(uint64_t pollID, AccountID voterID) = 0;

    virtual void
    deleteForPoll(uint64_t pollID) = 0;

    virtual void
    createIfNotExists() = 0;
};
}
