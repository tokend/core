#include "CancelDataUpdateRequestOpFrame.h"
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

CancelDataUpdateRequestOpFrame::CancelDataUpdateRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelDataUpdateRequestOp(op.body.cancelDataUpdateRequestOp())
{
}

bool
CancelDataUpdateRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    // only requester can remove request
    return true;
}

bool
CancelDataUpdateRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mCancelDataUpdateRequestOp.requestID);

    if (!request || (request->getType() != ReviewableRequestType::DATA_UPDATE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto dataFrame = storageHelper.getDataHelper().loadData(
        request->getRequestEntry().body.dataUpdateRequest().id);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_UPDATE);
    resource.reviewableRequest().details.dataUpdate().type =
        dataFrame->getData().type;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = request->getAllTasks();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelDataUpdateRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    innerResult().code(CancelDataUpdateRequestResultCode::SUCCESS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(
        mCancelDataUpdateRequestOp.requestID, getSourceID(),
        ReviewableRequestType::DATA_UPDATE);
    if (!requestFrame)
    {
        innerResult().code(
            CancelDataUpdateRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    storageHelper.getReviewableRequestHelper().storeDelete(
        requestFrame->getKey());

    return true;
}

bool
CancelDataUpdateRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelDataUpdateRequestOp.requestID == 0)
    {
        innerResult().code(
            CancelDataUpdateRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}
