#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class ManageAccountRoleTestHelper : TxHelper
{
  public:
    explicit ManageAccountRoleTestHelper(TestManager::pointer testManager);

    ManageAccountRoleOp buildCreateRoleOp(const std::string &name,
                                          std::vector<uint64_t> ruleIDs);

    ManageAccountRoleOp buildUpdateRoleOp(uint64_t accountRoleID,
                                          const std::string &name,
                                          std::vector<uint64_t> ruleIDs);

    ManageAccountRoleOp buildRemoveRoleOp(uint64_t accountRoleID);

    TransactionFramePtr createAccountRoleTx(Account& source,
                                            const ManageAccountRoleOp& op);

    ManageAccountRoleResult
    applyTx(Account &source, const ManageAccountRoleOp &op,
            ManageAccountRoleResultCode expectedResultCode =
            ManageAccountRoleResultCode::SUCCESS);

    uint64_t createTxSenderRole(Account& root);
};
} // namespace txtest
} // namespace stellar