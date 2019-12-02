// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/review_request/ReviewRequestOpFrame.h>
#include <ledger/FeeHelper.h>
#include "ledger/AccountHelper.h"
#include "ReviewIssuanceRequestHelper.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceFrame.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "test/test_marshaler.h"


namespace stellar
{

namespace txtest
{

ReviewIssuanceChecker::ReviewIssuanceChecker(
    const TestManager::pointer& testManager, const uint64_t requestID) : ReviewChecker(testManager)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto& reviewableRequestHelper = mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto request = reviewableRequestHelper.loadRequest(requestID);
    if (!request || request->getType() != ReviewableRequestType::CREATE_ISSUANCE)
    {
        return;
    }
    issuanceRequest = std::make_shared<IssuanceRequest>(request->getRequestEntry().body.issuanceRequest());
    assetFrameBeforeTx = assetHelper.loadActiveAsset(issuanceRequest->asset);
    balanceBeforeTx = balanceHelper.loadBalance(issuanceRequest->receiver);
    commissionBalanceBeforeTx = balanceHelper.loadBalance(testManager->getApp().getAdminID(),
                                                          issuanceRequest->asset);
}

ReviewIssuanceChecker::ReviewIssuanceChecker(
    const TestManager::pointer& testManager,
    std::shared_ptr<IssuanceRequest> request) : ReviewChecker(testManager)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();

    issuanceRequest = request;
    assetFrameBeforeTx = assetHelper.loadActiveAsset(issuanceRequest->asset);
    balanceBeforeTx = balanceHelper.loadBalance(issuanceRequest->receiver);
    commissionBalanceBeforeTx = balanceHelper.loadBalance(testManager->getApp().getAdminID(),
                                                          issuanceRequest->asset);
}

void ReviewIssuanceChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& accountHelper = storageHelper.getAccountHelper();

    // checkApprove can be called during auto approve, so the request can be nullptr
    if (request != nullptr)
    {
        auto& requestEntry = request->getRequestEntry();
        // if a request has pending tasks - no need to check approval effects
        if (requestEntry.tasks.pendingTasks != 0)
        {
            return;
        }
    }

    // check asset
    REQUIRE(!!issuanceRequest);
    REQUIRE(!!assetFrameBeforeTx);
    auto assetFrameAfterTx =
        assetHelper.loadActiveAsset(issuanceRequest->asset);
    REQUIRE(!!assetFrameAfterTx);
    REQUIRE(assetFrameAfterTx->getAvailableForIssuance()
            == assetFrameBeforeTx->getAvailableForIssuance() - issuanceRequest->amount);
    REQUIRE(assetFrameAfterTx->getIssued() == assetFrameBeforeTx->getIssued() + issuanceRequest->amount);
    REQUIRE(!!balanceBeforeTx);
    auto receiverFrame = accountHelper.loadAccount(balanceBeforeTx->getAccountID());
    auto feeFrame = mTestManager->getStorageHelper().getFeeHelper().loadForAccount(FeeType::ISSUANCE_FEE, issuanceRequest->asset,
                                                          FeeFrame::SUBTYPE_ANY, receiverFrame, issuanceRequest->amount);
    uint64_t totalFee = 0;
    if (feeFrame)
    {
        REQUIRE(feeFrame->calculatePercentFee(issuanceRequest->amount, totalFee, ROUND_UP,
                                              assetFrameAfterTx->getMinimumAmount()));
        totalFee += feeFrame->getFee().fixedFee;
        REQUIRE(!!commissionBalanceBeforeTx);
        auto commissionBalanceAfterTx = balanceHelper.loadBalance(mTestManager->getApp().getAdminID(),
                                                                  issuanceRequest->asset);
        REQUIRE(!!commissionBalanceAfterTx);
        //check commission balance change
        REQUIRE(commissionBalanceAfterTx->getAmount() == commissionBalanceBeforeTx->getAmount() + totalFee);
    }

    // check balance
    auto balanceAfterTx = balanceHelper.loadBalance(issuanceRequest->receiver);
    REQUIRE(!!balanceAfterTx);
    uint64_t destinationReceive = issuanceRequest->amount - totalFee;
    REQUIRE(balanceAfterTx->getAmount() == balanceBeforeTx->getAmount() + destinationReceive);
}

ReviewIssuanceRequestHelper::ReviewIssuanceRequestHelper(TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewIssuanceRequestHelper::applyReviewRequestTx(Account& source, uint64_t requestID, Hash requestHash,
                                                  ReviewableRequestType requestType, ReviewRequestOpAction action, std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto issuanceChecker = ReviewIssuanceChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID, requestHash, requestType, action, rejectReason, expectedResult,
                                                     issuanceChecker);
}

TransactionFramePtr
ReviewIssuanceRequestHelper::createReviewRequestTx(Account& source, uint64_t requestID, Hash requestHash,
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
    reviewRequestOp.reviewDetails.tasksToRemove = 0;
    reviewRequestOp.reviewDetails.externalDetails = "{}";
    reviewRequestOp.ext.v(LedgerVersion::EMPTY_VERSION);

    return txFromOperation(source, op, nullptr);
}

ReviewRequestResult
ReviewIssuanceRequestHelper::applyReviewRequestTx(Account& source, uint64_t requestID, ReviewRequestOpAction action, std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto& reviewableRequestHelper = mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto request = reviewableRequestHelper.loadRequest(requestID);
    REQUIRE(request);
    return applyReviewRequestTx(source, requestID, request->getHash(), request->getRequestType(), action, rejectReason, expectedResult);
}

ReviewRequestResult
ReviewIssuanceRequestHelper::applyReviewRequestTxWithTasks(Account& source, uint64_t requestID, Hash requestHash,
                                                           ReviewableRequestType requestType,
                                                           ReviewRequestOpAction action, std::string rejectReason,
                                                           ReviewRequestResultCode expectedResult,
                                                           uint32_t *tasksToAdd, uint32_t *tasksToRemove)
{
    auto checker = ReviewIssuanceChecker(mTestManager, requestID);
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
