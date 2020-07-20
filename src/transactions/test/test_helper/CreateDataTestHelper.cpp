#include "CreateDataTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar 
{
namespace txtest 
{
CreateDataTestHelper::CreateDataTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
CreateDataTestHelper::createDataTx(Account& source, uint64_t type, std::string value) 
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_DATA);
    auto& op = baseOp.body.createDataOp();
    op.type = type;
    op.value = value;
    
    return txFromOperation(source, baseOp, nullptr);
}

CreateDataResult
CreateDataTestHelper::applyCreateData(Account& source, uint64_t type, std::string value,
                                      CreateDataResultCode expectedResultCode,
                                      OperationResultCode operationResultCode) 
{
    auto txFrame = createDataTx(source, type, value);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(operationResultCode == opResult.code());

    if (operationResultCode != OperationResultCode::opINNER) 
    {
        return CreateDataResult{};
    }

    auto result = opResult.tr().createDataResult();

    REQUIRE(expectedResultCode == result.code());

    return result;
}
}
}