#include <ledger/BalanceHelperLegacy.h>
#include <ledger/AtomicSwapAskHelper.h>
#include <ledger/ReviewableRequestHelperLegacy.h>
#include "ReviewRequestTestHelper.h"
#include "ReviewASwapAskRequestTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{

namespace txtest
{

ASwapAskRequestReviewChecker::ASwapAskRequestReviewChecker(
        TestManager::pointer testManager, uint64_t requestID)
        : ReviewChecker(testManager)
{
    auto& db = mTestManager->getDB();
    auto request = ReviewableRequestHelperLegacy::Instance()->loadRequest(requestID, db);
    auto& aSwapCreationRequest =
            request->getRequestEntry().body.createAtomicSwapAskRequest();
    mBaseBalanceBeforeTx = BalanceHelperLegacy::Instance()->mustLoadBalance(
            aSwapCreationRequest.baseBalance, db);
}

void ASwapAskRequestReviewChecker::checkPermanentReject(
        ReviewableRequestFrame::pointer request)
{
    auto& db = mTestManager->getDB();

    auto requestAfterTx = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            request->getRequestID(), db);

    REQUIRE(requestAfterTx == nullptr);

    auto& aSwapCreationRequest =
            request->getRequestEntry().body.createAtomicSwapAskRequest();
    auto baseBalanceAfterTx = BalanceHelperLegacy::Instance()->loadBalance(
            aSwapCreationRequest.baseBalance, db);

    REQUIRE(baseBalanceAfterTx->getAmount() - aSwapCreationRequest.amount ==
            mBaseBalanceBeforeTx->getAmount());
    REQUIRE(mBaseBalanceBeforeTx->getLocked() - aSwapCreationRequest.amount ==
            baseBalanceAfterTx->getLocked());
}


void ASwapAskRequestReviewChecker::checkApprove(
        ReviewableRequestFrame::pointer request)
{
    auto requestAfterTx = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            request->getRequestID(), mTestManager->getDB());

    REQUIRE(requestAfterTx == nullptr);
}


ReviewASwapAskRequestHelper::ReviewASwapAskRequestHelper(
        TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

TransactionFramePtr
ReviewASwapAskRequestHelper::createReviewRequestTx(
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
ReviewASwapAskRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, Hash requestHash,
        ReviewableRequestType requestType, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto swapBidCreationRequestChecker =
            ASwapAskRequestReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash,
                                                     requestType, action, rejectReason,
                                                     expectedResult,
                                                     swapBidCreationRequestChecker);

}

ReviewRequestResult
ReviewASwapAskRequestHelper::applyReviewRequestTx(
        Account &source, uint64_t requestID, ReviewRequestOpAction action,
        std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto request = ReviewableRequestHelperLegacy::Instance()->loadRequest(
            requestID, mTestManager->getDB());
    REQUIRE(request != nullptr);
    return applyReviewRequestTx(source, requestID, request->getHash(),
                                request->getRequestType(), action, rejectReason,
                                expectedResult);
}

ReviewRequestResult
ReviewASwapAskRequestHelper::applyReviewRequestTxWithTasks(Account &source,
       uint64_t requestID, ReviewRequestOpAction action, std::string rejectReason,
       uint32_t tasksToRemove, ReviewRequestResultCode expectedResult)
{
    mTasksToRemove = tasksToRemove;
    return applyReviewRequestTx(source, requestID, action, rejectReason, expectedResult);
}

}

}
