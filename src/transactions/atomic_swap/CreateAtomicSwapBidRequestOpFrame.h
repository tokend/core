#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/AtomicSwapAskFrame.h"

namespace stellar
{

class CreateAtomicSwapBidRequestOpFrame : public OperationFrame
{
    CreateAtomicSwapBidRequestResult&
    innerResult()
    {
        return mResult.tr().createAtomicSwapBidRequestResult();
    }

    CreateAtomicSwapBidRequestOp const& mCreateASwapRequest;

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

    AtomicSwapAskFrame::pointer
    loadAtomicSwapAsk(CreateAtomicSwapBidRequest aSwapRequest, Database& db, LedgerDelta& delta);

    bool
    checkAmounts(StorageHelper& storageHelper, AtomicSwapAskFrame::pointer const& bidFrame);

    bool
    tryFillRequest(ReviewableRequestEntry& requestEntry, StorageHelper& storageHelper);

    std::vector<std::string>
    makeTasksKeyVector();

public:
    CreateAtomicSwapBidRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreateAtomicSwapBidRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().createAtomicSwapBidRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateAtomicSwapBidRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}
