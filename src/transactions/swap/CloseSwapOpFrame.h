#pragma once

#include "ledger/SwapFrame.h"
#include <transactions/OperationFrame.h>

namespace stellar
{
class CloseSwapOpFrame : public OperationFrame
{
    CloseSwapResult&
    innerResult()
    {
        return mResult.tr().closeSwapResult();
    }

    CloseSwapOp const& mCloseSwap;

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    bool secretValid(SwapFrame::pointer swap);

    bool processSwap(Application& app, StorageHelper& sh, LedgerManager& lm,
                     SwapFrame::pointer swap);
    bool cancelSwap(Application& app, StorageHelper& sh, LedgerManager& lm,
                    SwapFrame::pointer swap);

    bool isAuthorized(StorageHelper& sh, LedgerManager& lm, AccountID admin,
                      SwapFrame::pointer swap);

  public:
    CloseSwapOpFrame(Operation const& op, OperationResult& res,
                     TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CloseSwapResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().closeSwapResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CloseSwapResultCode>::enum_name(
            innerResult().code());
    }
};
}