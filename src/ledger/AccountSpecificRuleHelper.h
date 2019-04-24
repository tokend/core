#pragma once

#include "EntryHelper.h"
#include "AccountSpecificRuleFrame.h"

namespace stellar
{

class AccountSpecificRuleHelper : public EntryHelper
{
public:
    using EntryHelper::exists;

    virtual AccountSpecificRuleFrame::pointer
    loadRule(uint64_t id) = 0;

    virtual AccountSpecificRuleFrame::pointer
    mustLoadRule(uint64_t id) = 0;

    virtual bool
    exists(uint64_t id) = 0;
};
}
