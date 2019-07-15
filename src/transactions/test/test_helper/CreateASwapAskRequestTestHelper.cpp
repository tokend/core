#include <transactions/atomic_swap/CreateAtomicSwapAskRequestOpFrame.h>
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "CreateASwapAskRequestTestHelper.h"
#include "test/test_marshaler.h"

using namespace std;

namespace stellar
{

namespace txtest
{

CreateASwapAskRequestHelper::CreateASwapAskRequestHelper(
    TestManager::pointer testManager) : TxHelper(testManager)
{
}

CreateAtomicSwapAskRequest
CreateASwapAskRequestHelper::createASwapAskCreationRequest(
    BalanceID baseBalance, uint64_t amount, std::string details,
    std::vector<AtomicSwapAskQuoteAsset> quoteAssets)
{
    CreateAtomicSwapAskRequest request;
    request.baseBalance = baseBalance;
    request.amount = amount;
    request.creatorDetails = details;
    request.quoteAssets.clear();
    request.quoteAssets.append(&quoteAssets[0], quoteAssets.size());

    return request;
}

TransactionFramePtr
CreateASwapAskRequestHelper::createCreateASwapAskCreationRequestTx(
    Account& source, CreateAtomicSwapAskRequest request)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_ATOMIC_SWAP_ASK_REQUEST);
    auto& op = baseOp.body.createAtomicSwapAskRequestOp();
    op.request = request;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}

CreateAtomicSwapAskRequestResult
CreateASwapAskRequestHelper::applyCreateASwapAskCreationRequest(
    Account& source, CreateAtomicSwapAskRequest request,
    CreateAtomicSwapAskRequestResultCode expectedResult,
    OperationResultCode expectedOpResCode)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& reviewableRequestHelper = storageHelper.getReviewableRequestHelper();

    Database& db = mTestManager->getDB();

    auto reviewableRequestCountBeforeTx =
        reviewableRequestHelper.countObjects();

    auto baseBalanceBeforeTx = balanceHelper.loadBalance(request.baseBalance);

    auto txFrame = createCreateASwapAskCreationRequestTx(source, request);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(expectedOpResCode == opResult.code());

    if (expectedOpResCode != OperationResultCode::opINNER)
    {
        return CreateAtomicSwapAskRequestResult();
    }

    auto actualResultCode = CreateAtomicSwapAskRequestOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResult);

    auto createAskCreationRequestResult =
        opResult.tr().createAtomicSwapAskRequestResult();

    auto reviewableRequestCountAfterTx =
        reviewableRequestHelper.countObjects();

    if (expectedResult != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx == reviewableRequestCountAfterTx);
        return createAskCreationRequestResult;
    }

    auto baseBalanceAfterTx = balanceHelper.loadBalance(request.baseBalance);

    if (baseBalanceBeforeTx != nullptr)
    {
        REQUIRE(baseBalanceBeforeTx->getAmount() - request.amount ==
                baseBalanceAfterTx->getAmount());
        REQUIRE(baseBalanceAfterTx->getLocked() - request.amount ==
                baseBalanceBeforeTx->getLocked());
    }

    return createAskCreationRequestResult;
}

}

}
