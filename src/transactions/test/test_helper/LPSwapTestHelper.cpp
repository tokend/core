#include "LPSwapTestHelper.h"

#include <transactions/liquidity_pool/LiquidityPoolSwapOpFrame.h>
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{

LPSwapTestHelper::LPSwapTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

LPSwapResult
LPSwapTestHelper::applyLPSwapTx(Account& from, LPSwapType swapType, BalanceID& fromBalance,
    BalanceID& toBalance, uint64_t amountIn, uint64_t amountOut, LPSwapResultCode expectedResultCode, Account* signer)
{
    TransactionFramePtr txFramePtr = createLPSwapTx(from, swapType, fromBalance, toBalance, amountIn, amountOut, signer);

    mTestManager->applyCheck(txFramePtr);

    auto txResult = txFramePtr->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = LiquidityPoolSwapOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);

    return opResult.tr().lpSwapResult();
}

TransactionFramePtr
LPSwapTestHelper::createLPSwapTx(Account& from, LPSwapType swapType, BalanceID& fromBalance,
    BalanceID& toBalance, uint64_t amountIn, uint64_t amountOut, Account* signer)
{
    Operation op;
    op.body.type(OperationType::LP_SWAP);
    auto& swap = op.body.lpSwapOp();
    swap.fromBalance = fromBalance;
    swap.toBalance = toBalance;
    swap.lpSwapRequest.type(swapType);
    switch (swapType)
    {
    case LPSwapType::TOKENS_FOR_EXACT_TOKENS:
    {
        auto& request = swap.lpSwapRequest.swapTokensForExactTokens();
        request.amountOut = amountOut;
        request.amountInMax = amountIn;
    }
    break;
    case LPSwapType::EXACT_TOKENS_FOR_TOKENS:
    {
        auto& request = swap.lpSwapRequest.swapExactTokensForTokens();
        request.amountOutMin = amountOut;
        request.amountIn = amountIn;
    }
    break;
    }

    return TxHelper::txFromOperation(from, op, signer);
}

}
}
