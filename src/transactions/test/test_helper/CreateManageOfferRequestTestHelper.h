#pragma once

#include "TxHelper.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
namespace txtest
{
class CreateManageOfferRequestTestHelper : TxHelper
{
public:
    explicit CreateManageOfferRequestTestHelper(TestManager::pointer testManager);

    TransactionFramePtr
    createManageOfferRequestTx(Account &source, ManageOfferOp const& op, uint32 *allTasks);


    CreateManageOfferRequestResult
    applyTx(Account &source, ManageOfferOp const& op, uint32 *allTasks = nullptr,
            CreateManageOfferRequestResultCode expectedResultCode =
            CreateManageOfferRequestResultCode::SUCCESS);

protected:
    CreateManageOfferRequestResult
    checkApprovedCreation(Account& source, CreateManageOfferRequestResult opResult,
                           ManageOfferOp const& op, LedgerDelta::KeyEntryMap stateBeforeOp);

};
}
}
