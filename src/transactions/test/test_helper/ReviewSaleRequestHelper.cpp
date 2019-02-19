// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/AssetPairHelper.h>
#include "ReviewSaleRequestHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/SaleFrame.h"
#include "test/test_marshaler.h"
#include "transactions/review_request/ReviewSaleCreationRequestOpFrame.h"


namespace stellar
{
namespace txtest
{
SaleReviewChecker::SaleReviewChecker(const TestManager::pointer testManager,
                                     const uint64_t requestID) : ReviewChecker(testManager)
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(requestID, mTestManager->getDB());
    if (!request || request->getType() != ReviewableRequestType::CREATE_SALE)
    {
        return;
    }

    saleCreationRequest = std::make_shared<SaleCreationRequest>(request->getRequestEntry().body.saleCreationRequest());
    baseAssetBeforeTx = AssetHelperLegacy::Instance()->loadAsset(saleCreationRequest->baseAsset, mTestManager->getDB());
}

void SaleReviewChecker::checkApprove(ReviewableRequestFrame::pointer)
{
    REQUIRE(!!saleCreationRequest);
    REQUIRE(!!baseAssetBeforeTx);
    auto baseAssetAfterTx = AssetHelperLegacy::Instance()->loadAsset(saleCreationRequest->baseAsset, mTestManager->getDB());
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
