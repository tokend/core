#pragma once

#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class CreatePaymentRequestOpFrame : public OperationFrame
{
    CreatePaymentRequestOp const& mCreatePaymentRequest;
    PaymentOp const& mPayment;

    bool doApply(Application& app, StorageHelper& sh,
                 LedgerManager& lm) override;

    bool doCheckValid(Application& app) override;

    bool tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& sh,
        std::vector<SignerRequirement>& result) const override;

    AccountFrame::pointer
    tryLoadDestinationAccount(StorageHelper& storageHelper) const;

    bool isDestinationFeeValid();

    CreatePaymentRequestResult&
    innerResult()
    {
        return mResult.tr().createPaymentRequestResult();
    }

    bool tryAutoApprove(Application& app, StorageHelper& sh,
                        ReviewableRequestFrame::pointer request);

    std::vector<std::string> makeTasksKeyVector(LedgerManager& lm, AssetCode const& assetCode);

  public:
    CreatePaymentRequestOpFrame(Operation const& op, OperationResult& res,
                                TransactionFrame& tx);

    static CreatePaymentRequestResultCode
    getInnerCode(OperationResult const& result)
    {
        return result.tr().createPaymentRequestResult().code();
    };
};
}