#pragma once

#include "TxHelper.h"

namespace stellar 
{
namespace txtest 
{
class UpdateDataOwnerTestHelper : public TxHelper 
{
    TransactionFramePtr 
    updateDataOwnerTx(Account& source, uint64_t id, AccountID& newOwner);

public:    
    UpdateDataOwnerTestHelper(TestManager::pointer testManager);

    UpdateDataOwnerResult
    applyUpdateDataOwner(Account& source, uint64_t id, AccountID& newOwner, 
                    UpdateDataOwnerResultCode expectedResultCode = UpdateDataOwnerResultCode::SUCCESS,
                    OperationResultCode operationResultCode = OperationResultCode::opINNER);
};
}
}