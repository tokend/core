#pragma once

#include "ReviewCreateDeferredPaymentRequestHelper.h"
#include "TxHelper.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{
class CreateDeferredPaymentCreationTestHelper : TxHelper
{
  public:
    explicit CreateDeferredPaymentCreationTestHelper(
        TestManager::pointer testManager);

    TransactionFramePtr
    createDeferredPaymentCreationRequestTx(Account& source,
                                           CreateDeferredPaymentRequest request,
                                           uint64_t requestID, uint32* allTask);

    CreateDeferredPaymentCreationRequestResult
    applyCreateDeferredPaymentCreationRequest(
        Account& source, CreateDeferredPaymentRequest request,
        uint64_t requestID, uint32* allTasks = nullptr,
        OperationResultCode operationResultCode = OperationResultCode::opINNER,
        CreateDeferredPaymentCreationRequestResultCode expectedResultCode =
            CreateDeferredPaymentCreationRequestResultCode::SUCCESS);

  protected:
    CreateDeferredPaymentCreationRequestResult
    checkApprovedCreation(CreateDeferredPaymentCreationRequestResult opResult,
                          AccountID source,
                          LedgerDelta::KeyEntryMap stateBeforeOp);

    ReviewableRequestFrame::pointer
    createDeferredPaymentCreationRequest(Account& source,
                                         CreateDeferredPaymentRequest request,
                                         uint64 requestID);

    xdr::pointer<string64> getReference();
};
}
}
