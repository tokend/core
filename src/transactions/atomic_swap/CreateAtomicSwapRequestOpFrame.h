#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{
class CreateAtomicSwapRequestOpFrame : public OperationFrame
{

    ManageInvoiceRequestResult&
    innerResult()
    {
        return mResult.tr().createASwapRequestResult();
    }

    CreateASwapRequestOp const& mCreateASwapRequest;

    std::unordered_map<AccountID, CounterpartyDetails>
    getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;

    SourceDetails
    getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>
                            counterpartiesDetails,
                            int32_t ledgerVersion) const override;

    bool createManageInvoiceRequest(Application& app, LedgerDelta& delta,
                                    LedgerManager& ledgerManager);



public:
    CreateAtomicSwapRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static ManageInvoiceRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageInvoiceRequestResult().code();
    }
};
}
