#include "ReviewRedemptionRequestTestHelper.h"

namespace stellar {
    namespace txtest {
        ReviewRedemptionRequestTestHelper::ReviewRedemptionRequestTestHelper(
                TestManager::pointer testManager) : ReviewRequestHelper(testManager)
        {
            requestMustBeDeletedAfterApproval = true;
        }


        TransactionFramePtr
        ReviewRedemptionRequestTestHelper::createReviewRequestTx(struct stellar::txtest::Account &source,
                                                                 uint64_t requestID, stellar::Hash requestHash,
                                                                 enum stellar::ReviewableRequestType requestType,
                                                                 enum stellar::ReviewRequestOpAction action,
                                                                 std::string rejectReason) {
            Operation op;
            op.body.type(OperationType::REVIEW_REQUEST);
            ReviewRequestOp &reviewRequestOp = op.body.reviewRequestOp();
            reviewRequestOp.action = action;
            reviewRequestOp.reason = rejectReason;
            reviewRequestOp.requestHash = requestHash;
            reviewRequestOp.requestID = requestID;
            reviewRequestOp.requestDetails.requestType(requestType);
            reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);
            return txFromOperation(source, op, nullptr);
        }

        ReviewRequestResult ReviewRedemptionRequestTestHelper::applyReviewRequestTx(Account &source, uint64_t requestID,
                                                                                    Hash requestHash,
                                                                                    ReviewableRequestType requestType,
                                                                                    ReviewRequestOpAction action,
                                                                                    std::string rejectReason,
                                                                                    ReviewRequestResultCode expectedResult) {
            return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash, requestType,
                                                             action, rejectReason, expectedResult);
        }
    }
}