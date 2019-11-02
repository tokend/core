// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/AssetPairHelper.h>
#include "ReviewSaleRequestHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelperLegacy.h"
#include "test/test_marshaler.h"
#include "transactions/review_request/ReviewSaleCreationRequestOpFrame.h"


namespace stellar
{
namespace txtest
{
SaleReviewChecker::SaleReviewChecker(const TestManager::pointer testManager,
                                     const uint64_t requestID) : ReviewChecker(testManager)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();

    auto request = ReviewableRequestHelperLegacy::Instance()->loadRequest(requestID, mTestManager->getDB());
    if (!request || request->getType() != ReviewableRequestType::CREATE_SALE)
    {
        return;
    }

    saleCreationRequest = std::make_shared<SaleCreationRequest>(request->getRequestEntry().body.saleCreationRequest());
    baseAssetBeforeTx = assetHelper.loadAsset(saleCreationRequest->baseAsset);
}

void SaleReviewChecker::checkApprove(ReviewableRequestFrame::pointer)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();

    REQUIRE(!!saleCreationRequest);
    REQUIRE(!!baseAssetBeforeTx);
    auto baseAssetAfterTx = assetHelper.loadAsset(saleCreationRequest->baseAsset);
    REQUIRE(!!baseAssetAfterTx);
    auto saleCreationRequestTemp = *saleCreationRequest;
    uint64_t hardCapInBaseAsset = ReviewSaleCreationRequestOpFrame::getRequiredBaseAssetForHardCap(saleCreationRequestTemp);
    const auto saleRequest = *saleCreationRequest;
    REQUIRE(baseAssetBeforeTx->getPendingIssuance() + hardCapInBaseAsset == baseAssetAfterTx->getPendingIssuance());

    // check if asset pair was created
    for (auto saleQuoteAsset : saleRequest.quoteAssets)
    {
        auto assetPair = AssetPairHelper::Instance()->loadAssetPair(saleRequest.baseAsset, saleQuoteAsset.quoteAsset,
            mTestManager->getDB());
        REQUIRE(!!assetPair);
        REQUIRE(assetPair->getCurrentPrice() == saleQuoteAsset.price);
    }
}

ReviewSaleRequestHelper::ReviewSaleRequestHelper(
    TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult ReviewSaleRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker = SaleReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
        requestHash, requestType,
        action, rejectReason,
        expectedResult,
        checker
    );


}

    ReviewRequestResult
    ReviewSaleRequestHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                           ReviewableRequestType requestType,
                                                           ReviewRequestOpAction action, std::string rejectReason,
                                                           ReviewRequestResultCode expectedResult, uint32_t *tasksToAdd,
                                                           uint32_t *tasksToRemove) {
        auto checker = SaleReviewChecker(mTestManager, requestID);
        return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                                  requestHash, requestType,
                                                                  action, rejectReason,
                                                                  expectedResult,
                                                                  checker,
                                                                  tasksToAdd,
                                                                  tasksToRemove
        );
    }

    ReviewRequestResult ReviewSaleRequestHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
                                                                               ReviewRequestOpAction action,
                                                                               std::string rejectReason,
                                                                               ReviewRequestResultCode expectedResult,
                                                                               uint32_t *tasksToAdd,
                                                                               uint32_t *tasksToRemove) {
        return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID, action, rejectReason,
                                                                  expectedResult, tasksToAdd, tasksToRemove);
    }
}
}
