#include "CreateDataUpdateRequestOpFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include <ledger/AccountHelper.h>
#include <ledger/DataHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/LedgerDelta.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <src/main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>

namespace stellar
{

CreateDataUpdateRequestOpFrame::CreateDataUpdateRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateDataUpdateRequestOp(op.body.createDataUpdateRequestOp())
{
}

bool
CreateDataUpdateRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataUpdateRequestOp.dataUpdateRequest.id);

    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_UPDATE);
    resource.reviewableRequest().details.dataUpdate().type =
        dataFrame->getData().type;

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() == dataFrame->getData().owner))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateDataUpdateRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    else if (getSourceID() == dataFrame->getData().owner)
    {
        action = AccountRuleAction::CREATE;
        if (mCreateDataUpdateRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateDataUpdateRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{

    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataUpdateRequestOp.dataUpdateRequest.id);

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
    resource.reviewableRequest().allTasks = 0;
    if (mCreateDataUpdateRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks =
            *mCreateDataUpdateRequestOp.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateDataUpdateRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateDataUpdateRequestOp.dataUpdateRequest.value.empty() ||
        !isValidJson(mCreateDataUpdateRequestOp.dataUpdateRequest.value))
    {
        pickResultCode(CreateDataUpdateRequestResultCode::INVALID_VALUE);
        return false;
    }

    if (!isValidJson(
            mCreateDataUpdateRequestOp.dataUpdateRequest.creatorDetails))
    {
        pickResultCode(
            CreateDataUpdateRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

void
CreateDataUpdateRequestOpFrame::tryAutoApprove(
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

    innerResult().success().fulfilled = result.success().fulfilled;
}

bool
CreateDataUpdateRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    if (mCreateDataUpdateRequestOp.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateDataUpdateRequestOpFrame::createRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNew(
        delta, getSourceID(), app.getAdminID(), nullptr,
        ledgerManager.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::DATA_UPDATE);
    requestEntry.body.dataUpdateRequest() =
        mCreateDataUpdateRequestOp.dataUpdateRequest;
    requestEntry.body.dataUpdateRequest().sequenceNumber = 0;
    request->recalculateHashRejectReason();

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(storageHelper),
                                  mCreateDataUpdateRequestOp.allTasks.get()))
    {
        pickResultCode(
            CreateDataUpdateRequestResultCode::UPDATE_DATA_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);

    storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

    pickResultCode(CreateDataUpdateRequestResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);

    if (request->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(app, storageHelper, request);
    }

    return true;
}

bool
CreateDataUpdateRequestOpFrame::updateRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    const auto requestFrame = requestHelper.loadRequest(
        mCreateDataUpdateRequestOp.requestID, getSourceID());
    if (!requestFrame ||
        requestFrame->getType() != ReviewableRequestType::DATA_UPDATE)
    {
        innerResult().code(
            CreateDataUpdateRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& request = requestFrame->getRequestEntry();
    request.tasks.pendingTasks = request.tasks.allTasks;
    auto sequence = request.body.dataUpdateRequest().sequenceNumber;
    request.body.dataUpdateRequest() =
        mCreateDataUpdateRequestOp.dataUpdateRequest;
    request.body.dataUpdateRequest().sequenceNumber = sequence + 1;
    requestFrame->recalculateHashRejectReason();

    requestHelper.storeChange(requestFrame->mEntry);

    innerResult().code(CreateDataUpdateRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;
    return true;
}

void
CreateDataUpdateRequestOpFrame::pickResultCode(
    CreateDataUpdateRequestResultCode code)
{
    innerResult().code(code);
}

CreateDataUpdateRequestResult&
CreateDataUpdateRequestOpFrame::innerResult()
{
    return mResult.tr().createDataUpdateRequestResult();
}

std::vector<std::string>
CreateDataUpdateRequestOpFrame::makeTasksKeyVector(StorageHelper& sh)
{
    auto dataType =
        sh.getDataHelper()
            .loadData(mCreateDataUpdateRequestOp.dataUpdateRequest.id)
            ->getData()
            .type;

    return {ManageKeyValueOpFrame::makeCreateDataUpdateRequestTasksKey(
                std::to_string(dataType)),
            ManageKeyValueOpFrame::makeCreateDataUpdateRequestTasksKey("*")};
}

}
