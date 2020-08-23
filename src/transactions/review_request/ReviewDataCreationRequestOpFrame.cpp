#include "ReviewDataCreationRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/DataFrame.h"
#include "ledger/DataHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/SignerHelper.h"
#include "transactions/ManageSignerOpFrame.h"
#include <ledger/StorageHelperImpl.h>

namespace stellar
{

ReviewDataCreationRequestOpFrame::ReviewDataCreationRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewDataCreationRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::DATA_CREATION);

    auto& requestEntry = request->getRequestEntry();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& dataHelper = storageHelper.getDataHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    requestHelper.storeDelete(request->getKey());

    auto& dataCreationRequest = requestEntry.body.dataCreationRequest();

    auto dataFrame = DataFrame::create(dataCreationRequest);
    auto& header = storageHelper.mustGetLedgerDelta().getHeaderFrame();
    auto dataID = header.generateID(LedgerEntryType::DATA);
    ;
    dataFrame->getData().id = dataID;

    dataHelper.storeAdd(dataFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(
        ReviewableRequestType::DATA_CREATION);
    innerResult().success().typeExt.dataCreationExtended().type =
        dataCreationRequest.type;
    innerResult().success().typeExt.dataCreationExtended().owner =
        dataCreationRequest.owner;
    innerResult().success().typeExt.dataCreationExtended().id = dataID;

    return true;
}

bool
ReviewDataCreationRequestOpFrame::handleReject(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::KYC_RECOVERY);

    if (mReviewRequest.reviewDetails.tasksToRemove != 0)
    {
        innerResult().code(
            ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED);
        return false;
    }

    auto& requestEntry = request->getRequestEntry();
    requestEntry.tasks.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.tasks.externalDetails.emplace_back(
        mReviewRequest.reviewDetails.externalDetails);

    request->setRejectReason(mReviewRequest.reason);

    const auto newHash =
        ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;

    storageHelper.getReviewableRequestHelper().storeChange(request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}
bool
ReviewDataCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}
}
