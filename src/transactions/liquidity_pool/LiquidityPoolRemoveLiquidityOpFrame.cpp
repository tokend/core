#include "LiquidityPoolRemoveLiquidityOpFrame.h"

#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/LiquidityPoolHelper.h>
#include <ledger/AccountHelper.h>
#include <ledger/AssetHelper.h>
#include <transactions/managers/BalanceManager.h>

namespace stellar
{

    LiquidityPoolRemoveLiquidityOpFrame::
    LiquidityPoolRemoveLiquidityOpFrame(Operation const& op, OperationResult& opRes, TransactionFrame& parentTx)
        : OperationFrame(op, opRes, parentTx),
          mRemoveLiquidity(mOperation.body.lpRemoveLiquidityOp())
    {
    }

    bool LiquidityPoolRemoveLiquidityOpFrame::tryGetOperationConditions(StorageHelper& sh,
        std::vector<OperationCondition>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto lpTokensBalanceFrame = balanceHelper.loadBalance(mRemoveLiquidity.lpTokenBalance);
        if (!lpTokensBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& liquidityPoolHelper = sh.getLiquidityPoolHelper();
        auto lpFrame = liquidityPoolHelper.loadPool(lpTokensBalanceFrame->getAsset());
        if (!lpFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::LIQUIDITY_POOL;

            return false;
        }

        auto lpFirstBalanceFrame = balanceHelper.mustLoadBalance(lpFrame->getFirstAssetBalance());
        auto lpSecondBalanceFrame = balanceHelper.mustLoadBalance(lpFrame->getSecondAssetBalance());

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(lpFirstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(lpSecondBalanceFrame->getAsset());

        AccountRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, AccountRuleAction::LP_REMOVE_LIQUIDITY, mSourceAccount);

        return true;
    }

    bool LiquidityPoolRemoveLiquidityOpFrame::tryGetSignerRequirements(StorageHelper& sh,
        std::vector<SignerRequirement>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto lpTokensBalanceFrame = balanceHelper.loadBalance(mRemoveLiquidity.lpTokenBalance);
        if (!lpTokensBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& liquidityPoolHelper = sh.getLiquidityPoolHelper();
        auto lpFrame = liquidityPoolHelper.loadPool(lpTokensBalanceFrame->getAsset());
        if (!lpFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::LIQUIDITY_POOL;

            return false;
        }

        auto lpFirstBalanceFrame = balanceHelper.mustLoadBalance(lpFrame->getFirstAssetBalance());
        auto lpSecondBalanceFrame = balanceHelper.mustLoadBalance(lpFrame->getSecondAssetBalance());

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(lpFirstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(lpSecondBalanceFrame->getAsset());

        SignerRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, SignerRuleAction::LP_REMOVE_LIQUIDITY);

        return true;
    }

    bool LiquidityPoolRemoveLiquidityOpFrame::doCheckValid(Application& app)
    {
        if (mRemoveLiquidity.lpTokensAmount == 0)
        {
            innerResult().code(LPRemoveLiquidityResultCode::INVALID_LP_TOKENS_AMOUNT);
            return false;
        }

        return true;
    }

    bool LiquidityPoolRemoveLiquidityOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm)
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto& liquidityPoolHelper = sh.getLiquidityPoolHelper();

        mLPTokensBalanceFrame = balanceHelper.loadBalance(mRemoveLiquidity.lpTokenBalance, mSourceAccount->getID());
        if (!mLPTokensBalanceFrame)
        {
            innerResult().code(LPRemoveLiquidityResultCode::LP_TOKEN_BALANCE_NOT_FOUND);
            return false;
        }

        mLPFrame = liquidityPoolHelper.loadPool(mLPTokensBalanceFrame->getAsset());
        if (!mLPFrame)
        {
            innerResult().code(LPRemoveLiquidityResultCode::LP_NOT_FOUND);
            return false;
        }

        if (mRemoveLiquidity.lpTokensAmount > mLPFrame->getLPTokensAmount())
        {
            innerResult().code(LPRemoveLiquidityResultCode::UNDERFUNDED);
            return false;
        }

        auto outputs = calculateOutputs(sh);

        if (outputs[0] < mRemoveLiquidity.firstAssetMinAmount)
        {
            innerResult().code(LPRemoveLiquidityResultCode::INSUFFICIENT_FIRST_AMOUNT);
            return false;
        }

        if (outputs[1] < mRemoveLiquidity.secondAssetMinAmount)
        {
            innerResult().code(LPRemoveLiquidityResultCode::INSUFFICIENT_SECOND_AMOUNT);
            return false;
        }

        auto balances = getSourceBalances(app, sh);

        if (!distributeAssets(app, sh, balances[0], balances[1], outputs[0], outputs[1]))
        {
            return false;
        }

        syncReserves(liquidityPoolHelper);

        innerResult().code(LPRemoveLiquidityResultCode::SUCCESS);
        innerResult().success().liquidityPoolID = mLPFrame->getPoolID();
        innerResult().success().firstAssetBalanceID = balances[0]->getBalanceID();
        innerResult().success().secondAssetBalanceID = balances[1]->getBalanceID();
        innerResult().success().firstAssetAmount = outputs[0];
        innerResult().success().secondAssetAmount = outputs[1];

        return true;
    }

    std::array<uint64_t, 2> LiquidityPoolRemoveLiquidityOpFrame::calculateOutputs(StorageHelper& sh)
    {
        auto lpFirstBalance = mLPFrame->getFirstAssetBalance();
        auto lpSecondBalance = mLPFrame->getSecondAssetBalance();

        auto& balanceHelper = sh.getBalanceHelper();
        mLPFirstBalanceFrame = balanceHelper.mustLoadBalance(lpFirstBalance);
        mLPSecondBalanceFrame = balanceHelper.mustLoadBalance(lpSecondBalance);

        auto lpTokensReserve = mLPFrame->getLPTokensAmount();
        auto lpFirstAmount = mLPFirstBalanceFrame->getAmount();
        auto lpSecondAmount = mLPSecondBalanceFrame->getAmount();

        uint64_t firstAmount, secondAmount;
        if (!bigDivide(firstAmount, mRemoveLiquidity.lpTokensAmount, lpFirstAmount, lpTokensReserve, ROUND_DOWN) ||
            !bigDivide(secondAmount, mRemoveLiquidity.lpTokensAmount, lpSecondAmount, lpTokensReserve, ROUND_DOWN))
        {
            innerResult().code(LPRemoveLiquidityResultCode::BALANCE_OVERFLOW);
            return {0, 0};
        }

        return {firstAmount, secondAmount};
    }

    std::array<BalanceFrame::pointer, 2>
    LiquidityPoolRemoveLiquidityOpFrame::getSourceBalances(Application& app, StorageHelper& sh)
    {
        auto balanceManager = BalanceManager(app, sh);

        auto sourceAccountID = mSourceAccount->getID();

        auto firstAsset = mLPFirstBalanceFrame->getAsset();
        auto secondAsset = mLPSecondBalanceFrame->getAsset();

        auto firstBalanceFrame = balanceManager.loadOrCreateBalance(sourceAccountID, firstAsset);
        auto secondBalanceFrame = balanceManager.loadOrCreateBalance(sourceAccountID, secondAsset);

        return {firstBalanceFrame, secondBalanceFrame};
    }

    bool LiquidityPoolRemoveLiquidityOpFrame::distributeAssets(Application& app, StorageHelper& sh,
        BalanceFrame::pointer const& sourceFirstBalanceFrame, BalanceFrame::pointer const& sourceSecondBalanceFrame,
        uint64_t firstAmount, uint64_t secondAmount)
    {
        auto balanceManager = BalanceManager(app, sh);
        auto& accountHelper = sh.getAccountHelper();

        auto sourceAccountID = mSourceAccount->getID();
        auto lpAccountFrame = accountHelper.loadAccount(sourceAccountID);

        auto transferRes = balanceManager.transfer(lpAccountFrame, mLPFirstBalanceFrame, sourceFirstBalanceFrame,
            firstAmount);
        if (transferRes != BalanceManager::SUCCESS)
        {
            setTransferCode(transferRes);
            return false;
        }

        transferRes = balanceManager.transfer(lpAccountFrame, mLPSecondBalanceFrame, sourceSecondBalanceFrame,
            secondAmount);
        if (transferRes != BalanceManager::SUCCESS)
        {
            setTransferCode(transferRes);
            return false;
        }

        uint64_t lpTokensAmount = mRemoveLiquidity.lpTokensAmount;

        auto chargeRes = mLPTokensBalanceFrame->tryCharge(lpTokensAmount);
        if (chargeRes != BalanceFrame::Result::SUCCESS)
        {
            setChargeCode(chargeRes);
            return false;
        }

        auto& balanceHelper = sh.getBalanceHelper();
        balanceHelper.storeChange(mLPTokensBalanceFrame->mEntry);

        auto& assetHelper = sh.getAssetHelper();
        auto asset = assetHelper.mustLoadAsset(mLPTokensBalanceFrame->getAsset());
        if (!asset->tryUnIssue(lpTokensAmount))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unissue redundant LP tokens after removing liquidity: "
                << mLPFrame->getPoolID();
            throw std::runtime_error("Unexpected state: failed to unissue redundant LP tokens removing liquidity");
        }
        assetHelper.storeChange(asset->mEntry);

        return true;
    }

    void LiquidityPoolRemoveLiquidityOpFrame::setTransferCode(BalanceManager::Result transferResult)
    {
        switch (transferResult)
        {
        case BalanceManager::UNDERFUNDED:
            innerResult().code(LPRemoveLiquidityResultCode::UNDERFUNDED);
            return;
        case BalanceManager::LINE_FULL:
            innerResult().code(LPRemoveLiquidityResultCode::BALANCE_OVERFLOW);
            return;
        case BalanceManager::INCORRECT_PRECISION:
            innerResult().code(LPRemoveLiquidityResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from transfer: " << transferResult;
            throw std::runtime_error("Unexpected result code from balance manager transfers");
        }
    }

    void LiquidityPoolRemoveLiquidityOpFrame::setChargeCode(BalanceFrame::Result chargeResult)
    {
        switch (chargeResult)
        {
        case BalanceFrame::Result::UNDERFUNDED:
            innerResult().code(LPRemoveLiquidityResultCode::UNDERFUNDED);
            return;
        case BalanceFrame::Result::LINE_FULL:
            innerResult().code(LPRemoveLiquidityResultCode::BALANCE_OVERFLOW);
            return;
        case BalanceFrame::Result::NONMATCHING_PRECISION:
            innerResult().code(LPRemoveLiquidityResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from charge: " << chargeResult;
            throw std::runtime_error("Unexpected result code from balance frame charge");
        }
    }

    void LiquidityPoolRemoveLiquidityOpFrame::syncReserves(LiquidityPoolHelper& lpHelper)
    {
        auto lpEntry = mLPFrame->getLiquidityPoolEntry();

        lpEntry.firstReserve = mLPFirstBalanceFrame->getAmount();
        lpEntry.secondReserve = mLPSecondBalanceFrame->getAmount();
        lpEntry.lpTokensTotalCap -= mRemoveLiquidity.lpTokensAmount;

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LIQUIDITY_POOL);
        entry.data.liquidityPool() = lpEntry;

        lpHelper.storeChange(entry);
    }

}
