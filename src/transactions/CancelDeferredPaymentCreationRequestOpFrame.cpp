#include "CancelDeferredPaymentCreationRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include <ledger/AssetHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>

namespace stellar
{
using xdr::operator==;

CancelDeferredPaymentCreationRequestOpFrame::
    CancelDeferredPaymentCreationRequestOpFrame(
        const stellar::Operation& op, stellar::OperationResult& res,
        stellar::TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelDeferredPaymentCreationRequest(
          mOperation.body.cancelDeferredPaymentCreationRequestOp())
{
}

bool
CancelDeferredPaymentCreationRequestOpFrame::tryGetOperationConditions(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::OperationCondition>& result) const
{
    // only request creator can remove it
    return true;
}

bool
CancelDeferredPaymentCreationRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);

    auto& request =
        storageHelper.getReviewableRequestHelper()
            .loadRequest(mCancelDeferredPaymentCreationRequest.requestID)
            ->getRequestEntry()
            .body.createDeferredPaymentRequest();

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto srcBalanceFrame = balanceHelper.loadBalance(request.sourceBalance);
    if (!srcBalanceFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }
    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(srcBalanceFrame->getAsset());

    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.createDeferredPayment().assetType =
        assetFrame->getType();
    resource.reviewableRequest().details.createDeferredPayment().assetCode =
        assetFrame->getCode();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelDeferredPaymentCreationRequestOpFrame::doApply(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager)
{
    auto const requestID = mCancelDeferredPaymentCreationRequest.requestID;
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto requestFrame = requestHelper.loadRequest(
        requestID, getSourceID(),
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    if (!requestFrame)
    {
        innerResult().code(
            CancelDeferredPaymentCreationRequestResultCode::NOT_FOUND);
        return false;
    }

    auto& request =
        requestFrame->getRequestEntry().body.createDeferredPaymentRequest();

    auto srcBalance = request.sourceBalance;

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto srcBalanceFrame = balanceHelper.loadBalance(request.sourceBalance);

    auto result = srcBalanceFrame->unlock(request.amount);
    switch (result)
    {
    case BalanceFrame::Result::NONMATCHING_PRECISION:
    {
        throw std::runtime_error("Unexpected state: failed to unlock amount on "
                                 "balance - nonmatching precision");
    }
    case BalanceFrame::Result::UNDERFUNDED:
    {
        throw std::runtime_error("Unexpected state: failed to unlock amount on "
                                 "balance - underfunded");
    }
    case BalanceFrame::Result::LINE_FULL:
    {
        innerResult().code(
            CancelDeferredPaymentCreationRequestResultCode::LINE_FULL);
        return false;
    }
    }

    balanceHelper.storeChange(srcBalanceFrame->mEntry);
    requestHelper.storeDelete(requestFrame->getKey());

    innerResult().code(CancelDeferredPaymentCreationRequestResultCode::SUCCESS);
    return true;
}

bool
CancelDeferredPaymentCreationRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelDeferredPaymentCreationRequest.requestID == 0)
    {
        innerResult().code(
            CancelDeferredPaymentCreationRequestResultCode::REQUEST_ID_INVALID);
        return false;
    }

    return true;
}
}
