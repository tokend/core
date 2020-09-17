#include "CancelCloseDeferredPaymentRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include <ledger/AssetHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>

namespace stellar
{
using xdr::operator==;

CancelCloseDeferredPaymentRequestOpFrame::
    CancelCloseDeferredPaymentRequestOpFrame(
        const stellar::Operation& op, stellar::OperationResult& res,
        stellar::TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCancelCloseDeferredPaymentRequest(
          mOperation.body.cancelCloseDeferredPaymentRequestOp())
{
}

bool
CancelCloseDeferredPaymentRequestOpFrame::tryGetOperationConditions(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::OperationCondition>& result) const
{
    // only request creator can remove it
    return true;
}

bool
CancelCloseDeferredPaymentRequestOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);

    auto& request =
        storageHelper.getReviewableRequestHelper()
            .loadRequest(mCancelCloseDeferredPaymentRequest.requestID)
            ->getRequestEntry()
            .body.closeDeferredPaymentRequest();

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.loadBalance(request.destinationBalance);
    if (!balanceFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }
    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(balanceFrame->getAsset());

    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.closeDeferredPayment().assetType =
        assetFrame->getType();
    resource.reviewableRequest().details.closeDeferredPayment().assetCode =
        assetFrame->getCode();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelCloseDeferredPaymentRequestOpFrame::doApply(Application& app,
                                                  StorageHelper& storageHelper,
                                                  LedgerManager& ledgerManager)
{
    auto const requestID = mCancelCloseDeferredPaymentRequest.requestID;
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto requestFrame = requestHelper.loadRequest(
        requestID, getSourceID(),
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    if (!requestFrame)
    {
        innerResult().code(
            CancelCloseDeferredPaymentRequestResultCode::NOT_FOUND);
        return false;
    }

    requestHelper.storeDelete(requestFrame->getKey());

    innerResult().code(CancelCloseDeferredPaymentRequestResultCode::SUCCESS);
    return true;
}

bool
CancelCloseDeferredPaymentRequestOpFrame::doCheckValid(Application& app)
{
    if (mCancelCloseDeferredPaymentRequest.requestID == 0)
    {
        innerResult().code(
            CancelCloseDeferredPaymentRequestResultCode::NOT_FOUND);
        return false;
    }

    return true;
}
}
