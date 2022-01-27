#include "LPAddLiquidityTestHelper.h"
#include <transactions/liquidity_pool/LiquidityPoolAddLiquidityOpFrame.h>
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{

LPAddLiquidityTestHelper::LPAddLiquidityTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

LPAddLiquidityResult
LPAddLiquidityTestHelper::applyAddLiquidityTx(Account& from,
    BalanceID& firstBalance, BalanceID& secondBalance, uint64_t firstDesiredAmount, uint64_t secondDesiredAmount,
    uint64_t firstMinAmount, uint64_t secondMinAmount, LPAddLiquidityResultCode expectedResultCode, Account* signer)
{
    TransactionFramePtr txFramePtr = createAddLiquidityPoolTx(from, firstBalance, secondBalance,
        firstDesiredAmount, secondDesiredAmount, firstMinAmount, secondMinAmount, signer);

    mTestManager->applyCheck(txFramePtr);

    auto txResult = txFramePtr->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = LiquidityPoolAddLiquidityOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);
    return txResult.result.results()[0].tr().lpAddLiquidityResult();
}

TransactionFramePtr
LPAddLiquidityTestHelper::createAddLiquidityPoolTx(Account& from, BalanceID& firstBalance,
    BalanceID& secondBalance, uint64_t firstDesiredAmount, uint64_t secondDesiredAmount, uint64_t firstMinAmount,
    uint64_t secondMinAmount, Account* signer)
{
    Operation op;
    op.body.type(OperationType::LP_ADD_LIQUIDITY);
    auto& addLiquidity = op.body.lpAddLiquidityOp();
    addLiquidity.firstAssetBalance = firstBalance;
    addLiquidity.secondAssetBalance = secondBalance;
    addLiquidity.firstAssetDesiredAmount = firstDesiredAmount;
    addLiquidity.secondAssetDesiredAmount = secondDesiredAmount;
    addLiquidity.firstAssetMinAmount = firstMinAmount;
    addLiquidity.secondAssetMinAmount = secondMinAmount;

    return TxHelper::txFromOperation(from, op, signer);
}

}

}