#pragma once

#include "EntryHelper.h"
#include "ContractFrame.h"
#include <functional>
#include <unordered_map>

namespace soci
{
    class session;
}

namespace stellar
{
class StatementContext;

class ContractHelper : public EntryHelper
{
public:
    virtual void addCustomerDetails() = 0;

    virtual ContractFrame::pointer loadContract(uint64_t id) = 0;
    virtual uint64_t countContracts(AccountID const& contractor) = 0;

};

}