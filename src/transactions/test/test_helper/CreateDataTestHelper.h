#pragma once

#include "TxHelper.h"

namespace stellar 
{
namespace txtest 
{
class CreateDataTestHelper : public TxHelper 
{
    TransactionFramePtr 
    createDataTx(Account& source, uint64_t type, std::string value);

public:    
    CreateDataTestHelper(TestManager::pointer testManager);

    CreateDataResult
    applyCreateData(Account& source, uint64_t type, std::string value, 
                    CreateDataResultCode expectedResultCode = CreateDataResultCode::SUCCESS,
                    OperationResultCode operationResultCode = OperationResultCode::opINNER);
};
}
}