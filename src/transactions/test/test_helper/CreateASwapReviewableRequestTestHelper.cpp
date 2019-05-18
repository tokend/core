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

CreateAtomicSwapAskRequestOp
CreateASwapReviewableRequestTestHelper::createASwapRequestOp(uint64_t bidID,
                                                             AssetCode asset,
                                                             uint64_t amount)
{
    CreateAtomicSwapAskRequestOp result;
    result.request.baseAmount = amount;
    result.request.quoteAsset = asset;
    result.request.bidID = bidID;
    result.request.ext.v(LedgerVersion::EMPTY_VERSION);
    result.ext.v(LedgerVersion::EMPTY_VERSION);

    return result;
}

TransactionFramePtr
CreateASwapReviewableRequestTestHelper::createASwapRequestTx(
        txtest::Account &source, CreateAtomicSwapAskRequestOp &createASwapRequestOp)
{
    Operation op;
    op.body.type(OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST);
    op.body.createAtomicSwapAskRequestOp() = createASwapRequestOp;

    return txFromOperation(source, op, nullptr);
}

CreateAtomicSwapAskRequestResult
CreateASwapReviewableRequestTestHelper::applyCreateASwapRequest(
        txtest::Account &source, CreateAtomicSwapAskRequestOp &createASwapRequestOp,
        CreateAtomicSwapAskRequestResultCode expectedResult, OperationResultCode expectedOpRes)
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
        return CreateAtomicSwapAskRequestResult();
    }

    auto actualResult = CreateASwapRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResult == expectedResult);

    uint64 reviewableRequestCountAfterTx =
            reviewableRequestHelper->countObjects(db.getSession());
    if (expectedResult != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateAtomicSwapAskRequestResult{};
    }

    auto createASwapRequestResult = opResult.tr().createAtomicSwapAskRequestResult();

    auto requestAfterTx = reviewableRequestHelper->loadRequest(
            createASwapRequestResult.success().requestID, db);
    REQUIRE(requestAfterTx != nullptr);

    auto createASwapRequest = requestAfterTx->getRequestEntry().body.createAtomicSwapAskRequest();
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