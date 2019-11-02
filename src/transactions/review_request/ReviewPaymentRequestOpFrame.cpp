#include "ReviewPaymentRequestOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "main/Application.h"
#include "ledger/AccountHelper.h"
#include "transactions/payment/PaymentOpFrame.h"

namespace stellar
{
ReviewPaymentRequestOpFrame::ReviewPaymentRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& tx)
        : ReviewRequestOpFrame(op, res, tx)
{
}

bool
ReviewPaymentRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                            std::vector<SignerRequirement>& result, LedgerManager& lm) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
			mReviewRequest.requestID);
	if (!request || (request->getType() != ReviewableRequestType::CREATE_PAYMENT))
	{
		mResult.code(OperationResultCode::opNO_ENTRY);
		mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
		return false;
	}

    auto const& payment = request->getRequestEntry().body.createPaymentRequest().paymentOp;

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    AssetFrame::pointer assetFrame;
    BalanceFrame::pointer senderBalanceFrame;
    if (!lm.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        senderBalanceFrame = balanceHelper.mustLoadBalance(payment.sourceBalanceID);
        assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());
    }
    else
    {

        senderBalanceFrame = balanceHelper.loadBalance(payment.sourceBalanceID);
        if (!senderBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;
            return false;
        }
        assetFrame =
            assetHelper.loadActiveAsset(senderBalanceFrame->getAsset());
        if (!assetFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::ASSET;
            return false;
        }
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetCode = assetFrame->getCode();
    details.assetType = assetFrame->getType();
    resource.reviewableRequest().tasksToAdd =
        mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove =
        mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool
ReviewPaymentRequestOpFrame::handleApprove(Application& app,  StorageHelper& sh,
        LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_PAYMENT);

    auto& requestHelper = sh.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto requestBody = request->getRequestEntry().body.createPaymentRequest();

    Operation op;
    op.body.type(OperationType::PAYMENT);
    op.body.paymentOp() = requestBody.paymentOp;
    op.sourceAccount.activate() = request->getRequestor();

    OperationResult res;
    res.code(OperationResultCode::opINNER);
    res.tr().type(OperationType::PAYMENT);

    PaymentOpFrame opFrame(op, res, mParentTx);

    auto requestor = sh.getAccountHelper().mustLoadAccount(request->getRequestor());
    opFrame.setSourceAccountPtr(requestor);

    if (!opFrame.doCheckValid(app) || !opFrame.doApply(app, sh, ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::PAYMENT_FAILED);
        innerResult().paymentCode() = PaymentOpFrame::getInnerCode(res);
        return false;
    }

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_PAYMENT);
    innerResult().success().typeExt.paymentResult().paymentResponse() = res.tr().paymentResult().paymentResponse();
    return true;
}

bool
ReviewPaymentRequestOpFrame::handleReject(
    Application& app, StorageHelper& sh, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}
}