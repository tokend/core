#include "main/Application.h"
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelperLegacy.h>
#include "ledger/StorageHelper.h"
#include <ledger/ReviewableRequestFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include <ledger/KeyValueHelperLegacy.h>
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
        , mCreateASwapRequest(mOperation.body.createASwapRequestOp())
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

    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = asset->getType();
    resource.asset().assetCode = asset->getCode();

    result.emplace_back(resource, SignerRuleAction::RECEIVE_ATOMIC_SWAP);

    return true;
}

bool
CreateASwapRequestOpFrame::tryGetAtomicSwapTasks(Database& db, uint32_t &allTasks)
{
    auto aSwapKV = KeyValueHelperLegacy::Instance()->loadKeyValue(
            ManageKeyValueOpFrame::atomicSwapTasksPrefix, db);

    if (aSwapKV == nullptr)
    {
        innerResult().code(CreateASwapRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND);
        return false;
    }

    if (aSwapKV->getKeyValue().value.type() != KeyValueEntryType::UINT32)
    {
        throw std::runtime_error(
                "Unexpected database state, expected atomic swap tasks to be UINT32");
    }

    allTasks = aSwapKV->getKeyValue().value.ui32Value();
    return true;
}

bool
CreateASwapRequestOpFrame::tryFillRequest(ReviewableRequestEntry& requestEntry,
                                          Database& db)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP);
    requestEntry.body.aSwapRequest() = mCreateASwapRequest.request;

    uint32_t allTasks = 0;
    if (!tryGetAtomicSwapTasks(db, allTasks))
    {
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::ATOMIC_SWAP_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = allTasks;

    return true;
}

AtomicSwapBidFrame::pointer
CreateASwapRequestOpFrame::loadAtomicSwapBid(ASwapRequest aSwapRequest,
                                             Database& db, LedgerDelta& delta)
{
    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapRequest.bidID, db, &delta);
    if (!bidFrame)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return nullptr;
    }

    if (bidFrame->getOwnerID() == getSourceID())
    {
        innerResult().code(
                CreateASwapRequestResultCode::CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID);
        return nullptr;
    }

    if (bidFrame->isCancelled())
    {
        innerResult().code(CreateASwapRequestResultCode::BID_IS_CANCELLED);
        return nullptr;
    }

    uint64_t price = bidFrame->getQuoteAssetPrice(aSwapRequest.quoteAsset);
    if (price == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return nullptr;
    }

    auto quoteAsset = AssetHelperLegacy::Instance()->mustLoadAsset(aSwapRequest.quoteAsset, db);
    auto quoteAmount = OfferManager::calculateQuoteAmount(
            aSwapRequest.baseAmount, price, quoteAsset->getMinimumAmount());
    innerResult().success().quoteAmount = static_cast<uint64_t>(quoteAmount);

    return bidFrame;
}

bool
CreateASwapRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                   LedgerManager& ledgerManager)
{
    innerResult().code(CreateASwapRequestResultCode::SUCCESS);

    Database& db = ledgerManager.getDatabase();
    auto aSwapRequest = mCreateASwapRequest.request;

    auto bid = loadAtomicSwapBid(aSwapRequest, db, delta);
    if (!bid)
    {
        return false; // error codes are handled above
    }

    auto baseAssetFrame = AssetHelperLegacy::Instance()->mustLoadAsset(bid->getBaseAsset(), db);
    if (!baseAssetFrame->isAmountAppropriate(aSwapRequest.baseAmount))
    {
        innerResult().code(CreateASwapRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    if (!bid->tryLockAmount(aSwapRequest.baseAmount))
    {
        innerResult().code(CreateASwapRequestResultCode::BID_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());

    if (!tryFillRequest(requestFrame->getRequestEntry(), db))
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
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_BASE_AMOUNT);
        return false;
    }

    if (!AssetFrame::isAssetCodeValid(mCreateASwapRequest.request.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_QUOTE_ASSET);
        return false;
    }

    return true;
}

}
