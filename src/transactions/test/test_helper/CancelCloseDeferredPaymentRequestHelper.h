#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CancelCloseDeferredPaymentRequestHelper : TxHelper
{
  public:
    explicit CancelCloseDeferredPaymentRequestHelper(
        TestManager::pointer testManager);

    TransactionFramePtr cancelCloseDeferredPaymentRequest(Account& source,
                                                          uint64_t requestID);

    CancelCloseDeferredPaymentRequestResult
    applyCancelCloseDeferredPaymentRequest(
        Account& source, uint64_t requestID,
        CancelCloseDeferredPaymentRequestResultCode expectedResult =
            CancelCloseDeferredPaymentRequestResultCode::SUCCESS);
};
}
}