#pragma once

#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"
#include <vector>

namespace stellar
{
class CreateDeferredPaymentCreationRequestOpFrame : public OperationFrame
{
    CreateDeferredPaymentCreationRequestResult&
    innerResult()
    {
        return mResult.tr().createDeferredPaymentCreationRequestResult();
    }

    CreateDeferredPaymentCreationRequestOp const&
        mCreateDeferredPaymentCreationRequest;

    void pickResultCode(CreateDeferredPaymentCreationRequestResultCode code);

    std::vector<std::string> makeTasksKeyVector(AssetCode const& code);

    bool createRequest(Application& app, StorageHelper& sh, LedgerManager& lm);
    bool updateRequest(Application& app, StorageHelper& sh, LedgerManager& lm);

    bool tryAutoApprove(Application& app, StorageHelper& sh,
                        ReviewableRequestFrame::pointer request);
    bool tryGetOperationConditions(StorageHelper& storageHelper,
                                   std::vector<OperationCondition>& result,
                                   LedgerManager& ledgerManager) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

  public:
    CreateDeferredPaymentCreationRequestOpFrame(Operation const& op,
                                                OperationResult& res,
                                                TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CreateDeferredPaymentCreationRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().createDeferredPaymentCreationRequestResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateDeferredPaymentCreationRequestResultCode>::
            enum_name(innerResult().code());
    }
};
}
