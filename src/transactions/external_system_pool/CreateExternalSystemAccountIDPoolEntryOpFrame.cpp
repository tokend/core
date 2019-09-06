#include <xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include "CreateExternalSystemAccountIDPoolEntryOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "ledger/LedgerHeaderFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CreateExternalSystemAccountIDPoolEntryOpFrame::CreateExternalSystemAccountIDPoolEntryOpFrame(Operation const& op,
                                                                                             OperationResult& res,
                                                                                             TransactionFrame& parentTx)
    : ManageExternalSystemAccountIdPoolEntryOpFrame(op, res, parentTx),
      mInput(mManageExternalSystemAccountIdPoolEntryOp.actionInput.createExternalSystemAccountIdPoolEntryActionInput())
{
}

bool
CreateExternalSystemAccountIDPoolEntryOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                                       LedgerManager& ledgerManager)
{
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto& externalSystemAccountIDPoolEntryHelper = storageHelper.getExternalSystemAccountIDPoolEntryHelper();

    auto poolEntryFrame = externalSystemAccountIDPoolEntryHelper.load(mInput.externalSystemType,
                                                                      mInput.data);

    if (!!poolEntryFrame)
    {
        innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::ALREADY_EXISTS);
        return false;
    }

    auto newPoolEntryID = delta.getHeaderFrame().generateID(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY);
    poolEntryFrame = ExternalSystemAccountIDPoolEntryFrame::createNew(newPoolEntryID, mInput.externalSystemType,
                                                                      mInput.data, mInput.parent);

    externalSystemAccountIDPoolEntryHelper.storeAdd(poolEntryFrame->mEntry);
    innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS);
    innerResult().success().poolEntryID = newPoolEntryID;
    return true;
}

bool
CreateExternalSystemAccountIDPoolEntryOpFrame::doCheckValid(Application& app)
{
    if (mInput.data.empty())
    {
        innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::MALFORMED);
        return false;
    }

    return true;
}
}
