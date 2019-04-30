#pragma once

#include "ManageAccountSpecificRuleOpFrame.h"

namespace stellar
{

class CreateAccountSpecificRuleOpFrame : public ManageAccountSpecificRuleOpFrame
{
    CreateAccountSpecificRuleData const& mCreateData;
    bool mCheckRule = true;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool doCheckValid(Application& app) override;

    bool
    checkSaleRule(Application &app, StorageHelper &sh, uint64_t saleID);

    bool
    createSaleRule(Application &app, StorageHelper &sh, uint64_t saleID);

public:
    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    CreateAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);
};
}
