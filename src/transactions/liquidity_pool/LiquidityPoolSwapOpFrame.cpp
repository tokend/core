#include "LiquidityPoolSwapOpFrame.h"

#include <main/Application.h>

#include <ledger/LiquidityPoolHelper.h>
#include <ledger/StorageHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AccountHelper.h>
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

    }

    bool LiquidityPoolSwapOpFrame::tryGetSignerRequirements(StorageHelper& sh,
        std::vector<SignerRequirement>& result) const
    {

    }

    bool LiquidityPoolSwapOpFrame::doCheckValid(Application& app)
    {
        if (mLPSwap.toBalance == mLPSwap.fromBalance)
        {
            innerResult().code(LPSwapResultCode::MALFORMED);
            return false;
        }

        switch (mLPSwap.lpSwapRequest.type())
        {
        case LPSwapType::EXACT_TOKENS_FOR_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactTokensForTokens();

            if (request.amountIn == 0)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_INPUT_AMOUNT);
                return false;
            }
        }
        break;
        case LPSwapType::TOKENS_FOR_EXACT_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapTokensForExactTokens();

            if (request.amountOut == 0)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT);
                return false;
            }
        }
        break;
        }
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

        auto sourceToBalance = balanceHelper.loadBalance(mLPSwap.toBalance, sourceID);
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

        mLiquidityPoolFrame = liquidityPoolHelper.loadPool(mFromAsset, mToAsset);
        if (!mLiquidityPoolFrame)
        {
            innerResult().code(LPSwapResultCode::LIQUIDITY_POOL_NOT_FOUND);
            return false;
        }

        auto lpFirstBalance = balanceHelper.loadBalance(mLiquidityPoolFrame->getFirstAssetBalance());
        auto lpFirstAsset = lpFirstBalance->getAsset();
        if (lpFirstAsset == mFromAsset)
        {
            mReserveIn = mLiquidityPoolFrame->getFirstReserve();
            mReserveOut = mLiquidityPoolFrame->getSecondReserve();
        }
        else
        {
            mReserveIn = mLiquidityPoolFrame->getSecondReserve();
            mReserveOut = mLiquidityPoolFrame->getFirstReserve();
        }

        auto lpFromBalance = balanceHelper.loadBalance(mLiquidityPoolFrame->getAccountID(), mToAsset);
        auto lpToBalance = balanceHelper.loadBalance(mLiquidityPoolFrame->getAccountID(), mFromAsset);

        auto amounts = swap(sourceFromBalance, sourceToBalance, lpFromBalance, sourceToBalance, app, sh);
        if (!amounts[0] || !amounts[1])
        {
            return false;
        }

        innerResult().code(LPSwapResultCode::SUCCESS);
        innerResult().success().liquidityPoolID = mLiquidityPoolFrame->getPoolID();
        innerResult().success().poolAccount = mLiquidityPoolFrame->getAccountID();
        innerResult().success().sourceAsset = mFromAsset;
        innerResult().success().targetAsset = mToAsset;
        innerResult().success().swapInAmount = amounts[0];
        innerResult().success().swapOutAmount = amounts[1];

        return true;
    }

    uint64_t LiquidityPoolSwapOpFrame::calculateAmountIn(uint64_t amountOut) const
    {
        uint64_t amountIn;                              // TODO check underflow
        if (!bigDivide(amountIn, mReserveIn, amountOut, mReserveOut - amountOut, ROUND_UP))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: calculated amount in for LP swap overflows UINT64_MAX, "
                << "liquidity pool id: "
                << mLiquidityPoolFrame->getPoolID()
                << ", reserveOut: " << mReserveOut << ", amountOut: " << amountOut;
            throw std::runtime_error("Unexpected state: calculated amount in for LP swap overflows UINT64_MAX");
        }

        return amountIn;
    }

    uint64_t LiquidityPoolSwapOpFrame::calculateAmountOut(uint64_t amountIn) const
    {
        uint64_t amountOut;
        if (!bigDivide(amountOut, amountIn, mReserveOut, mReserveIn + amountIn, ROUND_DOWN))
        {                                    // TODO check overflow ^
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: calculated amount out for LP swap overflows UINT64_MAX, "
                << "liquidity pool id: "
                << mLiquidityPoolFrame->getPoolID()
                << ", reserveIn: " << mReserveIn << ", amountIn: " << amountIn;
            throw std::runtime_error("Unexpected state: calculated amount out for LP swap overflows UINT64_MAX");
        }

        return amountOut;
    }

    std::array<uint64_t, 2> LiquidityPoolSwapOpFrame::swap(BalanceFrame::pointer const& sourceFrom,
        BalanceFrame::pointer const& sourceTo, BalanceFrame::pointer const& lpFrom,
        BalanceFrame::pointer const& lpTo, Application& app, StorageHelper& sh)
    {
        uint64_t amountIn, amountOut;

        switch (mLPSwap.lpSwapRequest.type())
        {
        case LPSwapType::TOKENS_FOR_EXACT_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapTokensForExactTokens();

            if (request.amountOut > mReserveOut)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_LIQUIDITY);
                return {0, request.amountOut};
            }

            amountIn = calculateAmountIn(request.amountOut);
            if (amountIn > request.amountInMax)
            {
                innerResult().code(LPSwapResultCode::EXCESSIVE_INPUT_AMOUNT);
                return {0, request.amountOut};
            }

            amountOut = request.amountOut;
        }
        break;
        case LPSwapType::EXACT_TOKENS_FOR_TOKENS:
        {
            auto request = mLPSwap.lpSwapRequest.swapExactTokensForTokens();

            if (request.amountOutMin > mReserveOut)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_LIQUIDITY);
                return {request.amountIn, 0};
            }

            amountOut = calculateAmountOut(request.amountIn);
            if (amountOut < request.amountOutMin)
            {
                innerResult().code(LPSwapResultCode::INSUFFICIENT_OUTPUT_AMOUNT);
                return {request.amountIn, 0};
            }

            amountIn = request.amountIn;
        }
        break;
        default:
            // TODO handle
            ;
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
            innerResult().code(LPSwapResultCode::LINE_FULL);
            return;
        case BalanceManager::INCORRECT_PRECISION:
            innerResult().code(LPSwapResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from transfer: " << transferResult;
            throw std::runtime_error("Unexpected result code from balance manager transfers");
        }
    }
}
