#include "LPRemoveLiquidityTestHelper.h"
#include <transactions/liquidity_pool/LiquidityPoolRemoveLiquidityOpFrame.h>
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{

LPRemoveLiquidityTestHelper::LPRemoveLiquidityTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

TransactionFramePtr LPRemoveLiquidityTestHelper::createRemoveLiquidityPoolTx(Account& from, BalanceID& lpTokensBalance,
    uint64_t lpTokensAmount, uint64_t firstMinAmount, uint64_t secondMinAmount, Account* signer)
{
    Operation op;
    op.body.type(OperationType::LP_REMOVE_LIQUIDITY);
    auto& removeLiquidity = op.body.lpRemoveLiquidityOp();
    removeLiquidity.lpTokenBalance = lpTokensBalance;
    removeLiquidity.lpTokensAmount = lpTokensAmount;
    removeLiquidity.firstAssetMinAmount = firstMinAmount;
    removeLiquidity.secondAssetMinAmount = secondMinAmount;

    return TxHelper::txFromOperation(from, op, signer);
}

LPRemoveLiquidityResult LPRemoveLiquidityTestHelper::applyRemoveLiquidityTx(Account& from, BalanceID& lpTokensBalance,
    uint64_t lpTokensAmount, uint64_t firstMinAmount, uint64_t secondMinAmount,
    LPRemoveLiquidityResultCode expectedResultCode, Account* signer)
{
    TransactionFramePtr txFramePtr = createRemoveLiquidityPoolTx(from, lpTokensBalance, lpTokensAmount,
        firstMinAmount, secondMinAmount, signer);

    mTestManager->applyCheck(txFramePtr);

    auto txResult = txFramePtr->getResult();
    auto opResult = txResult.result.results()[0];

    LPRemoveLiquidityResultCode actualResultCode;

    if (opResult.code() == OperationResultCode::opNO_ENTRY)
    {
        switch (opResult.entryType())
        {
        case LedgerEntryType::LIQUIDITY_POOL:
            actualResultCode = LPRemoveLiquidityResultCode::LP_NOT_FOUND;
            break;
        case LedgerEntryType::BALANCE:
            actualResultCode = LPRemoveLiquidityResultCode::LP_TOKEN_BALANCE_NOT_FOUND;
            break;
        }

        REQUIRE(actualResultCode == expectedResultCode);
    }
    else
    {
        actualResultCode = LiquidityPoolRemoveLiquidityOpFrame::getInnerCode(opResult);

        REQUIRE(actualResultCode == expectedResultCode);
        return txResult.result.results()[0].tr().lpRemoveLiquidityResult();
    }
}

}
}
