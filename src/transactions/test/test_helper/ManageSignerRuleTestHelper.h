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
    createTx(Account &source, ManageSignerRuleOp op);

    ManageSignerRuleResult applyTx(Account &source, ManageSignerRuleOp &entry,
            ManageSignerRuleResultCode expectedResult =
            ManageSignerRuleResultCode::SUCCESS,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS);

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