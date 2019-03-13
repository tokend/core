#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class CancelASwapBidOpFrame : public OperationFrame
{
private:
    CancelASwapBidOp const& mCancelASwapBid;

    CancelASwapBidResult& innerResult()
    {
        return mResult.tr().cancelASwapBidResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    isSupported(LedgerManager& lm) const override
    {
        return lm.shouldUse(LedgerVersion::CHECK_SET_FEE_ACCOUNT_EXISTING);
    }

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