#include "CreateCloseDeferredPaymentRequestOpFrame.h"
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
#include <ledger/DeferredPaymentHelper.h>
#include <ledger/ReviewableRequestHelper.h>

namespace stellar
{
using xdr::operator==;

bool
CreateCloseDeferredPaymentRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result,
    LedgerManager& ledgerManager) const
{
    auto deferredPayment =
        storageHelper.getDeferredPaymentHelper().loadDeferredPayment(
            mCreateCloseDeferredPaymentRequest.request.deferredPaymentID);

    if (!deferredPayment)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DEFERRED_PAYMENT;
        return false;
    }

    auto srcBalance = storageHelper.getBalanceHelper().loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(srcBalance->getAsset());

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.closeDeferredPayment().assetType =
        assetFrame->getType();
    resource.reviewableRequest().details.closeDeferredPayment().assetCode =
        assetFrame->getCode();

    auto action = AccountRuleAction::CREATE;

    action = AccountRuleAction::CREATE;
    if (mCreateCloseDeferredPaymentRequest.allTasks)
    {
        action = AccountRuleAction::CREATE_WITH_TASKS;
    }
    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateCloseDeferredPaymentRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<SignerRequirement>& result) const
{
    auto deferredPayment =
        storageHelper.getDeferredPaymentHelper().loadDeferredPayment(
            mCreateCloseDeferredPaymentRequest.request.deferredPaymentID);

    if (!deferredPayment)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DEFERRED_PAYMENT;
        return false;
    }

    auto srcBalance = storageHelper.getBalanceHelper().loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(srcBalance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);

    auto& details = resource.reviewableRequest().details.closeDeferredPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();

    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    SignerRuleAction action = SignerRuleAction::CREATE;
    if (mCreateCloseDeferredPaymentRequest.allTasks)
    {
        action = SignerRuleAction::CREATE_WITH_TASKS;
        resource.reviewableRequest().allTasks =
            *mCreateCloseDeferredPaymentRequest.allTasks;
    }

    result.emplace_back(resource, action);

    return true;
}

CreateCloseDeferredPaymentRequestOpFrame::
    CreateCloseDeferredPaymentRequestOpFrame(Operation const& op,
                                             OperationResult& res,
                                             TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateCloseDeferredPaymentRequest(
          op.body.createCloseDeferredPaymentRequestOp())
{
}

bool
CreateCloseDeferredPaymentRequestOpFrame::doApply(Application& app,
                                                  StorageHelper& storageHelper,
                                                  LedgerManager& ledgerManager)
{
    if (mCreateCloseDeferredPaymentRequest.requestID == 0)
    {
        return createRequest(app, storageHelper, ledgerManager);
    }

    return updateRequest(app, storageHelper, ledgerManager);
}

bool
CreateCloseDeferredPaymentRequestOpFrame::createRequest(Application& app,
                                                        StorageHelper& sh,
                                                        LedgerManager& lm)
{
    if (!sh.getAccountHelper().exists(
            mCreateCloseDeferredPaymentRequest.request.destination))
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::
                           DESTINATION_ACCOUNT_NOT_FOUND);
        return false;
    }

    auto deferredPayment = sh.getDeferredPaymentHelper().loadDeferredPayment(
        mCreateCloseDeferredPaymentRequest.request.deferredPaymentID);

    // We already checked deferred payment existence, but to be extra sure

    if (!deferredPayment)
    {
        throw std::runtime_error("Expected deferred payment to exist");
    }

    if (deferredPayment->getDeferredPayment().amount <
        mCreateCloseDeferredPaymentRequest.request.amount)
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    auto& balanceHelper = sh.getBalanceHelper();
    // Source balance existence was checked on deferred payment creation. It is
    // not possible to remove balance with locked funds, so we are safe
    auto srcBalance = balanceHelper.loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);

    auto destBalance = balanceHelper.loadBalance(
        mCreateCloseDeferredPaymentRequest.request.destinationBalance);
    if (!destBalance)
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::
                           DESTINATION_BALANCE_NOT_FOUND);
        return false;
    }

    if (srcBalance->getAsset() != destBalance->getAsset())
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::ASSET_MISMATCH);
        return false;
    }

    auto assetFrame =
        sh.getAssetHelper().loadActiveAsset(srcBalance->getAsset());
    if (mCreateCloseDeferredPaymentRequest.request.amount %
            assetFrame->getMinimumAmount() !=
        0)
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    if (!destinationCanBeFunded(
            destBalance, mCreateCloseDeferredPaymentRequest.request.amount))
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::LINE_FULL);
        return false;
    }

    auto& requestHelper = sh.getReviewableRequestHelper();

    auto& delta = sh.mustGetLedgerDelta();
    const uint64 requestID =
        delta.getHeaderFrame().generateID(LedgerEntryType::REVIEWABLE_REQUEST);
    auto request = ReviewableRequestFrame::createNew(
        requestID, getSourceID(), app.getAdminID(), nullptr, lm.getCloseTime());

    auto& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    requestEntry.body.closeDeferredPaymentRequest() =
        mCreateCloseDeferredPaymentRequest.request;
    request->recalculateHashRejectReason();

    auto& kvHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!kvHelper.loadTasks(allTasks, makeTasksKeyVector(assetFrame->getCode()),
                            mCreateCloseDeferredPaymentRequest.allTasks.get()))
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::TASKS_NOT_FOUND);
        return false;
    }

    request->setTasks(allTasks);
    requestHelper.storeAdd(request->mEntry);

    // fixme autoapprove

    pickResultCode(CreateCloseDeferredPaymentRequestResultCode::SUCCESS);

    innerResult().success().requestID = requestID;
    innerResult().success().deferredPaymentID = 0;
    innerResult().success().fulfilled = false;
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    return true;
}

bool
CreateCloseDeferredPaymentRequestOpFrame::updateRequest(Application& app,
                                                        StorageHelper& sh,
                                                        LedgerManager& lm)
{
    if (!sh.getAccountHelper().exists(
            mCreateCloseDeferredPaymentRequest.request.destination))
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::
                           DESTINATION_ACCOUNT_NOT_FOUND);
        return false;
    }

    auto deferredPayment = sh.getDeferredPaymentHelper().loadDeferredPayment(
        mCreateCloseDeferredPaymentRequest.request.deferredPaymentID);

    // We already checked deferred payment existence, but to be extra sure

    if (!deferredPayment)
    {
        throw std::runtime_error("Expected deferred payment to exist");
    }

    if (deferredPayment->getDeferredPayment().amount <
        mCreateCloseDeferredPaymentRequest.request.amount)
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    auto& balanceHelper = sh.getBalanceHelper();
    // Source balance existence was checked on deferred payment creation. It
    // is not possible to remove balance with locked funds, so we are safe
    auto srcBalance = balanceHelper.loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);

    auto destBalance = balanceHelper.loadBalance(
        mCreateCloseDeferredPaymentRequest.request.destinationBalance);
    if (!destBalance)
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::
                           DESTINATION_BALANCE_NOT_FOUND);
        return false;
    }

    if (srcBalance->getAsset() != destBalance->getAsset())
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::ASSET_MISMATCH);
        return false;
    }

    auto assetFrame =
        sh.getAssetHelper().loadActiveAsset(srcBalance->getAsset());
    if (mCreateCloseDeferredPaymentRequest.request.amount %
            assetFrame->getMinimumAmount() !=
        0)
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    if (!destinationCanBeFunded(
            destBalance, mCreateCloseDeferredPaymentRequest.request.amount))
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::LINE_FULL);
        return false;
    }

    auto& requestHelper = sh.getReviewableRequestHelper();

    auto request =
        requestHelper.loadRequest(mCreateCloseDeferredPaymentRequest.requestID);
    auto closeDeferredPayment =
        request->getRequestEntry().body.closeDeferredPaymentRequest();

    closeDeferredPayment.sequenceNumber++;
    closeDeferredPayment.destinationBalance =
        mCreateCloseDeferredPaymentRequest.request.destinationBalance;
    closeDeferredPayment.deferredPaymentID =
        mCreateCloseDeferredPaymentRequest.request.deferredPaymentID;
    closeDeferredPayment.destination =
        mCreateCloseDeferredPaymentRequest.request.destination;
    closeDeferredPayment.creatorDetails =
        mCreateCloseDeferredPaymentRequest.request.creatorDetails;
    closeDeferredPayment.feeData =
        mCreateCloseDeferredPaymentRequest.request.feeData;
    closeDeferredPayment.amount =
        mCreateCloseDeferredPaymentRequest.request.amount;

    request->recalculateHashRejectReason();
    requestHelper.storeChange(request->mEntry);

    // fixme autoapprove

    pickResultCode(CreateCloseDeferredPaymentRequestResultCode::SUCCESS);

    innerResult().success().requestID = request->getRequestID();
    innerResult().success().deferredPaymentID =
        deferredPayment->getDeferredPayment().id;
    innerResult().success().fulfilled = false;
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    return true;
}

bool
CreateCloseDeferredPaymentRequestOpFrame::tryAutoApprove(
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
    innerResult().success().extendedResult.activate() =
        result.success().typeExt.closeDeferredPaymentResult();
    innerResult().success().deferredPaymentID =
        result.success()
            .typeExt.createDeferredPaymentResult()
            .deferredPaymentID;

    return true;
}

bool
CreateCloseDeferredPaymentRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateCloseDeferredPaymentRequest.request.creatorDetails.empty() ||
        !isValidJson(mCreateCloseDeferredPaymentRequest.request.creatorDetails))
    {
        pickResultCode(CreateCloseDeferredPaymentRequestResultCode::
                           INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mCreateCloseDeferredPaymentRequest.request.amount == 0)
    {
        pickResultCode(
            CreateCloseDeferredPaymentRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    return true;
}

void
CreateCloseDeferredPaymentRequestOpFrame::pickResultCode(
    CreateCloseDeferredPaymentRequestResultCode code)
{
    innerResult().code(code);
}

std::vector<std::string>
CreateCloseDeferredPaymentRequestOpFrame::makeTasksKeyVector(
    AssetCode const& code)
{
    return {
        ManageKeyValueOpFrame::makeCreateDeferredPaymentCloseTasksKey(code),
        ManageKeyValueOpFrame::makeCreateDeferredPaymentCloseTasksKey("*"),
    };
}

bool
CreateCloseDeferredPaymentRequestOpFrame::destinationCanBeFunded(
    BalanceFrame::pointer destBalance, uint64_t amount)
{
    uint64_t updatedAmount;
    if (!safeSum(destBalance->getAmount(), amount, updatedAmount))
    {
        return false;
    }

    uint64_t totalFunds;
    if (!safeSum(updatedAmount, destBalance->getLocked(), totalFunds))
    {
        return false;
    }

    return true;
}

bool
CreateCloseDeferredPaymentRequestOpFrame::isAuthorized(
    DeferredPaymentFrame::pointer deferredPayment)
{
    return (deferredPayment->getDeferredPayment().source == getSourceID()) ||
           (deferredPayment->getDeferredPayment().destination == getSourceID());
}
}
