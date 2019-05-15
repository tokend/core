#include <main/Application.h>
#include <database/Database.h>
#include <ledger/LedgerDelta.h>
#include "ledger/LedgerHeaderFrame.h"
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/atomic_swap/CreateASwapBidCreationRequestOpFrame.h>
#include <ledger/AccountHelperLegacy.h>
#include "ReviewASwapBidCreationRequestOpFrame.h"

using namespace std;

namespace stellar
{

ReviewASwapBidCreationRequestOpFrame::ReviewASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewASwapBidCreationRequestOpFrame::handleReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool ReviewASwapBidCreationRequestOpFrame::handleAllAssetsValidationResultCode(
        CreateAtomicSwapBidCreationRequestResultCode code) {
    switch (code)
    {
        case CreateAtomicSwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::BASE_ASSET_NOT_FOUND);
            return false;
        }
        case CreateAtomicSwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateAtomicSwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::QUOTE_ASSET_NOT_FOUND);
            return false;
        }
        case CreateAtomicSwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateAtomicSwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL:
        {
            innerResult().code(ReviewRequestResultCode::ASSETS_ARE_EQUAL);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected error code from atomic swap bid assets validator: "
                << xdr::xdr_traits<CreateAtomicSwapBidCreationRequestResultCode>::enum_name(
                        code);
            throw runtime_error(
                    "Unexpected error code from atomic swap bid assets validator");
        }
    }
}

AtomicSwapBidFrame::pointer
ReviewASwapBidCreationRequestOpFrame::buildNewBid(AccountID ownerID, AssetCode baseAsset,
                                                  uint64_t ledgerCloseTime,
                                                  AtomicSwapBidCreationRequest request,
                                                  LedgerDelta &delta)
{
    AtomicSwapBidEntry bidEntry;
    bidEntry.bidID = delta.getHeaderFrame().generateID(LedgerEntryType::ATOMIC_SWAP_BID);
    bidEntry.ownerID = ownerID;
    bidEntry.baseAsset = baseAsset;
    bidEntry.baseBalance = request.baseBalance;
    bidEntry.amount = request.amount;
    bidEntry.lockedAmount = 0;
    bidEntry.isCancelled = false;
    bidEntry.createdAt = ledgerCloseTime;
    bidEntry.details = request.creatorDetails;
    bidEntry.quoteAssets = request.quoteAssets;

    LedgerEntry le;
    le.data.type(LedgerEntryType::ATOMIC_SWAP_BID);
    le.data.atomicSwapBid() = bidEntry;
    return make_shared<AtomicSwapBidFrame>(le);
}

bool ReviewASwapBidCreationRequestOpFrame::handleApprove(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);

    auto requestBody = request->getRequestEntry().body.atomicSwapBidCreationRequest();

    Database& db = app.getDatabase();
    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto baseBalanceFrame = BalanceHelperLegacy::Instance()->loadBalance(
            requestBody.baseBalance, db);

    if (baseBalanceFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected base balance to exist: "
                << "atomic swap bid creation request ID: " << request->getRequestID();
        throw runtime_error("Unexpected state: expected base balance to exist");
    }

    auto validationResultCode = CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(
            db, requestBody.amount, baseBalanceFrame->getAsset(), requestBody.quoteAssets);
    if (validationResultCode != CreateAtomicSwapBidCreationRequestResultCode::SUCCESS)
    {
        return handleAllAssetsValidationResultCode(validationResultCode);
    }

    auto requestor = AccountHelperLegacy::Instance()->mustLoadAccount(request->getRequestor(),
                                                                db);

    auto bidFrame = buildNewBid(requestor->getID(), baseBalanceFrame->getAsset(),
                                ledgerManager.getCloseTime(), requestBody,
                                delta);

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    EntryHelperProvider::storeAddEntry(delta, db, bidFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    innerResult().success().typeExt.aSwapBidExtended().bidID = bidFrame->getBidID();

    return true;
}

bool ReviewASwapBidCreationRequestOpFrame::handlePermanentReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);

    auto aSwapCreationRequest = request->getRequestEntry().body.atomicSwapBidCreationRequest();
    auto& db = app.getDatabase();

    auto baseBalanceFrame = BalanceHelperLegacy::Instance()->loadBalance(
            aSwapCreationRequest.baseBalance, db);

    if (baseBalanceFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected base balance to exist: "
                << "atomic swap bid creation request ID: " << request->getRequestID();
        throw runtime_error("Unexpected state: expected base balance to exist");
    }

    if (baseBalanceFrame->unlock(aSwapCreationRequest.amount) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock amount in bid creation requestor balance, "
                   "request ID: " << request->getRequestID();
        throw runtime_error(
                "Unexpected state: failed to unlock amount in bid creation requestor balance");
    }

    EntryHelperProvider::storeChangeEntry(delta, db, baseBalanceFrame->mEntry);
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

}