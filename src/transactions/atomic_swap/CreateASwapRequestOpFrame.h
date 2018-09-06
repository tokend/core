#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{
class CreateASwapRequestOpFrame : public OperationFrame
{

    CreateASwapRequestResult&
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

public:
    CreateASwapRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreateASwapRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().createASwapRequestResult().code();
    }
};
}
