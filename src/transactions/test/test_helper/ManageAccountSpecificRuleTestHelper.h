#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{

class ManageAccountSpecificRuleTestHelper : public TxHelper
{
public:
    explicit ManageAccountSpecificRuleTestHelper(TestManager::pointer const& testManager);

    TransactionFramePtr
    createManageRuleTx(Account &source, ManageAccountSpecificRuleOp const& op);

    ManageAccountSpecificRuleResult
    applyTx(Account &source, uint64_t ruleID,
            ManageAccountSpecificRuleResultCode expectedResult =
            ManageAccountSpecificRuleResultCode::SUCCESS,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS);

    ManageAccountSpecificRuleResult
    applyTx(Account &source, LedgerKey const& ledgerKey, bool forbids,
            AccountID* accountID = nullptr,
            ManageAccountSpecificRuleResultCode expectedResult =
            ManageAccountSpecificRuleResultCode::SUCCESS,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS);

    ManageAccountSpecificRuleResult
    applyTx(Account &source, ManageAccountSpecificRuleOp const& op,
            ManageAccountSpecificRuleResultCode expectedResult =
            ManageAccountSpecificRuleResultCode::SUCCESS,
            TransactionResultCode expectedTxResult =
            TransactionResultCode::txSUCCESS);
};
}
}
