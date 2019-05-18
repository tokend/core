#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/AtomicSwapBidFrame.h"

namespace stellar
{

class CreateASwapRequestOpFrame : public OperationFrame
{
    CreateAtomicSwapAskRequestResult&
    innerResult()
    {
        return mResult.tr().createAtomicSwapAskRequestResult();
    }

    CreateAtomicSwapAskRequestOp const& mCreateASwapRequest;

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
    loadAtomicSwapBid(CreateAtomicSwapAskRequest aSwapRequest, Database& db, LedgerDelta& delta);

    bool
    checkAmounts(StorageHelper& storageHelper, AtomicSwapBidFrame::pointer const& bidFrame);

    bool
    tryFillRequest(ReviewableRequestEntry& requestEntry, StorageHelper& storageHelper);

public:
    CreateASwapRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreateAtomicSwapAskRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().createAtomicSwapAskRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapAskRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}
