#pragma once

#include "ledger/EntryHelper.h"
#include "AccountRoleFrame.h"

namespace soci
{
class session;
}

namespace stellar
{

class AccountRoleHelper : public EntryHelper
{
public:
    virtual AccountRoleFrame::pointer
    loadAccountRole(uint64_t const roleID) = 0;

    virtual bool
    isRuleUsed(uint64_t const ruleID) = 0;
};

} // namespace stellar