#include "CreateDeferredPaymentCreationRequestOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelper.h"
#include "managers/BalanceManager.h"
#include "review_request/ReviewRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include <ledger/AccountHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>

namespace stellar
{
using xdr::operator==;

bool
CreateDeferredPaymentCreationRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result,
    LedgerManager& ledgerManager) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto srcBalanceFrame = balanceHelper.loadBalance(
        mCreateDeferredPaymentCreationRequest.request.sourceBalance);
    if (!srcBalanceFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto& accountHelper = storageHelper.getAccountHelper();
    auto dstAccountFrame = accountHelper.loadAccount(
        mCreateDeferredPaymentCreationRequest.request.destination);
    if (!dstAccountFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ACCOUNT;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(srcBalanceFrame->getAsset());

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.createDeferredPayment().assetType =
        assetFrame->getType();
    resource.reviewableRequest().details.createDeferredPayment().assetCode =
        assetFrame->getCode();

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() == srcBalanceFrame->getAccountID()))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateDeferredPaymentCreationRequest.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    if (getSourceID() == srcBalanceFrame->getAccountID())
    {
        action = AccountRuleAction::CREATE;
        if (mCreateDeferredPaymentCreationRequest.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateDeferredPaymentCreationRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame = balanceHelper.mustLoadBalance(
        mCreateDeferredPaymentCreationRequest.request.sourceBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);

    auto& details =
        resource.reviewableRequest().details.createDeferredPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();

    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    SignerRuleAction action = SignerRuleAction::CREATE;
    if (mCreateDeferredPaymentCreationRequest.allTasks)
    {
        action = SignerRuleAction::CREATE_WITH_TASKS;
        resource.reviewableRequest().allTasks =
            *mCreateDeferredPaymentCreationRequest.allTasks;
    }

    result.emplace_back(resource, action);

    return true;
}

CreateDeferredPaymentCreationRequestOpFrame::
    CreateDeferredPaymentCreationRequestOpFrame(Operation const& op,
                                                OperationResult& res,
                                                TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateDeferredPaymentCreationRequest(
          op.body.createDeferredPaymentCreationRequestOp())
{
}

bool
CreateDeferredPaymentCreationRequestOpFrame::doApply(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager)
{
    if (mCreateDeferredPaymentCreationRequest.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateDeferredPaymentCreationRequestOpFrame::createRequest(Application& app,
                                                           StorageHelper& sh,
                                                           LedgerManager& lm)
{
    auto& balanceHelper = sh.getBalanceHelper();
    auto sourceBalance = balanceHelper.loadBalance(
        mCreateDeferredPaymentCreationRequest.request.sourceBalance);
    if (!sourceBalance)
    {
        pickResultCode(CreateDeferredPaymentCreationRequestResultCode::
                           SOURCE_BALANCE_NOT_FOUND);
        return false;
    }

    auto asset = sh.getAssetHelper().loadActiveAsset(sourceBalance->getAsset());

    if (!sh.getAccountHelper().exists(
            mCreateDeferredPaymentCreationRequest.request.destination))
    {
        pickResultCode(CreateDeferredPaymentCreationRequestResultCode::
                           DESTINATION_ACCOUNT_NOT_FOUND);
        return false;
    }

    const auto result = sourceBalance->tryLock(
        mCreateDeferredPaymentCreationRequest.request.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        pickResultCode(
            result == BalanceFrame::Result::NONMATCHING_PRECISION
                ? CreateDeferredPaymentCreationRequestResultCode::
                      INCORRECT_PRECISION
                : CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED);
        return false;
    }

    auto& requestHelper = sh.getReviewableRequestHelper();

    auto& delta = sh.mustGetLedgerDelta();
    const uint64 requestID =
        delta.getHeaderFrame().generateID(LedgerEntryType::REVIEWABLE_REQUEST);
    auto request = ReviewableRequestFrame::createNew(
        requestID, getSourceID(), app.getAdminID(), nullptr, lm.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    requestEntry.body.createDeferredPaymentRequest() =
        mCreateDeferredPaymentCreationRequest.request;
    request->recalculateHashRejectReason();
    balanceHelper.storeChange(sourceBalance->mEntry);

    auto& kvHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!kvHelper.loadTasks(
            allTasks, makeTasksKeyVector(sourceBalance->getAsset()),
            mCreateDeferredPaymentCreationRequest.allTasks.get()))
    {
        pickResultCode(
            CreateDeferredPaymentCreationRequestResultCode::TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    requestHelper.storeAdd(request->mEntry);

    if (request->canBeFulfilled(lm))
    {
        return tryAutoApprove(app, sh, request);
    }
    pickResultCode(CreateDeferredPaymentCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestID;
    innerResult().success().deferredPaymentID = 0;
    innerResult().success().fulfilled = false;
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    return true;
}

bool
CreateDeferredPaymentCreationRequestOpFrame::updateRequest(Application& app,
                                                           StorageHelper& sh,
                                                           LedgerManager& lm)
{
    auto& requestHelper = sh.getReviewableRequestHelper();

    auto request = requestHelper.loadRequest(
        mCreateDeferredPaymentCreationRequest.requestID);

    auto& createDeferredPaymentRequest =
        request->getRequestEntry().body.createDeferredPaymentRequest();

    if (!request)
    {
        pickResultCode(
            CreateDeferredPaymentCreationRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& balanceHelper = sh.getBalanceHelper();
    auto sourceBalance = balanceHelper.loadBalance(
        mCreateDeferredPaymentCreationRequest.request.sourceBalance);
    if (!sourceBalance)
    {
        pickResultCode(CreateDeferredPaymentCreationRequestResultCode::
                           SOURCE_BALANCE_NOT_FOUND);
        return false;
    }

    auto asset = sh.getAssetHelper().loadActiveAsset(sourceBalance->getAsset());

    if (!sh.getAccountHelper().exists(
            mCreateDeferredPaymentCreationRequest.request.destination))
    {
        pickResultCode(CreateDeferredPaymentCreationRequestResultCode::
                           DESTINATION_ACCOUNT_NOT_FOUND);
        return false;
    }

    auto result = sourceBalance->unlock(createDeferredPaymentRequest.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        pickResultCode(
            result == BalanceFrame::Result::NONMATCHING_PRECISION
                ? CreateDeferredPaymentCreationRequestResultCode::
                      INCORRECT_PRECISION
                : CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED);
        return false;
    }
    result = sourceBalance->tryLock(
        mCreateDeferredPaymentCreationRequest.request.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        pickResultCode(
            result == BalanceFrame::Result::NONMATCHING_PRECISION
                ? CreateDeferredPaymentCreationRequestResultCode::
                      INCORRECT_PRECISION
                : CreateDeferredPaymentCreationRequestResultCode::UNDERFUNDED);
        return false;
    }

    balanceHelper.storeChange(sourceBalance->mEntry);

    createDeferredPaymentRequest.amount =
        mCreateDeferredPaymentCreationRequest.request.amount;
    createDeferredPaymentRequest.destination =
        mCreateDeferredPaymentCreationRequest.request.destination;
    createDeferredPaymentRequest.sourceBalance =
        mCreateDeferredPaymentCreationRequest.request.sourceBalance;
    createDeferredPaymentRequest.creatorDetails =
        mCreateDeferredPaymentCreationRequest.request.creatorDetails;
    createDeferredPaymentRequest.sequenceNumber++;
    request->recalculateHashRejectReason();
    request->getRequestEntry().tasks.pendingTasks = request->getAllTasks();

    requestHelper.storeChange(request->mEntry);

    if (request->canBeFulfilled(lm))
    {
        return tryAutoApprove(app, sh, request);
    }
    pickResultCode(CreateDeferredPaymentCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID =
        mCreateDeferredPaymentCreationRequest.requestID;
    innerResult().success().deferredPaymentID = 0;
    innerResult().success().fulfilled = false;
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    return true;
}

bool
CreateDeferredPaymentCreationRequestOpFrame::tryAutoApprove(
    Application& app, StorageHelper& sh,
    ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(
        mParentTx, app, ledgerManager, sh, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        throw std::runtime_error(
            "Failed to review deferred payment creation request");
    }

    innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = true;
    innerResult().success().deferredPaymentID =
        result.success()
            .typeExt.createDeferredPaymentResult()
            .deferredPaymentID;
    return true;
}

bool
CreateDeferredPaymentCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateDeferredPaymentCreationRequest.request.creatorDetails.empty() ||
        !isValidJson(
            mCreateDeferredPaymentCreationRequest.request.creatorDetails))
    {
        pickResultCode(CreateDeferredPaymentCreationRequestResultCode::
                           INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mCreateDeferredPaymentCreationRequest.request.amount == 0)
    {
        pickResultCode(
            CreateDeferredPaymentCreationRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    return true;
}

void
CreateDeferredPaymentCreationRequestOpFrame::pickResultCode(
    CreateDeferredPaymentCreationRequestResultCode code)
{
    innerResult().code(code);
}

std::vector<std::string>
CreateDeferredPaymentCreationRequestOpFrame::makeTasksKeyVector(
    AssetCode const& code)
{
    return {
        ManageKeyValueOpFrame::makeCreateDeferredPaymentCreationTasksKey(code),
        ManageKeyValueOpFrame::makeCreateDeferredPaymentCreationTasksKey("*"),
    };
}

}
