#pragma once

#include "ReviewRequestTestHelper.h"
#include "ledger/DeferredPaymentFrame.h"

namespace stellar
{

namespace txtest
{
class ReviewCloseDeferredPaymentRequestChecker : public ReviewChecker
{

    std::shared_ptr<CloseDeferredPaymentRequest> closeDeferredPaymentRequest;
    BalanceFrame::pointer balanceBeforeTx;
    DeferredPaymentFrame::pointer deferredPaymentBeforeTx;

  public:
    ReviewCloseDeferredPaymentRequestChecker(
        TestManager::pointer testManager, uint64_t requestID);
    ReviewCloseDeferredPaymentRequestChecker(
        TestManager::pointer testManager, std::shared_ptr<CloseDeferredPaymentRequest> req);

    void checkApprove(ReviewableRequestFrame::pointer request) override;
};

class ReviewCloseDeferredPaymentRequestTestHelper : public ReviewRequestHelper
{
  public:
    explicit ReviewCloseDeferredPaymentRequestTestHelper(
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
