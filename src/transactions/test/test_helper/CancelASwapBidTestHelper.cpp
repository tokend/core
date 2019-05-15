#include <ledger/BalanceHelperLegacy.h>
#include <ledger/AtomicSwapBidHelper.h>
#include <transactions/atomic_swap/CancelASwapBidOpFrame.h>
#include "CancelASwapBidTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

CancelASwapBidHelper::CancelASwapBidHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
CancelASwapBidHelper::createCancelASwapBidTx(Account &source, uint64_t bidID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_ATOMIC_SWAP_BID);
    auto& op = baseOp.body.cancelAtomicSwapBidOp();
    op.bidID = bidID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

CancelAtomicSwapBidResult
CancelASwapBidHelper::applyCancelASwapBid(Account &source, uint64_t bidID,
                                          CancelAtomicSwapBidResultCode expectedResult,
                                          OperationResultCode expectedOpCode)
{
    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto aSwapBidHelper = AtomicSwapBidHelper::Instance();

    Database& db = mTestManager->getDB();

    AtomicSwapBidFrame::pointer bidBeforeTx = nullptr;
    BalanceFrame::pointer baseBalanceBeforeTx = nullptr;

    bidBeforeTx = aSwapBidHelper->loadAtomicSwapBid(bidID, db);
    if (bidBeforeTx != nullptr)
        baseBalanceBeforeTx = balanceHelper->mustLoadBalance(bidBeforeTx->getOwnerID(),
                                                             bidBeforeTx->getBaseAsset(),
                                                             db);

    auto txFrame = createCancelASwapBidTx(source, bidID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpCode);
    if (expectedOpCode != OperationResultCode::opINNER)
    {
        return CancelAtomicSwapBidResult();
    }

    auto actualResultCode = CancelASwapBidOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    auto cancelASwapBidResult = opResult.tr().cancelAtomicSwapBidResult();

    if (expectedResult != CancelAtomicSwapBidResultCode::SUCCESS)
    {
        return cancelASwapBidResult;
    }

    auto bidFrameAfterTx = aSwapBidHelper->loadAtomicSwapBid(bidID, db);

    if (bidFrameAfterTx != nullptr)
    {
        REQUIRE(bidFrameAfterTx->getLockedAmount() != 0);
        REQUIRE(bidFrameAfterTx->isCancelled());
        return cancelASwapBidResult;
    }

    REQUIRE(baseBalanceBeforeTx != nullptr);

    auto baseBalanceAfterTx = balanceHelper->mustLoadBalance(bidBeforeTx->getOwnerID(),
                                                             bidBeforeTx->getBaseAsset(),
                                                             db);
    REQUIRE(baseBalanceAfterTx != nullptr);

    REQUIRE(baseBalanceAfterTx->getAmount() - bidBeforeTx->getAmount() ==
            baseBalanceBeforeTx->getAmount());

    REQUIRE(baseBalanceBeforeTx->getLocked() - bidBeforeTx->getAmount() ==
            baseBalanceAfterTx->getLocked());

    return cancelASwapBidResult;
}


}

}