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
    mBidOwnerBalanceBeforeTx = BalanceHelper::Instance()->loadBalance(
            mBidBeforeTx->getOwnerID(), mBidBeforeTx->getBaseAsset(), db, nullptr);
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

    auto bidAfterTx = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapRequest.bidID, db);

    if (bidAfterTx != nullptr)
    {
        REQUIRE(bidAfterTx->getAmount() - aSwapRequest.baseAmount ==
                mBidBeforeTx->getAmount());
        REQUIRE(mBidBeforeTx->getLockedAmount() - aSwapRequest.baseAmount ==
                bidAfterTx->getLockedAmount());
        return;
    }

    auto baseBalanceAfterTx = BalanceHelper::Instance()->mustLoadBalance(
            mBidBeforeTx->getOwnerID(), mBidBeforeTx->getBaseAsset(), db);

    REQUIRE(baseBalanceAfterTx->getAmount() - mBidBeforeTx->getTotalAmount() ==
            mBidOwnerBalanceBeforeTx->getAmount());
    REQUIRE(mBidOwnerBalanceBeforeTx->getLocked() - mBidBeforeTx->getTotalAmount() ==
            baseBalanceAfterTx->getLocked());
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

    auto baseBalanceAfterTx = balanceHelper->mustLoadBalance(
            mBidBeforeTx->getOwnerID(), mBidBeforeTx->getBaseAsset(), db);

    if (bidAfterTx == nullptr)
    {
        REQUIRE(mBidOwnerBalanceBeforeTx->getLocked() - mBidBeforeTx->getTotalAmount() ==
                baseBalanceAfterTx->getLocked());
        return;
    }

    REQUIRE(mBidOwnerBalanceBeforeTx->getLocked() - aSwapRequest.baseAmount ==
            baseBalanceAfterTx->getLocked());
}

ReviewASwapRequestHelper::ReviewASwapRequestHelper(TestManager::pointer testManager)
        : ReviewRequestHelper(testManager)
{
}

TransactionFramePtr
ReviewASwapRequestHelper::createReviewRequestTx(Account &source, uint64_t requestID,
                                                Hash requestHash,
                                                ReviewableRequestType requestType,
                                                ReviewRequestOpAction action,
                                                std::string rejectReason)
{
    Operation op;
    op.body.type(OperationType::REVIEW_REQUEST);
    ReviewRequestOp& reviewRequestOp = op.body.reviewRequestOp();
    reviewRequestOp.action = action;
    reviewRequestOp.reason = rejectReason;
    reviewRequestOp.requestHash = requestHash;
    reviewRequestOp.requestID = requestID;
    reviewRequestOp.requestDetails.requestType(requestType);
    reviewRequestOp.ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    reviewRequestOp.ext.reviewDetails().tasksToAdd = 0;
    reviewRequestOp.ext.reviewDetails().tasksToRemove =
            action == ReviewRequestOpAction::APPROVE ? 2 : 0;
    reviewRequestOp.ext.reviewDetails().externalDetails = "";

    return txFromOperation(source, op, nullptr);
}

ReviewRequestResult
ReviewASwapRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, Hash requestHash,
        ReviewableRequestType requestType, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto aSwapRequestChecker = ASwapRequestReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash,
                                                     requestType, action, rejectReason,
                                                     expectedResult,
                                                     aSwapRequestChecker);
}

ReviewRequestResult
ReviewASwapRequestHelper::applyReviewRequestTx(Account &source, uint64_t requestID,
                                               ReviewRequestOpAction action,
                                               std::string rejectReason,
                                               ReviewRequestResultCode expectedResult)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            requestID, mTestManager->getDB());
    REQUIRE(request != nullptr);
    return applyReviewRequestTx(source, requestID, request->getHash(),
                                request->getRequestType(), action, rejectReason,
                                expectedResult);
}

}

}