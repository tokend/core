#include "CreateAtomicSwapReviewableRequestTestHelper.h"

#include <ledger/ReviewableRequestHelper.h>
#include <transactions/ManageInvoiceRequestOpFrame.h>
#include <lib/catch.hpp>


namespace stellar
{
namespace txtest
{

CreateAtomicSwapReviewableRequestTestHelper::
CreateAtomicSwapReviewableRequestTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

CreateASwapRequestOp
CreateAtomicSwapReviewableRequestTestHelper::createASwapRequestOp(
        uint64_t bidID, AssetCode asset, uint64_t amount, uint64_t fee)
{
    CreateASwapRequestOp result;
    result.request.baseAmount = amount;
    result.request.quoteAsset = asset;
    result.request.bidID = bidID;
    result.request.fee = fee;
    result.request.ext.v(LedgerVersion::EMPTY_VERSION);
    result.ext.v(LedgerVersion::EMPTY_VERSION);

    return result;
}

TransactionFramePtr
CreateAtomicSwapReviewableRequestTestHelper::createASwapRequestTx(
        txtest::Account &source, CreateASwapRequestOp &createASwapRequestOp)
{
    Operation op;
    op.body.type(OperationType::CREATE_A_SWAP_REQUEST);
    op.body.createASwapRequestOp() = createASwapRequestOp;

    return txFromOperation(source, op, nullptr);
}

CreateASwapRequestResult
CreateAtomicSwapReviewableRequestTestHelper::applyCreateASwapRequest(
        txtest::Account &source, CreateASwapRequestOp &createASwapRequestOp,
        CreateASwapRequestResultCode expectedResult)
{
    Database& db = mTestManager->getDB();

    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    uint64 reviewableRequestCountBeforeTx =
            reviewableRequestHelper->countObjects(db.getSession());

    auto txFrame = createASwapRequestTx(source, createASwapRequestOp);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    auto actualResult = ManageInvoiceRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResult == expectedResult);

    uint64 reviewableRequestCountAfterTx =
            reviewableRequestHelper->countObjects(db.getSession());
    if (expectedResult != ManageInvoiceRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateASwapRequestResult{};
    }

    auto createASwapRequestResult = opResult.tr().createASwapRequestResult();

    auto aSwapRequest = reviewableRequestHelper->loadRequest(
            createASwapRequestResult.success().requestID, db);
    REQUIRE(!!aSwapRequest);
    REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);


    return createASwapRequestResult;
}

}
}