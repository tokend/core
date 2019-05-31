#include <main/Application.h>
#include <database/Database.h>
#include <ledger/LedgerDelta.h>
#include "ledger/LedgerHeaderFrame.h"
#include <ledger/BalanceHelperLegacy.h>
#include <transactions/atomic_swap/CreateAtomicSwapAskRequestOpFrame.h>
#include <ledger/AccountHelperLegacy.h>
#include "ReviewASwapAskRequestOpFrame.h"
#include <ledger/BalanceHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StorageHelper.h>
#include <ledger/AssetHelper.h>

using namespace std;

namespace stellar
{

ReviewASwapAskRequestOpFrame::ReviewASwapAskRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewASwapAskRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                    std::vector<SignerRequirement>& result) const
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            mReviewRequest.requestID, storageHelper.getDatabase());
    if (!request || (request->getType() != ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto balance = storageHelper.getBalanceHelper().mustLoadBalance(
            request->getRequestEntry().body.createAtomicSwapAskRequest().baseBalance);

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(balance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    resource.reviewableRequest().details.createAtomicSwapAskExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetType = asset->getType();
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool ReviewASwapAskRequestOpFrame::handleReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool
ReviewASwapAskRequestOpFrame::handleAllAssetsValidationResultCode(
        CreateAtomicSwapAskRequestResultCode code)
{
    switch (code)
    {
        case CreateAtomicSwapAskRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected error code from atomic swap bid assets validator: "
                << xdr::xdr_traits<CreateAtomicSwapAskRequestResultCode>::enum_name(
                        code);
            throw runtime_error(
                    "Unexpected error code from atomic swap bid assets validator");
        }
    }
}

AtomicSwapAskFrame::pointer
ReviewASwapAskRequestOpFrame::buildNewAsk(AccountID ownerID, AssetCode baseAsset,
        uint64_t ledgerCloseTime, CreateAtomicSwapAskRequest request, LedgerDelta &delta)
{
    AtomicSwapAskEntry entry;
    entry.id = delta.getHeaderFrame().generateID(LedgerEntryType::ATOMIC_SWAP_ASK);
    entry.ownerID = ownerID;
    entry.baseAsset = baseAsset;
    entry.baseBalance = request.baseBalance;
    entry.amount = request.amount;
    entry.lockedAmount = 0;
    entry.isCancelled = false;
    entry.createdAt = ledgerCloseTime;
    entry.details = request.creatorDetails;
    entry.quoteAssets = request.quoteAssets;

    LedgerEntry le;
    le.data.type(LedgerEntryType::ATOMIC_SWAP_ASK);
    le.data.atomicSwapAsk() = entry;
    return make_shared<AtomicSwapAskFrame>(le);
}

bool ReviewASwapAskRequestOpFrame::handleApprove(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);

    auto requestBody = request->getRequestEntry().body.createAtomicSwapAskRequest();

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
                << "atomic swap ask creation request ID: " << request->getRequestID();
        throw runtime_error("Unexpected state: expected base balance to exist");
    }

    auto validationResultCode = CreateAtomicSwapAskRequestOpFrame::areAllAssetsValid(
            db, requestBody.amount, baseBalanceFrame->getAsset(), requestBody.quoteAssets);
    if (validationResultCode != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        return handleAllAssetsValidationResultCode(validationResultCode);
    }

    auto requestor = AccountHelperLegacy::Instance()->mustLoadAccount(request->getRequestor(),
                                                                db);

    auto askFrame = buildNewAsk(requestor->getID(), baseBalanceFrame->getAsset(),
                                ledgerManager.getCloseTime(), requestBody,
                                delta);

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    EntryHelperProvider::storeAddEntry(delta, db, askFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    innerResult().success().typeExt.atomicSwapAskExtended().askID = askFrame->getID();

    return true;
}

bool ReviewASwapAskRequestOpFrame::handlePermanentReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);

    auto aSwapCreationRequest = request->getRequestEntry().body.createAtomicSwapAskRequest();
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