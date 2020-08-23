#include "CancelDataCreationRequestOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <src/main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>

namespace stellar
{

CancelDataCreationRequestOpFrame::CancelDataCreationRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelDataCreationRequestOp(op.body.cancelDataCreationRequestOp())
{
}

bool
CancelDataCreationRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    // only requester can remove request
    return true;
}

bool
CancelDataCreationRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mCancelDataCreationRequestOp.requestID);
    if (!request ||
        (request->getType() != ReviewableRequestType::DATA_CREATION))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_CREATION);
    resource.reviewableRequest().details.dataCreation().type =
        request->getRequestEntry().body.dataCreationRequest().type;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = request->getAllTasks();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelDataCreationRequestOpFrame::doApply(Application& app,
                                          StorageHelper& storageHelper,
                                          LedgerManager& ledgerManager)
{
    innerResult().code(CancelDataCreationRequestResultCode::SUCCESS);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto requestFrame = requestHelper.loadRequest(
        mCancelDataCreationRequestOp.requestID, getSourceID(),
        ReviewableRequestType::DATA_CREATION);
    if (!requestFrame)
    {
        innerResult().code(
            CancelDataCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    storageHelper.getReviewableRequestHelper().storeDelete(
        requestFrame->getKey());

    return true;
}

bool
CancelDataCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelDataCreationRequestOp.requestID == 0)
    {
        innerResult().code(
            CancelDataCreationRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}
