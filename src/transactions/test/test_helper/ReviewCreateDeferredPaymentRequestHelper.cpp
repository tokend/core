#include "ReviewCreateDeferredPaymentRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/DeferredPaymentHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "transactions/payment/CreateDeferredPaymentCreationRequestOpFrame.h"

namespace stellar
{

namespace txtest
{

ReviewCreateDeferredPaymentRequestTestHelper::
    ReviewCreateDeferredPaymentRequestTestHelper(
        TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewCreateDeferredPaymentRequestChecker::
    ReviewCreateDeferredPaymentRequestChecker(const TestManager::pointer& testManager)
    : ReviewChecker(testManager)
{
}

void
ReviewCreateDeferredPaymentRequestChecker::checkApprove(
    ReviewableRequestFrame::pointer request)
{
    auto requestAfterTx = mTestManager->getStorageHelper()
                              .getReviewableRequestHelper()
                              .loadRequest(request->getRequestID());

    REQUIRE(requestAfterTx == nullptr);
}

ReviewRequestResult
ReviewCreateDeferredPaymentRequestTestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{

    auto& storageHelper = mTestManager->getStorageHelper();

    auto checker = ReviewCreateDeferredPaymentRequestChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTx(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker);
}

TransactionFramePtr
ReviewCreateDeferredPaymentRequestTestHelper::createReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
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
    reviewRequestOp.reviewDetails.tasksToAdd = 0;
    reviewRequestOp.reviewDetails.tasksToRemove =
        action == ReviewRequestOpAction::APPROVE ? 30 : 0;
    reviewRequestOp.reviewDetails.externalDetails = "{}";

    return txFromOperation(source, op, nullptr);
}

}
}
