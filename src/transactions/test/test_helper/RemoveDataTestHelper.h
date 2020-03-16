#pragma once

#include "TxHelper.h"

namespace stellar 
{
namespace txtest 
{
class RemoveDataTestHelper : public TxHelper 
{
    TransactionFramePtr 
    removeDataTx(Account& source, uint64_t id);

public:    
    RemoveDataTestHelper(TestManager::pointer testManager);

    RemoveDataResult
    applyRemoveData(Account& source, uint64_t type,
                    RemoveDataResultCode expectedResultCode = RemoveDataResultCode::SUCCESS,
                    OperationResultCode operationResultCode = OperationResultCode::opINNER);
};
}
}