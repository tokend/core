#pragma once

#include "ledger/EntryHelper.h"

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
};

} // namespace stellar