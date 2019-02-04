#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class CancelASwapBidOpFrame : public OperationFrame
{
protected:
    CancelASwapBidOp const& mCancelASwapBid;

    CancelASwapBidResult& innerResult()
    {
        return mResult.tr().cancelASwapBidResult();
    }

    std::unordered_map<AccountID, CounterpartyDetails>
    getCounterpartyDetails(Database &db, LedgerDelta *delta) const override;

    SourceDetails
    getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>
                            counterpartiesDetails, int32_t ledgerVersion) const override;

public:
    CancelASwapBidOpFrame(Operation const &op, OperationResult &opRes,
                          TransactionFrame &parentTx);

    bool doApply(Application &app, LedgerDelta &delta,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CancelASwapBidResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().cancelASwapBidResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelASwapBidResultCode>::enum_name(innerResult().code());
    }

};

}