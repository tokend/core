#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class CancelAtomicSwapAskOpFrame : public OperationFrame {
private:
    CancelAtomicSwapAskOp const& mCancelASwapBid;

    CancelAtomicSwapAskResult& innerResult()
    {
        return mResult.tr().cancelAtomicSwapAskResult();
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
    CancelAtomicSwapAskOpFrame(Operation const& op, OperationResult& opRes,
                               TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CancelAtomicSwapAskResultCode getInnerCode(OperationResult& res)
    {
        return res.tr().cancelAtomicSwapAskResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelAtomicSwapAskResultCode>::enum_name(innerResult().code());
    }

};

}
