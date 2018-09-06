#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/ReviewableRequestFrame.h>
#include "CreateASwapRequestOpFrame.h"

namespace stellar
{
using xdr::operator==;

std::unordered_map<AccountID, CounterpartyDetails>
CreateASwapRequestOpFrame::getCounterpartyDetails(Database & db,
                                                    LedgerDelta * delta) const
{
}

SourceDetails
CreateASwapRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID,
        CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails(getAllAccountTypes(),
                         mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
}

CreateASwapRequestOpFrame::CreateASwapRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateASwapRequest(mOperation.body.createASwapRequestOp())
{
}

bool
CreateASwapRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                        LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto request = mCreateASwapRequest.request;

    auto bidFrame = AtomicSwapBidHelper::Instance()->
            loadAtomicSwapBid(request.bidID, db, &delta);
    if (!bidFrame)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (!bidFrame->hasQuoteAsset(request.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    if (!bidFrame->tryDecreaseAvailableAmount(request.baseAmount))
    {
        innerResult().code(CreateASwapRequestResultCode::BASE_AMOUNT_TOO_MUCH);
        return false;
    }

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::ATOMIC_SWAP);
    body.aSwapRequest() = request;

    auto reviewableRequest = ReviewableRequestFrame::createNewWithHash(
            delta, getSourceID(), bidFrame->getOwner(),
            nullptr, body, ledgerManager.getCloseTime());

    EntryHelperProvider::storeAddEntry(delta, db, reviewableRequest->mEntry);

    innerResult().code(CreateASwapRequestResultCode::SUCCESS);
    innerResult().success().requestID = reviewableRequest->getRequestID();
    innerResult().success().owner = bidFrame->getOwner();

    return true;
}

bool
CreateASwapRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_BASE_AMOUNT);
        return false;
    }

    if (mCreateASwapRequest.request.quoteAsset.empty())
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_QUOTE_ASSET);
        return false;
    }

    return true;
}

}
