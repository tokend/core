#include "UpdateDataOwnerTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar 
{
namespace txtest 
{
UpdateDataOwnerTestHelper::UpdateDataOwnerTestHelper(TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
UpdateDataOwnerTestHelper::updateDataOwnerTx(Account& source, uint64_t id, AccountID& newOwner) 
{
    Operation baseOp;
    baseOp.body.type(OperationType::UPDATE_DATA_OWNER);
    auto& op = baseOp.body.updateDataOwnerOp();
    op.dataID = id;
    op.newOwner = newOwner;
    
    return txFromOperation(source, baseOp, nullptr);
}

UpdateDataOwnerResult
UpdateDataOwnerTestHelper::applyUpdateDataOwner(Account& source, uint64_t id, AccountID& newOwner,
                                      UpdateDataOwnerResultCode expectedResultCode,
                                      OperationResultCode operationResultCode) 
{
    auto txFrame = updateDataOwnerTx(source, id, newOwner);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(operationResultCode == opResult.code());

    if (operationResultCode != OperationResultCode::opINNER) 
    {
        return UpdateDataOwnerResult{};
    }

    auto result = opResult.tr().updateDataOwnerResult();

    REQUIRE(expectedResultCode == result.code());

    return result;
}
}
}