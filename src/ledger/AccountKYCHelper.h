#pragma once

#include "EntryHelper.h"
#include "AccountKYCFrame.h"
#include "LedgerDelta.h"

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class AccountKYCHelper : public EntryHelper
{
public:
    virtual void storeUpdate(const LedgerEntry& entry, bool insert) = 0;
    virtual AccountKYCFrame::pointer loadAccountKYC(const AccountID &accountID) = 0;
};

}