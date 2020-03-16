#include "RemoveDataTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar 
{
namespace txtest 
{
RemoveDataTestHelper::RemoveDataTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
RemoveDataTestHelper::removeDataTx(Account& source, uint64_t id) 
{
    Operation baseOp;
    baseOp.body.type(OperationType::REMOVE_DATA);
    auto& op = baseOp.body.removeDataOp();
    op.dataID = id;
    
    return txFromOperation(source, baseOp, nullptr);
}

RemoveDataResult
RemoveDataTestHelper::applyRemoveData(Account& source, uint64_t id,
                                      RemoveDataResultCode expectedResultCode,
                                      OperationResultCode operationResultCode) 
{
    auto txFrame = removeDataTx(source, id);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(operationResultCode == opResult.code());

    if (operationResultCode != OperationResultCode::opINNER) 
    {
        return RemoveDataResult{};
    }

    auto result = opResult.tr().removeDataResult();

    REQUIRE(expectedResultCode == result.code());

    return result;
}
}
}