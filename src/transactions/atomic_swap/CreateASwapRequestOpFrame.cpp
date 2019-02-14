#include "main/Application.h"
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelperLegacy.h>
#include <ledger/KeyValueHelper.h>
#include "ledger/StorageHelper.h"
#include <ledger/ReviewableRequestFrame.h>
#include <transactions/FeesManager.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include <ledger/KeyValueHelperLegacy.h>
#include <ledger/AssetHelper.h>
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
    
    result.emplace_back(resource, "receive_from_atomic_swap", mSourceAccount);
    
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

    result.emplace_back(resource, "receive_from_atomic_swap");

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
CreateASwapRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                   LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto aSwapRequest = mCreateASwapRequest.request;

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(aSwapRequest.bidID,
                                                                       db, &delta);
    if (bidFrame == nullptr)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (bidFrame->getOwnerID() == getSourceID())
    {
        innerResult().code(
                CreateASwapRequestResultCode::CANNOT_CREATE_ASWAP_REQUEST_FOR_OWN_BID);
        return false;
    }

    if (bidFrame->isCancelled())
    {
        innerResult().code(CreateASwapRequestResultCode::BID_IS_CANCELLED);
        return false;
    }

    if (!bidFrame->hasQuoteAsset(aSwapRequest.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    // TODO: move asset requirements check to separate method
    auto baseAssetFrame = AssetHelperLegacy::Instance()->loadAsset(bidFrame->getBaseAsset(),
                                                             db);
    if (baseAssetFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected base asset to exist, asset code: "
                   << bidFrame->getBaseAsset();
        throw runtime_error("Unexpected state: expected base asset to exist");
    }

    if (!bidFrame->tryLockAmount(aSwapRequest.baseAmount))
    {
        innerResult().code(CreateASwapRequestResultCode::BID_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                          app.getAdminID(), nullptr,
                                                          ledgerManager.getCloseTime());

    auto& requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP);
    requestEntry.body.aSwapRequest() = mCreateASwapRequest.request;

    uint32_t allTasks = 0;
    if (!tryGetAtomicSwapTasks(db, allTasks))
    {
        return false;
    }
    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = allTasks;

    requestFrame->recalculateHashRejectReason();

    EntryHelperProvider::storeChangeEntry(delta, db, bidFrame->mEntry);
    EntryHelperProvider::storeAddEntry(delta, db, requestFrame->mEntry);

    innerResult().code(CreateASwapRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().bidOwnerID = bidFrame->getOwnerID();

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
