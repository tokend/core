#pragma once

#include <ledger/LiquidityPoolFrame.h>
#include <transactions/OperationFrame.h>
#include <transactions/managers/BalanceManager.h>
#include <operation-lp-remove-liquidity.h>

namespace stellar
{

class LiquidityPoolHelper;

class LiquidityPoolRemoveLiquidityOpFrame : public OperationFrame
{
public:
    LiquidityPoolRemoveLiquidityOpFrame(Operation const& op, OperationResult& opRes, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;

    bool doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<LPRemoveLiquidityResultCode>::enum_name(innerResult().code());
    }

    static LPRemoveLiquidityResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().lpRemoveLiquidityResult().code();
    }

private:
    LPRemoveLiquidityResult& innerResult()
    {
      return mResult.tr().lpRemoveLiquidityResult();
    }

    LPRemoveLiquidityOp const& mRemoveLiquidity;

    bool tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& sh,
        std::vector<SignerRequirement>& result) const override;

    std::array<uint64_t, 2> calculateOutputs(StorageHelper& sh);

    std::array<BalanceFrame::pointer, 2> getSourceBalances(Application& app, StorageHelper& sh);

    bool distributeAssets(Application& app, StorageHelper& sh, BalanceFrame::pointer const& sourceFirstBalanceFrame,
        BalanceFrame::pointer const& sourceSecondBalanceFrame, uint64_t firstAmount, uint64_t secondAmount);

    void setTransferCode(BalanceManager::Result transferResult);
    void setChargeCode(BalanceFrame::Result chargeResult);

    void syncReserves(LiquidityPoolHelper& lpHelper);

    LiquidityPoolFrame::pointer mLPFrame;

    BalanceFrame::pointer mLPFirstBalanceFrame;
    BalanceFrame::pointer mLPSecondBalanceFrame;

    BalanceFrame::pointer mLPTokensBalanceFrame;
};

}
