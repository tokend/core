#pragma once

#include "TxHelper.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{
class CreateChangeRoleTestHelper : TxHelper
{
public:
    explicit CreateChangeRoleTestHelper(TestManager::pointer testManager);

    TransactionFramePtr createUpdateKYCRequestTx(Account &source, uint64_t requestID,
                                                 AccountID accountToUpdateKYC, uint64_t roleIDToSet,
                                                 longstring kycData, uint32 *allTasks);


    CreateChangeRoleRequestResult
    applyCreateChangeRoleRequest(Account &source, uint64_t requestID,
                                 AccountID accountToUpdateKYC,
                                 uint64_t roleIDToSet, longstring kycData,
                                 uint32 *allTasks = nullptr,
                                 CreateChangeRoleRequestResultCode expectedResultCode =
                                 CreateChangeRoleRequestResultCode::SUCCESS);

protected:
    CreateChangeRoleRequestResult
    checkApprovedCreation(CreateChangeRoleRequestResult opResult, AccountID accountToUpdateKYC,
                          LedgerDelta::KeyEntryMap stateBeforeOp);

    ReviewableRequestFrame::pointer
    createReviewableChangeKYCRequest(ChangeRoleRequest request, uint64 requestID);

    xdr::pointer<string64> getReference();
};
}
}