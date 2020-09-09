#pragma once

#include "ledger/DeferredPaymentFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"
#include <vector>

namespace stellar
{
class CreateCloseDeferredPaymentRequestOpFrame : public OperationFrame
{
    CreateCloseDeferredPaymentRequestResult&
    innerResult()
    {
        return mResult.tr().createCloseDeferredPaymentRequestResult();
    }

    CreateCloseDeferredPaymentRequestOp const&
        mCreateCloseDeferredPaymentRequest;

    void pickResultCode(CreateCloseDeferredPaymentRequestResultCode code);

    std::vector<std::string> makeTasksKeyVector(AssetCode const& code);

    bool tryGetOperationConditions(StorageHelper& storageHelper,
                                   std::vector<OperationCondition>& result,
                                   LedgerManager& ledgerManager) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    bool isAuthorized(DeferredPaymentFrame::pointer deferredPayment);

    bool createRequest(Application& app, StorageHelper& sh, LedgerManager& lm);
    bool updateRequest(Application& app, StorageHelper& sh, LedgerManager& lm);

    bool tryAutoApprove(Application& app, StorageHelper& sh,
                        ReviewableRequestFrame::pointer request);

    bool destinationCanBeFunded(BalanceFrame::pointer destBalance, uint64_t amount);

  public:
    CreateCloseDeferredPaymentRequestOpFrame(Operation const& op,
                                             OperationResult& res,
                                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CreateCloseDeferredPaymentRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().createCloseDeferredPaymentRequestResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateCloseDeferredPaymentRequestResultCode>::
            enum_name(innerResult().code());
    }
};
}
