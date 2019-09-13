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
                                            std::vector<SignerRequirement>& result) const
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
			mReviewRequest.requestID, storageHelper.getDatabase());
	if (!request || (request->getType() != ReviewableRequestType::CREATE_PAYMENT))
	{
		mResult.code(OperationResultCode::opNO_ENTRY);
		mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
		return false;
	}

    auto const& payment = request->getRequestEntry().body.createPaymentRequest().paymentOp;

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame = balanceHelper.mustLoadBalance(payment.sourceBalanceID);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetCode = assetFrame->getCode();
    details.assetType = assetFrame->getType();
	resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
	resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
	resource.reviewableRequest().allTasks = 0;

	result.emplace_back(resource, SignerRuleAction::REVIEW);

	return true;
}

bool 
ReviewPaymentRequestOpFrame::handleApprove(Application& app, LedgerDelta& delta,
        LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) 
{
    request->checkRequestType(ReviewableRequestType::CREATE_PAYMENT);

    Database& db = app.getDatabase();
    handleTasks(db, delta, request);

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

    StorageHelperImpl storageHelperImpl(db, &delta);
    StorageHelper& storageHelper = storageHelperImpl;
    auto requestor = storageHelper.getAccountHelper().mustLoadAccount(request->getRequestor());
    opFrame.setSourceAccountPtr(requestor);

    if (!opFrame.doCheckValid(app) || !opFrame.doApply(app, storageHelper, ledgerManager)) 
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
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}
}