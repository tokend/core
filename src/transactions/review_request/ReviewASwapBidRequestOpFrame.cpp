#include <main/Application.h>
#include <database/Database.h>
#include <ledger/AtomicSwapAskHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/dex/OfferManager.h>
#include <ledger/StorageHelperImpl.h>
#include <ledger/AssetHelper.h>
#include "ReviewASwapBidRequestOpFrame.h"

using namespace std;

namespace stellar
{

stellar::ReviewASwapBidRequestOpFrame::ReviewASwapBidRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewASwapBidRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            mReviewRequest.requestID, storageHelper.getDatabase());
    if (!request || (request->getType() != ReviewableRequestType::CREATE_ATOMIC_SWAP_BID))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(
            request->getRequestEntry().body.createAtomicSwapBidRequest().quoteAsset);

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    resource.reviewableRequest().details.createAtomicSwapBidExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetType = asset->getType();
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool ReviewASwapBidRequestOpFrame::handleReject(Application &app, LedgerDelta &delta,
                                             LedgerManager &ledgerManager,
                                             ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

void ReviewASwapBidRequestOpFrame::removeAsk(Database &db, LedgerDelta &delta,
                                             BalanceFrame::pointer askOwnerBalance,
                                             AtomicSwapAskFrame::pointer ask)
{
    if (askOwnerBalance->unlock(ask->getAmount()) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in ask owner balance, "
                   "bid ID: " << ask->getID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in ask owner balance");
    }
    EntryHelperProvider::storeChangeEntry(delta, db, askOwnerBalance->mEntry);
    EntryHelperProvider::storeDeleteEntry(delta, db, ask->getKey());
}

bool
ReviewASwapBidRequestOpFrame::handlePermanentReject(Application &app, LedgerDelta &delta,
                                                 LedgerManager &ledgerManager,
                                                 ReviewableRequestFrame::pointer request)
{
    Database& db = app.getDatabase();
    auto& aSwapCreationRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();

    auto askFrame = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
            aSwapCreationRequest.askID, db, &delta);

    if (askFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected atomic swap bid to exist, bid ID: "
                << askFrame->getID();
        throw runtime_error("Unexpected state: expected atomic swap bid to exist");
    }

    if (!askFrame->tryUnlockAmount(aSwapCreationRequest.baseAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in atomic swap bid: "
                   "insufficient locked amount, atomic swap bid ID:"
                << askFrame->getID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in atomic swap bid");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, askFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    auto& aSwapExtended = innerResult().success().typeExt.atomicSwapBidExtended();
    aSwapExtended.unlockedAmount = 0;

    BalanceFrame::pointer askOwnerBalance = BalanceHelperLegacy::Instance()->mustLoadBalance(
            askFrame->getOwnerID(), askFrame->getBaseAsset(), db, &delta);
    if (canRemoveAsk(askFrame))
    {
        removeAsk(db, delta, askOwnerBalance, askFrame);
        aSwapExtended.unlockedAmount = askFrame->getAmount();
    }

    aSwapExtended.askID = askFrame->getID();
    aSwapExtended.askOwnerID = askFrame->getOwnerID();
    aSwapExtended.bidOwnerID = request->getRequestor();
    aSwapExtended.baseAsset = askFrame->getBaseAsset();
    aSwapExtended.quoteAsset = aSwapCreationRequest.quoteAsset;
    aSwapExtended.baseAmount = aSwapCreationRequest.baseAmount;
    aSwapExtended.quoteAmount = 0;
    aSwapExtended.price = 0;
    aSwapExtended.askOwnerBaseBalanceID = askOwnerBalance->getBalanceID();
    // askOwnerBaseBalance omitted because it might not exist, default value will be assigned

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    return true;
}

bool ReviewASwapBidRequestOpFrame::canRemoveAsk(AtomicSwapAskFrame::pointer bid)
{
    bool bidIsSoldOut = (bid->getAmount() == 0) && (bid->getLockedAmount() == 0);
    return bidIsSoldOut || (bid->isCancelled() && (bid->getLockedAmount() == 0));
}

bool ReviewASwapBidRequestOpFrame::handleApprove(Application &app, LedgerDelta &delta,
                                              LedgerManager &ledgerManager,
                                              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);

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

    auto aSwapRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();

    auto askFrame = AtomicSwapAskHelper::Instance()->loadAtomicSwapAsk(
            aSwapRequest.askID, db, &delta);
    if (askFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected atomic swap bid to exist, bid ID: "
                << askFrame->getID();
        throw runtime_error("Unexpected state: expected atomic swap bid to exist");
    }

    if (!askFrame->tryChargeFromLocked(aSwapRequest.baseAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Expected bid has enough locked amount";
        throw runtime_error("Unexpected state. Expected bid has enough locked amount");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, askFrame->mEntry);

    AccountManager accountManager(app, db, delta, ledgerManager);
    BalanceFrame::pointer purchaserBalanceFrame =
            accountManager.loadOrCreateBalanceFrameForAsset(
                    request->getRequestor(), askFrame->getBaseAsset(), db, delta);

    if (purchaserBalanceFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Expected purchaser balance to exist";
        throw std::runtime_error(
                "Unexpected state. Expected purchaser balance to exist");
    }

    if (purchaserBalanceFrame->tryFundAccount(aSwapRequest.baseAmount) != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(ReviewRequestResultCode::ATOMIC_SWAP_BID_OWNER_FULL_LINE);
        return false;
    }

    EntryHelperProvider::storeChangeEntry(delta, db, purchaserBalanceFrame->mEntry);

    auto askOwnerBalanceFrame = BalanceHelperLegacy::Instance()->mustLoadBalance(
            askFrame->getOwnerID(), askFrame->getBaseAsset(), db, &delta);

    if (askOwnerBalanceFrame->tryChargeFromLocked(aSwapRequest.baseAmount) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge from ask owner balance locked amount, "
                   "ask ID: " << askFrame->getID();
        throw runtime_error(
                "Unexpected state: failed to charge from ask owner balance locked amount");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, askOwnerBalanceFrame->mEntry);

    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    auto& aSwapExtended = innerResult().success().typeExt.atomicSwapBidExtended();
    aSwapExtended.unlockedAmount = 0;

    if (canRemoveAsk(askFrame))
    {
        removeAsk(db, delta, askOwnerBalanceFrame, askFrame);
        aSwapExtended.unlockedAmount = askFrame->getAmount();
    }

    auto quoteAssetPrice = askFrame->getQuoteAssetPrice(aSwapRequest.quoteAsset);
    if (quoteAssetPrice == 0)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
        << "Unexpected state: quote asset not found in bid's quote assets list, "
        << "quote asset code: " << aSwapRequest.quoteAsset << ", "
        << "atomic swap bid ID: " << askFrame->getID();
        throw runtime_error(
                "Unexpected state: quote asset not found in bid's quote assets list");
    }

    StorageHelperImpl storageHelperImpl(db, &delta);
    auto& assetHelper = static_cast<StorageHelper&>(storageHelperImpl).getAssetHelper();
    auto quoteAssetFrame = assetHelper.mustLoadAsset(aSwapRequest.quoteAsset);

    auto quoteAmount = OfferManager::calculateQuoteAmount(
            aSwapRequest.baseAmount, quoteAssetPrice, quoteAssetFrame->getMinimumAmount());

    aSwapExtended.askID = askFrame->getID();
    aSwapExtended.askOwnerID = askFrame->getOwnerID();
    aSwapExtended.bidOwnerID = request->getRequestor();
    aSwapExtended.baseAsset = askFrame->getBaseAsset();
    aSwapExtended.quoteAsset = aSwapRequest.quoteAsset;
    aSwapExtended.baseAmount = aSwapRequest.baseAmount;
    aSwapExtended.quoteAmount = static_cast<uint64>(quoteAmount);
    aSwapExtended.price = quoteAssetPrice;
    aSwapExtended.askOwnerBaseBalanceID = askOwnerBalanceFrame->getBalanceID();
    aSwapExtended.bidOwnerBaseBalanceID = purchaserBalanceFrame->getBalanceID();

    return true;
}

}