#include "CancelChangeRoleRequestOpFrame.h"
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/StorageHelper.h"

namespace stellar
{
using xdr::operator==;

CancelChangeRoleRequestOpFrame::CancelChangeRoleRequestOpFrame(
        const stellar::Operation &op,
        stellar::OperationResult &res,
        stellar::TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx),
        mCancelChangeRoleRequest(mOperation.body.cancelChangeRoleRequestOp())
{
}

bool
CancelChangeRoleRequestOpFrame::tryGetOperationConditions(stellar::StorageHelper &storageHelper,
                                                          std::vector<stellar::OperationCondition> &result) const
{
    // only request creator can remove it
    return true;
}

bool
CancelChangeRoleRequestOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                         std::vector<stellar::SignerRequirement> &result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CHANGE_ROLE);
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelChangeRoleRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                        LedgerManager& ledgerManager)
{
    auto const requestID = mCancelChangeRoleRequest.requestID;
    auto& db = ledgerManager.getDatabase();
    auto requestHelper = ReviewableRequestHelper::Instance();

    auto requestFrame = requestHelper->loadRequest(requestID, getSourceID(),
                                                   ReviewableRequestType::CHANGE_ROLE, db, &delta);
    if (!requestFrame)
    {
        innerResult().code(CancelChangeRoleRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    requestHelper->storeDelete(delta, db, requestFrame->getKey());

    innerResult().code(CancelChangeRoleRequestResultCode::SUCCESS);
    return true;
}

bool
CancelChangeRoleRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelChangeRoleRequest.requestID == 0) {
        innerResult().code(CancelChangeRoleRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}

