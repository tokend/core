#include "CreatePollRequestOpFrame.h"
#include "main/Application.h"
#include "ledger/StorageHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"

namespace stellar
{

CreatePollRequestOpFrame::CreatePollRequestOpFrame(Operation const& op,
        OperationResult& res, TransactionFrame& parentTx)
        : ManageCreatePollRequestOpFrame(op, res, parentTx)
        , mCreatePollRequestData(mManageCreatePollRequest.data.createData())
{
}

bool
CreatePollRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                              std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_POLL);
    resource.reviewableRequest().details.createPoll().permissionType =
            mCreatePollRequestData.request.permissionType;

    if (mCreatePollRequestData.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreatePollRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                             std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_POLL);
    resource.reviewableRequest().details.createPoll().permissionType =
            mCreatePollRequestData.request.permissionType;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreatePollRequestData.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreatePollRequestData.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreatePollRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper,
                                  LedgerManager &ledgerManager)
{
    innerResult().code(ManageCreatePollRequestResultCode::SUCCESS);

    if (!checkDates(ledgerManager))
    {
        return false;
    }

    if (!storageHelper.getAccountHelper().exists(mCreatePollRequestData.request.resultProviderID))
    {
        innerResult().code(ManageCreatePollRequestResultCode::RESULT_PROVIDER_NOT_FOUND);
        return false;
    }

    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());

    if (!tryPopulateRequest(storageHelper, requestFrame->getRequestEntry()))
    {
        return false;
    }

    Database& db = storageHelper.getDatabase();
    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().success().details.action(ManageCreatePollRequestAction::CREATE);
    innerResult().success().details.response().fulfilled = false;
    innerResult().success().details.response().requestID = requestFrame->getRequestID();
    innerResult().success().details.response().pollID = nullptr;

    if (requestFrame->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(app, storageHelper, requestFrame);
    }

    return true;
}

bool
CreatePollRequestOpFrame::tryPopulateRequest(StorageHelper &storageHelper,
                                             ReviewableRequestEntry &requestEntry)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_POLL);
    requestEntry.body.createPollRequest() = mCreatePollRequestData.request;

    uint32_t allTasks;
    KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeys(), mCreatePollRequestData.allTasks.get()))
    {
        innerResult().code(ManageCreatePollRequestResultCode::CREATE_POLL_TASKS_NOT_FOUND);
        return false;
    }

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = allTasks;
    requestEntry.hash = ReviewableRequestFrame::calculateHash(requestEntry.body);

    return true;
}

void
CreatePollRequestOpFrame::tryAutoApprove(Application& app, StorageHelper& storageHelper,
        ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app,
            ledgerManager, storageHelper.mustGetLedgerDelta(), request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state on create poll request: "
                << "tryApproveRequest expected to be success, but was: "
                << xdr::xdr_to_string(result.code());
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().details.response().fulfilled = true;
    innerResult().success().details.response().pollID.activate() =
            result.success().typeExt.createPoll().pollID;
}

bool
CreatePollRequestOpFrame::checkDates(LedgerManager& lm)
{
    if (mCreatePollRequestData.request.endTime <= lm.getCloseTime())
    {
        innerResult().code(ManageCreatePollRequestResultCode::INVALID_END_TIME);
        return false;
    }

    return true;
}

bool
CreatePollRequestOpFrame::doCheckValid(Application &app)
{
    if (!isValidJson(mCreatePollRequestData.request.creatorDetails))
    {
        innerResult().code(ManageCreatePollRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mCreatePollRequestData.request.startTime >= mCreatePollRequestData.request.endTime)
    {
        innerResult().code(ManageCreatePollRequestResultCode::INVALID_DATES);
        return false;
    }

    if (mCreatePollRequestData.request.numberOfChoices == 0)
    {
        innerResult().code(ManageCreatePollRequestResultCode::INVALID_NUMBER_OF_CHOICES);
        return false;
    }

    return true;
}

std::vector<std::string>
CreatePollRequestOpFrame::makeTasksKeys() const
{
    return
    {
        ManageKeyValueOpFrame::makeCreatePollKey(std::to_string(
                mCreatePollRequestData.request.permissionType)),
        ManageKeyValueOpFrame::makeCreatePollKey("*")
    };
}

}
