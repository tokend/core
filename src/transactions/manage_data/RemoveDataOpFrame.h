#pragma once

#include "transactions/OperationFrame.h"

namespace stellar 
{
class RemoveDataOpFrame : public OperationFrame 
{
    RemoveDataOp const& mRemoveData;

    bool
    doCheckValid(Application &app) override;

    bool
    doApply(Application &app, StorageHelper& storageHelper,
            LedgerManager &ledgerManager) override;

    RemoveDataResult&
    innerResult()
    {
        return mResult.tr().removeDataResult();
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
    RemoveDataOpFrame(Operation const& op, OperationResult& res,
                      TransactionFrame& parentTx);
};
}