#include "CreateDataCreationRequestOpFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include <ledger/AccountHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <src/main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>

namespace stellar
{

CreateDataCreationRequestOpFrame::CreateDataCreationRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateDataCreationRequestOp(op.body.createDataCreationRequestOp())
{
}

bool
CreateDataCreationRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_CREATION);
    resource.reviewableRequest().details.dataCreation().type =
        mCreateDataCreationRequestOp.dataCreationRequest.type;

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() ==
          mCreateDataCreationRequestOp.dataCreationRequest.owner))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateDataCreationRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    if (getSourceID() == mCreateDataCreationRequestOp.dataCreationRequest.owner)
    {
        action = AccountRuleAction::CREATE;
        if (mCreateDataCreationRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateDataCreationRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_CREATION);
    resource.reviewableRequest().details.dataCreation().type =
        mCreateDataCreationRequestOp.dataCreationRequest.type;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateDataCreationRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks =
            *mCreateDataCreationRequestOp.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateDataCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateDataCreationRequestOp.dataCreationRequest.value.empty() ||
        !isValidJson(mCreateDataCreationRequestOp.dataCreationRequest.value))
    {
        pickResultCode(CreateDataCreationRequestResultCode::INVALID_VALUE);
        return false;
    }

    if (!isValidJson(
            mCreateDataCreationRequestOp.dataCreationRequest.creatorDetails))
    {
        pickResultCode(
            CreateDataCreationRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

void
CreateDataCreationRequestOpFrame::tryAutoApprove(
    Application& app, StorageHelper& storageHelper,
    ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(
        mParentTx, app, ledgerManager, storageHelper, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state on create poll request: "
            << "tryApproveRequest expected to be success, but was: "
            << xdr::xdr_to_string(result.code());
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled =
        result.success().fulfilled;
    innerResult().success().id =
        result.success().fulfilled
            ? result.success().typeExt.dataCreationExtended().id
            : 0;
}

bool
CreateDataCreationRequestOpFrame::doApply(Application& app,
                                          StorageHelper& storageHelper,
                                          LedgerManager& ledgerManager)
{
    if (mCreateDataCreationRequestOp.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateDataCreationRequestOpFrame::createRequest(Application& app,
                                                StorageHelper& storageHelper,
                                                LedgerManager& ledgerManager)
{

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNew(
        delta, getSourceID(), app.getAdminID(), nullptr,
        ledgerManager.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::DATA_CREATION);
    requestEntry.body.dataCreationRequest() =
        mCreateDataCreationRequestOp.dataCreationRequest;
    requestEntry.body.dataCreationRequest().sequenceNumber = 0;
    request->recalculateHashRejectReason();

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(),
                                  mCreateDataCreationRequestOp.allTasks.get()))
    {
        pickResultCode(
            CreateDataCreationRequestResultCode::CREATE_DATA_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);

    storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

    pickResultCode(CreateDataCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID =
        request->getRequestID();
    innerResult().success().value =
        mCreateDataCreationRequestOp.dataCreationRequest.value;
    innerResult().success().type =
        mCreateDataCreationRequestOp.dataCreationRequest.type;
    innerResult().success().ext.v(
        LedgerVersion::EMPTY_VERSION);

    if (request->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(app, storageHelper, request);
    }

    return true;
}

bool
CreateDataCreationRequestOpFrame::updateRequest(Application& app,
                                                StorageHelper& storageHelper,
                                                LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    const auto requestFrame = requestHelper.loadRequest(
        mCreateDataCreationRequestOp.requestID, getSourceID());
    if (!requestFrame ||
        requestFrame->getType() != ReviewableRequestType::DATA_CREATION)
    {
        innerResult().code(
            CreateDataCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& request = requestFrame->getRequestEntry();
    request.tasks.pendingTasks = request.tasks.allTasks;
    auto sequence = request.body.dataCreationRequest().sequenceNumber;
    request.body.dataCreationRequest() =
        mCreateDataCreationRequestOp.dataCreationRequest;
    request.body.dataCreationRequest().sequenceNumber = sequence + 1;
    requestFrame->recalculateHashRejectReason();

    requestHelper.storeChange(requestFrame->mEntry);

    innerResult().code(CreateDataCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID =
        requestFrame->getRequestID();
    innerResult().success().fulfilled = false;
    innerResult().success().id = 0;
    return true;
}

void
CreateDataCreationRequestOpFrame::pickResultCode(
    CreateDataCreationRequestResultCode code)
{
    innerResult().code(code);
}

CreateDataCreationRequestResult&
CreateDataCreationRequestOpFrame::innerResult()
{
    return mResult.tr().createDataCreationRequestResult();
}

std::vector<std::string>
CreateDataCreationRequestOpFrame::makeTasksKeyVector()
{
    return {ManageKeyValueOpFrame::makeCreateDataCreationRequestTasksKey(
                std::to_string(
                    mCreateDataCreationRequestOp.dataCreationRequest.type)),
            ManageKeyValueOpFrame::makeCreateDataCreationRequestTasksKey("*")};
}
}
