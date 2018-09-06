#include <main/Application.h>
#include <database/Database.h>
#include <ledger/LedgerDelta.h>
#include <ledger/BalanceHelper.h>
#include <transactions/atomic_swap/CreateASwapBidCreationRequestOpFrame.h>
#include <transactions/FeesManager.h>
#include <ledger/AccountHelper.h>
#include "ReviewASwapBidCreationRequestOpFrame.h"

using namespace std;

namespace stellar
{

ReviewASwapBidCreationRequestOpFrame::ReviewASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

SourceDetails ReviewASwapBidCreationRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails({ AccountType::MASTER }, mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
}

bool ReviewASwapBidCreationRequestOpFrame::handleReject(
        Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
        ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool ReviewASwapBidCreationRequestOpFrame::handleAllAssetsValidationResultCode(
        CreateASwapBidCreationRequestResultCode code) {
    switch (code)
    {
        case CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::ASWAP_BID_BASE_ASSET_NOT_FOUND);
            return false;
        }
        case CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::ASWAP_BID_BASE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND:
        {
            innerResult().code(ReviewRequestResultCode::ASWAP_BID_QUOTE_ASSET_NOT_FOUND);
            return false;
        }
        case CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED:
        {
            innerResult().code(
                    ReviewRequestResultCode::ASWAP_BID_QUOTE_ASSET_CANNOT_BE_SWAPPED);
            return false;
        }
        case CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL:
        {
            innerResult().code(ReviewRequestResultCode::ASWAP_BID_ASSETS_ARE_EQUAL);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected error code from atomic swap bid assets validator: "
                << xdr::xdr_traits<CreateASwapBidCreationRequestResultCode>::enum_name(
                        code);
            throw runtime_error(
                    "Unexpected error code from atomic swap bid assets validator");
        }
    }
}

AtomicSwapBidFrame::pointer
ReviewASwapBidCreationRequestOpFrame::buildNewBid(AccountID ownerID, AssetCode baseAsset,
                                                  uint64_t ledgerCloseTime,
                                                  ASwapBidCreationRequest request,
                                                  LedgerDelta &delta)
{
    AtomicSwapBidEntry bidEntry;
    bidEntry.bidID = delta.getHeaderFrame().generateID(LedgerEntryType::ATOMIC_SWAP_BID);
    bidEntry.ownerID = ownerID;
    bidEntry.baseAsset = baseAsset;
    bidEntry.baseBalance = request.baseBalance;
    bidEntry.amount = request.amount;
    bidEntry.lockedAmount = 0;
    bidEntry.createdAt = ledgerCloseTime;
    bidEntry.details = request.details;
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

    auto aSwapCreationRequest = request->getRequestEntry().body.aSwapBidCreationRequest();

    Database& db = app.getDatabase();

    auto baseBalanceFrame = BalanceHelper::Instance()->loadBalance(
            aSwapCreationRequest.baseBalance, db);

    if (baseBalanceFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected base balance to exist: "
                << "atomic swap bid creation request ID: " << request->getRequestID();
        throw runtime_error("Unexpected state: expected base balance to exist");
    }

    CreateASwapBidCreationRequestResultCode validationResultCode =
            CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(
                    db, baseBalanceFrame->getAsset(), aSwapCreationRequest.quoteAssets);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return handleAllAssetsValidationResultCode(validationResultCode);
    }

    auto requestor = AccountHelper::Instance()->mustLoadAccount(request->getRequestor(),
                                                                db);

    auto bidFrame = buildNewBid(requestor->getID(), baseBalanceFrame->getAsset(),
                                ledgerManager.getCloseTime(), aSwapCreationRequest,
                                delta);

    auto const feeResult = FeeManager::calcualteFeeForAccount(
            requestor, FeeType::ATOMIC_SWAP_SALE_FEE, baseBalanceFrame->getAsset(),
            FeeFrame::SUBTYPE_ANY, bidFrame->getAmount(), db);
    if (feeResult.isOverflow)
    {
        innerResult().code(ReviewRequestResultCode::ASWAP_BID_OVERFLOW);
        return false;
    }

    bidFrame->setFee(feeResult.calculatedPercentFee);
    bidFrame->setPercentFee(feeResult.percentFee);

    bool const isFeeEnough = bidFrame->getFee() <= aSwapCreationRequest.fee;
    if (!isFeeEnough)
    {
        innerResult().code(ReviewRequestResultCode::ASWAP_BID_INSUFFICIENT_FEE);
        return false;
    }

    bidFrame->setFee(aSwapCreationRequest.fee);

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
    EntryHelperProvider::storeAddEntry(delta, db, bidFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    innerResult().success().ext.extendedResult().fulfilled = true;
    innerResult().success().ext.extendedResult().typeExt.requestType(
            ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    innerResult().success().ext.extendedResult().typeExt.aSwapBidExtended().bidID =
            bidFrame->getBidID();

    return true;
}

}