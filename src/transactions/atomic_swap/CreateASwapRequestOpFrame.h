#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/AtomicSwapBidFrame.h"

namespace stellar
{

class CreateASwapRequestOpFrame : public OperationFrame
{
    CreateAtomicSwapRequestResult&
    innerResult()
    {
        return mResult.tr().createAtomicSwapRequestResult();
    }

    CreateAtomicSwapRequestOp const& mCreateASwapRequest;

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

    AtomicSwapBidFrame::pointer
    loadAtomicSwapBid(AtomicSwapRequest aSwapRequest, Database& db, LedgerDelta& delta);

    bool
    tryFillRequest(ReviewableRequestEntry& requestEntry, StorageHelper& storageHelper);

public:
    CreateASwapRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreateAtomicSwapRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().createAtomicSwapRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}
