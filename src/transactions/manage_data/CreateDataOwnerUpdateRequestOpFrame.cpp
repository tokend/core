#include "CreateDataOwnerUpdateRequestOpFrame.h"
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

CreateDataOwnerUpdateRequestOpFrame::CreateDataOwnerUpdateRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateDataOwnerUpdateRequestOp(op.body.createDataOwnerUpdateRequestOp())
{
}

bool
CreateDataOwnerUpdateRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest.updateDataOwnerOp.dataID);

    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_OWNER_UPDATE);
    resource.reviewableRequest().details.dataOwnerUpdate().type =
        dataFrame->getData().type;

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() == dataFrame->getData().owner))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateDataOwnerUpdateRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    else 
    {
        if (mCreateDataOwnerUpdateRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateDataOwnerUpdateRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{

    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest.updateDataOwnerOp.dataID);

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
    resource.reviewableRequest().allTasks = 0;
    if (mCreateDataOwnerUpdateRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks =
            *mCreateDataOwnerUpdateRequestOp.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateDataOwnerUpdateRequestOpFrame::doCheckValid(Application& app)
{

    if (!isValidJson(
            mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest.creatorDetails))
    {
        pickResultCode(
            CreateDataOwnerUpdateRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

void
CreateDataOwnerUpdateRequestOpFrame::tryAutoApprove(
    Application& app, StorageHelper& storageHelper,
    ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(
        mParentTx, app, ledgerManager, storageHelper, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state on update data owner request: "
            << "tryApproveRequest expected to be success, but was: "
            << xdr::xdr_to_string(result.code());
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled = result.success().fulfilled;
}

bool
CreateDataOwnerUpdateRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    if (mCreateDataOwnerUpdateRequestOp.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateDataOwnerUpdateRequestOpFrame::createRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNew(
        delta, getSourceID(), app.getAdminID(), nullptr,
        ledgerManager.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::DATA_OWNER_UPDATE);
    requestEntry.body.dataOwnerUpdateRequest() =
        mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest;
    requestEntry.body.dataOwnerUpdateRequest().sequenceNumber = 0;
    request->recalculateHashRejectReason();

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(storageHelper),
                                  mCreateDataOwnerUpdateRequestOp.allTasks.get()))
    {
        pickResultCode(
            CreateDataOwnerUpdateRequestResultCode::UPDATE_DATA_OWNER_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);

    storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

    pickResultCode(CreateDataOwnerUpdateRequestResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);

    if (request->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(app, storageHelper, request);
    }

    return true;
}

bool
CreateDataOwnerUpdateRequestOpFrame::updateRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    const auto requestFrame = requestHelper.loadRequest(
        mCreateDataOwnerUpdateRequestOp.requestID, getSourceID());
    if (!requestFrame ||
        requestFrame->getType() != ReviewableRequestType::DATA_OWNER_UPDATE)
    {
        innerResult().code(
            CreateDataOwnerUpdateRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& request = requestFrame->getRequestEntry();
    request.tasks.pendingTasks = request.tasks.allTasks;
    auto sequence = request.body.dataOwnerUpdateRequest().sequenceNumber;
    request.body.dataOwnerUpdateRequest() =
        mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest;
    request.body.dataOwnerUpdateRequest().sequenceNumber = sequence + 1;
    requestFrame->recalculateHashRejectReason();

    requestHelper.storeChange(requestFrame->mEntry);

    innerResult().code(CreateDataOwnerUpdateRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;
    return true;
}

void
CreateDataOwnerUpdateRequestOpFrame::pickResultCode(
    CreateDataOwnerUpdateRequestResultCode code)
{
    innerResult().code(code);
}

CreateDataOwnerUpdateRequestResult&
CreateDataOwnerUpdateRequestOpFrame::innerResult()
{
    return mResult.tr().createDataOwnerUpdateRequestResult();
}

std::vector<std::string>
CreateDataOwnerUpdateRequestOpFrame::makeTasksKeyVector(StorageHelper& sh)
{
    auto dataType =
        sh.getDataHelper()
            .loadData(mCreateDataOwnerUpdateRequestOp.dataOwnerUpdateRequest.updateDataOwnerOp.dataID)
            ->getData()
            .type;

    return {ManageKeyValueOpFrame::makeCreateDataOwnerUpdateRequestTasksKey(
                std::to_string(dataType)),
            ManageKeyValueOpFrame::makeCreateDataOwnerUpdateRequestTasksKey("*")};
}

}
