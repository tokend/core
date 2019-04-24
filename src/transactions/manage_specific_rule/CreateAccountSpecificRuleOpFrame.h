#pragma once

#include "ManageAccountSpecificRuleOpFrame.h"

namespace stellar
{

class CreateAccountSpecificRuleOpFrame : private ManageAccountSpecificRuleOpFrame
{
    CreateAccountSpecificRuleData const& mCreateData;

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
    createSaleRule(Application& app,StorageHelper& sh, uint64_t id);

public:
    CreateAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);
};
}
