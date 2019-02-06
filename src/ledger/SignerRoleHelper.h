#pragma once

#include "EntryHelper.h"
#include "SignerRoleFrame.h"

namespace stellar
{

class SignerRoleHelper : public EntryHelper
{
public:
    virtual bool
    exists(LedgerKey const& key) = 0;

    virtual bool
    exists(uint64_t const roleID) = 0;

    virtual SignerRoleFrame::pointer
    loadSignerRole(uint64_t const roleID) = 0;
};
}