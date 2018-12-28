// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/StatisticsHelper.h>
#include "ReviewWithdrawalRequestHelper.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceFrame.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
WithdrawReviewChecker::WithdrawReviewChecker(TestManager::pointer testManager, const uint64_t requestID) : TwoStepWithdrawReviewChecker(testManager, requestID)
{
}

void WithdrawReviewChecker::checkApprove(ReviewableRequestFrame::pointer)
{
    REQUIRE(!!withdrawalRequest);
    // check balance
    REQUIRE(!!balanceBeforeTx);
    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto balanceAfterTx = balanceHelper->loadBalance(withdrawalRequest->balance,
        mTestManager->getDB());
    REQUIRE(!!balanceAfterTx);
    REQUIRE(balanceAfterTx->getAmount() == balanceBeforeTx->getAmount());
    REQUIRE(balanceBeforeTx->getLocked() == balanceAfterTx->getLocked() +
        withdrawalRequest->amount + withdrawalRequest->fee.fixed +
        withdrawalRequest->fee.percent);

    // check commission
    REQUIRE(!!commissionBalanceBeforeTx);
    auto commissionBalanceAfterTx = balanceHelper->loadBalance(commissionBalanceBeforeTx->getBalanceID(), mTestManager->getDB());
    REQUIRE(!!commissionBalanceAfterTx);
    REQUIRE(commissionBalanceAfterTx->getAmount() == commissionBalanceBeforeTx->getAmount() + withdrawalRequest->fee.fixed + withdrawalRequest->fee.percent);

    // check asset
    REQUIRE(!!assetBeforeTx);
    auto assetAfterTx = AssetHelperLegacy::Instance()->loadAsset(balanceAfterTx->getAsset(), mTestManager->getDB());
    REQUIRE(!!assetAfterTx);
    REQUIRE(assetBeforeTx->getIssued() == assetAfterTx->getIssued() + withdrawalRequest->amount);
    REQUIRE(assetBeforeTx->getAvailableForIssuance() == assetAfterTx->getAvailableForIssuance());
}

TransactionFramePtr ReviewWithdrawRequestHelper::createReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
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
    reviewRequestOp.requestDetails.withdrawal().externalDetails = "{}";
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, op, nullptr);
}

TransactionFramePtr ReviewWithdrawRequestHelper::createReviewRequestTxWithTasks(txtest::Account &source,
                                                                                uint64_t requestID, Hash requestHash,
                                                                                ReviewableRequestType requestType,
                                                                                ReviewRequestOpAction action,
                                                                                std::string rejectReason,
                                                                                uint32_t *tasksToAdd,
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
    reviewRequestOp.requestDetails.withdrawal().externalDetails = "{}";
    reviewRequestOp.ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    if ( tasksToAdd != nullptr) {
        reviewRequestOp.ext.reviewDetails().tasksToAdd = *tasksToAdd;
    }
    if ( tasksToRemove != nullptr) {
        reviewRequestOp.ext.reviewDetails().tasksToRemove = *tasksToRemove;
    }
    return txFromOperation(source, op, nullptr);
}

ReviewWithdrawRequestHelper::ReviewWithdrawRequestHelper(
    TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
    requestMustBeDeletedAfterApproval = true;
}

ReviewRequestResult ReviewWithdrawRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker = WithdrawReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     checker
                                                    );
}

ReviewRequestResult ReviewWithdrawRequestHelper::applyReviewRequestTxWithTasks(txtest::Account &source,
                                                                               uint64_t requestID, Hash requestHash,
                                                                               ReviewableRequestType requestType,
                                                                               ReviewRequestOpAction action,
                                                                               std::string rejectReason,
                                                                               ReviewRequestResultCode expectedResult,
                                                                               uint32_t *tasksToAdd,
                                                                               uint32_t *tasksToRemove)
{
    auto checker = WithdrawReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     checker,
                                                     tasksToAdd,
                                                     tasksToRemove
                                                    );
}
}
}
