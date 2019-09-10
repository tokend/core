// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewPaymentRequestHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include <ledger/AssetPairHelper.h>

namespace stellar
{
namespace txtest
{
PaymentReviewChecker::PaymentReviewChecker(
    const TestManager::pointer testManager, const uint64_t requestID)
    : ReviewChecker(testManager)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
        requestID, mTestManager->getDB());
    if (!request || request->getType() != ReviewableRequestType::CREATE_PAYMENT)
    {
        return;
    }

    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    paymentRequest = std::make_shared<CreatePaymentRequest>(
        request->getRequestEntry().body.createPaymentRequest());
    sourceBalanceBefore =
        balanceHelper.loadBalance(request->getRequestEntry()
                                      .body.createPaymentRequest()
                                      .paymentOp.sourceBalanceID);
}

void PaymentReviewChecker::checkApprove(ReviewableRequestFrame::pointer)
{
    REQUIRE(!!paymentRequest);
    REQUIRE(!!sourceBalanceBefore);

    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    auto sourceBalanceAfter =
        balanceHelper.loadBalance(paymentRequest->paymentOp.sourceBalanceID);

    auto amount = paymentRequest->paymentOp.amount;
    uint64_t totalFee = 0;
    if (paymentRequest->paymentOp.feeData.sourcePaysForDest)
    {
        if (!safeSum(paymentRequest->paymentOp.feeData.sourceFee.fixed,
                     paymentRequest->paymentOp.feeData.sourceFee.percent,
                     totalFee))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to calculate total sum of fees to "
                   "be charged - overflow";
            throw std::runtime_error(
                "Total sum of fees to be charged overflows");
        }

        amount += totalFee;
    }

    REQUIRE(sourceBalanceBefore->getAmount() ==
            sourceBalanceAfter->getAmount() + totalFee);
    REQUIRE(sourceBalanceBefore->getAmount() ==
                sourceBalanceAfter->getAmount() + amount);
}

ReviewPaymentRequestHelper::ReviewPaymentRequestHelper(
    TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker = PaymentReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker);
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTxWithTasks(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult,
    uint32_t* tasksToAdd, uint32_t* tasksToRemove)
{
    auto checker = PaymentReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker, tasksToAdd, tasksToRemove);
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTxWithTasks(
    Account& source, uint64_t requestID, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult,
    uint32_t* tasksToAdd, uint32_t* tasksToRemove)
{
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(
        source, requestID, action, rejectReason, expectedResult, tasksToAdd,
        tasksToRemove);
}
}
}
