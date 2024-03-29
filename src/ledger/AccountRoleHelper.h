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
    using EntryHelper::exists;

    virtual bool
    exists(uint64 roleID) = 0;

    virtual AccountRoleFrame::pointer
    loadAccountRole(uint64_t const roleID) = 0;

    virtual std::vector<uint64_t>
    loadRoleIDsByRule(uint64_t const ruleID) = 0;
};

} // namespace stellar