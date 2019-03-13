#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/AtomicSwapBidFrame.h"

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

    AtomicSwapBidFrame::pointer
    loadAtomicSwapBid(ASwapRequest aSwapRequest, Database& db, LedgerDelta& delta);

    bool
    tryFillRequest(ReviewableRequestEntry& requestEntry, Database& db);

public:
    CreateASwapRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    bool tryGetAtomicSwapTasks(Database& db, uint32_t& allTasks);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static CreateASwapRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().createASwapRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateASwapRequestResultCode>::enum_name(
                innerResult().code());
    }
};

}
