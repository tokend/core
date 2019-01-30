#include "ReviewChangeRoleRequestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountKYCHelper.h"
#include "transactions/CreateChangeRoleRequestOpFrame.h"

namespace stellar
{

namespace txtest
{
void ReviewChangeRoleRequestChecker::checkApprove(ReviewableRequestFrame::pointer request) {
    auto updateKYCRequest = request->getRequestEntry().body.changeRoleRequest();
    auto accountAfterTx = AccountHelperLegacy::Instance()->loadAccount(updateKYCRequest.destinationAccount, mTestManager->getDB());
    REQUIRE(!!accountAfterTx);
    REQUIRE(accountAfterTx->getAccountRole() == updateKYCRequest.accountRoleToSet);

    auto accountKYCAfterTx = AccountKYCHelper::Instance()->loadAccountKYC(updateKYCRequest.destinationAccount,mTestManager->getDB());
    REQUIRE(!!accountKYCAfterTx);
    REQUIRE(accountKYCAfterTx->getKYCData() == updateKYCRequest.kycData);
}

ReviewChangeRoleRequestChecker::ReviewChangeRoleRequestChecker(TestManager::pointer testManager)
        : ReviewChecker(testManager)
{
}

ReviewChangeRoleRequestTestHelper::ReviewChangeRoleRequestTestHelper(
        TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult ReviewChangeRoleRequestTestHelper::applyReviewRequestTx(Account &source, uint64_t requestID,
                                                                     Hash requestHash,
                                                                     ReviewableRequestType requestType,
                                                                     ReviewRequestOpAction action,
                                                                     std::string rejectReason,
                                                                     ReviewRequestResultCode expectedResult) {
    auto checker = ReviewChangeRoleRequestChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     checker);
}

TransactionFramePtr
ReviewChangeRoleRequestTestHelper::createReviewRequestTx(Account& source, uint64_t requestID, Hash requestHash,
                                                  ReviewableRequestType requestType,
                                                  ReviewRequestOpAction action, std::string rejectReason) {
    Operation op;
    op.body.type(OperationType::REVIEW_REQUEST);
    ReviewRequestOp& reviewRequestOp = op.body.reviewRequestOp();
    reviewRequestOp.action = action;
    reviewRequestOp.reason = rejectReason;
    reviewRequestOp.requestHash = requestHash;
    reviewRequestOp.requestID = requestID;
    reviewRequestOp.requestDetails.requestType(requestType);
    reviewRequestOp.reviewDetails.tasksToAdd = 0;
    reviewRequestOp.reviewDetails.tasksToRemove = action == ReviewRequestOpAction::APPROVE
            ? CreateChangeRoleRequestOpFrame::defaultTasks
            : 0;
    reviewRequestOp.reviewDetails.externalDetails = "{}";

    return txFromOperation(source, op, nullptr);
}

}
}