#pragma once

#include "ledger/EntryHelper.h"
#include "ledger/AccountFrame.h"

namespace soci
{
class session;
}

namespace stellar
{
class StorageHelper;

class AccountRuleHelper : public EntryHelper
{
public:
    virtual std::vector<AccountRuleFrame::pointer>
    loadAccountRules(std::vector<uint64_t> const ruleIDs) = 0;
};

} // namespace stellar