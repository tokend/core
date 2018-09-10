#include "ReviewAswapRequestTestHelper.h"
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/BalanceHelper.h>
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

ASwapRequestReviewChecker::ASwapRequestReviewChecker(TestManager::pointer testManager,
                                                     uint64_t requestID)
        : ReviewChecker(testManager)
{
    auto& db = mTestManager->getDB();
    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
    auto& aSwapRequest = request->getRequestEntry().body.aSwapRequest();
    mBidBeforeTx = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapRequest.bidID, db);
    mPurchaserBalanceBeforeTx = BalanceHelper::Instance()->loadBalance(
            request->getRequestor(), mBidBeforeTx->getBaseAsset(), db, nullptr);
}

void
ASwapRequestReviewChecker::checkPermanentReject(ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto& aSwapRequest = request->getRequestEntry().body.aSwapRequest();

    auto bidFrameAfterTx = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapRequest.bidID, db);

    REQUIRE(bidFrameAfterTx != nullptr);

    REQUIRE(bidFrameAfterTx->getAmount() - aSwapRequest.baseAmount ==
            mBidBeforeTx->getAmount());
    REQUIRE(mBidBeforeTx->getLockedAmount() - aSwapRequest.baseAmount ==
            bidFrameAfterTx->getLockedAmount());
}

void
ASwapRequestReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto balanceHelper = BalanceHelper::Instance();

    auto purchaserBalanceAfterTx = balanceHelper->loadBalance(
            request->getRequestor(), mBidBeforeTx->getBaseAsset(), db, nullptr);

    auto& aSwapRequest = request->getRequestEntry().body.aSwapRequest();

    if (mPurchaserBalanceBeforeTx != nullptr)
    {
        REQUIRE(purchaserBalanceAfterTx->getAmount() - aSwapRequest.baseAmount ==
                mPurchaserBalanceBeforeTx->getAmount());
    }
    else
    {
        REQUIRE(purchaserBalanceAfterTx->getAmount() == aSwapRequest.baseAmount);
    }

    auto bidAfterTx = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            mBidBeforeTx->getBidID(), db);

    if (bidAfterTx != nullptr)
    {
        REQUIRE(mBidBeforeTx->getLockedAmount() - aSwapRequest.baseAmount ==
                bidAfterTx->getLockedAmount());
    }

    auto baseBalanceAfterTx = balanceHelper->mustLoadBalance(mBidBeforeTx->getOwnerID(),
                                                      mBidBeforeTx->getBaseAsset(), db);

    REQUIRE(mBaseBalanceBeforeTx->getLocked() - aSwapRequest.baseAmount ==
            baseBalanceAfterTx->getLocked());
}

}

}