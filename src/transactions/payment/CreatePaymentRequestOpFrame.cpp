#include "CreatePaymentRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "main/Application.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"

namespace stellar 
{
CreatePaymentRequestOpFrame::CreatePaymentRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& tx)
        : OperationFrame(op, res, tx)
        , mCreatePaymentRequest(op.body.createPaymentRequestOp()) 
        , mPayment(mCreatePaymentRequest.request.paymentOp)
{
}

bool
CreatePaymentRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper, 
                                        std::vector<OperationCondition>& result) const 
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame = balanceHelper.loadBalance(mPayment.sourceBalanceID);
    if (!senderBalanceFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto destinationAccountFrame = tryLoadDestinationAccount(storageHelper);
    if (!destinationAccountFrame)
    {
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();
    result.emplace_back(resource, AccountRuleAction::RECEIVE_PAYMENT, destinationAccountFrame);

    resource.type(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreatePaymentRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                         std::vector<SignerRequirement>& result) const 
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame = balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();
    resource.reviewableRequest().tasksToRemove = 0;
	resource.reviewableRequest().tasksToAdd = 0;
	resource.reviewableRequest().allTasks = 0;
	if (mCreatePaymentRequest.allTasks)
	{
		resource.reviewableRequest().allTasks = *mCreatePaymentRequest.allTasks;
	}

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

AccountFrame::pointer
CreatePaymentRequestOpFrame::tryLoadDestinationAccount(StorageHelper &storageHelper) const
{
    AccountID accountID;
    switch (mPayment.destination.type())
    {
        case PaymentDestinationType::ACCOUNT:
        {
            accountID = mPayment.destination.accountID();
            break;
        }
        case PaymentDestinationType::BALANCE:
        {
            auto destinationBalanceFrame = storageHelper.getBalanceHelper().loadBalance(mPayment.destination.balanceID());
            if (!destinationBalanceFrame)
            {
                mResult.code(OperationResultCode::opNO_ENTRY);
                mResult.entryType() = LedgerEntryType::BALANCE;
                return nullptr;
            }

            accountID = destinationBalanceFrame->getAccountID();
            break;
        }
        default:
            throw std::runtime_error("Unexpected destination type on payment v2 when load account");
    }

    auto account = storageHelper.getAccountHelper().loadAccount(accountID);
    if (!account)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ACCOUNT;
        return nullptr;
    }

    return account;
}

bool 
CreatePaymentRequestOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm) 
{
    innerResult().code(CreatePaymentRequestResultCode::SUCCESS);

    auto& balanceHelper = sh.getBalanceHelper();

    auto sourceBalance = balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& keyValueHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(sourceBalance->getAsset()),
                                  mCreatePaymentRequest.allTasks.get()))
    {
        innerResult().code(CreatePaymentRequestResultCode::PAYMENT_TASKS_NOT_FOUND);
        return false;
    }

    ReviewableRequestEntry::_body_t body(ReviewableRequestType::MANAGE_OFFER);
    body.createPaymentRequest() = mCreatePaymentRequest.request;
    auto request = ReviewableRequestFrame::createNewWithHash(sh.mustGetLedgerDelta(), getSourceID(),
                                              app.getAdminID(), nullptr, body, lm.getCloseTime());
    request->setTasks(allTasks);

    auto requestHelper = ReviewableRequestHelper::Instance();
    Database& db = sh.getDatabase();
    LedgerDelta& delta = sh.mustGetLedgerDelta();
    if (!request->canBeFulfilled(lm)) 
    {
        requestHelper->storeAdd(delta, db, request->mEntry);
        return true;
    }

    tryAutoApprove(db, delta, app, request);

    return true;
}

void
CreatePaymentRequestOpFrame::tryAutoApprove(
        Database& db, LedgerDelta& delta, Application& app,
        ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx,
            app, ledgerManager, delta, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: "
                   "tryApproveRequest expected to be success, but was: "
                << xdr::xdr_to_string(result);
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled = true;
}

std::vector<std::string>
CreatePaymentRequestOpFrame::makeTasksKeyVector(AssetCode const& code)
{
    return {
        ManageKeyValueOpFrame::makePaymentTasksKey(code)
    };
}

bool
CreatePaymentRequestOpFrame::isDestinationFeeValid()
{
    uint64_t totalDestinationFee;
    if (!safeSum(mPayment.feeData.destinationFee.fixed, mPayment.feeData.destinationFee.percent,
                 totalDestinationFee)) 
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() = PaymentResultCode::INVALID_DESTINATION_FEE;
        return false;
    }

    if (mPayment.feeData.sourcePaysForDest)
        return true;

    if (mPayment.amount < totalDestinationFee) 
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() = PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE;
        return false;
    }

    return true;
}

bool
CreatePaymentRequestOpFrame::doCheckValid(Application &app) 
{
    if (mPayment.reference.length() > 64) 
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() = PaymentResultCode::MALFORMED;   
        return false;
    }

    if (!isDestinationFeeValid()) 
    {
        return false;
    }

    if (mPayment.destination.type() != PaymentDestinationType::BALANCE) 
    {
        return true;
    }

    if (mPayment.sourceBalanceID == mPayment.destination.balanceID()) 
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() = PaymentResultCode::MALFORMED;   
        return false;
    }

    return true;
}

}