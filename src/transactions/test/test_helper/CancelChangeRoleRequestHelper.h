#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CancelChangeRoleRequestHelper : TxHelper
{
public:
    explicit CancelChangeRoleRequestHelper(TestManager::pointer testManager);

    TransactionFramePtr cancelChangeRoleRequest(Account &source, uint64_t requestID);

    CancelChangeRoleRequestResult
    applyCancelChangeRoleRequest(Account &source, uint64_t requestID, CancelChangeRoleRequestResultCode expectedResult);
};
}
}