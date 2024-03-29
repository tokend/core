#include "LiquidityPoolSwapOpFrame.h"

#include <main/Application.h>

#include <ledger/LiquidityPoolHelper.h>
#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AccountHelper.h>
#include <ledger/AssetHelper.h>
#include <transactions/managers/BalanceManager.h>

namespace stellar
{
    LiquidityPoolSwapOpFrame::
    LiquidityPoolSwapOpFrame(const Operation& op, OperationResult& opRes, TransactionFrame& parentTx)
        : OperationFrame(op, opRes, parentTx),
          mLPSwap(mOperation.body.lpSwapOp())
    {
    }

    bool LiquidityPoolSwapOpFrame::tryGetOperationConditions(StorageHelper& sh,
        std::vector<OperationCondition>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto firstBalanceFrame = balanceHelper.loadBalance(mLPSwap.fromBalance);
        auto secondBalanceFrame = balanceHelper.loadBalance(mLPSwap.toBalance);
        if (!firstBalanceFrame || !secondBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(firstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(secondBalanceFrame->getAsset());

        AccountRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, AccountRuleAction::LP_SWAP, mSourceAccount);

        return true;
    }

    bool LiquidityPoolSwapOpFrame::tryGetSignerRequirements(StorageHelper& sh,
        std::vector<SignerRequirement>& result) const
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto firstBalanceFrame = balanceHelper.loadBalance(mLPSwap.fromBalance);
        auto secondBalanceFrame = balanceHelper.loadBalance(mLPSwap.toBalance);
        if (!firstBalanceFrame || !secondBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;

            return false;
        }

        auto& assetHelper = sh.getAssetHelper();
        auto firstAssetFrame = assetHelper.mustLoadAsset(firstBalanceFrame->getAsset());
        auto secondAssetFrame = assetHelper.mustLoadAsset(secondBalanceFrame->getAsset());

        SignerRuleResource resource(LedgerEntryType::LIQUIDITY_POOL);
        resource.liquidityPool().firstAsset = firstAssetFrame->getCode();
        resource.liquidityPool().firstAssetType = firstAssetFrame->getType();
        resource.liquidityPool().secondAsset = secondAssetFrame->getCode();
        resource.liquidityPool().secondAssetType = secondAssetFrame->getType();

        result.emplace_back(resource, SignerRuleAction::LP_SWAP);

        return true;
    }

    bool LiquidityPoolSwapOpFrame::doCheckValid(Application& app)
    {
        if (mLPSwap.toBalance == mLPSwap.fromBalance)
        {
            innerResult().code(LPSwapResultCode::SAME_BALANCES);
            return false;
        }

        switch (mLPSwap.lpSwapRequest.type())
        {
        case LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactInTokensForOutTokens();

            if (request.amountIn == 0)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_INPUT_AMOUNT);
                return false;
            }
        }
        break;
        case LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactOutTokensForInTokens();

            if (request.amountOut == 0)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT);
                return false;
            }
        }
        break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "unexpected swap type";
            throw std::runtime_error("unexpected swap type");
        }

        return true;
    }

    bool LiquidityPoolSwapOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm)
    {
        auto& balanceHelper = sh.getBalanceHelper();
        auto& liquidityPoolHelper = sh.getLiquidityPoolHelper();

        auto sourceID = mSourceAccount->getID();

        auto sourceFromBalance = balanceHelper.loadBalance(mLPSwap.fromBalance, sourceID);
        if (!sourceFromBalance)
        {
            innerResult().code(LPSwapResultCode::FROM_BALANCE_NOT_FOUND);
            return false;
        }

        auto sourceToBalance = balanceHelper.loadBalance(mLPSwap.toBalance);
        if (!sourceToBalance)
        {
            innerResult().code(LPSwapResultCode::TO_BALANCE_NOT_FOUND);
            return false;
        }

        mFromAsset = sourceFromBalance->getAsset();
        mToAsset = sourceToBalance->getAsset();

        if (mFromAsset == mToAsset)
        {
            innerResult().code(LPSwapResultCode::SAME_ASSETS);
            return false;
        }

        auto lpTokenAsset = LiquidityPoolFrame::calculateLPTokenAssetCode(mFromAsset, mToAsset);
        mLiquidityPoolFrame = liquidityPoolHelper.loadPool(lpTokenAsset);
        if (!mLiquidityPoolFrame)
        {
            innerResult().code(LPSwapResultCode::LIQUIDITY_POOL_NOT_FOUND);
            return false;
        }

        auto lpFirstBalance = balanceHelper.mustLoadBalance(mLiquidityPoolFrame->getFirstAssetBalance());
        auto lpFirstAsset = lpFirstBalance->getAsset();

        bool assetsSorted = lpFirstAsset == mFromAsset;
        mReserveIn = assetsSorted ? mLiquidityPoolFrame->getFirstReserve() : mLiquidityPoolFrame->getSecondReserve();
        mReserveOut = assetsSorted ? mLiquidityPoolFrame->getSecondReserve() : mLiquidityPoolFrame->getFirstReserve();

        auto lpFromBalance = balanceHelper.loadBalance(mLiquidityPoolFrame->getAccountID(), mToAsset);
        auto lpToBalance = balanceHelper.loadBalance(mLiquidityPoolFrame->getAccountID(), mFromAsset);

        auto amounts = swap(sourceFromBalance, sourceToBalance, lpFromBalance, lpToBalance, app, sh);
        if (!amounts[0] || !amounts[1])
        {
            return false;
        }

        syncReserves(balanceHelper, liquidityPoolHelper);

        innerResult().code(LPSwapResultCode::SUCCESS);
        innerResult().success().liquidityPoolID = mLiquidityPoolFrame->getPoolID();
        innerResult().success().poolAccount = mLiquidityPoolFrame->getAccountID();
        innerResult().success().sourceInBalanceID = sourceFromBalance->getBalanceID();
        innerResult().success().sourceOutBalanceID = sourceToBalance->getBalanceID();
        innerResult().success().lpInBalanceID = lpToBalance->getBalanceID();
        innerResult().success().lpOutBalanceID = lpFromBalance->getBalanceID();
        innerResult().success().swapInAmount = amounts[0];
        innerResult().success().swapOutAmount = amounts[1];

        return true;
    }

    bool LiquidityPoolSwapOpFrame::calculateAmountIn(uint64_t amountOut, uint64_t& amountIn)
    {
        uint64_t denominator = mReserveOut - amountOut;

        if (denominator == 0 ||
            !bigDivide(amountIn, mReserveIn, amountOut, denominator, ROUND_UP))
        {
            innerResult().code(LPSwapResultCode::BALANCE_OVERFLOW);
            return false;
        }

        return true;
    }

    bool LiquidityPoolSwapOpFrame::calculateAmountOut(uint64_t amountIn, uint64_t& amountOut)
    {
        uint64_t denominator;
        if (!safeSum(mReserveIn, amountIn, denominator))
        {
            innerResult().code(LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT);
            return false;
        }

        if (!bigDivide(amountOut, amountIn, mReserveOut, denominator, ROUND_DOWN))
        {
            innerResult().code(LPSwapResultCode::BALANCE_OVERFLOW);
            return false;
        }

        return true;
    }

    std::array<uint64_t, 2> LiquidityPoolSwapOpFrame::swap(BalanceFrame::pointer const& sourceFrom,
        BalanceFrame::pointer const& sourceTo, BalanceFrame::pointer const& lpFrom,
        BalanceFrame::pointer const& lpTo, Application& app, StorageHelper& sh)
    {
        uint64_t amountIn, amountOut;

        switch (mLPSwap.lpSwapRequest.type())
        {
        case LPSwapType::EXACT_OUT_TOKENS_FOR_IN_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactOutTokensForInTokens();

            if (request.amountOut > mReserveOut)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_LIQUIDITY);
                return {0, request.amountOut};
            }

            if (!calculateAmountIn(request.amountOut, amountIn))
            {
                return {0, 0};
            }

            if (amountIn > request.amountInMax)
            {
                innerResult().code(LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT);
                return {0, request.amountOut};
            }

            amountOut = request.amountOut;
        }
        break;
        case LPSwapType::EXACT_IN_TOKENS_FOR_OUT_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactInTokensForOutTokens();

            if (request.amountOutMin > mReserveOut)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_LIQUIDITY);
                return {request.amountIn, 0};
            }

            if (!calculateAmountOut(request.amountIn, amountOut))
            {
                return {0, 0};
            }

            if (amountOut < request.amountOutMin)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT);
                return {request.amountIn, 0};
            }

            amountIn = request.amountIn;
        }
        break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "unexpected swap type";
            throw std::runtime_error("unexpected swap type");
        }

        auto balanceManager = BalanceManager(app, sh);

        auto res = balanceManager.transfer(mSourceAccount, sourceFrom, lpTo, amountIn);
        if (res != BalanceManager::SUCCESS)
        {
            setTransferCode(res);
            return {0, 0};
        }

        auto& accountHelper = sh.getAccountHelper();
        auto lpAccount = accountHelper.loadAccount(mLiquidityPoolFrame->getAccountID());

        res = balanceManager.transfer(lpAccount, lpFrom, sourceTo, amountOut);
        if (res != BalanceManager::SUCCESS)
        {
            setTransferCode(res);
            return {0, 0};
        }

        return {amountIn, amountOut};
    }

    void LiquidityPoolSwapOpFrame::setTransferCode(BalanceManager::Result transferResult)
    {
        switch (transferResult)
        {
        case BalanceManager::UNDERFUNDED:
            innerResult().code(LPSwapResultCode::UNDERFUNDED);
            return;
        case BalanceManager::LINE_FULL:
            innerResult().code(LPSwapResultCode::BALANCE_OVERFLOW);
            return;
        case BalanceManager::INCORRECT_PRECISION:
            innerResult().code(LPSwapResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from transfer: " << transferResult;
            throw std::runtime_error("Unexpected result code from balance manager transfers");
        }
    }

    void LiquidityPoolSwapOpFrame::syncReserves(BalanceHelper& balanceHelper, LiquidityPoolHelper& lpHelper)
    {
        auto lpEntry = mLiquidityPoolFrame->getLiquidityPoolEntry();

        auto firstBalance = balanceHelper.mustLoadBalance(lpEntry.firstAssetBalance);
        auto secondBalance = balanceHelper.mustLoadBalance(lpEntry.secondAssetBalance);

        lpEntry.firstReserve = firstBalance->getAmount();
        lpEntry.secondReserve = secondBalance->getAmount();

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LIQUIDITY_POOL);
        entry.data.liquidityPool() = lpEntry;

        lpHelper.storeChange(entry);
    }
}
