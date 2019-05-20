#include <main/Application.h>
#include <database/Database.h>
#include <ledger/LedgerDelta.h>
#include "ledger/LedgerHeaderFrame.h"
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/atomic_swap/CreateASwapBidCreationRequestOpFrame.h>
#include <ledger/AccountHelperLegacy.h>
#include "ReviewASwapBidCreationRequestOpFrame.h"
#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <ledger/AssetHelper.h>

using namespace std;

namespace stellar
{

ReviewASwapBidCreationRequestOpFrame::ReviewASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewASwapBidCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
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

    auto balance = storageHelper.getBalanceHelper().mustLoadBalance(
            request->getRequestEntry().body.createAtomicSwapBidRequest().baseBalance);

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(balance->getAsset());

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

bool ReviewASwapBidCreationRequestOpFrame::handleReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool ReviewASwapBidCreationRequestOpFrame::handleAllAssetsValidationResultCode(
        CreateAtomicSwapBidRequestResultCode code) {
    switch (code)
    {
        case CreateAtomicSwapBidRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected error code from atomic swap bid assets validator: "
                << xdr::xdr_traits<CreateAtomicSwapBidRequestResultCode>::enum_name(
                        code);
            throw runtime_error(
                    "Unexpected error code from atomic swap bid assets validator");
        }
    }
}

AtomicSwapBidFrame::pointer
ReviewASwapBidCreationRequestOpFrame::buildNewBid(AccountID ownerID, AssetCode baseAsset,
        uint64_t ledgerCloseTime, CreateAtomicSwapBidRequest request, LedgerDelta &delta)
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

    auto requestBody = request->getRequestEntry().body.createAtomicSwapBidRequest();

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
    if (validationResultCode != CreateAtomicSwapBidRequestResultCode::SUCCESS)
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
    innerResult().success().typeExt.atomicSwapBidExtended().bidID = bidFrame->getBidID();

    return true;
}

bool ReviewASwapBidCreationRequestOpFrame::handlePermanentReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);

    auto aSwapCreationRequest = request->getRequestEntry().body.createAtomicSwapBidRequest();
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