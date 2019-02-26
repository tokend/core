#include <lib/xdrpp/xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include "CreateExternalSystemAccountIDPoolEntryOpFrame.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelperLegacy.h"
#include "ledger/LedgerHeaderFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CreateExternalSystemAccountIDPoolEntryOpFrame::CreateExternalSystemAccountIDPoolEntryOpFrame(Operation const &op,
                                                                                             OperationResult &res,
                                                                                             TransactionFrame &parentTx)
    : ManageExternalSystemAccountIdPoolEntryOpFrame(op, res, parentTx),
      mInput(mManageExternalSystemAccountIdPoolEntryOp.actionInput.createExternalSystemAccountIdPoolEntryActionInput())
{
}

bool
CreateExternalSystemAccountIDPoolEntryOpFrame::doApply(Application &app, LedgerDelta &delta,
                                                       LedgerManager &ledgerManager)
{
    Database& db = ledgerManager.getDatabase();

    auto poolEntryFrame = ExternalSystemAccountIDPoolEntryHelperLegacy::Instance()->load(mInput.externalSystemType,
                                                                                   mInput.data, db, nullptr);

    if (!!poolEntryFrame)
    {
        innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::ALREADY_EXISTS);
        return false;
    }

    auto newPoolEntryID = delta.getHeaderFrame().generateID(LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY);
    poolEntryFrame = ExternalSystemAccountIDPoolEntryFrame::createNew(newPoolEntryID, mInput.externalSystemType,
                                                                      mInput.data, mInput.parent);

    ExternalSystemAccountIDPoolEntryHelperLegacy::Instance()->storeAdd(delta, db, poolEntryFrame->mEntry);
    innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS);
    innerResult().success().poolEntryID = newPoolEntryID;
    return true;
}

bool
CreateExternalSystemAccountIDPoolEntryOpFrame::doCheckValid(Application &app)
{
    if (mInput.data.empty())
    {
        innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::MALFORMED);
        return false;
    }

    return true;
}
}