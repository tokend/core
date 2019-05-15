#include "CreateASwapReviewableRequestTestHelper.h"
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/atomic_swap/CreateASwapRequestOpFrame.h>
#include <lib/catch.hpp>
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/BalanceHelper.h>
#include "test/test_marshaler.h"


namespace stellar
{
namespace txtest
{

CreateASwapReviewableRequestTestHelper::
CreateASwapReviewableRequestTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

CreateAtomicSwapRequestOp
CreateASwapReviewableRequestTestHelper::createASwapRequestOp(uint64_t bidID,
                                                             AssetCode asset,
                                                             uint64_t amount)
{
    CreateAtomicSwapRequestOp result;
    result.request.baseAmount = amount;
    result.request.quoteAsset = asset;
    result.request.bidID = bidID;
    result.request.ext.v(LedgerVersion::EMPTY_VERSION);
    result.ext.v(LedgerVersion::EMPTY_VERSION);

    return result;
}

TransactionFramePtr
CreateASwapReviewableRequestTestHelper::createASwapRequestTx(
        txtest::Account &source, CreateAtomicSwapRequestOp &createASwapRequestOp)
{
    Operation op;
    op.body.type(OperationType::CREATE_ATOMIC_SWAP_REQUEST);
    op.body.createAtomicSwapRequestOp() = createASwapRequestOp;

    return txFromOperation(source, op, nullptr);
}

CreateAtomicSwapRequestResult
CreateASwapReviewableRequestTestHelper::applyCreateASwapRequest(
        txtest::Account &source, CreateAtomicSwapRequestOp &createASwapRequestOp,
        CreateAtomicSwapRequestResultCode expectedResult, OperationResultCode expectedOpRes)
{
    Database& db = mTestManager->getDB();

    auto aSwapBidHelper = AtomicSwapBidHelper::Instance();
    auto bidFrameBeforeTx = aSwapBidHelper->loadAtomicSwapBid(
            createASwapRequestOp.request.bidID, db);

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    uint64 reviewableRequestCountBeforeTx =
            reviewableRequestHelper->countObjects(db.getSession());

    auto txFrame = createASwapRequestTx(source, createASwapRequestOp);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(expectedOpRes == opResult.code());

    if (expectedOpRes != OperationResultCode::opINNER)
    {
        return CreateAtomicSwapRequestResult();
    }

    auto actualResult = CreateASwapRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResult == expectedResult);

    uint64 reviewableRequestCountAfterTx =
            reviewableRequestHelper->countObjects(db.getSession());
    if (expectedResult != CreateAtomicSwapRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateAtomicSwapRequestResult{};
    }

    auto createASwapRequestResult = opResult.tr().createAtomicSwapRequestResult();

    auto requestAfterTx = reviewableRequestHelper->loadRequest(
            createASwapRequestResult.success().requestID, db);
    REQUIRE(requestAfterTx != nullptr);

    auto createASwapRequest = requestAfterTx->getRequestEntry().body.atomicSwapRequest();
    REQUIRE(createASwapRequest == createASwapRequestOp.request);

    REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);

    auto bidFrameAfterTx = aSwapBidHelper->loadAtomicSwapBid(
            createASwapRequestOp.request.bidID, db);

    REQUIRE(bidFrameAfterTx->getLockedAmount() -
            createASwapRequestOp.request.baseAmount ==
            bidFrameBeforeTx->getLockedAmount());

    REQUIRE(bidFrameBeforeTx->getAmount() - createASwapRequestOp.request.baseAmount ==
            bidFrameAfterTx->getAmount());

    return createASwapRequestResult;
}

}
}