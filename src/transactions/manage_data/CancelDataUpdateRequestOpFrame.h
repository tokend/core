#pragma once


#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{

class CancelDataUpdateRequestOpFrame : public OperationFrame
{
    CancelDataUpdateRequestOp const& mCancelDataUpdateRequestOp;

    CancelDataUpdateRequestResult&
    innerResult()
    {
        return mResult.tr().cancelDataUpdateRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;
public:
    CancelDataUpdateRequestOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};


}

