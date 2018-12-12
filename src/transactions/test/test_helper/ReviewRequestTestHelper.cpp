// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestTestHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/review_request/ReviewRequestOpFrame.h"
#include <functional>
#include "test/test_marshaler.h"


namespace stellar
{
namespace txtest
{
ReviewRequestHelper::
ReviewRequestHelper(TestManager::pointer testManager): TxHelper(testManager)
{
    requestMustBeDeletedAfterApproval = true;
}

ReviewRequestResult ReviewRequestHelper::applyReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
                                                                           Hash requestHash,
                                                                           ReviewableRequestType requestType,
                                                                           ReviewRequestOpAction action,
                                                                           std::string rejectReason,
                                                                           ReviewRequestResultCode expectedResult,
                                                                           txtest::ReviewChecker &reviewChecker,
                                                                           uint32_t *tasksToAdd,
                                                                           uint32_t *tasksToRemove)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());
    auto requestBeforeTx = reviewableRequestHelper->loadRequest(requestID,
                                                                mTestManager->
                                                                        getDB(),
                                                                nullptr);
    auto txFrame = createReviewRequestTxWithTasks(source, requestID, requestHash,
                                         requestType, action, rejectReason,
                                         tasksToAdd, tasksToRemove);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
    mTestManager->applyCheck(txFrame, stateBeforeOp);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == OperationResultCode::opINNER);
    auto actualResultCode = ReviewRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto txOperation = txFrame->getOperations()[0]->getOperation();
    reviewChecker.setOperation(txOperation);
    REQUIRE(stateBeforeOp.size() == 1);
    const StateBeforeTxHelper stateBeforeTxHelper(stateBeforeOp[0]);
    reviewChecker.setStateBeforeTxHelper(stateBeforeTxHelper);

    auto reviewResult = opResult.tr().reviewRequestResult();
    if (expectedResult != ReviewRequestResultCode::SUCCESS)
    {
        uint64 reviewableRequestCountAfterTx = reviewableRequestHelper->
                countObjects(mTestManager->getDB().getSession());
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx)
                ;
        return reviewResult;
    }

    REQUIRE(!!requestBeforeTx);

    auto requestAfterTx = reviewableRequestHelper->loadRequest(requestID,
                                                               mTestManager->
                                                                       getDB(), nullptr);
    if (action == ReviewRequestOpAction::REJECT)
    {
        REQUIRE(!!requestAfterTx);
        REQUIRE(requestAfterTx->getRejectReason() == rejectReason);
        reviewChecker.checkReject(requestBeforeTx, requestAfterTx);
        return reviewResult;
    }

    if (action == ReviewRequestOpAction::PERMANENT_REJECT)
    {
        REQUIRE(!requestAfterTx);
        reviewChecker.checkPermanentReject(requestBeforeTx);
        return reviewResult;
    }

    reviewChecker.checkApprove(requestBeforeTx);
    return reviewResult;

}

ReviewRequestResult ReviewRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason,
    ReviewRequestResultCode expectedResult, ReviewChecker& reviewChecker)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->
        countObjects(mTestManager->getDB().getSession());
    auto requestBeforeTx = reviewableRequestHelper->loadRequest(requestID,
                                                                mTestManager->
                                                                getDB(),
                                                                nullptr);
    auto txFrame = createReviewRequestTx(source, requestID, requestHash,
                                         requestType, action, rejectReason);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOp;
    mTestManager->applyCheck(txFrame, stateBeforeOp);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == OperationResultCode::opINNER);
    auto actualResultCode = ReviewRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto txOperation = txFrame->getOperations()[0]->getOperation();
    reviewChecker.setOperation(txOperation);
    REQUIRE(stateBeforeOp.size() == 1);
    const StateBeforeTxHelper stateBeforeTxHelper(stateBeforeOp[0]);
    reviewChecker.setStateBeforeTxHelper(stateBeforeTxHelper);

    auto reviewResult = opResult.tr().reviewRequestResult();
    if (expectedResult != ReviewRequestResultCode::SUCCESS)
    {
        uint64 reviewableRequestCountAfterTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx)
        ;
        return reviewResult;
    }

    REQUIRE(!!requestBeforeTx);

    auto requestAfterTx = reviewableRequestHelper->loadRequest(requestID,
                                                               mTestManager->
                                                               getDB(), nullptr);
    if (action == ReviewRequestOpAction::REJECT)
    {
        REQUIRE(!!requestAfterTx);
        REQUIRE(requestAfterTx->getRejectReason() == rejectReason);
        reviewChecker.checkReject(requestBeforeTx, requestAfterTx);
        return reviewResult;
    }

    if (action == ReviewRequestOpAction::PERMANENT_REJECT)
    {
        REQUIRE(!requestAfterTx);
        reviewChecker.checkPermanentReject(requestBeforeTx);
        return reviewResult;
    }

    if (requestMustBeDeletedAfterApproval)
    {
        if (requestBeforeTx->getRequestType() != ReviewableRequestType::ISSUANCE_CREATE
        && requestBeforeTx->getRequestType() != ReviewableRequestType::WITHDRAW)
        {
            REQUIRE(!requestAfterTx);
        }
    }
    else
    {
        REQUIRE(!!requestAfterTx);
    }

    reviewChecker.checkApprove(requestBeforeTx);
    return reviewResult;
}

ReviewRequestResult ReviewRequestHelper::applyReviewRequestTx(Account& source,
    uint64_t requestID, ReviewRequestOpAction action, std::string rejectReason,
    ReviewRequestResultCode expectedResult)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, mTestManager->getDB());
    REQUIRE(!!request);
    return applyReviewRequestTx(source, requestID, request->getHash(), request->getRequestType(), action, rejectReason, expectedResult);
}

ReviewRequestResult ReviewRequestHelper::applyReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
                                                                       ReviewRequestOpAction action,
                                                                       std::string rejectReason,
                                                                       ReviewRequestResultCode expectedResult,
                                                                       uint32_t *tasksToAdd, uint32_t *tasksToRemove) {

    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, mTestManager->getDB());
    REQUIRE(!!request);
    return applyReviewRequestTxWithTasks(source, requestID, request->getHash(), request->getRequestType(), action, rejectReason, expectedResult, tasksToAdd, tasksToRemove);
}

ReviewRequestResult ReviewRequestHelper::applyReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
                                                                       Hash requestHash,
                                                                       ReviewableRequestType requestType,
                                                                       ReviewRequestOpAction action,
                                                                       std::string rejectReason,
                                                                       ReviewRequestResultCode expectedResult,
                                                                       uint32_t *tasksToAdd, uint32_t *tasksToRemove) {
    return ReviewRequestResult(ReviewRequestResultCode::SUCCESS);
}
TransactionFramePtr ReviewRequestHelper::createReviewRequestTx(
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
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, op, nullptr);
}

TransactionFramePtr ReviewRequestHelper::createReviewRequestTxWithTasks(txtest::Account &source, uint64_t requestID,
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
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);
    if (tasksToAdd != nullptr){
        reviewRequestOp.reviewDetails.tasksToAdd = *tasksToAdd;
    }

    if (tasksToRemove != nullptr){
        reviewRequestOp.reviewDetails.tasksToRemove = *tasksToRemove;
    }
    return txFromOperation(source, op, nullptr);
}
}
}
