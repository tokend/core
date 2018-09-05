#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/ReviewableRequestFrame.h>
#include "CreateAtomicSwapRequestOpFrame.h"

namespace stellar
{
using xdr::operator==;

std::unordered_map<AccountID, CounterpartyDetails>
CreateAtomicSwapRequestOpFrame::getCounterpartyDetails(Database & db,
                                                    LedgerDelta * delta) const
{
    return{
            {mManageInvoiceRequest.details.invoiceRequest().sender,
                    CounterpartyDetails(getAllAccountTypes(), true, true)},
    };
}

SourceDetails
CreateAtomicSwapRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID,
        CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails(getAllAccountTypes(),
                         mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::FIX_ME));
}

CreateAtomicSwapRequestOpFrame::CreateAtomicSwapRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageInvoiceRequest(mOperation.body.manageInvoiceRequestOp())
{
}

bool
CreateAtomicSwapRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                     LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto request = mCreateASwapRequest.request;

    auto swapBidHelper = AtomicSwapBidHelper::Instance();
    auto bidFrame = swapBidHelper->loadAtomicSwapBid(request.bidID, db, &delta);
    if (!bidFrame)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (bidFrame->isInQuoteAssets(request.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::BID_QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    if (bidFrame->getReservedAmount() < request.baseAmount)
    {
        innerResult().code(CreateASwapRequestResultCode::BASE_AMOUNT_TOO_MUCH);
        return false;
    }

    ReviewableRequestEntry::_body_t body;
    body.type(ReviewableRequestType::ATOMIC_SWAP);
    body.invoiceRequest() = request;

    auto reviewableRequest = ReviewableRequestFrame::createNewWithHash(
            delta, getSourceID(), bidFrame->getOwner(),
            nullptr, body, ledgerManager.getCloseTime());

    EntryHelperProvider::storeAddEntry(delta, db, request->mEntry);

    return true;
}

bool
CreateAtomicSwapRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::MALFORMED);
        return false;
    }

    if (mCreateASwapRequest.request.quoteAsset.empty())
    {
        innerResult().code(CreateASwapRequestResultCode::MALFORMED);
        return false;
    }

    return true;
}

}
