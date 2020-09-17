#pragma once


#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{

class CancelDataRemoveRequestOpFrame : public OperationFrame
{
    CancelDataRemoveRequestOp const& mCancelDataRemoveRequestOp;

    CancelDataRemoveRequestResult&
    innerResult()
    {
        return mResult.tr().cancelDataRemoveRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;
public:
    CancelDataRemoveRequestOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};


}

