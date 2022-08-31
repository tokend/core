#include "ReviewDataOwnerUpdateRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/DataFrame.h"
#include "ledger/DataHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/SignerHelper.h"
#include "transactions/ManageSignerOpFrame.h"
#include <ledger/StorageHelperImpl.h>
#include "transactions/manage_data/UpdateDataOwnerOpFrame.h"

namespace stellar
{

ReviewDataOwnerUpdateRequestOpFrame::ReviewDataOwnerUpdateRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewDataOwnerUpdateRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                         std::vector<SignerRequirement>& result, LedgerManager& lm) const
{

    auto request = storageHelper.getReviewableRequestHelper().loadRequest(mReviewRequest.requestID);

    if (!request || (request->getType() != ReviewableRequestType::DATA_OWNER_UPDATE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto dataFrame = storageHelper.getDataHelper().loadData(
        request->getRequestEntry().body.dataOwnerUpdateRequest().updateDataOwnerOp.dataID);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::DATA_OWNER_UPDATE);
    resource.reviewableRequest().details.dataOwnerUpdate().type = dataFrame->getData().type;
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool
ReviewDataOwnerUpdateRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::DATA_OWNER_UPDATE);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }


    auto requestBody = request->getRequestEntry().body.dataOwnerUpdateRequest();

    Operation op;
    op.body.type(OperationType::UPDATE_DATA_OWNER);
    op.body.updateDataOwnerOp() = requestBody.updateDataOwnerOp;
    op.sourceAccount.activate() = request->getRequestor();

    OperationResult res;
    res.code(OperationResultCode::opINNER);
    res.tr().type(OperationType::UPDATE_DATA_OWNER);

    UpdateDataOwnerOpFrame opFrame(op, res, mParentTx);

    auto requestor = storageHelper.getAccountHelper().mustLoadAccount(request->getRequestor());
    opFrame.setSourceAccountPtr(requestor);

    if (!opFrame.doCheckValid(app) || !opFrame.doApply(app, storageHelper, ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::DATA_NOT_FOUND);
        return false;
    }

    if (ledgerManager.shouldUse(LedgerVersion::FIX_MOVEMENT_REVIEW)) 
    {
        requestHelper.storeDelete(request->getKey());
    }

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewDataOwnerUpdateRequestOpFrame::handleReject(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::DATA_OWNER_UPDATE);

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
ReviewDataOwnerUpdateRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}
}
