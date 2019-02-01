#pragma once

#include "ReviewRequestTestHelper.h"
#include <ledger/AtomicSwapBidHelper.h>

namespace stellar
{

namespace txtest
{

class ASwapRequestReviewChecker : public ReviewChecker
{
protected:
    AtomicSwapBidFrame::pointer mBidBeforeTx;
    BalanceFrame::pointer mBidOwnerBalanceBeforeTx;
    BalanceFrame::pointer mPurchaserBalanceBeforeTx;

public:
    ASwapRequestReviewChecker(TestManager::pointer testManager, uint64_t requestID);

    void checkPermanentReject(ReviewableRequestFrame::pointer request) override;

    void checkApprove(ReviewableRequestFrame::pointer request) override;
};

class ReviewASwapRequestHelper : public ReviewRequestHelper
{
public:
    explicit ReviewASwapRequestHelper(TestManager::pointer testManager);

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
};

}

}