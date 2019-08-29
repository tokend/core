#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar 
{
class CreatePaymentRequestOpFrame : public OperationFrame 
{
    CreatePaymentRequestOp const& mCreatePaymentRequest;
    PaymentOp const& mPayment;

    bool
    doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    bool 
    doCheckValid(Application& app) override;

    bool
    tryGetOperationConditions(StorageHelper& sh, std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& sh, std::vector<SignerRequirement>& result) const override;

    AccountFrame::pointer
    tryLoadDestinationAccount(StorageHelper &storageHelper) const;

    bool
    isDestinationFeeValid();

    CreatePaymentRequestResult&
    innerResult() 
    {
        return mResult.tr().createPaymentRequestResult();
    }

    void
    tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
        ReviewableRequestFrame::pointer request);

    std::vector<std::string>
    makeTasksKeyVector(AssetCode const& assetCode);

public:
    CreatePaymentRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& tx);
};
}