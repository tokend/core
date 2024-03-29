#include "CancelPollRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{

CancelPollRequestOpFrame::CancelPollRequestOpFrame(Operation const& op,
                                                   OperationResult& res, TransactionFrame& parentTx)
    : ManageCreatePollRequestOpFrame(op, res, parentTx), mCancelPollRequestData(mManageCreatePollRequest.data.cancelData())
{
}

bool
CancelPollRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                    std::vector<OperationCondition>& result) const
{
    // only requester can remove request
    return true;
}

bool
CancelPollRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                   std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mCancelPollRequestData.requestID);
    if (!request || (request->getType() != ReviewableRequestType::CREATE_POLL))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_POLL);
    resource.reviewableRequest().details.createPoll().permissionType =
        request->getRequestEntry().body.createPollRequest().permissionType;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelPollRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    innerResult().code(ManageCreatePollRequestResultCode::SUCCESS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(mCancelPollRequestData.requestID,
                                                   getSourceID(), ReviewableRequestType::CREATE_POLL);
    if (!requestFrame)
    {
        innerResult().code(ManageCreatePollRequestResultCode::NOT_FOUND);
        return false;
    }

    storageHelper.getReviewableRequestHelper().storeDelete(requestFrame->getKey());

    return true;
}

bool
CancelPollRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelPollRequestData.requestID == 0)
    {
        innerResult().code(ManageCreatePollRequestResultCode::NOT_FOUND);
        return false;
    }

    return true;
}
}
