#include <xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include "ledger/StorageHelper.h"
#include "ledger/ExternalSystemAccountIDHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "DeleteExternalSystemAccountIDPoolEntryOpFrame.h"

namespace stellar
{
using namespace std;

DeleteExternalSystemAccountIDPoolEntryOpFrame::DeleteExternalSystemAccountIDPoolEntryOpFrame(Operation const& op,
                                                                                             OperationResult& res,
                                                                                             TransactionFrame& parentTx)
    : ManageExternalSystemAccountIdPoolEntryOpFrame(op, res, parentTx),
      mInput(mManageExternalSystemAccountIdPoolEntryOp.actionInput.deleteExternalSystemAccountIdPoolEntryActionInput())
{
}

bool
DeleteExternalSystemAccountIDPoolEntryOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                                       LedgerManager& ledgerManager)
{
    innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS);

    auto& poolEntryHelper = storageHelper.getExternalSystemAccountIDPoolEntryHelper();

    auto poolEntryToDeleteFrame = poolEntryHelper.load(mInput.poolEntryID);

    if (!poolEntryToDeleteFrame)
    {
        innerResult().code(ManageExternalSystemAccountIdPoolEntryResultCode::NOT_FOUND);
        return false;
    }

    if (poolEntryToDeleteFrame->getExternalSystemAccountIDPoolEntry().expiresAt > ledgerManager.getCloseTime())
    {
        poolEntryToDeleteFrame->markAsDeleted();
        poolEntryHelper.storeChange(poolEntryToDeleteFrame->mEntry);
        return true;
    }

    ExternalSystemAccountIDPoolEntry& poolEntryToDelete = poolEntryToDeleteFrame->getExternalSystemAccountIDPoolEntry();

    if (!!poolEntryToDelete.accountID)
    {
        auto& externalSystemAccountIDHelper = storageHelper.getExternalSystemAccountIDHelper();
        auto existingExternalSystemAccountIDFrame = externalSystemAccountIDHelper.load(*poolEntryToDelete.accountID,
                                                                                       poolEntryToDelete.externalSystemType);

        if (!existingExternalSystemAccountIDFrame)
        {
            auto accIDStr = PubKeyUtils::toStrKey(*poolEntryToDelete.accountID);
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Failed to load existing external system account id for account id:"
                << accIDStr;
            throw runtime_error("Unexpected state: external system account id expected to exist");
        }

        externalSystemAccountIDHelper.storeDelete(existingExternalSystemAccountIDFrame->getKey());
    }

    poolEntryHelper.storeDelete(poolEntryToDeleteFrame->getKey());

    return true;
}

bool
DeleteExternalSystemAccountIDPoolEntryOpFrame::doCheckValid(Application& app)
{
    return true;
}

}
