#pragma once

#include "ledger/EntryHelper.h"
#include "ledger/LedgerManager.h"
#include "ledger/KeyValueEntryFrame.h"

namespace soci
{
    class session;
}

namespace stellar
{

class StatementContext;

class KeyValueHelper : public EntryHelper
{

public:

    virtual KeyValueEntryFrame::pointer
    loadKeyValue(string256 valueKey) = 0;

    virtual void
    loadKeyValues(StatementContext &prep,
                  std::function<void(LedgerEntry const &)> keyValueProcessor) = 0;

    virtual bool
    loadTasks(uint32_t &allTasks, std::vector<std::string> keys,
              uint32_t* passedTasks = nullptr) = 0;

    virtual bool
    loadBalanceID(BalanceID &pubKey, std::vector<std::string> keys) = 0;
};

}
