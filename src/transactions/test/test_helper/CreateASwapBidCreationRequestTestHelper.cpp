#include <ledger/ReviewableRequestHelper.h>
#include <transactions/atomic_swap/CreateASwapBidCreationRequestOpFrame.h>
#include <ledger/BalanceHelperLegacy.h>
#include "CreateASwapBidCreationRequestTestHelper.h"
#include "test/test_marshaler.h"

using namespace std;

namespace stellar
{

namespace txtest
{

CreateASwapBidCreationRequestHelper::CreateASwapBidCreationRequestHelper(
        TestManager::pointer testManager) : TxHelper(testManager)
{
}

CreateAtomicSwapBidRequest
CreateASwapBidCreationRequestHelper::createASwapBidCreationRequest(
        BalanceID baseBalance, uint64_t amount, std::string creatorDetails,
        std::vector<AtomicSwapBidQuoteAsset> quoteAssets)
{
    CreateAtomicSwapBidRequest request;
    request.baseBalance = baseBalance;
    request.amount = amount;
    request.creatorDetails = creatorDetails;
    request.quoteAssets.clear();
    request.quoteAssets.append(&quoteAssets[0], quoteAssets.size());

    return request;
}

TransactionFramePtr
CreateASwapBidCreationRequestHelper::createCreateASwapBidCreationRequestTx(
        Account &source, CreateAtomicSwapBidRequest request)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_ATOMIC_SWAP_BID_REQUEST);
    auto& op = baseOp.body.createAtomicSwapBidRequestOp();
    op.request = request;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

CreateAtomicSwapBidRequestResult
CreateASwapBidCreationRequestHelper::applyCreateASwapBidCreationRequest(
        Account &source, CreateAtomicSwapBidRequest request,
        CreateAtomicSwapBidRequestResultCode expectedResult,
        OperationResultCode expectedOpResCode)
{
    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();

    Database& db = mTestManager->getDB();

    auto reviewableRequestCountBeforeTx =
            reviewableRequestHelper->countObjects(db.getSession());

    auto baseBalanceBeforeTx = balanceHelper->loadBalance(request.baseBalance, db);

    auto txFrame = createCreateASwapBidCreationRequestTx(source, request);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(expectedOpResCode == opResult.code());

    if (expectedOpResCode != OperationResultCode::opINNER)
    {
        return CreateAtomicSwapBidRequestResult();
    }

    auto actualResultCode = CreateASwapBidCreationRequestOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    auto createBidCreationRequestResult =
            opResult.tr().createAtomicSwapBidRequestResult();

    auto reviewableRequestCountAfterTx =
            reviewableRequestHelper->countObjects(db.getSession());

    if (expectedResult != CreateAtomicSwapBidRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return createBidCreationRequestResult;
    }

    auto baseBalanceAfterTx = balanceHelper->loadBalance(request.baseBalance, db);

    if (baseBalanceBeforeTx != nullptr)
    {
        REQUIRE(baseBalanceBeforeTx->getAmount() - request.amount ==
                baseBalanceAfterTx->getAmount());
        REQUIRE(baseBalanceAfterTx->getLocked() - request.amount ==
                baseBalanceBeforeTx->getLocked());
    }

    return createBidCreationRequestResult;
}

}

}