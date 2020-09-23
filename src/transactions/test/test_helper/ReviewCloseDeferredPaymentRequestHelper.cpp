#include "ReviewCloseDeferredPaymentRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/DeferredPaymentHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "transactions/CreateCloseDeferredPaymentRequestOpFrame.h"

namespace stellar
{

namespace txtest
{
void
ReviewCloseDeferredPaymentRequestChecker::checkApprove(
    ReviewableRequestFrame::pointer request)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& deferredPaymentHelper = storageHelper.getDeferredPaymentHelper();

//    auto balanceAfter = balanceHelper.loadBalance(
//        closeDeferredPaymentRequest->destinationBalance);
    uint64_t amount = closeDeferredPaymentRequest->amount;

//    auto feeData = closeDeferredPaymentRequest->feeData;
//    uint64_t totalFee = feeData.sourceFee.fixed + feeData.sourceFee.percent;
//    if (feeData.sourcePaysForDest)
//    {
//        totalFee += feeData.destinationFee.fixed;
//        totalFee += feeData.destinationFee.percent;
//
//        REQUIRE((balanceBeforeTx->getAmount() + amount) ==
//                balanceAfter->getAmount());
//    }
//
//    if (!feeData.sourcePaysForDest)
//    {
//        REQUIRE((balanceBeforeTx->getAmount() + amount - totalFee) ==
//                balanceAfter->getAmount());
//    }

    if (closeDeferredPaymentRequest->amount > (amount))
    {
        auto deferredPaymentAfter = deferredPaymentHelper.loadDeferredPayment(
            closeDeferredPaymentRequest->deferredPaymentID);

        REQUIRE(deferredPaymentAfter);
        REQUIRE((deferredPaymentAfter->getDeferredPayment().amount +
                 closeDeferredPaymentRequest->amount) ==
                deferredPaymentBeforeTx->getDeferredPayment().amount);
    }
}

ReviewCloseDeferredPaymentRequestChecker::
    ReviewCloseDeferredPaymentRequestChecker(TestManager::pointer testManager,
                                             uint64_t requestID)
    : ReviewChecker(testManager)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& deferredPaymentHelper = storageHelper.getDeferredPaymentHelper();

    auto request = requestHelper.loadRequest(requestID);

    closeDeferredPaymentRequest = std::make_shared<CloseDeferredPaymentRequest>(
        request->getRequestEntry().body.closeDeferredPaymentRequest());
//    balanceBeforeTx = balanceHelper.loadBalance(
//        closeDeferredPaymentRequest->destinationBalance);
    deferredPaymentBeforeTx = deferredPaymentHelper.loadDeferredPayment(
        closeDeferredPaymentRequest->deferredPaymentID);
}

ReviewCloseDeferredPaymentRequestChecker::
    ReviewCloseDeferredPaymentRequestChecker(
        TestManager::pointer testManager,
        std::shared_ptr<CloseDeferredPaymentRequest> req)
    : ReviewChecker(testManager)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& deferredPaymentHelper = storageHelper.getDeferredPaymentHelper();

    closeDeferredPaymentRequest = req;
//    balanceBeforeTx = balanceHelper.loadBalance(
//        closeDeferredPaymentRequest->destinationBalance);
    deferredPaymentBeforeTx = deferredPaymentHelper.loadDeferredPayment(
        closeDeferredPaymentRequest->deferredPaymentID);
}

ReviewCloseDeferredPaymentRequestTestHelper::
    ReviewCloseDeferredPaymentRequestTestHelper(
        TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewCloseDeferredPaymentRequestTestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker =
        ReviewCloseDeferredPaymentRequestChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker);
}

TransactionFramePtr
ReviewCloseDeferredPaymentRequestTestHelper::createReviewRequestTx(
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
