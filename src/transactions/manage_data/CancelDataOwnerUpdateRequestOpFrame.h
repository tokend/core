#pragma once


#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{

class CancelDataOwnerUpdateRequestOpFrame : public OperationFrame
{
    CancelDataOwnerUpdateRequestOp const& mCancelDataOwnerUpdateRequestOp;

    CancelDataOwnerUpdateRequestResult&
    innerResult()
    {
        return mResult.tr().cancelDataOwnerUpdateRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;
public:
    CancelDataOwnerUpdateRequestOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};


}

