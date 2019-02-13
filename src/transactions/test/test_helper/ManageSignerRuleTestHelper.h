#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{

class ManageSignerRuleTestHelper : TxHelper
{
public:
    ManageSignerRuleTestHelper(TestManager::pointer testManager);

    TransactionFramePtr
    createTx(Account &source, ManageSignerRuleOp op, Account* signer = nullptr);

    ManageSignerRuleResult applyTx(Account &source, ManageSignerRuleOp &op,
            ManageSignerRuleResultCode expectedResult =
            ManageSignerRuleResultCode::SUCCESS,
            OperationResultCode operationResultCode =
            OperationResultCode::opINNER,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS, Account* signer = nullptr);

    ManageSignerRuleOp buildCreateRuleOp(SignerRuleResource resource,
                                         std::string action, bool isForbid,
                                         bool isDefault, bool isReadOnly);

    ManageSignerRuleOp buildUpdateRoleOp(uint64_t id, SignerRuleResource resource,
                                         std::string action, bool isForbid,
                                         bool isDefault);

    ManageSignerRuleOp buildRemoveRoleOp(uint64_t ruleID);
};

} // namespace txtest
} // namespace stellar