// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/sale/CancelSaleCreationRequestOpFrame.h>
#include "SaleRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/SaleHelper.h"
#include "ReviewSaleRequestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
SaleRequestHelper::SaleRequestHelper(const TestManager::pointer testManager) : TxHelper(testManager)
{
}

ReviewRequestResult SaleRequestHelper::createApprovedSale(Account& root, Account& source,
                                           const SaleCreationRequest request)
{
    auto requestCreationResult = applyCreateSaleRequest(source, 0, request);
    if (requestCreationResult.code() == CreateSaleCreationRequestResultCode::SUCCESS
        && requestCreationResult.success().fulfilled)
    {
        auto result = ReviewRequestResult{};
        result.code(ReviewRequestResultCode::SUCCESS);
        result.success().fulfilled = true;
        result.success().typeExt.requestType(ReviewableRequestType::SALE);
        result.success().typeExt.saleExtended().saleID = requestCreationResult.success().saleID;
        return result;
    }

    auto reviewer = ReviewSaleRequestHelper(mTestManager);
    return reviewer.applyReviewRequestTx(root, requestCreationResult.success().requestID, ReviewRequestOpAction::APPROVE, "");

}

SaleCreationRequestQuoteAsset SaleRequestHelper::createSaleQuoteAsset(AssetCode asset,
                                                                      const uint64_t price)
{
    SaleCreationRequestQuoteAsset result;
    result.quoteAsset = asset;
    result.price = price;
    return result;
}

CreateSaleCreationRequestResult
SaleRequestHelper::applyCreateSaleRequest(Account &source, const uint64_t requestID, const SaleCreationRequest request,
                                          uint32_t *allTasks, CreateSaleCreationRequestResultCode expectedResult)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->countObjects(mTestManager->getDB().getSession());


    auto txFrame = createSaleRequestTx(source, requestID, request, allTasks);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = CreateSaleCreationRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper->countObjects(mTestManager->getDB().getSession());
    if (expectedResult != CreateSaleCreationRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateSaleCreationRequestResult{};
    }

    return opResult.tr().createSaleCreationRequestResult();
}

CancelSaleCreationRequestResult
SaleRequestHelper::applyCancelSaleRequest(Account &source, uint64_t requestID,
        CancelSaleCreationRequestResultCode expectedResult)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());


    auto txFrame = cancelSaleRequestTx(source, requestID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode =
            CancelSaleCreationRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper->
            countObjects(mTestManager->getDB().getSession());
    if (expectedResult != CancelSaleCreationRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CancelSaleCreationRequestResult{};
    }

    REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx + 1);

    return opResult.tr().cancelSaleCreationRequestResult();
}

SaleCreationRequest
SaleRequestHelper::createSaleRequest(AssetCode base, AssetCode defaultQuoteAsset, const uint64_t startTime, const uint64_t endTime,
                                     const uint64_t softCap, const uint64_t hardCap, std::string details,
                                     std::vector<SaleCreationRequestQuoteAsset> quoteAssets, uint64_t requiredBaseAssetForHardCap,
                                     SaleType saleType, uint64_t saleTypeInt)
{
    SaleCreationRequest request;
    request.baseAsset = base;
    request.saleType = saleTypeInt;
    request.defaultQuoteAsset = defaultQuoteAsset;
    request.startTime = startTime;
    request.endTime = endTime;
    request.quoteAssets.clear();
    request.quoteAssets.append(&quoteAssets[0], quoteAssets.size());
    request.softCap = softCap;
    request.hardCap = hardCap;
    request.details = details;

    request.saleTypeExt.saleType(saleType);
    request.requiredBaseAssetForHardCap = requiredBaseAssetForHardCap;
    return request;
}

TransactionFramePtr SaleRequestHelper::createSaleRequestTx(Account& source, const uint64_t requestID,
                                                           const SaleCreationRequest request,
                                                           uint32_t* allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_SALE_REQUEST);
    auto& op = baseOp.body.createSaleCreationRequestOp();
    op.request = request;
    if (allTasks)
        op.allTasks.activate() = *allTasks;
    op.requestID = requestID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

TransactionFramePtr SaleRequestHelper::cancelSaleRequestTx(Account &source,
                                                           uint64_t requestID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_SALE_REQUEST);
    auto& op = baseOp.body.cancelSaleCreationRequestOp();
    op.requestID = requestID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
