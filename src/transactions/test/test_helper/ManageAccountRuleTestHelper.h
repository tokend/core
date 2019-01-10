#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{

class ManageAccountRuleTestHelper : TxHelper
{
  public:
    explicit ManageAccountRuleTestHelper(TestManager::pointer testManager);

    TransactionFramePtr
    createManageAccountRuleTx(Account &source, AccountRuleEntry permissionEntry,
            ManageAccountRuleAction action);

    ManageAccountRuleResult
    applyTx(Account &source, AccountRuleEntry &permissionEntry,
            ManageAccountRuleAction action,
            ManageAccountRuleResultCode expectedResult =
            ManageAccountRuleResultCode::SUCCESS);

    AccountRuleEntry
    createAccountRolePermissionEntry(uint64_t id, AccountRuleResource resource,
                                     std::string action, bool isForbid);
};

} // namespace txtest
} // namespace stellar