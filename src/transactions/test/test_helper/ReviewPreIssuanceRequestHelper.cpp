// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewPreIssuanceRequestHelper.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelperLegacy.h"
#include "test/test_marshaler.h"



namespace stellar
{

namespace txtest
{
ReviewPreIssuanceChecker::ReviewPreIssuanceChecker(
    const TestManager::pointer& testManager, const uint64_t requestID) : ReviewChecker(testManager)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();

    auto reviewableRequestHelper = ReviewableRequestHelperLegacy::Instance();
    auto request = reviewableRequestHelper->loadRequest(requestID, mTestManager->getDB());
    if (!request || request->getType() != ReviewableRequestType::CREATE_PRE_ISSUANCE) {
        return;
    }
    preIssuanceRequest = std::make_shared<PreIssuanceRequest>(request->getRequestEntry().body.preIssuanceRequest());
    assetFrameBeforeTx = assetHelper.loadAsset(preIssuanceRequest->asset);
}

void ReviewPreIssuanceChecker::checkApprove(ReviewableRequestFrame::pointer requestBeforeTx)
{
    REQUIRE(!!assetFrameBeforeTx);
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();
    auto assetFrameAfterTx = assetHelper.loadAsset(preIssuanceRequest->asset);
    REQUIRE(assetFrameAfterTx->getAvailableForIssuance() == assetFrameBeforeTx->getAvailableForIssuance() + preIssuanceRequest->amount);
}

ReviewPreIssuanceChecker::ReviewPreIssuanceChecker(const TestManager::pointer &testManager,
                                                   std::shared_ptr<PreIssuanceRequest> request) : ReviewChecker(testManager)
{
    preIssuanceRequest = request;
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();
    assetFrameBeforeTx = assetHelper.loadAsset(preIssuanceRequest->asset);
}

ReviewPreIssuanceRequestHelper::ReviewPreIssuanceRequestHelper(TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult ReviewPreIssuanceRequestHelper::applyReviewRequestTx(Account & source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action, std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto reviewPreIssuanceChecker = ReviewPreIssuanceChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash, requestType, action, rejectReason, expectedResult,
                reviewPreIssuanceChecker);
}

ReviewRequestResult ReviewPreIssuanceRequestHelper::applyReviewRequestTx(Account & source, uint64_t requestID,
                                                                         ReviewRequestOpAction action, std::string rejectReason,
                                                                         ReviewRequestResultCode expectedResult)
{
    auto reviewableRequestHelper = ReviewableRequestHelperLegacy::Instance();
    auto request = reviewableRequestHelper->loadRequest(requestID, mTestManager->getDB());
    REQUIRE(request);
    return applyReviewRequestTx(source, requestID, request->getHash(), request->getRequestType(), action, rejectReason, expectedResult);
}

ReviewRequestResult
ReviewPreIssuanceRequestHelper::applyReviewRequestTxWithTasks(Account & source, uint64_t requestID,
                                                              ReviewRequestOpAction action,
                                                              std::string rejectReason,
                                                              uint32_t tasksToRemove,
                                                              ReviewRequestResultCode expectedResult)
{
    mTasksToRemove = tasksToRemove;
    return applyReviewRequestTx(source, requestID, action, rejectReason, expectedResult);
}

TransactionFramePtr
ReviewPreIssuanceRequestHelper::createReviewRequestTx(Account &source, uint64_t requestID, Hash requestHash,
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
    reviewRequestOp.reviewDetails.tasksToAdd = 0;
    reviewRequestOp.reviewDetails.tasksToRemove = mTasksToRemove;
    reviewRequestOp.reviewDetails.externalDetails = "{}";
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);

    return txFromOperation(source, op, nullptr);
}

}

}
