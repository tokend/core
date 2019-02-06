#pragma once

#include "ledger/EntryHelper.h"
#include "AccountFrame.h"

namespace stellar
{

class AccountHelper : public EntryHelper
{
public:
    virtual bool
    exists(AccountID const& accountID) = 0;

    virtual AccountFrame::pointer
    loadAccount(AccountID const& accountID) = 0;

    virtual AccountFrame::pointer
    mustLoadAccount(AccountID const& accountID) = 0;

    virtual bool
    isRoleIDUsed(uint64_t roleID) = 0;
};
}