#pragma once

#include "ledger/EntryHelper.h"
#include "AccountFrame.h"

namespace stellar
{

class AccountHelper : public EntryHelper
{
public:
    virtual AccountFrame::pointer
    loadAccount(AccountID const& accountID) = 0;

    virtual bool
    isRoleIDUsed(uint64_t roleID) = 0;
};
}