#pragma once

#include <ledger/LiquidityPoolFrame.h>
#include <transactions/OperationFrame.h>
#include <transactions/managers/BalanceManager.h>
#include <xdr/operation-lp-add-liquidity.h>

namespace stellar
{

class BalanceHelper;

class LiquidityPoolAddLiquidityOpFrame : public OperationFrame
{
public:
    LiquidityPoolAddLiquidityOpFrame(Operation const& op, OperationResult& opRes, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;

    bool doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<LPAddLiquidityResultCode>::enum_name(innerResult().code());
    }

    static LPAddLiquidityResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().lpAddLiquidityResult().code();
    }

private:
    LPAddLiquidityResult& innerResult()
    {
        return mResult.tr().lpAddLiquidityResult();
    }

    LPAddLiquidityOp& mAddLiquidity;

    bool tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& sh,
        std::vector<SignerRequirement>& result) const override;

    LiquidityPoolFrame::pointer mustCreateLiquidityPool(Application& app, StorageHelper& sh);

    void mustCreateLiquidityPoolAccount(StorageHelper& sh);
    void mustCreateLiquidityPoolBalances(Application& app, StorageHelper& sh);

    bool distributeAssets(Application& app, StorageHelper& sh, LedgerManager& lm);

    void setTransferCode(BalanceManager::Result transferResult);

    static bool quote(uint64_t firstAmount, uint64_t firstReserve, uint64_t secondReserve, uint64_t* quote);

    void normalize(AssetCode const& firstAsset, AssetCode const& secondAsset);

    bool calculateLPOutputs(uint64_t firstAssetReserve, uint64_t secondAssetReserve);

    std::array<uint64_t, 2> addToExistingPool(BalanceHelper& balanceHelper);

    LiquidityPoolFrame::pointer mPoolFrame;

    uint64_t mLiquidityPoolID;

    AccountID mLPAccountID;

    BalanceFrame::pointer mLPFirstBalance;
    BalanceFrame::pointer mLPSecondBalance;

    BalanceFrame::pointer mSourceFirstBalance;
    BalanceFrame::pointer mSourceSecondBalance;

    BalanceFrame::pointer mSourceLPTokensBalance;

    uint64_t mFromFirstAssetAmount;
    uint64_t mFromSecondAssetAmount;
    uint64_t mLPTokensAmountToIssue;

    AssetCode mLPTokenAssetCode;
};

}
