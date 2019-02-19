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
            ManageAccountRuleResultCode::SUCCESS,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS);

    AccountRuleEntry
    createAccountRuleEntry(uint64_t id, AccountRuleResource resource,
                           AccountRuleAction action, bool isForbid);
};

} // namespace txtest
} // namespace stellar