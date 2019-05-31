#include <ledger/BalanceHelperLegacy.h>
#include <ledger/AtomicSwapAskHelper.h>
#include <transactions/atomic_swap/CancelAtomicSwapAskOpFrame.h>
#include "CancelASwapAskTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

CancelASwapAskHelper::CancelASwapAskHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
CancelASwapAskHelper::createCancelASwapAskTx(Account &source, uint64_t askID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_ATOMIC_SWAP_ASK);
    auto& op = baseOp.body.cancelAtomicSwapAskOp();
    op.askID = askID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

CancelAtomicSwapAskResult
CancelASwapAskHelper::applyCancelASwapBid(Account &source, uint64_t bidID,
                                          CancelAtomicSwapAskResultCode expectedResult,
                                          OperationResultCode expectedOpCode)
{
    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto aSwapBidHelper = AtomicSwapAskHelper::Instance();

    Database& db = mTestManager->getDB();

    AtomicSwapAskFrame::pointer askBeforeTx = nullptr;
    BalanceFrame::pointer baseBalanceBeforeTx = nullptr;

    askBeforeTx = aSwapBidHelper->loadAtomicSwapAsk(bidID, db);
    if (askBeforeTx != nullptr)
        baseBalanceBeforeTx = balanceHelper->mustLoadBalance(askBeforeTx->getOwnerID(),
                                                             askBeforeTx->getBaseAsset(),
                                                             db);

    auto txFrame = createCancelASwapAskTx(source, bidID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpCode);
    if (expectedOpCode != OperationResultCode::opINNER)
    {
        return CancelAtomicSwapAskResult();
    }

    auto actualResultCode = CancelAtomicSwapAskOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    auto cancelASwapBidResult = opResult.tr().cancelAtomicSwapAskResult();

    if (expectedResult != CancelAtomicSwapAskResultCode::SUCCESS)
    {
        return cancelASwapBidResult;
    }

    auto bidFrameAfterTx = aSwapBidHelper->loadAtomicSwapAsk(bidID, db);

    if (bidFrameAfterTx != nullptr)
    {
        REQUIRE(bidFrameAfterTx->getLockedAmount() != 0);
        REQUIRE(bidFrameAfterTx->isCancelled());
        return cancelASwapBidResult;
    }

    REQUIRE(baseBalanceBeforeTx != nullptr);

    auto baseBalanceAfterTx = balanceHelper->mustLoadBalance(askBeforeTx->getOwnerID(),
                                                             askBeforeTx->getBaseAsset(),
                                                             db);
    REQUIRE(baseBalanceAfterTx != nullptr);

    REQUIRE(baseBalanceAfterTx->getAmount() - askBeforeTx->getAmount() ==
            baseBalanceBeforeTx->getAmount());

    REQUIRE(baseBalanceBeforeTx->getLocked() - askBeforeTx->getAmount() ==
            baseBalanceAfterTx->getLocked());

    return cancelASwapBidResult;
}


}

}