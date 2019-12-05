#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "ReviewRequestTestHelper.h"
#include "ledger/AccountLimitsFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{

class LimitsUpdateReviewChecker : public ReviewChecker
{
    std::shared_ptr<LimitsUpdateRequest> manageLimitsRequest;

public:
    LimitsUpdateReviewChecker(TestManager::pointer testManager, uint64_t requestID);
    void checkApprove(ReviewableRequestFrame::pointer) override;
    void checkPermanentReject(ReviewableRequestFrame::pointer) override;
};

class ReviewLimitsUpdateRequestHelper : public ReviewRequestHelper
{
public:
    LimitsV2Entry limitsV2Entry;

    explicit ReviewLimitsUpdateRequestHelper(TestManager::pointer testManager);

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

    TransactionFramePtr createReviewRequestTx(Account& source,
          uint64_t requestID, Hash requestHash, ReviewableRequestType requestType,
          ReviewRequestOpAction action, std::string rejectReason) override;

    TransactionFramePtr createReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
                                                       Hash requestHash,
                                                       ReviewableRequestType requestType,
                                                       ReviewRequestOpAction action,
                                                       std::string rejectReason, uint32_t *tasksToAdd = nullptr,
                                                       uint32_t *tasksToRemove = nullptr) override;

    void initializeLimits(AccountID& requestorID, AssetCode const& assetCode);

    ReviewRequestResult applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                      ReviewableRequestType requestType, ReviewRequestOpAction action,
                                                      std::string rejectReason, ReviewRequestResultCode expectedResult,
                                                      uint32_t *tasksToAdd, uint32_t *tasksToRemove) override;
};

}
}