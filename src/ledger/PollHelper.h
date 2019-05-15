#pragma once

#include "EntryHelper.h"
#include "PollFrame.h"

namespace stellar
{

class PollHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

    virtual PollFrame::pointer
    loadPoll(uint64_t id) = 0;

    virtual PollFrame::pointer
    mustLoadPoll(uint64_t id) = 0;

    virtual bool
    exists(uint64_t id) = 0;

    virtual void
    permissionTypeMigration() = 0;

    virtual void
    createIfNotExists() = 0;
};
}
