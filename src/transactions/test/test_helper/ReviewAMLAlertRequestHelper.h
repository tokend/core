#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "ReviewRequestTestHelper.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{

    class AmlReviewChecker : public ReviewChecker
    {
    protected:
        void checkApproval(AMLAlertRequest const& request,
            AccountID const& requestor);
        void checkPermanentReject(AMLAlertRequest const& request,
            AccountID const& requestor);
    public:
        explicit AmlReviewChecker(const TestManager::pointer& testManager)
            : ReviewChecker(testManager)
        {
        }

        void checkApprove(ReviewableRequestFrame::pointer) override;
        void checkPermanentReject(ReviewableRequestFrame::pointer) override;
    };
class ReviewAmlAlertHelper : public ReviewRequestHelper
{
public:
    ReviewAmlAlertHelper(TestManager::pointer testManager);

    using ReviewRequestHelper::applyReviewRequestTx;
    ReviewRequestResult applyReviewRequestTx(Account& source,
                                             uint64_t requestID,
                                             Hash requestHash,
                                             ReviewableRequestType requestType,
                                             ReviewRequestOpAction action,
                                             std::string rejectReason,
                                             ReviewRequestResultCode
                                             expectedResult =
                                                 ReviewRequestResultCode::
                                                 SUCCESS) override;

    ReviewRequestResult applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                      ReviewableRequestType requestType, ReviewRequestOpAction action,
                                                      std::string rejectReason, ReviewRequestResultCode expectedResult,
                                                      uint32_t *tasksToAdd, uint32_t *tasksToRemove) override;

    ReviewRequestResult applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, ReviewRequestOpAction action,
                                                      std::string rejectReason, ReviewRequestResultCode expectedResult,
                                                      uint32_t *tasksToAdd, uint32_t *tasksToRemove) override;
};
}
}
