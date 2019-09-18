#include "CloseSwapHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/SwapHelper.h"
#include "test/test_marshaler.h"
#include "transactions/swap/CloseSwapOpFrame.h"

namespace stellar
{
namespace txtest
{
CloseSwapTestHelper::CloseSwapTestHelper(TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

TransactionFramePtr
CloseSwapTestHelper::createCloseSwapTx(Account& source, int64_t swapID,
                                       Hash* secret)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CLOSE_SWAP);
    baseOp.body.closeSwapOp() = makeCloseSwap(swapID, secret);

    return txFromOperation(source, baseOp, nullptr);
}

CloseSwapOp
CloseSwapTestHelper::makeCloseSwap(int64_t swapID, Hash* secret)
{
    CloseSwapOp op;
    op.swapID = swapID;
    if (secret)
    {
        op.secret.activate() = *secret;
    }
    return op;
}

CloseSwapResult
CloseSwapTestHelper::applyCloseSwapTx(Account& source, int64_t swapID,
                                      Hash* secret,
                                      CloseSwapDelta* closeSwapDelta,
                                      CloseSwapResultCode expectedResultCode,
                                      OperationResultCode expectedOpResultCode)
{
    auto& sh = mTestManager->getStorageHelper();
    auto& swapHelper = sh.getSwapHelper();
    auto& balanceHelper = sh.getBalanceHelper();

    auto swap = swapHelper.mustLoadSwap(swapID);
    auto swapEntry = swap->getSwapEntry();
    auto sourceBalanceBeforeTx =
        balanceHelper.loadBalance(swapEntry.sourceBalance);

    BalanceFrame::pointer destBalanceBeforeTx;
    destBalanceBeforeTx = balanceHelper.loadBalance(swapEntry.destinationBalance);
    REQUIRE(destBalanceBeforeTx);

    std::vector<BalanceFrame::pointer> commissionBalancesBeforeTx;
    balanceHelper.loadBalances(mTestManager->getApp().getAdminID(),
                               commissionBalancesBeforeTx);

    std::unordered_map<std::string, BalanceFrame::pointer>
        commissionBalancesBeforeTxByAsset;
    for (auto& balanceFrame : commissionBalancesBeforeTx)
    {
        commissionBalancesBeforeTxByAsset[balanceFrame->getAsset()] =
            balanceFrame;
    }

    TransactionFramePtr txFrame;

    txFrame = createCloseSwapTx(source, swapID, secret);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpResultCode);
    if (expectedOpResultCode != OperationResultCode::opINNER)
    {
        return CloseSwapResult();
    }

    auto actualResultCode = CloseSwapOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);

    auto actualCloseSwapResult = opResult.tr().closeSwapResult();

    if (expectedResultCode != CloseSwapResultCode::SUCCESS)
    {
        return actualCloseSwapResult;
    }

    if (!closeSwapDelta)
        return actualCloseSwapResult;

    REQUIRE(closeSwapDelta->source.size() < 3);
    REQUIRE(closeSwapDelta->destination.size() < 2);
    REQUIRE(closeSwapDelta->commission.size() < 3);

    auto sourceDelta = closeSwapDelta->source;
    auto destDelta = closeSwapDelta->destination;
    auto commissionDelta = closeSwapDelta->commission;

    for (auto& item : sourceDelta)
    {
        if (item.asset == sourceBalanceBeforeTx->getAsset())
        {
            auto sourceBalanceAfterTx =
                balanceHelper.loadBalance(swapEntry.sourceBalance);
            REQUIRE(sourceBalanceAfterTx->getAmount() ==
                    sourceBalanceBeforeTx->getAmount() + item.amountDelta);
            continue;
        }

        throw std::runtime_error("Unexpected asset code");
    }

    for (auto& item : destDelta)
    {
        BalanceFrame::pointer destBalanceAfterTx;

            destBalanceAfterTx =
                balanceHelper.loadBalance(swapEntry.destinationBalance);

        REQUIRE(!!destBalanceAfterTx);
        REQUIRE(destBalanceAfterTx->getAmount() ==
                destBalanceBeforeTx->getAmount() + item.amountDelta);
    }

    for (auto& item : commissionDelta)
    {
        BalanceFrame::pointer commissionBalanceBeforeTx;

        if (commissionBalancesBeforeTxByAsset.count(item.asset) > 0)
            commissionBalanceBeforeTx =
                commissionBalancesBeforeTxByAsset[item.asset];

        auto commissionBalanceAfterTx = balanceHelper.loadBalance(
            mTestManager->getApp().getAdminID(), item.asset);
        if (!commissionBalanceBeforeTx)
        {
            REQUIRE(commissionBalanceAfterTx->getAmount() == item.amountDelta);
            continue;
        }
        REQUIRE(commissionBalanceAfterTx->getAmount() ==
                commissionBalanceBeforeTx->getAmount() + item.amountDelta);
    }
    return actualCloseSwapResult;
}
}
}
