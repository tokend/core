#include "UpdateDataTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar 
{
namespace txtest 
{
UpdateDataTestHelper::UpdateDataTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
UpdateDataTestHelper::updateDataTx(Account& source, uint64_t id, std::string value) 
{
    Operation baseOp;
    baseOp.body.type(OperationType::UPDATE_DATA);
    auto& op = baseOp.body.updateDataOp();
    op.dataID = id;
    op.value = value;
    
    return txFromOperation(source, baseOp, nullptr);
}

UpdateDataResult
UpdateDataTestHelper::applyUpdateData(Account& source, uint64_t id, std::string value,
                                      UpdateDataResultCode expectedResultCode,
                                      OperationResultCode operationResultCode) 
{
    auto txFrame = updateDataTx(source, id, value);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(operationResultCode == opResult.code());

    if (operationResultCode != OperationResultCode::opINNER) 
    {
        return UpdateDataResult{};
    }

    auto result = opResult.tr().updateDataResult();

    REQUIRE(expectedResultCode == result.code());

    return result;
}
}
}