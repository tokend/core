#pragma once

#include "EntryHelper.h"
#include "SignerRoleFrame.h"

namespace stellar
{

class SignerRoleHelper : public EntryHelper
{
public:
    virtual SignerRoleFrame::pointer
    loadSignerRole(uint64_t const roleID) = 0;
};
}