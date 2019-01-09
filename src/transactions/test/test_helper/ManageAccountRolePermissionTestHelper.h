#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{

class ManageAccountRolePermissionTestHelper : TxHelper
{
  public:
    explicit ManageAccountRolePermissionTestHelper(
        TestManager::pointer testManager);

    TransactionFramePtr createSetAccountRolePermissionTx(
        Account& source, AccountRuleEntry permissionEntry,
        ManageAccountRolePermissionOpAction action);

    ManageAccountRolePermissionResult
    applySetIdentityPermissionTx(Account& source,
                                 AccountRuleEntry& permissionEntry,
        ManageAccountRolePermissionOpAction action,
        ManageAccountRolePermissionResultCode expectedResult =
            ManageAccountRolePermissionResultCode::SUCCESS);

    AccountRuleEntry
    createAccountRolePermissionEntry(uint64_t id, AccountRuleResource resource,
                                     std::string action, bool isForbid);
};

} // namespace txtest
} // namespace stellar