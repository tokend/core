#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class CancelCloseDeferredPaymentRequestOpFrame : public OperationFrame {
    CancelCloseDeferredPaymentRequestResult& innerResult()
    {
        return mResult.tr().cancelCloseDeferredPaymentRequestResult();
    }

    CancelCloseDeferredPaymentRequestOp const& mCancelCloseDeferredPaymentRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;



public:

    CancelCloseDeferredPaymentRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CancelCloseDeferredPaymentRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().cancelCloseDeferredPaymentRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelCloseDeferredPaymentRequestResultCode>::
        enum_name(innerResult().code());
    }
};
}
