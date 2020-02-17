#include "CreateManageOfferRequestOpFrame.h"
#include "ManageOfferOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"

namespace stellar
{
CreateManageOfferRequestOpFrame::CreateManageOfferRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : OperationFrame(op, res, tx)
    , mCreateManageOfferRequest(op.body.createManageOfferRequestOp())
    , mManageOffer(mCreateManageOfferRequest.request.op)
    , mValidator(std::make_unique<OfferValidator>(mManageOffer, tx))
{
    if (mManageOffer.orderBookID ==
        ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID)
    {
        if (mManageOffer.amount == 0)
        {
            mManageAction = ManageOfferAction::REMOVE;
            mKeyMaker = ManageKeyValueOpFrame::makeDeleteOfferKey;
        }
        else
        {
            mManageAction = ManageOfferAction::CREATE;
            mKeyMaker = ManageKeyValueOpFrame::makeCreateOfferKey;
        }
    }
    else
    {
        if (mManageOffer.amount == 0)
        {
            mManageAction = ManageOfferAction::REMOVE_PARTICIPATION;
            mKeyMaker = ManageKeyValueOpFrame::makeDeleteSaleParticipationKey;
        }
        else
        {
            mManageAction = ManageOfferAction::CREATE_PARTICIPATION;
            mKeyMaker = ManageKeyValueOpFrame::makeCreateSaleParticipationKey;
        }
    }
}

bool
CreateManageOfferRequestOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.loadBalance(mManageOffer.baseBalance);
    if (!baseBalance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto quoteBalance = balanceHelper.loadBalance(mManageOffer.quoteBalance);
    if (!quoteBalance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto baseAsset = assetHelper.mustLoadAsset(baseBalance->getAsset());
    auto quoteAsset = assetHelper.mustLoadAsset(quoteBalance->getAsset());

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::MANAGE_OFFER);
    auto& details = resource.reviewableRequest().details.manageOffer();
    details.baseAssetCode = baseAsset->getCode();
    details.quoteAssetCode = quoteAsset->getCode();
    details.baseAssetType = baseAsset->getType();
    details.quoteAssetType = quoteAsset->getType();
    details.isBuy = mManageOffer.isBuy;
    details.orderBookID = mManageOffer.orderBookID;
    details.manageAction = static_cast<uint64_t>(mManageAction);

    AccountRuleAction action = AccountRuleAction::CREATE;
    if (mCreateManageOfferRequest.allTasks)
    {
        action = AccountRuleAction::CREATE_WITH_TASKS;
    }

    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
CreateManageOfferRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(mManageOffer.baseBalance);
    auto quoteBalance =
        balanceHelper.mustLoadBalance(mManageOffer.quoteBalance);

    auto baseAsset = assetHelper.mustLoadAsset(baseBalance->getAsset());
    auto quoteAsset = assetHelper.mustLoadAsset(quoteBalance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::MANAGE_OFFER);
    auto& details = resource.reviewableRequest().details.manageOffer();
    details.baseAssetCode = baseAsset->getCode();
    details.quoteAssetCode = quoteAsset->getCode();
    details.baseAssetType = baseAsset->getType();
    details.quoteAssetType = quoteAsset->getType();
    details.isBuy = mManageOffer.isBuy;
    details.manageAction = static_cast<uint64_t>(mManageAction);
    details.orderBookID = mManageOffer.orderBookID;
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    SignerRuleAction action = SignerRuleAction::CREATE;
    if (mCreateManageOfferRequest.allTasks)
    {
        action = SignerRuleAction::CREATE_WITH_TASKS;
        resource.reviewableRequest().allTasks =
            *mCreateManageOfferRequest.allTasks;
    }

    result.emplace_back(resource, action);

    return true;
}

bool
CreateManageOfferRequestOpFrame::doApply(Application& app, StorageHelper& sh,
                                         LedgerManager& lm)
{
    innerResult().code(CreateManageOfferRequestResultCode::SUCCESS);

    auto& balanceHelper = sh.getBalanceHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(mManageOffer.baseBalance);
    auto quoteBalance =
        balanceHelper.mustLoadBalance(mManageOffer.quoteBalance);

    auto& keyValueHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks,
                                  makeTasksKeyVector(baseBalance->getAsset(),
                                                     quoteBalance->getAsset()),
                                  mCreateManageOfferRequest.allTasks.get()))
    {
        innerResult().code(
            CreateManageOfferRequestResultCode::MANAGE_OFFER_TASKS_NOT_FOUND);
        return false;
    }

    ReviewableRequestEntry::_body_t body(ReviewableRequestType::MANAGE_OFFER);
    body.manageOfferRequest() = mCreateManageOfferRequest.request;
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
        innerResult().success().fulfilled = false;
        innerResult().success().requestID = request->getRequestID();
        return true;
    }

    return tryAutoApprove(app, sh, request);
}

bool
CreateManageOfferRequestOpFrame::doCheckValid(Application& app)
{

    if (app.getLedgerManager().shouldUse(
            LedgerVersion::MOVEMENT_REQUESTS_DETAILS))
    {
        switch (mCreateManageOfferRequest.request.ext.v())
        {
        case LedgerVersion::EMPTY_VERSION:
            break;
        case LedgerVersion::MOVEMENT_REQUESTS_DETAILS:
            if (!isValidJson(
                    mCreateManageOfferRequest.request.ext.creatorDetails()))
            {
                innerResult().code(CreateManageOfferRequestResultCode ::
                                       INVALID_CREATOR_DETAILS);
                return false;
            }
            break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected manage offer request version"
                                                   << static_cast<int32_t>(mCreateManageOfferRequest.request.ext.v());
            throw std::runtime_error("Unexpected payment request version");

        }
    }

    auto res = mValidator->validate(app);
    if (res == ManageOfferResultCode::SUCCESS)
    {
        return true;
    }

    innerResult().code(CreateManageOfferRequestResultCode::INVALID_OFFER);
    innerResult().manageOfferCode() = res;
    return false;
}

bool
CreateManageOfferRequestOpFrame::tryAutoApprove(
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
        innerResult().code(CreateManageOfferRequestResultCode::INVALID_OFFER);
        innerResult().manageOfferCode() = result.manageOfferCode();
        return false;
    }

    innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = true;
    innerResult().success().manageOfferResult.activate() =
        result.success().typeExt.manageOfferResult();
    return true;
}

std::vector<std::string>
CreateManageOfferRequestOpFrame::makeTasksKeyVector(AssetCode const& base,
                                                    AssetCode const& quote)
{
    return {mKeyMaker(base, quote), mKeyMaker(base, "*"), mKeyMaker("*", quote),
            mKeyMaker("*", "*")};
}

}