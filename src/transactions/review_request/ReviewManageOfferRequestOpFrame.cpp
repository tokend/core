#include "ReviewManageOfferRequestOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"
#include "transactions/dex/CreateManageOfferRequestOpFrame.h"
#include "transactions/dex/ManageOfferOpFrame.h"

namespace stellar
{
ReviewManageOfferRequestOpFrame::ReviewManageOfferRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& tx)
    : ReviewRequestOpFrame(op, res, tx)
{
}

bool
ReviewManageOfferRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
        mReviewRequest.requestID, storageHelper.getDatabase());
    if (!request || (request->getType() != ReviewableRequestType::MANAGE_OFFER))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto const& manageOffer =
        request->getRequestEntry().body.manageOfferRequest().op;

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(manageOffer.baseBalance);
    auto quoteBalance = balanceHelper.mustLoadBalance(manageOffer.quoteBalance);

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
    details.isBuy = manageOffer.isBuy;
    details.manageAction =
        static_cast<uint64_t>(getManageOfferAction(manageOffer));
    resource.reviewableRequest().tasksToAdd =
        mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove =
        mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

ManageOfferAction
ReviewManageOfferRequestOpFrame::getManageOfferAction(
    ManageOfferOp const& op) const
{
    if (op.orderBookID == ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID)
    {
        if (op.amount == 0)
        {
            return ManageOfferAction::REMOVE;
        }

        return ManageOfferAction::CREATE;
    }

    if (op.amount == 0)
    {
        return ManageOfferAction::REMOVE_PARTICIPATION;
    }

    return ManageOfferAction::CREATE_PARTICIPATION;
}

bool
ReviewManageOfferRequestOpFrame::handleApprove(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::MANAGE_OFFER);

    Database& db = app.getDatabase();
    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto requestBody = request->getRequestEntry().body.manageOfferRequest();

    Operation op;
    op.body.type(OperationType::MANAGE_OFFER);
    op.body.manageOfferOp() = requestBody.op;
    op.sourceAccount.activate() = request->getRequestor();

    OperationResult res;
    res.code(OperationResultCode::opINNER);
    res.tr().type(OperationType::MANAGE_OFFER);

    ManageOfferOpFrame& opFrame = *ManageOfferOpFrame::make(op, res, mParentTx);

    StorageHelperImpl storageHelperImpl(db, &delta);
    StorageHelper& storageHelper = storageHelperImpl;
    auto requestor = storageHelper.getAccountHelper().mustLoadAccount(
        request->getRequestor());
    opFrame.setSourceAccountPtr(requestor);

    if (!opFrame.doCheckValid(app) ||
        !opFrame.doApply(app, delta, ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::MANAGE_OFFER_FAILED);
        innerResult().manageOfferCode() = opFrame.getInnerCode();
        return false;
    }

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::MANAGE_OFFER);
    innerResult().success().typeExt.manageOfferResult() =
        res.tr().manageOfferResult();
    return true;
}

bool
ReviewManageOfferRequestOpFrame::handleReject(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}
}