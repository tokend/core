#include "CancelDataRemoveRequestOpFrame.h"
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

CancelDataRemoveRequestOpFrame::CancelDataRemoveRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelDataRemoveRequestOp(op.body.cancelDataRemoveRequestOp())
{
}

bool
CancelDataRemoveRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    // only requester can remove request
    return true;
}

bool
CancelDataRemoveRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mCancelDataRemoveRequestOp.requestID);

    if (!request || (request->getType() != ReviewableRequestType::DATA_REMOVE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto dataFrame = storageHelper.getDataHelper().loadData(
        request->getRequestEntry().body.dataRemoveRequest().id);
    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_REMOVE);
    resource.reviewableRequest().details.dataRemove().type =
        dataFrame->getData().type;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = request->getAllTasks();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelDataRemoveRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    innerResult().code(CancelDataRemoveRequestResultCode::SUCCESS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(
        mCancelDataRemoveRequestOp.requestID, getSourceID(),
        ReviewableRequestType::DATA_REMOVE);
    if (!requestFrame)
    {
        innerResult().code(
            CancelDataRemoveRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    storageHelper.getReviewableRequestHelper().storeDelete(
        requestFrame->getKey());

    return true;
}

bool
CancelDataRemoveRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelDataRemoveRequestOp.requestID == 0)
    {
        innerResult().code(
            CancelDataRemoveRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}
