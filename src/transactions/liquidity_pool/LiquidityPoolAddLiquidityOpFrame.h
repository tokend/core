#pragma once

#include <ledger/LiquidityPoolFrame.h>
#include <transactions/OperationFrame.h>

namespace stellar
{
class LiquidityPoolAddLiquidityOpFrame : public OperationFrame
{
    LPAddLiquidityResult& innerResult()
    {
        return mResult.tr().lpAddLiquidityResult();
    }

    LpAddLiquidityOp const& mAddLiquidity;

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;


};
}
