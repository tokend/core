// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

//#include <ledger/StatisticsHelper.h>
#include <ledger/AssetPairHelper.h>
#include <transactions/CreateManageLimitsRequestOpFrame.h>
#include "LimitsUpdateRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
//#include "ledger/AccountLimitsHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
LimitsUpdateRequestHelper::
LimitsUpdateRequestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

CreateManageLimitsRequestResult
LimitsUpdateRequestHelper::applyCreateLimitsUpdateRequest(Account& source, LimitsUpdateRequest request, uint32_t *allTasks, uint64_t *requestID,
                                                          CreateManageLimitsRequestResultCode expectedResult,
                                                          OperationResultCode expectedOpResultCode)
{
    Database& db = mTestManager->getDB();
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    uint64 reviewableRequestCountBeforeTx = requestHelper.countObjects();

    ReviewableRequestFrame::pointer limitsUpdateRequestBeforeTx;
    if (requestID != nullptr)
    {
        limitsUpdateRequestBeforeTx = requestHelper.loadRequest(*requestID, source.key.getPublicKey());
    }

    auto txFrame = createLimitsUpdateRequestTx(source, request, allTasks, requestID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpResultCode);
    if (opResult.code() != OperationResultCode::opINNER)
    {
        return CreateManageLimitsRequestResult();
    }

    auto actualResultCode = CreateManageLimitsRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    uint64 reviewableRequestCountAfterTx = requestHelper.countObjects();
    if (expectedResult != CreateManageLimitsRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateManageLimitsRequestResult{};
    }

    CreateManageLimitsRequestResult createManageLimitsRequestResult = opResult.tr().createManageLimitsRequestResult();
    auto limitsUpdateRequestAfterTx = requestHelper.loadRequest(
        createManageLimitsRequestResult.success().manageLimitsRequestID);
    REQUIRE(!!limitsUpdateRequestAfterTx);

    if (limitsUpdateRequestBeforeTx == nullptr)
    {
        REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);
        return createManageLimitsRequestResult;
    }

    REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
    REQUIRE(limitsUpdateRequestBeforeTx->getRequestID() == limitsUpdateRequestAfterTx->getRequestID());
    REQUIRE(limitsUpdateRequestBeforeTx->getRequestEntry().body.limitsUpdateRequest().creatorDetails !=
            limitsUpdateRequestAfterTx->getRequestEntry().body.limitsUpdateRequest().creatorDetails);

    return createManageLimitsRequestResult;
}

LimitsUpdateRequest
LimitsUpdateRequestHelper::createLimitsUpdateRequest(longstring creatorDetails)
{
    LimitsUpdateRequest result;
    result.creatorDetails = creatorDetails;
    return result;
}

TransactionFramePtr
LimitsUpdateRequestHelper::createLimitsUpdateRequestTx(Account& source, LimitsUpdateRequest request,
                                                       uint32_t *allTasks,
                                                       uint64_t *requestID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_MANAGE_LIMITS_REQUEST);
    auto& op = baseOp.body.createManageLimitsRequestOp();
    op.manageLimitsRequest.creatorDetails = request.creatorDetails;

    if (allTasks)
    {
        op.allTasks.activate() = *allTasks;
    }

    if (requestID == nullptr)
    {
        op.ext.v(LedgerVersion::EMPTY_VERSION);
        return txFromOperation(source, baseOp, nullptr);
    }

    op.requestID = *requestID;

    return txFromOperation(source, baseOp, nullptr);
}

}
}
