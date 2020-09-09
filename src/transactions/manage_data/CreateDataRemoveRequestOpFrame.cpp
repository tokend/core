#include "CreateDataRemoveRequestOpFrame.h"
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

CreateDataRemoveRequestOpFrame::CreateDataRemoveRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateDataRemoveRequestOp(op.body.createDataRemoveRequestOp())
{
}

bool
CreateDataRemoveRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataRemoveRequestOp.dataRemoveRequest.id);

    if (!dataFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DATA;
        return false;
    }
    
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::DATA_REMOVE);
    resource.reviewableRequest().details.dataRemove().type =
        dataFrame->getData().type;

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() == dataFrame->getData().owner))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateDataRemoveRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    else if (getSourceID() == dataFrame->getData().owner)
    {
        action = AccountRuleAction::CREATE;
        if (mCreateDataRemoveRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateDataRemoveRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{

    auto dataFrame = storageHelper.getDataHelper().loadData(
        mCreateDataRemoveRequestOp.dataRemoveRequest.id);
    
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
    resource.reviewableRequest().allTasks = 0;
    if (mCreateDataRemoveRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks =
            *mCreateDataRemoveRequestOp.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateDataRemoveRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(
            mCreateDataRemoveRequestOp.dataRemoveRequest.creatorDetails))
    {
        pickResultCode(
            CreateDataRemoveRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

void
CreateDataRemoveRequestOpFrame::tryAutoApprove(
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
CreateDataRemoveRequestOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    if (mCreateDataRemoveRequestOp.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateDataRemoveRequestOpFrame::createRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto request = ReviewableRequestFrame::createNew(
        delta, getSourceID(), app.getAdminID(), nullptr,
        ledgerManager.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::DATA_REMOVE);
    requestEntry.body.dataRemoveRequest() =
        mCreateDataRemoveRequestOp.dataRemoveRequest;
    requestEntry.body.dataRemoveRequest().sequenceNumber = 0;
    request->recalculateHashRejectReason();

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(storageHelper),
                                  mCreateDataRemoveRequestOp.allTasks.get()))
    {
        pickResultCode(
            CreateDataRemoveRequestResultCode::REMOVE_DATA_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);

    storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);

    pickResultCode(CreateDataRemoveRequestResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);

    if (request->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(app, storageHelper, request);
    }

    return true;
}

bool
CreateDataRemoveRequestOpFrame::updateRequest(Application& app,
                                              StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    const auto requestFrame = requestHelper.loadRequest(
        mCreateDataRemoveRequestOp.requestID, getSourceID());
    if (!requestFrame ||
        requestFrame->getType() != ReviewableRequestType::DATA_REMOVE)
    {
        innerResult().code(
            CreateDataRemoveRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& request = requestFrame->getRequestEntry();
    request.tasks.pendingTasks = request.tasks.allTasks;
    auto sequence = request.body.dataRemoveRequest().sequenceNumber;
    request.body.dataRemoveRequest() =
        mCreateDataRemoveRequestOp.dataRemoveRequest;
    request.body.dataRemoveRequest().sequenceNumber = sequence + 1;
    requestFrame->recalculateHashRejectReason();

    requestHelper.storeChange(requestFrame->mEntry);

    innerResult().code(CreateDataRemoveRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;
    return true;
}

void
CreateDataRemoveRequestOpFrame::pickResultCode(
    CreateDataRemoveRequestResultCode code)
{
    innerResult().code(code);
}

CreateDataRemoveRequestResult&
CreateDataRemoveRequestOpFrame::innerResult()
{
    return mResult.tr().createDataRemoveRequestResult();
}

std::vector<std::string>
CreateDataRemoveRequestOpFrame::makeTasksKeyVector(StorageHelper& sh)
{

    auto dataType =
        sh.getDataHelper()
            .loadData(mCreateDataRemoveRequestOp.dataRemoveRequest.id)
            ->getData()
            .type;
    return {ManageKeyValueOpFrame::makeCreateDataRemoveRequestTasksKey(
                std::to_string(dataType)),
            ManageKeyValueOpFrame::makeCreateDataRemoveRequestTasksKey("*")};
}
}
