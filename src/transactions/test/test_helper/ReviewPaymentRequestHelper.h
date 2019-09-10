#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "ReviewRequestTestHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/AssetFrame.h"
#include "ledger/BalanceFrame.h"
#include "PaymentTestHelper.h"

namespace stellar
{
namespace txtest
{

class PaymentReviewChecker : public ReviewChecker
{
    std::shared_ptr<CreatePaymentRequest> paymentRequest;
    BalanceFrame::pointer sourceBalanceBefore;
    BalanceFrame::pointer destBalanceBefore;
    std::vector<BalanceFrame::pointer> commissionBalancesBefore;
    std::unordered_map<std::string, BalanceFrame::pointer>
        commissionBalancesBeforeTxByAsset;

    PaymentDelta* delta;
  public:
    PaymentReviewChecker(TestManager::pointer testManager, uint64_t requestID, PaymentDelta *delta = nullptr);
    void checkApprove(ReviewableRequestFrame::pointer) override;
};

class ReviewPaymentRequestHelper : public ReviewRequestHelper
{

public:
    ReviewPaymentRequestHelper(TestManager::pointer testManager);

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
                                                      uint32_t *tasksToAdd = nullptr, uint32_t *tasksToRemove = nullptr) override;
};
}
}
