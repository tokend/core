#include "ReviewASwapBidRequestTestHelper.h"
#include <ledger/ReviewableRequestHelperLegacy.h>
#include <ledger/BalanceHelperLegacy.h>
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

ASwapBidRequestReviewChecker::ASwapBidRequestReviewChecker(TestManager::pointer testManager,
                                                     uint64_t requestID)
        : ReviewChecker(testManager)
{
    auto& db = mTestManager->getDB();
    auto request = ReviewableRequestHelperLegacy::Instance()->loadRequest(requestID, db);
    auto& aSwapRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();
    mAskBeforeTx = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
            aSwapRequest.askID, db);
    mAskOwnerBalanceBeforeTx = BalanceHelperLegacy::Instance()->loadBalance(
            mAskBeforeTx->getOwnerID(), mAskBeforeTx->getBaseAsset(), db, nullptr);
    mPurchaserBalanceBeforeTx = BalanceHelperLegacy::Instance()->loadBalance(
            request->getRequestor(), mAskBeforeTx->getBaseAsset(), db, nullptr);
}

void
ASwapBidRequestReviewChecker::checkPermanentReject(ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto& aSwapRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();

    auto bidAfterTx = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
            aSwapRequest.askID, db);

    if (bidAfterTx != nullptr)
    {
        REQUIRE(bidAfterTx->getAmount() - aSwapRequest.baseAmount ==
                mAskBeforeTx->getAmount());
        REQUIRE(mAskBeforeTx->getLockedAmount() - aSwapRequest.baseAmount ==
                bidAfterTx->getLockedAmount());
        return;
    }

    auto baseBalanceAfterTx = BalanceHelperLegacy::Instance()->mustLoadBalance(
            mAskBeforeTx->getOwnerID(), mAskBeforeTx->getBaseAsset(), db);

    REQUIRE(baseBalanceAfterTx->getAmount() - mAskBeforeTx->getTotalAmount() ==
            mAskOwnerBalanceBeforeTx->getAmount());
    REQUIRE(mAskOwnerBalanceBeforeTx->getLocked() - mAskBeforeTx->getTotalAmount() ==
            baseBalanceAfterTx->getLocked());
}

void
ASwapBidRequestReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto balanceHelper = BalanceHelperLegacy::Instance();

    auto purchaserBalanceAfterTx = balanceHelper->loadBalance(
            request->getRequestor(), mAskBeforeTx->getBaseAsset(), db, nullptr);

    auto& aSwapRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();

    if (mPurchaserBalanceBeforeTx != nullptr)
    {
        REQUIRE(purchaserBalanceAfterTx->getAmount() - aSwapRequest.baseAmount ==
                mPurchaserBalanceBeforeTx->getAmount());
    }
    else
    {
        REQUIRE(purchaserBalanceAfterTx->getAmount() == aSwapRequest.baseAmount);
    }

    auto bidAfterTx = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
            mAskBeforeTx->getID(), db);

    auto baseBalanceAfterTx = balanceHelper->mustLoadBalance(
            mAskBeforeTx->getOwnerID(), mAskBeforeTx->getBaseAsset(), db);

    if (bidAfterTx == nullptr)
    {
        REQUIRE(mAskOwnerBalanceBeforeTx->getLocked() - mAskBeforeTx->getTotalAmount() ==
                baseBalanceAfterTx->getLocked());
        return;
    }

    REQUIRE(mAskOwnerBalanceBeforeTx->getLocked() - aSwapRequest.baseAmount ==
            baseBalanceAfterTx->getLocked());
}

ReviewASwapBidRequestHelper::ReviewASwapBidRequestHelper(TestManager::pointer testManager)
        : ReviewRequestHelper(testManager)
{
}

TransactionFramePtr
ReviewASwapBidRequestHelper::createReviewRequestTx(Account &source, uint64_t requestID,
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
    reviewRequestOp.reviewDetails.tasksToAdd = 0;
    reviewRequestOp.reviewDetails.tasksToRemove =
            action == ReviewRequestOpAction::APPROVE ? 2 : 0;
    reviewRequestOp.reviewDetails.externalDetails = "";

    return txFromOperation(source, op, nullptr);
}

ReviewRequestResult
ReviewASwapBidRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, Hash requestHash,
        ReviewableRequestType requestType, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto aSwapRequestChecker = ASwapBidRequestReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash,
                                                     requestType, action, rejectReason,
                                                     expectedResult,
                                                     aSwapRequestChecker);
}

ReviewRequestResult
ReviewASwapBidRequestHelper::applyReviewRequestTx(Account &source, uint64_t requestID,
                                               ReviewRequestOpAction action,
                                               std::string rejectReason,
                                               ReviewRequestResultCode expectedResult)
{
    auto request = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            requestID, mTestManager->getDB());
    REQUIRE(request != nullptr);
    return applyReviewRequestTx(source, requestID, request->getHash(),
                                request->getRequestType(), action, rejectReason,
                                expectedResult);
}

}

}
