#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class CancelDeferredPaymentCreationRequestOpFrame : public OperationFrame {
    CancelDeferredPaymentCreationRequestResult& innerResult()
    {
        return mResult.tr().cancelDeferredPaymentCreationRequestResult();
    }

    CancelDeferredPaymentCreationRequestOp const& mCancelDeferredPaymentCreationRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    CancelDeferredPaymentCreationRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CancelDeferredPaymentCreationRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().cancelDeferredPaymentCreationRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelDeferredPaymentCreationRequestResultCode>::
        enum_name(innerResult().code());
    }
};
}
