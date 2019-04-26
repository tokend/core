#pragma once

#include "ManageAccountSpecificRuleOpFrame.h"
#include "ledger/AccountSpecificRuleFrame.h"

namespace stellar
{

class RemoveAccountSpecificRuleOpFrame : private ManageAccountSpecificRuleOpFrame
{
    RemoveAccountSpecificRuleData const& mRemoveData;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    bool
    tryRemoveSaleRule(Application& app, StorageHelper& storageHelper,
            AccountSpecificRuleFrame::pointer const& ruleFrame);

public:
    RemoveAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);
};
}
