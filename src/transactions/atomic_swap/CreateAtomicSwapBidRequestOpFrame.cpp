#include "main/Application.h"
#include <ledger/AtomicSwapAskHelper.h>
#include <ledger/AssetHelperLegacy.h>
#include "ledger/StorageHelper.h"
#include <ledger/ReviewableRequestFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include "ledger/KeyValueHelper.h"
#include <ledger/AssetHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/dex/OfferManager.h>
#include "CreateAtomicSwapBidRequestOpFrame.h"

using namespace std;

namespace stellar
{
using xdr::operator==;

CreateAtomicSwapBidRequestOpFrame::CreateAtomicSwapBidRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateASwapRequest(mOperation.body.createAtomicSwapBidRequestOp())
{
}

bool
CreateAtomicSwapBidRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                             std::vector<OperationCondition>& result) const
{
    auto bid = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
        mCreateASwapRequest.request.askID, storageHelper.getDatabase());
    if (!bid)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ATOMIC_SWAP_ASK;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(bid->getBaseAsset());

    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = asset->getType();
    resource.asset().assetCode = asset->getCode();

    result.emplace_back(resource, AccountRuleAction::RECEIVE_ATOMIC_SWAP, mSourceAccount);

    return true;
}

bool
CreateAtomicSwapBidRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                            std::vector<SignerRequirement>& result) const
{
    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.loadAsset(mCreateASwapRequest.request.quoteAsset);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    resource.reviewableRequest().details.createAtomicSwapBidExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateAtomicSwapBidRequestOpFrame::tryFillRequest(ReviewableRequestEntry& requestEntry,
                                                  StorageHelper& storageHelper)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    requestEntry.body.createAtomicSwapBidRequest() = mCreateASwapRequest.request;

    uint32_t allTasks = 0;
    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector()))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND);
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = allTasks;

    return true;
}

AtomicSwapAskFrame::pointer
CreateAtomicSwapBidRequestOpFrame::loadAtomicSwapAsk(CreateAtomicSwapBidRequest atomicSwapRequest,
                                                     StorageHelper& storageHelper)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto bidFrame = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
        atomicSwapRequest.askID, db, &delta);
    if (!bidFrame)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND);
        return nullptr;
    }

    if (bidFrame->getOwnerID() == getSourceID())
    {
        innerResult().code(
            CreateAtomicSwapBidRequestResultCode::SOURCE_ACCOUNT_EQUALS_ASK_OWNER);
        return nullptr;
    }

    if (bidFrame->isCancelled())
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ASK_IS_CANCELLED);
        return nullptr;
    }

    return bidFrame;
}

bool
CreateAtomicSwapBidRequestOpFrame::checkAmounts(StorageHelper& storageHelper,
                                                AtomicSwapAskFrame::pointer const& bidFrame)
{
    auto& atomicSwapRequest = mCreateASwapRequest.request;
    auto& assetHelper = storageHelper.getAssetHelper();
    auto baseAssetFrame = assetHelper.mustLoadAsset(bidFrame->getBaseAsset());

    if (!baseAssetFrame->isAmountAppropriate(atomicSwapRequest.baseAmount))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    uint64_t price = bidFrame->getQuoteAssetPrice(atomicSwapRequest.quoteAsset);
    if (price == 0)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    auto quoteAsset = assetHelper.mustLoadAsset(atomicSwapRequest.quoteAsset);
    auto quoteAmount = OfferManager::calculateQuoteAmount(
        atomicSwapRequest.baseAmount, price, quoteAsset->getMinimumAmount());

    if (quoteAmount == 0)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::QUOTE_AMOUNT_OVERFLOWS);
        return false;
    }

    innerResult().success().quoteAmount = static_cast<uint64_t>(quoteAmount);
    return true;
}

bool
CreateAtomicSwapBidRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                           LedgerManager& ledgerManager)
{
    innerResult().code(CreateAtomicSwapBidRequestResultCode::SUCCESS);

    auto aSwapRequest = mCreateASwapRequest.request;

    auto bid = loadAtomicSwapAsk(aSwapRequest, storageHelper);
    if (!bid)
    {
        return false; // error codes are handled above
    }

    if (!checkAmounts(storageHelper, bid))
    {
        return false;
    }

    if (!bid->tryLockAmount(aSwapRequest.baseAmount))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ASK_UNDERFUNDED);
        return false;
    }

    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                          app.getAdminID(), nullptr, ledgerManager.getCloseTime());

    if (!tryFillRequest(requestFrame->getRequestEntry(), storageHelper))
    {
        return false;
    }

    requestFrame->recalculateHashRejectReason();

    Database& db = storageHelper.getDatabase();
    AtomicSwapAskHelper::Instance()->storeChange(delta, db, bid->mEntry);
    storageHelper.getReviewableRequestHelper().storeAdd(requestFrame->mEntry);

    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().askOwnerID = bid->getOwnerID();

    return true;
}

bool
CreateAtomicSwapBidRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateASwapRequest.request.askID == 0)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ASK_NOT_FOUND);
        return false;
    }

    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::INVALID_BASE_AMOUNT);
        return false;
    }

    if (!AssetFrame::isAssetCodeValid(mCreateASwapRequest.request.quoteAsset))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET);
        return false;
    }

    return true;
}

std::vector<std::string>
CreateAtomicSwapBidRequestOpFrame::makeTasksKeyVector()
{
    return {ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey(mCreateASwapRequest.request.quoteAsset),
            ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey("*")};
}

}
