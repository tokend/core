#pragma once

#include <ledger/LiquidityPoolFrame.h>
#include <transactions/OperationFrame.h>
#include <transactions/managers/BalanceManager.h>
#include <xdr/operation-lp-swap.h>

namespace stellar
{
class LiquidityPoolSwapOpFrame : public OperationFrame
{
public:
    LiquidityPoolSwapOpFrame(Operation const& op, OperationResult& opRes, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;

    bool doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<LPSwapResultCode>::enum_name(innerResult().code());
    }

    static LPSwapResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().lpSwapResult().code();
    }

private:
    LPSwapResult& innerResult()
    {
        return mResult.tr().lpSwapResult();
    }

    LPSwapOp const& mLPSwap;

    bool tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& sh,
        std::vector<SignerRequirement>& result) const override;

    uint64_t calculateAmountIn(uint64_t amountOut) const;
    uint64_t calculateAmountOut(uint64_t amountIn) const;

    std::array<uint64_t, 2> swap(BalanceFrame::pointer const& sourceFrom, BalanceFrame::pointer const& sourceTo,
        BalanceFrame::pointer const& lpFrom, BalanceFrame::pointer const& lpTo, Application& app, StorageHelper& sh);

    void setTransferCode(BalanceManager::Result transferResult);

    LiquidityPoolFrame::pointer mLiquidityPoolFrame;

    uint64_t mReserveIn;
    uint64_t mReserveOut;

    AssetCode mFromAsset;
    AssetCode mToAsset;
};
}
