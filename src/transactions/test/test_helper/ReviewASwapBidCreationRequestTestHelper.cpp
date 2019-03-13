#include <ledger/BalanceHelperLegacy.h>
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include "ReviewRequestTestHelper.h"
#include "ReviewASwapBidCreationRequestTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

ASwapBidCreationRequestReviewChecker::ASwapBidCreationRequestReviewChecker(
        TestManager::pointer testManager, uint64_t requestID)
        : ReviewChecker(testManager)
{
    auto& db = mTestManager->getDB();
    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
    auto& aSwapCreationRequest =
            request->getRequestEntry().body.aSwapBidCreationRequest();
    mBaseBalanceBeforeTx = BalanceHelperLegacy::Instance()->mustLoadBalance(
            aSwapCreationRequest.baseBalance, db);
}

void ASwapBidCreationRequestReviewChecker::checkPermanentReject(
        ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto& aSwapCreationRequest =
            request->getRequestEntry().body.aSwapBidCreationRequest();
    auto baseBalanceAfterTx = BalanceHelperLegacy::Instance()->loadBalance(
            aSwapCreationRequest.baseBalance, db);

    REQUIRE(baseBalanceAfterTx->getAmount() - aSwapCreationRequest.amount ==
            mBaseBalanceBeforeTx->getAmount());
    REQUIRE(mBaseBalanceBeforeTx->getLocked() - aSwapCreationRequest.amount ==
            baseBalanceAfterTx->getLocked());
}


void ASwapBidCreationRequestReviewChecker::checkApprove(
        ReviewableRequestFrame::pointer request)
{
    auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(
            request->getRequestID(), mTestManager->getDB());

    REQUIRE(requestAfterTx == nullptr);
}


ReviewASwapBidCreationRequestHelper::ReviewASwapBidCreationRequestHelper(
        TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

TransactionFramePtr
ReviewASwapBidCreationRequestHelper::createReviewRequestTx(
        Account &source, uint64_t requestID, Hash requestHash,
        ReviewableRequestType requestType, ReviewRequestOpAction action,
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
    reviewRequestOp.reviewDetails.tasksToRemove = mTasksToRemove;
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);

    return txFromOperation(source, op, nullptr);
}

ReviewRequestResult
ReviewASwapBidCreationRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, Hash requestHash,
        ReviewableRequestType requestType, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto swapBidCreationRequestChecker =
            ASwapBidCreationRequestReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash,
                                                     requestType, action, rejectReason,
                                                     expectedResult,
                                                     swapBidCreationRequestChecker);

}

ReviewRequestResult
ReviewASwapBidCreationRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            requestID, mTestManager->getDB());
    REQUIRE(request != nullptr);
    return applyReviewRequestTx(source, requestID, request->getHash(),
                                request->getRequestType(), action, rejectReason,
                                expectedResult);
}

ReviewRequestResult
ReviewASwapBidCreationRequestHelper::applyReviewRequestTxWithTasks(Account &source,
       uint64_t requestID, ReviewRequestOpAction action, std::string rejectReason,
       uint32_t tasksToRemove, ReviewRequestResultCode expectedResult)
{
    mTasksToRemove = tasksToRemove;
    return applyReviewRequestTx(source, requestID, action, rejectReason, expectedResult);
}

}

}