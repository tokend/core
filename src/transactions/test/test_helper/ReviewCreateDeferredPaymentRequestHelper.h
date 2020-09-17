#pragma once

#include "ReviewRequestTestHelper.h"

namespace stellar
{

namespace txtest
{
class ReviewCreateDeferredPaymentRequestChecker : public ReviewChecker
{
  public:
    explicit ReviewCreateDeferredPaymentRequestChecker(
        const TestManager::pointer& testManager);

    void checkApprove(ReviewableRequestFrame::pointer request) override;
};

class ReviewCreateDeferredPaymentRequestTestHelper : public ReviewRequestHelper
{
  public:
    explicit ReviewCreateDeferredPaymentRequestTestHelper(
        TestManager::pointer testManager);

    ReviewRequestResult
    applyReviewRequestTx(Account& source, uint64_t requestID, Hash requestHash,
                         ReviewableRequestType requestType,
                         ReviewRequestOpAction action, std::string rejectReason,
                         ReviewRequestResultCode expectedResult) override;
    using ReviewRequestHelper::applyReviewRequestTx;

    TransactionFramePtr
    createReviewRequestTx(Account& source, uint64_t requestID, Hash requestHash,
                          ReviewableRequestType requestType,
                          ReviewRequestOpAction action,
                          std::string rejectReason) override;
};
}

}
