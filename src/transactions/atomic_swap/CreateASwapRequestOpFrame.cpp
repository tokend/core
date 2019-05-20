#include "main/Application.h"
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelperLegacy.h>
#include "ledger/StorageHelper.h"
#include <ledger/ReviewableRequestFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include "ledger/KeyValueHelper.h"
#include <ledger/AssetHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/dex/OfferManager.h>
#include "CreateASwapRequestOpFrame.h"

using namespace std;

namespace stellar
{
using xdr::operator==;

CreateASwapRequestOpFrame::CreateASwapRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateASwapRequest(mOperation.body.createAtomicSwapAskRequestOp())
{
}

bool
CreateASwapRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const
{ 
    auto bid = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            mCreateASwapRequest.request.bidID, storageHelper.getDatabase());
    if (!bid) 
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ATOMIC_SWAP_BID;
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
CreateASwapRequestOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                    std::vector<SignerRequirement> &result) const
{
    auto bid = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            mCreateASwapRequest.request.bidID, storageHelper.getDatabase());
    if (!bid)
    {
        throw std::runtime_error("Expected bid to exists");
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(bid->getBaseAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    resource.reviewableRequest().details.createAtomicSwapAskExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateASwapRequestOpFrame::tryFillRequest(ReviewableRequestEntry& requestEntry,
                                          StorageHelper& storageHelper)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    requestEntry.body.createAtomicSwapAskRequest() = mCreateASwapRequest.request;

    uint32_t allTasks = 0;
    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!keyValueHelper.loadTasks(allTasks, {ManageKeyValueOpFrame::makeAtomicSwapTasksKey()}))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND);
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = allTasks;

    return true;
}

AtomicSwapBidFrame::pointer
CreateASwapRequestOpFrame::loadAtomicSwapBid(CreateAtomicSwapAskRequest atomicSwapRequest,
                                             Database& db, LedgerDelta& delta)
{
    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            atomicSwapRequest.bidID, db, &delta);
    if (!bidFrame)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BID_NOT_FOUND);
        return nullptr;
    }

    if (bidFrame->getOwnerID() == getSourceID())
    {
        innerResult().code(
                CreateAtomicSwapAskRequestResultCode::SOURCE_ACCOUNT_EQUALS_BID_OWNER);
        return nullptr;
    }

    if (bidFrame->isCancelled())
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BID_IS_CANCELLED);
        return nullptr;
    }

    return bidFrame;
}

bool
CreateASwapRequestOpFrame::checkAmounts(StorageHelper& storageHelper,
        AtomicSwapBidFrame::pointer const& bidFrame)
{
    auto& atomicSwapRequest = mCreateASwapRequest.request;
    auto& assetHelper = storageHelper.getAssetHelper();
    auto baseAssetFrame = assetHelper.mustLoadAsset(bidFrame->getBaseAsset());

    if (!baseAssetFrame->isAmountAppropriate(atomicSwapRequest.baseAmount))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    uint64_t price = bidFrame->getQuoteAssetPrice(atomicSwapRequest.quoteAsset);
    if (price == 0)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    auto quoteAsset = assetHelper.mustLoadAsset(atomicSwapRequest.quoteAsset);
    auto quoteAmount = OfferManager::calculateQuoteAmount(
            atomicSwapRequest.baseAmount, price, quoteAsset->getMinimumAmount());

     if (quoteAmount == 0)
     {
         innerResult().code(CreateAtomicSwapAskRequestResultCode::QUOTE_AMOUNT_OVERFLOWS);
         return false;
     }

    innerResult().success().quoteAmount = static_cast<uint64_t>(quoteAmount);
    return true;
}

bool
CreateASwapRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                   LedgerManager& ledgerManager)
{
    innerResult().code(CreateAtomicSwapAskRequestResultCode::SUCCESS);

    Database& db = storageHelper.getDatabase();
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto aSwapRequest = mCreateASwapRequest.request;

    auto bid = loadAtomicSwapBid(aSwapRequest, db, delta);
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
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BID_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());

    if (!tryFillRequest(requestFrame->getRequestEntry(), storageHelper))
    {
        return false;
    }

    requestFrame->recalculateHashRejectReason();

    AtomicSwapBidHelper::Instance()->storeChange(delta, db, bid->mEntry);
    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().bidOwnerID = bid->getOwnerID();

    return true;
}

bool
CreateASwapRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateASwapRequest.request.bidID == 0)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::INVALID_BASE_AMOUNT);
        return false;
    }

    if (!AssetFrame::isAssetCodeValid(mCreateASwapRequest.request.quoteAsset))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET);
        return false;
    }

    return true;
}

}
