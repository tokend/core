#include "main/Application.h"
#include <database/Database.h>
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include "CancelASwapBidOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"

using namespace std;

namespace stellar
{

CancelASwapBidOpFrame::CancelASwapBidOpFrame(Operation const &op, OperationResult &opRes,
                                             TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx),
          mCancelASwapBid(mOperation.body.cancelASwapBidOp())
{
}

bool
CancelASwapBidOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                 std::vector<OperationCondition> &result) const
{
    // only bid owner can do this
    return true;
}

bool
CancelASwapBidOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                    std::vector<SignerRequirement> &result) const
{
    auto bid = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            mCancelASwapBid.bidID, storageHelper.getDatabase());
    if (!bid)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ATOMIC_SWAP_BID;
        return false;
    }

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(bid->getBaseAsset());
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::ATOMIC_SWAP_BID);
    resource.atomicSwapBid().assetCode = asset->getCode();
    resource.atomicSwapBid().assetType = asset->getType();

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool CancelASwapBidOpFrame::doApply(Application &app, LedgerDelta &delta,
                                    LedgerManager &ledgerManager)
{
    innerResult().code(CancelASwapBidResultCode::SUCCESS);
    Database& db = app.getDatabase();

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            getSourceID(), mCancelASwapBid.bidID, db, &delta);
    if (bidFrame == nullptr)
    {
        innerResult().code(CancelASwapBidResultCode::NOT_FOUND);
        return false;
    }

    if (bidFrame->isCancelled())
    {
        innerResult().code(CancelASwapBidResultCode::ALREADY_CANCELLED);
        return false;
    }

    innerResult().success().lockedAmount = bidFrame->getLockedAmount();
    if (bidFrame->getLockedAmount() != 0)
    {
        bidFrame->setIsCancelled(true);
        EntryHelperProvider::storeChangeEntry(delta, db, bidFrame->mEntry);
        return true;
    }

    auto bidOwnerBalanceFrame = BalanceHelperLegacy::Instance()->mustLoadBalance(
            bidFrame->getOwnerID(), bidFrame->getBaseAsset(), db, &delta);

    if (bidOwnerBalanceFrame->unlock(bidFrame->getAmount()) != BalanceFrame::Result ::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in bid owner balance, "
                   "bid ID: " << bidFrame->getBidID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in bid owner balance");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, bidOwnerBalanceFrame->mEntry);
    EntryHelperProvider::storeDeleteEntry(delta, db, bidFrame->getKey());

    return true;
}

bool CancelASwapBidOpFrame::doCheckValid(Application &app)
{
    if (mCancelASwapBid.bidID == 0)
    {
        innerResult().code(CancelASwapBidResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

}