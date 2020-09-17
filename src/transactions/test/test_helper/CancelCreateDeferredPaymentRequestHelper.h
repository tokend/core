#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{
class CancelCreateDeferredPaymentRequestHelper : TxHelper
{
public:
    explicit CancelCreateDeferredPaymentRequestHelper(TestManager::pointer testManager);

    TransactionFramePtr cancelCreateDeferredPaymentRequest(Account &source, uint64_t requestID);

    CancelDeferredPaymentCreationRequestResultCode
    applyCancelCreateDeferredPaymentRequest(Account &source, uint64_t requestID, CancelDeferredPaymentCreationRequestResultCode expectedResult);
};
}
}