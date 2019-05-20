#include <main/Application.h>
#include <database/Database.h>
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/dex/OfferManager.h>
#include <ledger/StorageHelperImpl.h>
#include <ledger/AssetHelper.h>
#include "ReviewASwapRequestOpFrame.h"

using namespace std;

namespace stellar
{

stellar::ReviewASwapRequestOpFrame::ReviewASwapRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewASwapRequestOpFrame::handleReject(Application &app, LedgerDelta &delta,
                                             LedgerManager &ledgerManager,
                                             ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

void ReviewASwapRequestOpFrame::removeBid(Database &db, LedgerDelta &delta,
                                          BalanceFrame::pointer bidOwnerBalance,
                                          AtomicSwapBidFrame::pointer bid)
{
    if (bidOwnerBalance->unlock(bid->getAmount()) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in bid owner balance, "
                   "bid ID: " << bid->getBidID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in bid owner balance");
    }
    EntryHelperProvider::storeChangeEntry(delta, db, bidOwnerBalance->mEntry);
    EntryHelperProvider::storeDeleteEntry(delta, db, bid->getKey());
}


bool
ReviewASwapRequestOpFrame::handlePermanentReject(Application &app, LedgerDelta &delta,
                                                 LedgerManager &ledgerManager,
                                                 ReviewableRequestFrame::pointer request)
{
    Database& db = app.getDatabase();
    auto& aSwapCreationRequest = request->getRequestEntry().body.createAtomicSwapAskRequest();

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapCreationRequest.bidID, db, &delta);

    if (bidFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected atomic swap bid to exist, bid ID: "
                << bidFrame->getBidID();
        throw runtime_error("Unexpected state: expected atomic swap bid to exist");
    }

    if (!bidFrame->tryUnlockAmount(aSwapCreationRequest.baseAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in atomic swap bid: "
                   "insufficient locked amount, atomic swap bid ID:"
                << bidFrame->getBidID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in atomic swap bid");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, bidFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    auto& aSwapExtended = innerResult().success().typeExt.atomicSwapAskExtended();
    aSwapExtended.unlockedAmount = 0;

    BalanceFrame::pointer bidOwnerBalance = BalanceHelperLegacy::Instance()->mustLoadBalance(
            bidFrame->getOwnerID(), bidFrame->getBaseAsset(), db, &delta);
    if (canRemoveBid(bidFrame))
    {
        removeBid(db, delta, bidOwnerBalance, bidFrame);
        aSwapExtended.unlockedAmount = bidFrame->getAmount();
    }

    aSwapExtended.bidID = bidFrame->getBidID();
    aSwapExtended.bidOwnerID = bidFrame->getOwnerID();
    aSwapExtended.askOwnerID = request->getRequestor();
    aSwapExtended.baseAsset = bidFrame->getBaseAsset();
    aSwapExtended.quoteAsset = aSwapCreationRequest.quoteAsset;
    aSwapExtended.baseAmount = aSwapCreationRequest.baseAmount;
    aSwapExtended.quoteAmount = 0;
    aSwapExtended.price = 0;
    aSwapExtended.bidOwnerBaseBalanceID = bidOwnerBalance->getBalanceID();
    // askOwnerBaseBalance omitted because it might not exist

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    return true;
}

bool ReviewASwapRequestOpFrame::canRemoveBid(AtomicSwapBidFrame::pointer bid)
{
    bool bidIsSoldOut = (bid->getAmount() == 0) && (bid->getLockedAmount() == 0);
    return bidIsSoldOut || (bid->isCancelled() && (bid->getLockedAmount() == 0));
}

bool ReviewASwapRequestOpFrame::handleApprove(Application &app, LedgerDelta &delta,
                                              LedgerManager &ledgerManager,
                                              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);

    auto& requestTasksExt = request->getRequestEntry().tasks;

    requestTasksExt.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestTasksExt.pendingTasks &= ~mReviewRequest.reviewDetails.tasksToRemove;
    requestTasksExt.pendingTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestTasksExt.externalDetails.emplace_back(
            mReviewRequest.reviewDetails.externalDetails);

    auto& requestEntry = request->getRequestEntry();
    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;

    Database& db = app.getDatabase();

    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().success().fulfilled = false;
        innerResult().success().typeExt.requestType(ReviewableRequestType::NONE);
        return true;
    }
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    auto aSwapRequest = request->getRequestEntry().body.createAtomicSwapAskRequest();

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            aSwapRequest.bidID, db, &delta);
    if (bidFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected atomic swap bid to exist, bid ID: "
                << bidFrame->getBidID();
        throw runtime_error("Unexpected state: expected atomic swap bid to exist");
    }

    if (!bidFrame->tryChargeFromLocked(aSwapRequest.baseAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Expected bid has enough locked amount";
        throw runtime_error("Unexpected state. Expected bid has enough locked amount");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, bidFrame->mEntry);

    AccountManager accountManager(app, db, delta, ledgerManager);
    BalanceFrame::pointer purchaserBalanceFrame =
            accountManager.loadOrCreateBalanceFrameForAsset(
                    request->getRequestor(), bidFrame->getBaseAsset(), db, delta);

    if (purchaserBalanceFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Expected purchaser balance to exist";
        throw std::runtime_error(
                "Unexpected state. Expected purchaser balance to exist");
    }

    if (purchaserBalanceFrame->tryFundAccount(aSwapRequest.baseAmount) != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(ReviewRequestResultCode::ATOMIC_SWAP_ASK_OWNER_FULL_LINE);
        return false;
    }

    EntryHelperProvider::storeChangeEntry(delta, db, purchaserBalanceFrame->mEntry);

    auto bidOwnerBalanceFrame = BalanceHelperLegacy::Instance()->mustLoadBalance(
            bidFrame->getOwnerID(), bidFrame->getBaseAsset(), db, &delta);

    if (bidOwnerBalanceFrame->tryChargeFromLocked(aSwapRequest.baseAmount) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge from bid owner balance locked amount, "
                   "bid ID: " << bidFrame->getBidID();
        throw runtime_error(
                "Unexpected state: failed to charge from bid owner balance locked amount");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, bidOwnerBalanceFrame->mEntry);

    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    auto& aSwapExtended = innerResult().success().typeExt.atomicSwapAskExtended();
    aSwapExtended.unlockedAmount = 0;

    if (canRemoveBid(bidFrame))
    {
        removeBid(db, delta, bidOwnerBalanceFrame, bidFrame);
        aSwapExtended.unlockedAmount = bidFrame->getAmount();
    }

    auto quoteAssetPrice = bidFrame->getQuoteAssetPrice(aSwapRequest.quoteAsset);
    if (quoteAssetPrice == 0)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
        << "Unexpected state: quote asset not found in bid's quote assets list, "
        << "quote asset code: " << aSwapRequest.quoteAsset << ", "
        << "atomic swap bid ID: " << bidFrame->getBidID();
        throw runtime_error(
                "Unexpected state: quote asset not found in bid's quote assets list");
    }

    StorageHelperImpl storageHelperImpl(db, &delta);
    auto& assetHelper = static_cast<StorageHelper&>(storageHelperImpl).getAssetHelper();
    auto quoteAssetFrame = assetHelper.mustLoadAsset(aSwapRequest.quoteAsset);

    auto quoteAmount = OfferManager::calculateQuoteAmount(
            aSwapRequest.baseAmount, quoteAssetPrice, quoteAssetFrame->getMinimumAmount());

    aSwapExtended.bidID = bidFrame->getBidID();
    aSwapExtended.bidOwnerID = bidFrame->getOwnerID();
    aSwapExtended.askOwnerID = request->getRequestor();
    aSwapExtended.baseAsset = bidFrame->getBaseAsset();
    aSwapExtended.quoteAsset = aSwapRequest.quoteAsset;
    aSwapExtended.baseAmount = aSwapRequest.baseAmount;
    aSwapExtended.quoteAmount = static_cast<uint64>(quoteAmount);
    aSwapExtended.price = quoteAssetPrice;
    aSwapExtended.bidOwnerBaseBalanceID = bidOwnerBalanceFrame->getBalanceID();
    aSwapExtended.askOwnerBaseBalanceID = purchaserBalanceFrame->getBalanceID();

    return true;
}

}