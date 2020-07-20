#pragma once

#include "transactions/OperationFrame.h"

namespace stellar 
{
class CreateDataOpFrame : public OperationFrame 
{
    CreateDataOp const& mCreateData;

    bool
    doCheckValid(Application &app) override;

    bool
    doApply(Application &app, StorageHelper& storageHelper,
            LedgerManager &ledgerManager) override;

    CreateDataResult&
    innerResult()
    {
        return mResult.tr().createDataResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    std::string 
    getInnerResultCodeAsStr() override;

public:
    CreateDataOpFrame(Operation const& op, OperationResult& res,
                      TransactionFrame& parentTx);
};
}