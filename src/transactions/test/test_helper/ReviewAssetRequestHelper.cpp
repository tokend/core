// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewAssetRequestHelper.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"


namespace stellar
{
namespace txtest
{
void AssetReviewChecker::checkApproval(AssetCreationRequest const& request,
    AccountID const& requestor) const
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();
    auto assetFrame = assetHelper.loadAsset(request.code);
    REQUIRE(!!assetFrame);
    auto assetEntry = assetFrame->getAsset();
    REQUIRE(assetEntry.availableForIssueance == request.initialPreissuedAmount);
    REQUIRE(assetEntry.code == request.code);
    REQUIRE(assetEntry.details == request.creatorDetails);
    REQUIRE(assetEntry.issued == 0);
    REQUIRE(assetEntry.maxIssuanceAmount == request.maxIssuanceAmount);
    REQUIRE(assetEntry.owner == requestor);
    REQUIRE(assetEntry.policies == request.policies);
    REQUIRE(assetEntry.maxIssuanceAmount == request.maxIssuanceAmount);
}

void AssetReviewChecker::checkApproval(AssetUpdateRequest const& request,
    AccountID const& requestor)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();
    auto assetFrame = assetHelper.loadAsset(request.code);
    REQUIRE(!!assetFrame);
    auto assetEntry = assetFrame->getAsset();
    REQUIRE(assetEntry.code == request.code);
    REQUIRE(assetEntry.details == request.creatorDetails);
    REQUIRE(assetEntry.owner == requestor);
    REQUIRE(assetEntry.policies == request.policies);
}

void AssetReviewChecker::checkApprove(ReviewableRequestFrame::pointer requestBeforeTx)
{
    switch (requestBeforeTx->getRequestEntry().body.type())
    {
    case ReviewableRequestType::CREATE_ASSET:
        checkApproval(requestBeforeTx->getRequestEntry().body.
            assetCreationRequest(),
            requestBeforeTx->getRequestor());
        break;
    case ReviewableRequestType::UPDATE_ASSET:
        checkApproval(requestBeforeTx->getRequestEntry().body.
            assetUpdateRequest(),
            requestBeforeTx->getRequestor());
        break;
    default:
        throw std::runtime_error("Unexecpted request type");
    }
}

ReviewRequestResult ReviewAssetRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType,
    ReviewRequestOpAction action, std::string rejectReason,
    ReviewRequestResultCode expectedResult)
{
    auto assetReviewChecker = AssetReviewChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     assetReviewChecker);
}

    ReviewRequestResult
    ReviewAssetRequestHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                            ReviewableRequestType requestType,
                                                            ReviewRequestOpAction action, std::string rejectReason,
                                                            ReviewRequestResultCode expectedResult,
                                                            uint32_t *tasksToAdd, uint32_t *tasksToRemove) {
        auto assetReviewChecker = AssetReviewChecker(mTestManager);
        return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID, requestHash, requestType, action, rejectReason,
                                                                  expectedResult, assetReviewChecker, tasksToAdd, tasksToRemove);
    }

    ReviewAssetRequestHelper::ReviewAssetRequestHelper(
    TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}
}
}
