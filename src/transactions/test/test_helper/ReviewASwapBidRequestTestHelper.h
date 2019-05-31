#pragma once

#include "ReviewRequestTestHelper.h"
#include <ledger/AtomicSwapAskHelper.h>

namespace stellar
{

namespace txtest
{

class ASwapBidRequestReviewChecker : public ReviewChecker
{
protected:
    AtomicSwapAskFrame::pointer mAskBeforeTx;
    BalanceFrame::pointer mAskOwnerBalanceBeforeTx;
    BalanceFrame::pointer mPurchaserBalanceBeforeTx;

public:
    ASwapBidRequestReviewChecker(TestManager::pointer testManager, uint64_t requestID);

    void checkPermanentReject(ReviewableRequestFrame::pointer request) override;

    void checkApprove(ReviewableRequestFrame::pointer request) override;
};

class ReviewASwapBidRequestHelper : public ReviewRequestHelper
{
public:
    explicit ReviewASwapBidRequestHelper(TestManager::pointer testManager);

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