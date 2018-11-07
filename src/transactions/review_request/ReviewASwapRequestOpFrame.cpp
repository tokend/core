#include <main/Application.h>
#include <database/Database.h>
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/dex/OfferManager.h>
#include "ReviewASwapRequestOpFrame.h"

using namespace std;

namespace stellar
{

stellar::ReviewASwapRequestOpFrame::ReviewASwapRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

SourceDetails ReviewASwapRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails({ AccountType::MASTER }, mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
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
    if (!bidOwnerBalance->unlock(bid->getAmount()))
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
    auto& aSwapCreationRequest = request->getRequestEntry().body.aSwapRequest();

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

    if (canRemoveBid(bidFrame))
    {
        BalanceFrame::pointer bidOwnerBalance =
                BalanceHelperLegacy::Instance()->mustLoadBalance(bidFrame->getOwnerID(),
                                                           bidFrame->getBaseAsset(),
                                                           db, &delta);
        removeBid(db, delta, bidOwnerBalance, bidFrame);
    }

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

bool ReviewASwapRequestOpFrame::canRemoveBid(AtomicSwapBidFrame::pointer bid)
{
    bool bidIsSoldOut = bid->getAmount() == 0 && bid->getLockedAmount() == 0;
    return bidIsSoldOut || (bid->isCancelled() && bid->getLockedAmount() == 0);
}

bool ReviewASwapRequestOpFrame::handleApprove(Application &app, LedgerDelta &delta,
                                              LedgerManager &ledgerManager,
                                              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::ATOMIC_SWAP);

    auto& requestTasksExt = request->getRequestEntry().ext.tasksExt();

    requestTasksExt.allTasks |= mReviewRequest.ext.reviewDetails().tasksToAdd;
    requestTasksExt.pendingTasks &= ~mReviewRequest.ext.reviewDetails().tasksToRemove;
    requestTasksExt.pendingTasks |= mReviewRequest.ext.reviewDetails().tasksToAdd;
    requestTasksExt.externalDetails.emplace_back(
            mReviewRequest.ext.reviewDetails().externalDetails);

    auto& requestEntry = request->getRequestEntry();
    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;

    Database& db = app.getDatabase();

    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
        innerResult().success().ext.extendedResult().fulfilled = false;
        innerResult().success().ext.extendedResult().typeExt.requestType(
                ReviewableRequestType::NONE);
        return true;
    }

    auto aSwapRequest = request->getRequestEntry().body.aSwapRequest();

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
        innerResult().code(ReviewRequestResultCode::ASWAP_BID_UNDERFUNDED);
        return false;
    }

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

    if (!purchaserBalanceFrame->tryFundAccount(aSwapRequest.baseAmount))
    {
        innerResult().code(ReviewRequestResultCode::ASWAP_PURCHASER_FULL_LINE);
        return false;
    }

    auto bidOwnerBalanceFrame = BalanceHelperLegacy::Instance()->mustLoadBalance(
            bidFrame->getOwnerID(), bidFrame->getBaseAsset(), db, &delta);

    if (!bidOwnerBalanceFrame->tryChargeFromLocked(aSwapRequest.baseAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge from bid owner balance locked amount, "
                   "bid ID: " << bidFrame->getBidID();
        throw runtime_error(
                "Unexpected state: failed to charge from bid owner balance locked amount");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, bidFrame->mEntry);
    EntryHelperProvider::storeChangeEntry(delta, db, bidOwnerBalanceFrame->mEntry);
    EntryHelperProvider::storeChangeEntry(delta, db, purchaserBalanceFrame->mEntry);
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    if (canRemoveBid(bidFrame))
    {
        removeBid(db, delta, bidOwnerBalanceFrame, bidFrame);
    }

    if (!ledgerManager.shouldUse(LedgerVersion::EXTEND_REVIEW_ATOMIC_SWAP_REQUEST_RESULT))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
        innerResult().success().ext.extendedResult().fulfilled = true;
        innerResult().success().ext.extendedResult().typeExt.requestType(
                ReviewableRequestType::NONE);
        return true;
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

    auto quoteAmount = OfferManager::calculateQuoteAmount(
            aSwapRequest.baseAmount, quoteAssetPrice);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    innerResult().success().ext.extendedResult().fulfilled = true;
    innerResult().success().ext.extendedResult().typeExt.requestType(
            ReviewableRequestType::ATOMIC_SWAP);

    auto& aSwapExtended =
            innerResult().success().ext.extendedResult().typeExt.aSwapExtended();

    aSwapExtended.bidID = bidFrame->getBidID();
    aSwapExtended.bidOwnerID = bidFrame->getOwnerID();
    aSwapExtended.purchaserID = request->getRequestor();
    aSwapExtended.baseAsset = bidFrame->getBaseAsset();
    aSwapExtended.quoteAsset = aSwapRequest.quoteAsset;
    aSwapExtended.baseAmount = aSwapRequest.baseAmount;
    aSwapExtended.quoteAmount = static_cast<uint64>(quoteAmount);
    aSwapExtended.price = quoteAssetPrice;

    return true;
}

}