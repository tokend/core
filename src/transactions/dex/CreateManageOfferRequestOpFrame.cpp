#include "CreateManageOfferRequestOpFrame.h"
#include "ManageOfferOpFrame.h"
#include "OfferValidator.h"
#include "ledger/ReviewableRequestFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"

namespace stellar 
{
CreateManageOfferRequestOpFrame::CreateManageOfferRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& tx)
        : OperationFrame(op, res, tx)
        , mCreateManageOfferRequest(op.body.createManageOfferRequestOp())
        , mValidator(OfferValidator(mCreateManageOfferRequest.request.op, tx))
{
    //mValidator = OfferValidator(mCreateManageOfferRequest.request.op, tx)
    const auto manageOffer = mCreateManageOfferRequest.request.op;
    if (manageOffer.orderBookID == ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID)
    {
        if (manageOffer.amount == 0)
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
        if (manageOffer.amount == 0)
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
    resource.reviewableRequest().details.requestType(ReviewableRequestType::MANAGE_OFFER);
    auto& details = resource.reviewableRequest().details.manageOffer();
    details.baseAssetCode = baseAsset->getCode();
    details.quoteAssetCode = quoteAsset->getCode();
    details.baseAssetType = baseAsset->getType();
    details.quoteAssetType = quoteAsset->getType();
    details.isBuy = mManageOffer.isBuy;
    details.manageAction = static_cast<uint64_t>(mManageAction);

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateManageOfferRequestOpFrame::tryGetSignerRequirements(
         StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(mManageOffer.baseBalance);
    auto quoteBalance = balanceHelper.mustLoadBalance(mManageOffer.quoteBalance);

    auto baseAsset = assetHelper.mustLoadAsset(baseBalance->getAsset());
    auto quoteAsset = assetHelper.mustLoadAsset(quoteBalance->getAsset());

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::MANAGE_OFFER);
    auto& details = resource.reviewableRequest().details.manageOffer();
    details.baseAssetCode = baseAsset->getCode();
    details.quoteAssetCode = quoteAsset->getCode();
    details.baseAssetType = baseAsset->getType();
    details.quoteAssetType = quoteAsset->getType();
    details.isBuy = mManageOffer.isBuy;
    details.manageAction = static_cast<uint64_t>(mManageAction);

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateManageOfferRequestOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm) 
{
    innerResult().code(CreateManageOfferRequestResultCode::SUCCESS);

    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(mManageOffer.baseBalance);
    auto quoteBalance = balanceHelper.mustLoadBalance(mManageOffer.quoteBalance);

    auto& keyValueHelper = sh.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(baseBalance->getAsset(), quoteBalance->getAsset()),
                                  mCreateManageOfferRequest.allTasks.get()))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_ASK_TASKS_NOT_FOUND);
        return false;
    }

    ReviewableRequestEntry::_body_t body(ReviewableRequestType::MANAGE_OFFER);
    body.manageOfferRequest() = mCreateManageOfferRequest.request;
    auto request = ReviewableRequestFrame::createNewWithHash(sh.mustGetLedgerDelta(), getSourceID(),
                                              app.getAdminID(), nullptr, body, lm.getCloseTime());
    request->setTasks(allTasks);

    auto requestHelper = ReviewableRequestHelper::Instance();
    if (!request.canBeFulfilled(lm)) 
    {
        requestHelper->storeAdd(request->mEntry);
        return true;
    }

    tryAutoApprove(db, delta, app, request);

    return true;
}

bool
CreateManageOfferRequestOpFrame::doCheckValid(Application& app) 
{
    auto res = mValidator.validate(app);
    if (res == ManageOfferResultCode::SUCCESS) {
        return true;
    }

    innerResult().code(CreateManageOfferRequestResultCode::INVALID_OFFER);
    innerResult().validationCode() = res;
    return false;
}

void
CreateManageOfferRequestOpFrame::tryAutoApprove(
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
    innerResult().success().askID = result.success().typeExt.atomicSwapAskExtended().askID;
}

std::vector<std::string>
CreateManageOfferRequestOpFrame::makeTasksKeyVector(AssetCode const& base, AssetCode const& quote) 
{
    return {
        mKeyMaker(base, quote),
        mKeyMaker(base, "*"),
        mKeyMaker("*", quote),
        mKeyMaker("*", "*")
    };
}

}