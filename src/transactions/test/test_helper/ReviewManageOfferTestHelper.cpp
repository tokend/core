// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewManageOfferTestHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
ManageOfferReviewChecker::ManageOfferReviewChecker(
    const TestManager::pointer testManager, const uint64_t requestID)
    : ReviewChecker(testManager)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
        requestID, mTestManager->getDB());
    if (!request || request->getType() != ReviewableRequestType::MANAGE_OFFER)
    {
        return;
    }
}

void
ManageOfferReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    REQUIRE(!!manageOfferRequest);
}

ReviewManageOfferRequestHelper::ReviewManageOfferRequestHelper(
    TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewManageOfferRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker = ManageOfferReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker);
}

ReviewRequestResult
ReviewManageOfferRequestHelper::applyReviewRequestTxWithTasks(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult,
    uint32_t* tasksToAdd, uint32_t* tasksToRemove)
{
    auto checker = ManageOfferReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker, tasksToAdd, tasksToRemove);
}

ReviewRequestResult
ReviewManageOfferRequestHelper::applyReviewRequestTxWithTasks(
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
