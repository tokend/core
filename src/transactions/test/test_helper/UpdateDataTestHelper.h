#pragma once

#include "TxHelper.h"

namespace stellar 
{
namespace txtest 
{
class UpdateDataTestHelper : public TxHelper 
{
    TransactionFramePtr 
    updateDataTx(Account& source, uint64_t id, std::string value);

public:    
    UpdateDataTestHelper(TestManager::pointer testManager);

    UpdateDataResult
    applyUpdateData(Account& source, uint64_t id, std::string value, 
                    UpdateDataResultCode expectedResultCode = UpdateDataResultCode::SUCCESS,
                    OperationResultCode operationResultCode = OperationResultCode::opINNER);
};
}
}