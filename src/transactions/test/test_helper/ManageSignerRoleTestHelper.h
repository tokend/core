#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class ManageSignerRoleTestHelper : TxHelper
{
public:
    ManageSignerRoleTestHelper(TestManager::pointer testManager);

    ManageSignerRoleOp buildCreateRoleOp(const std::string &name,
                                         std::vector<uint64_t> ruleIDs,
                                         bool isReadOnly);

    ManageSignerRoleOp buildUpdateRoleOp(uint64_t accountRoleID,
                                          const std::string &name,
                                          std::vector<uint64_t> ruleIDs);

    ManageSignerRoleOp buildRemoveRoleOp(uint64_t accountRoleID);

    TransactionFramePtr createSignerRoleTx(Account& source,
                                            const ManageSignerRoleOp& op);

    ManageSignerRoleResult
    applyTx(Account &source, const ManageSignerRoleOp &op,
            ManageSignerRoleResultCode expectedResultCode =
            ManageSignerRoleResultCode::SUCCESS);
};
} // namespace txtest
} // namespace stellar