#pragma once

#include "ReviewRequestTestHelper.h"

namespace stellar
{

namespace txtest
{

class ASwapBidCreationRequestReviewChecker : public ReviewChecker
{
protected:
    BalanceFrame::pointer mBaseBalanceBeforeTx;

public:
    ASwapBidCreationRequestReviewChecker(TestManager::pointer testManager, uint64_t requestID);

    void checkPermanentReject(ReviewableRequestFrame::pointer request) override;

    void checkApprove(ReviewableRequestFrame::pointer request) override;
};

class ReviewASwapBidCreationRequestHelper : public ReviewRequestHelper
{
    uint32_t mTasksToRemove = 0;

public:
    explicit ReviewASwapBidCreationRequestHelper(TestManager::pointer testManager);

    TransactionFramePtr createReviewRequestTx(Account& source,
                                              uint64_t requestID, Hash requestHash,
                                              ReviewableRequestType requestType,
                                              ReviewRequestOpAction action,
                                              std::string rejectReason) override;

    using ReviewRequestHelper::applyReviewRequestTx;
    ReviewRequestResult applyReviewRequestTx(
            Account& source, uint64_t requestID, Hash requestHash,
            ReviewableRequestType requestType,
            ReviewRequestOpAction action, std::string rejectReason,
            ReviewRequestResultCode expectedResult =
            ReviewRequestResultCode::SUCCESS) override;

    ReviewRequestResult applyReviewRequestTx(
            Account & source, uint64_t requestID, ReviewRequestOpAction action,
            std::string rejectReason,
            ReviewRequestResultCode expectedResult = ReviewRequestResultCode::SUCCESS);

    ReviewRequestResult
    applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
                                  ReviewRequestOpAction action, std::string rejectReason,
                                  uint32_t tasksToRemove, ReviewRequestResultCode expectedResult =
                                          ReviewRequestResultCode::SUCCESS);
};


}

}