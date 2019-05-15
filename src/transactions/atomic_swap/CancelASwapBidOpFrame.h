#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class CancelASwapBidOpFrame : public OperationFrame
{
private:
    CancelAtomicSwapBidOp const& mCancelASwapBid;

    CancelAtomicSwapBidResult& innerResult()
    {
        return mResult.tr().cancelAtomicSwapBidResult();
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
        return lm.shouldUse(LedgerVersion::ATOMIC_SWAP_RETURNING);
    }

public:
    CancelASwapBidOpFrame(Operation const &op, OperationResult &opRes,
                          TransactionFrame &parentTx);

    bool doApply(Application &app, LedgerDelta &delta,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static CancelAtomicSwapBidResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().cancelAtomicSwapBidResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelAtomicSwapBidResultCode>::enum_name(innerResult().code());
    }

};

}