#include <ledger/EntryHelper.h>
#include "ledger/KeyValueHelper.h"
#include <ledger/ReviewableRequestFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/StorageHelper.h"
#include "review_request/ReviewRequestHelper.h"
#include <xdrpp/marshal.h>
#include "CreateManageLimitsRequestOpFrame.h"
#include "ManageKeyValueOpFrame.h"

namespace stellar
{

bool
CreateManageLimitsRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                            std::vector<OperationCondition>& result,
                                                            LedgerManager& ledgerManager) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::UPDATE_LIMITS);

    if (ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS)
        && mCreateManageLimitsRequest.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
    }
    else
    {
        result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    }

    return true;
}

bool
CreateManageLimitsRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                           std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::UPDATE_LIMITS);
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateManageLimitsRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateManageLimitsRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

CreateManageLimitsRequestOpFrame::CreateManageLimitsRequestOpFrame(
    Operation const& op, OperationResult& res,
    TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateManageLimitsRequest(mOperation.body.createManageLimitsRequestOp())
{
}

std::string
CreateManageLimitsRequestOpFrame::getLimitsManageRequestDetailsReference(longstring const& details) const
{
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::UPDATE_LIMITS, details));
    return binToHex(hash);
}

bool
CreateManageLimitsRequestOpFrame::updateManageLimitsRequest(Application& app, StorageHelper& storageHelper, LedgerManager& lm)
{
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto& db = storageHelper.getDatabase();

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto requestFrame = requestHelper.loadRequest(mCreateManageLimitsRequest.requestID, getSourceID(),
                                                  ReviewableRequestType::UPDATE_LIMITS);
    if (!requestFrame)
    {
        innerResult().code(CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_NOT_FOUND);
        return false;
    }

    if (!ensureLimitsUpdateValid())
    {
        innerResult().code(CreateManageLimitsRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }

    auto& limitsUpdateRequest = requestFrame->getRequestEntry().body.limitsUpdateRequest();

    limitsUpdateRequest.creatorDetails = mCreateManageLimitsRequest.manageLimitsRequest.creatorDetails;

    requestFrame->recalculateHashRejectReason();
    requestHelper.storeChange(requestFrame->mEntry);

    innerResult().success().fulfilled = false;
    innerResult().code(CreateManageLimitsRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().manageLimitsRequestID = requestFrame->getRequestID();

    return true;
}

bool CreateManageLimitsRequestOpFrame::createManageLimitsRequest(Application& app, StorageHelper& storageHelper,
                                                                 LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();

    auto& manageLimitsRequest = mCreateManageLimitsRequest.manageLimitsRequest;

    auto details = manageLimitsRequest.creatorDetails;
    longstring reference = getLimitsManageRequestDetailsReference(details);
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    if (requestHelper.isReferenceExist(getSourceID(), reference, 0))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::MANAGE_LIMITS_REQUEST_REFERENCE_DUPLICATION);
        return false;
    }

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::UPDATE_LIMITS);
    body.limitsUpdateRequest().creatorDetails = mCreateManageLimitsRequest.manageLimitsRequest.creatorDetails;

    auto request = ReviewableRequestFrame::createNewWithHash(delta, getSourceID(),
                                                             app.getAdminID(), referencePtr,
                                                             body, ledgerManager.getCloseTime());

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, {ManageKeyValueOpFrame::makeLimitsUpdateTasksKey()},
                                  mCreateManageLimitsRequest.allTasks.get()))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::LIMITS_UPDATE_TASKS_NOT_FOUND);
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateManageLimitsRequestResultCode::LIMITS_UPDATE_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }
    request->setTasks(allTasks);
    requestHelper.storeAdd(request->mEntry);

    innerResult().code(CreateManageLimitsRequestResultCode::SUCCESS);
    innerResult().success().manageLimitsRequestID = request->getRequestID();
    innerResult().success().fulfilled = false;

    return true;
}

bool
CreateManageLimitsRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    // required for the new flow, when source have to specify request id for creation or update of the request
    bool isUpdating = mCreateManageLimitsRequest.requestID != 0;
    if (isUpdating)
    {
        return updateManageLimitsRequest(app, storageHelper, ledgerManager);
    }

    return createManageLimitsRequest(app, storageHelper, ledgerManager);
}

bool CreateManageLimitsRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mCreateManageLimitsRequest.manageLimitsRequest.creatorDetails))
    {
        innerResult().code(CreateManageLimitsRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

bool CreateManageLimitsRequestOpFrame::ensureLimitsUpdateValid()
{
    if (mCreateManageLimitsRequest.allTasks)
    {
        return false;
    }

    return true;
}

}
