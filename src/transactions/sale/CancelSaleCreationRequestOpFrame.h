#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class CancelSaleCreationRequestOpFrame : public OperationFrame
{
    CancelSaleCreationRequestResult& innerResult()
    {
        return mResult.tr().cancelSaleCreationRequestResult();
    }

    CancelSaleCreationRequestOp const& mCancelSaleCreationRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    CancelSaleCreationRequestOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx);
    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CancelSaleCreationRequestResultCode getInnerCode(
            OperationResult const& res)
    {
        return res.tr().cancelSaleCreationRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelSaleCreationRequestResultCode>::
                enum_name(innerResult().code());
    }
};
}
