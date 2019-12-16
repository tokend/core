#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include "transactions/CreateAMLAlertRequestOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/LedgerHeaderFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "review_request/ReviewRequestHelper.h"

namespace stellar
{
using xdr::operator==;

bool
CreateAMLAlertRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                        std::vector<OperationCondition>& result,
                                                        LedgerManager& ledgerManager) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_AML_ALERT);

    if (ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS)
        && mCreateAMLAlertRequest.allTasks)
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
CreateAMLAlertRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                       std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_AML_ALERT);
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateAMLAlertRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateAMLAlertRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

CreateAMLAlertRequestOpFrame::CreateAMLAlertRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateAMLAlertRequest(mOperation.body.createAMLAlertRequestOp())
{
}

bool
CreateAMLAlertRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                      LedgerManager& ledgerManager)
{
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto& balanceHelper = storageHelper.getBalanceHelper();
    const auto amlAlertRequest = mCreateAMLAlertRequest.amlAlertRequest;
    auto balanceFrame = balanceHelper.loadBalance(amlAlertRequest.balanceID);
    if (!balanceFrame)
    {
        pickResultCode(app.getLedgerManager(), CreateAMLAlertRequestResultCode::BALANCE_NOT_EXIST);
        return false;
    }
    const auto result = balanceFrame->tryLock(amlAlertRequest.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        pickResultCode(app.getLedgerManager(), result == BalanceFrame::Result::NONMATCHING_PRECISION ?
                                               CreateAMLAlertRequestResultCode::INCORRECT_PRECISION :
                                               CreateAMLAlertRequestResultCode::UNDERFUNDED);
        return false;
    }

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    const bool isReferenceExists = requestHelper.isReferenceExist(getSourceID(), mCreateAMLAlertRequest.reference, 0);
    if (isReferenceExists)
    {
        pickResultCode(app.getLedgerManager(), CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION);
        return false;
    }

    const uint64 requestID = delta.
        getHeaderFrame().
        generateID(LedgerEntryType::REVIEWABLE_REQUEST);
    const auto referencePtr = xdr::pointer<string64>(new string64(mCreateAMLAlertRequest.reference));
    auto request = ReviewableRequestFrame::createNew(requestID,
                                                     getSourceID(),
                                                     app.getAdminID(),
                                                     referencePtr,
                                                     ledgerManager.
                                                         getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_AML_ALERT);
    requestEntry.body.amlAlertRequest() = amlAlertRequest;
    request->recalculateHashRejectReason();
    balanceHelper.storeChange(balanceFrame->mEntry);
    requestHelper.storeAdd(request->mEntry);

    KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, {ManageKeyValueOpFrame::makeAmlAlertCreateTasksKey()},
                                  mCreateAMLAlertRequest.allTasks.get()))
    {
        innerResult().code(CreateAMLAlertRequestResultCode::AML_ALERT_TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    requestHelper.storeChange(request->mEntry);

    bool fulfilled = false;

    if (allTasks == 0)
    {
        auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, storageHelper, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS)
        {
            throw std::runtime_error("Failed to review AML alert request");
        }
        fulfilled = result.success().fulfilled;
    }

    innerResult().code(CreateAMLAlertRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestID;
    innerResult().success().fulfilled = fulfilled;
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    return true;
}

bool CreateAMLAlertRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateAMLAlertRequest.amlAlertRequest.creatorDetails.empty())
    {
        pickResultCode(app.getLedgerManager(), CreateAMLAlertRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mCreateAMLAlertRequest.amlAlertRequest.amount == 0)
    {
        pickResultCode(app.getLedgerManager(), CreateAMLAlertRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    return true;
}

void
CreateAMLAlertRequestOpFrame::pickResultCode(LedgerManager& lm, CreateAMLAlertRequestResultCode code)
{
    if (lm.shouldUse(LedgerVersion::FIX_AML_ALERT_ERROR_CODES))
    {
        innerResult().code(code);
        return;
    }

    if (mOldCodes.find(code) == mOldCodes.end())
    {
        throw std::runtime_error("No mapping from new to old code for aml alert");
    }

    innerResult().code(mOldCodes.at(code));
}
}
