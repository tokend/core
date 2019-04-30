#pragma once

#include "ManageAccountSpecificRuleOpFrame.h"

namespace stellar
{

class CreateAccountSpecificRuleOpFrame : public ManageAccountSpecificRuleOpFrame
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
    createSaleRuleWithChecks(Application &app, StorageHelper &sh,
                             uint64_t saleID);

    bool
    createSaleRule(StorageHelper& sh);

    friend class ReviewSaleCreationRequestOpFrame;

public:
    CreateAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);
};
}
