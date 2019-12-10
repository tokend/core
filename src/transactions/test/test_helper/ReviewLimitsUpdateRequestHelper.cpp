// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/LimitsV2Helper.h>
#include "ReviewLimitsUpdateRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test_marshaler.h"
#include "src/ledger/StorageHelperImpl.h"

namespace stellar
{
namespace txtest
{
LimitsUpdateReviewChecker::LimitsUpdateReviewChecker(TestManager::pointer testManager,
                                                     uint64_t requestID) : ReviewChecker(testManager)
{
    auto& reviewableRequestHelper = mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto request = reviewableRequestHelper.loadRequest(requestID);
    if (!request || request->getType() != ReviewableRequestType::UPDATE_LIMITS)
    {
        return;
    }
    manageLimitsRequest = std::make_shared<LimitsUpdateRequest>(request->getRequestEntry().body.limitsUpdateRequest());
}

void
LimitsUpdateReviewChecker::checkApprove(ReviewableRequestFrame::pointer request) {
    REQUIRE(!!manageLimitsRequest);

    // check accountLimits
    auto& limitsHelper = mTestManager->getStorageHelper().getLimitsV2Helper();
    auto limitsEntry = mOperation.body.reviewRequestOp().requestDetails.limitsUpdate().newLimitsV2;
    auto limitsAfterTx = limitsHelper.loadLimits(limitsEntry.statsOpType, limitsEntry.assetCode,
            limitsEntry.accountID, limitsEntry.accountRole.get(), limitsEntry.isConvertNeeded);
    REQUIRE(!!limitsAfterTx);
    auto limitsEntryAfterTx = limitsAfterTx->getLimits();
    auto reviewRequestLimits = mOperation.body.reviewRequestOp().requestDetails.limitsUpdate().newLimitsV2;
    REQUIRE(limitsEntryAfterTx.dailyOut == reviewRequestLimits.dailyOut);
    REQUIRE(limitsEntryAfterTx.weeklyOut == reviewRequestLimits.weeklyOut);
    REQUIRE(limitsEntryAfterTx.monthlyOut == reviewRequestLimits.monthlyOut);
    REQUIRE(limitsEntryAfterTx.annualOut == reviewRequestLimits.annualOut);
}

void
LimitsUpdateReviewChecker::checkPermanentReject(ReviewableRequestFrame::pointer request)
{
}

ReviewLimitsUpdateRequestHelper::ReviewLimitsUpdateRequestHelper(
        TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewLimitsUpdateRequestHelper::applyReviewRequestTx(Account &source, uint64_t requestID, Hash requestHash,
                                                      ReviewableRequestType requestType,
                                                      ReviewRequestOpAction action,
                                                      std::string rejectReason,
                                                      ReviewRequestResultCode expectedResult)
{
    auto checker = LimitsUpdateReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     checker);
}

TransactionFramePtr
ReviewLimitsUpdateRequestHelper::createReviewRequestTx(Account &source, uint64_t requestID, Hash requestHash,
                                                       ReviewableRequestType requestType,
                                                       ReviewRequestOpAction action,
                                                       std::string rejectReason)
{
    Operation op;
    op.body.type(OperationType::REVIEW_REQUEST);
    ReviewRequestOp& reviewRequestOp = op.body.reviewRequestOp();
    reviewRequestOp.action = action;
    reviewRequestOp.reason = rejectReason;
    reviewRequestOp.requestHash = requestHash;
    reviewRequestOp.requestID = requestID;
    reviewRequestOp.requestDetails.requestType(requestType);
    reviewRequestOp.requestDetails.limitsUpdate().newLimitsV2 = limitsV2Entry;
    return txFromOperation(source, op, nullptr);
}

TransactionFramePtr
ReviewLimitsUpdateRequestHelper::createReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
                                                                Hash requestHash,
                                                                ReviewableRequestType requestType,
                                                                ReviewRequestOpAction action,
                                                                std::string rejectReason, uint32_t *tasksToAdd,
                                                                uint32_t *tasksToRemove)
{
    Operation op;
    op.body.type(OperationType::REVIEW_REQUEST);
    ReviewRequestOp& reviewRequestOp = op.body.reviewRequestOp();
    reviewRequestOp.action = action;
    reviewRequestOp.reason = rejectReason;
    reviewRequestOp.requestHash = requestHash;
    reviewRequestOp.requestID = requestID;
    reviewRequestOp.requestDetails.requestType(requestType);
    reviewRequestOp.requestDetails.limitsUpdate().newLimitsV2 = limitsV2Entry;

    if (tasksToAdd != nullptr){
        reviewRequestOp.reviewDetails.tasksToAdd = *tasksToAdd;
    }

    if (tasksToRemove != nullptr){
        reviewRequestOp.reviewDetails.tasksToRemove = *tasksToRemove;
    }

    return txFromOperation(source, op, nullptr);
}

void
ReviewLimitsUpdateRequestHelper::initializeLimits(AccountID& requestorID, AssetCode const& code)
{
    limitsV2Entry.accountID.activate() = requestorID;
    limitsV2Entry.assetCode = code;
    limitsV2Entry.statsOpType = StatsOpType::PAYMENT_OUT;
    limitsV2Entry.isConvertNeeded = false;
    limitsV2Entry.dailyOut = 100;
    limitsV2Entry.weeklyOut = 200;
    limitsV2Entry.monthlyOut = 300;
    limitsV2Entry.annualOut = 500;
}

    ReviewRequestResult
    ReviewLimitsUpdateRequestHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
                                                                   Hash requestHash, ReviewableRequestType requestType,
                                                                   ReviewRequestOpAction action,
                                                                   std::string rejectReason,
                                                                   ReviewRequestResultCode expectedResult,
                                                                   uint32_t *tasksToAdd, uint32_t *tasksToRemove) {

        auto checker = LimitsUpdateReviewChecker(mTestManager, requestID);
        return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                         requestHash, requestType,
                                                         action, rejectReason,
                                                         expectedResult,
                                                         checker,
                                                         tasksToAdd,
                                                         tasksToRemove);
    }
}
}
