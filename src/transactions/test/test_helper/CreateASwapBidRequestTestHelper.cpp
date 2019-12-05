#include "CreateASwapBidRequestTestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include <transactions/atomic_swap/CreateAtomicSwapBidRequestOpFrame.h>
#include <lib/catch.hpp>
#include "ledger/AtomicSwapAskHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "test/test_marshaler.h"


namespace stellar
{
namespace txtest
{

CreateASwapBidRequestTestHelper::
CreateASwapBidRequestTestHelper(TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

CreateAtomicSwapBidRequestOp
CreateASwapBidRequestTestHelper::createASwapRequestOp(uint64_t askID,
                                                      AssetCode asset,
                                                      uint64_t amount)
{
    CreateAtomicSwapBidRequestOp result;
    result.request.baseAmount = amount;
    result.request.quoteAsset = asset;
    result.request.askID = askID;
    result.request.ext.v(LedgerVersion::EMPTY_VERSION);
    result.ext.v(LedgerVersion::EMPTY_VERSION);

    return result;
}

TransactionFramePtr
CreateASwapBidRequestTestHelper::createASwapRequestTx(
    txtest::Account& source, CreateAtomicSwapBidRequestOp& createASwapRequestOp)
{
    Operation op;
    op.body.type(OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST);
    op.body.createAtomicSwapBidRequestOp() = createASwapRequestOp;

    return txFromOperation(source, op, nullptr);
}

CreateAtomicSwapBidRequestResult
CreateASwapBidRequestTestHelper::applyCreateASwapRequest(
    txtest::Account& source, CreateAtomicSwapBidRequestOp& createASwapRequestOp,
    CreateAtomicSwapBidRequestResultCode expectedResult, OperationResultCode expectedOpRes)
{
    auto& aSwapBidHelper = mTestManager->getStorageHelper().getAtomicSwapAskHelper();
    auto bidFrameBeforeTx = aSwapBidHelper.loadAtomicSwapAsk(
        createASwapRequestOp.request.askID);

    auto& storageHelper = mTestManager->getStorageHelper();
    auto& reviewableRequestHelper = storageHelper.getReviewableRequestHelper();
    uint64 reviewableRequestCountBeforeTx =
        reviewableRequestHelper.countObjects();

    auto txFrame = createASwapRequestTx(source, createASwapRequestOp);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(expectedOpRes == opResult.code());

    if (expectedOpRes != OperationResultCode::opINNER)
    {
        return CreateAtomicSwapBidRequestResult();
    }

    auto actualResult = CreateAtomicSwapBidRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResult == expectedResult);

    uint64 reviewableRequestCountAfterTx =
        reviewableRequestHelper.countObjects();
    if (expectedResult != CreateAtomicSwapBidRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return CreateAtomicSwapBidRequestResult{};
    }

    auto createASwapRequestResult = opResult.tr().createAtomicSwapBidRequestResult();

    auto requestAfterTx = reviewableRequestHelper.loadRequest(createASwapRequestResult.success().requestID);
    REQUIRE(requestAfterTx != nullptr);

    auto createASwapRequest = requestAfterTx->getRequestEntry().body.createAtomicSwapBidRequest();
    REQUIRE(createASwapRequest == createASwapRequestOp.request);

    REQUIRE(reviewableRequestCountBeforeTx + 1 == reviewableRequestCountAfterTx);

    auto bidFrameAfterTx = aSwapBidHelper.loadAtomicSwapAsk(
        createASwapRequestOp.request.askID);

    REQUIRE(bidFrameAfterTx->getLockedAmount() -
            createASwapRequestOp.request.baseAmount ==
            bidFrameBeforeTx->getLockedAmount());

    REQUIRE(bidFrameBeforeTx->getAmount() - createASwapRequestOp.request.baseAmount ==
            bidFrameAfterTx->getAmount());

    return createASwapRequestResult;
}

}
}
