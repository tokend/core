#include "CancelDataOwnerUpdateRequestOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include <ledger/DataHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <src/main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>

namespace stellar
{

CancelDataOwnerUpdateRequestOpFrame::CancelDataOwnerUpdateRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelDataOwnerUpdateRequestOp(op.body.cancelDataOwnerUpdateRequestOp())
{
}

bool
CancelDataOwnerUpdateRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    // only requester can remove request
    return true;
}

bool
CancelDataOwnerUpdateRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mCancelDataOwnerUpdateRequestOp.requestID);

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
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_OWNER_UPDATE);
    resource.reviewableRequest().details.dataOwnerUpdate().type =
        dataFrame->getData().type;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = request->getAllTasks();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelDataOwnerUpdateRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    innerResult().code(CancelDataOwnerUpdateRequestResultCode::SUCCESS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(
        mCancelDataOwnerUpdateRequestOp.requestID, getSourceID(),
        ReviewableRequestType::DATA_OWNER_UPDATE);
    if (!requestFrame)
    {
        innerResult().code(
            CancelDataOwnerUpdateRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    storageHelper.getReviewableRequestHelper().storeDelete(
        requestFrame->getKey());

    return true;
}

bool
CancelDataOwnerUpdateRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelDataOwnerUpdateRequestOp.requestID == 0)
    {
        innerResult().code(
            CancelDataOwnerUpdateRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}
