#include "CreatePaymentRequestOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"

namespace stellar
{
CreatePaymentRequestOpFrame::CreatePaymentRequestOpFrame(Operation const& op,
                                                         OperationResult& res,
                                                         TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreatePaymentRequest(op.body.createPaymentRequestOp())
    , mPayment(mCreatePaymentRequest.request.paymentOp)
{
}

bool
CreatePaymentRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame =
        balanceHelper.loadBalance(mPayment.sourceBalanceID);
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
    result.emplace_back(resource, AccountRuleAction::RECEIVE_PAYMENT,
                        destinationAccountFrame);

    resource.type(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();
    AccountRuleAction action = AccountRuleAction::CREATE;
    if (mCreatePaymentRequest.allTasks)
    {
        action = AccountRuleAction::CREATE_WITH_TASKS;
    }

    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreatePaymentRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame =
        balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CREATE_PAYMENT);
    auto& details = resource.reviewableRequest().details.createPayment();
    details.assetType = assetFrame->getType();
    details.assetCode = assetFrame->getCode();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    SignerRuleAction action = SignerRuleAction::CREATE;
    if (mCreatePaymentRequest.allTasks)
    {
        action = SignerRuleAction::CREATE_WITH_TASKS;
        resource.reviewableRequest().allTasks = *mCreatePaymentRequest.allTasks;
    }

    result.emplace_back(resource, action);

    return true;
}

AccountFrame::pointer
CreatePaymentRequestOpFrame::tryLoadDestinationAccount(
    StorageHelper& storageHelper) const
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
        auto destinationBalanceFrame =
            storageHelper.getBalanceHelper().loadBalance(
                mPayment.destination.balanceID());
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
        throw std::runtime_error(
            "Unexpected destination type on payment v2 when load account");
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
CreatePaymentRequestOpFrame::doApply(Application& app, StorageHelper& sh,
                                     LedgerManager& lm)
{
    innerResult().code(CreatePaymentRequestResultCode::SUCCESS);

    auto& balanceHelper = sh.getBalanceHelper();

    auto sourceBalance =
        balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& keyValueHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks,
                                  makeTasksKeyVector(lm, sourceBalance->getAsset()),
                                  mCreatePaymentRequest.allTasks.get()))
    {
        innerResult().code(
            CreatePaymentRequestResultCode::PAYMENT_TASKS_NOT_FOUND);
        return false;
    }

    ReviewableRequestEntry::_body_t body(ReviewableRequestType::CREATE_PAYMENT);
    body.createPaymentRequest() = mCreatePaymentRequest.request;
    auto request = ReviewableRequestFrame::createNewWithHash(
        sh.mustGetLedgerDelta(), getSourceID(), app.getAdminID(), nullptr, body,
        lm.getCloseTime());
    request->setTasks(allTasks);

    auto& requestHelper = sh.getReviewableRequestHelper();
    Database& db = sh.getDatabase();
    LedgerDelta& delta = sh.mustGetLedgerDelta();
    requestHelper.storeAdd(request->mEntry);
    if (!request->canBeFulfilled(lm))
    {
        innerResult().success().requestID =
            request->getRequestEntry().requestID;
        innerResult().success().fulfilled = false;
        return true;
    }

    return tryAutoApprove(app, sh, request);
}

bool
CreatePaymentRequestOpFrame::tryAutoApprove(
    Application& app, StorageHelper& sh,
    ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(
        mParentTx, app, ledgerManager, sh, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(DEBUG, Logging::OPERATION_LOGGER)
            << "Unexpected state: "
               "tryApproveRequest expected to be success, but was: "
            << xdr::xdr_to_string(result);
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() = result.paymentCode();
        return false;
    }

    innerResult().success().fulfilled = true;
    innerResult().success().paymentResult.activate() =
        result.success().typeExt.paymentResult();
    return true;
}

std::vector<std::string>
CreatePaymentRequestOpFrame::makeTasksKeyVector(LedgerManager& lm, AssetCode const& code)
{
    std::vector<std::string> tasksKey;
    tasksKey.emplace_back(ManageKeyValueOpFrame::makePaymentTasksKey(code));
    if (lm.shouldUse(LedgerVersion::FIX_PAYMENT_TASKS_WILDCARD_VALUE)) {
        tasksKey.emplace_back(ManageKeyValueOpFrame::makePaymentTasksKey("*"));
    }

    return tasksKey;
}

bool
CreatePaymentRequestOpFrame::isDestinationFeeValid()
{
    uint64_t totalDestinationFee;
    if (!safeSum(mPayment.feeData.destinationFee.fixed,
                 mPayment.feeData.destinationFee.percent, totalDestinationFee))
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() =
            PaymentResultCode::INVALID_DESTINATION_FEE;
        return false;
    }

    if (mPayment.feeData.sourcePaysForDest)
        return true;

    if (mPayment.amount < totalDestinationFee)
    {
        innerResult().code(CreatePaymentRequestResultCode::INVALID_PAYMENT);
        innerResult().paymentCode() =
            PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE;
        return false;
    }

    return true;
}

bool
CreatePaymentRequestOpFrame::doCheckValid(Application& app)
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

    if (app.getLedgerManager().shouldUse(
            LedgerVersion::MOVEMENT_REQUESTS_DETAILS))
    {
        switch (mCreatePaymentRequest.request.ext.v()) {
        case LedgerVersion::EMPTY_VERSION:
            break;
        case LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
            if (!isValidJson(mCreatePaymentRequest.request.ext.creatorDetails())) {
                innerResult().code(CreatePaymentRequestResultCode::INVALID_CREATOR_DETAILS);
                return false;
            }
            break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected payment request version"
                << static_cast<int32_t>(mCreatePaymentRequest.request.ext.v());
            throw std::runtime_error("Unexpected payment request version");

        }
    }

    return true;
}

}