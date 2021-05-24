#pragma once

#include "ReviewCloseDeferredPaymentRequestHelper.h"
#include "TxHelper.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{
class CreateCloseDeferredPaymentTestHelper : TxHelper
{
  public:
    explicit CreateCloseDeferredPaymentTestHelper(
        TestManager::pointer testManager);

    TransactionFramePtr
    createCloseDeferredPaymentRequestTx(Account& source,
                                           CloseDeferredPaymentRequest request,
                                           uint64_t requestID, uint32* allTask);

    CreateCloseDeferredPaymentRequestResult
    applyCreateCloseDeferredPaymentRequest(
        Account& source, CloseDeferredPaymentRequest request,
        uint64_t requestID, uint32* allTasks = nullptr,
        OperationResultCode operationResultCode = OperationResultCode::opINNER,
        CreateCloseDeferredPaymentRequestResultCode expectedResultCode =
        CreateCloseDeferredPaymentRequestResultCode::SUCCESS);

  protected:
    CreateCloseDeferredPaymentRequestResult
    checkApprovedCreation(CreateCloseDeferredPaymentRequestResult opResult,
                          AccountID source,
                          LedgerDelta::KeyEntryMap stateBeforeOp);

    ReviewableRequestFrame::pointer
    createCloseDeferredPaymentRequest(Account& source,
                                         CloseDeferredPaymentRequest request,
                                         uint64 requestID);

    xdr::pointer<string64> getReference();
};
}
}
