#pragma once

#include "EntryHelper.h"
#include "SignerFrame.h"

namespace stellar
{

class SignerHelper : public EntryHelper
{
public:
    virtual std::vector<SignerFrame::pointer>
    loadSigners(AccountID const& accountID) = 0;

    virtual bool
    isRoleIDUsed(uint64_t const roleID) = 0;
};
}