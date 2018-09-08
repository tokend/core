#include "main/Application.h"
#include <ledger/AtomicSwapBidHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/ReviewableRequestFrame.h>
#include <transactions/FeesManager.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include "CreateASwapRequestOpFrame.h"

using namespace std;

namespace stellar
{
using xdr::operator==;

CreateASwapRequestOpFrame::CreateASwapRequestOpFrame(
        Operation const& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateASwapRequest(mOperation.body.createASwapRequestOp())
{
}

std::unordered_map<AccountID, CounterpartyDetails>
CreateASwapRequestOpFrame::getCounterpartyDetails(Database & db,
                                                  LedgerDelta* delta) const
{
    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            mCreateASwapRequest.request.bidID, db);
    if (bidFrame == nullptr)
    {
        // no bid - no counterparties
        return {};
    }

    return {
        {
            bidFrame->getOwnerID(),
            CounterpartyDetails(getAllAccountTypes(), true, true)
        }
    };
}

SourceDetails
CreateASwapRequestOpFrame::getSourceAccountDetails(
        std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails(getAllAccountTypes(),
                         mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
}

bool CreateASwapRequestOpFrame::tryGetAtomicSwapTasks(Database& db, uint32_t &allTasks)
{
    auto aSwapKV = KeyValueHelper::Instance()->loadKeyValue(
            ManageKeyValueOpFrame::atomicSwapTasksPrefix, db);

    if (aSwapKV == nullptr)
    {
        innerResult().code(CreateASwapRequestResultCode::ATOMIC_SWAP_TASKS_NOT_FOUND);
        return false;
    }

    if (aSwapKV->getKeyValue().value.type() != KeyValueEntryType::UINT32)
    {
        throw std::runtime_error(
                "Unexpected database state, expected atomic swap tasks to be UINT32");
    }

    allTasks = aSwapKV->getKeyValue().value.ui32Value();
    return true;
}

bool
CreateASwapRequestOpFrame::doApply(Application& app, LedgerDelta& delta,
                                   LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    auto aSwapRequest = mCreateASwapRequest.request;

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(aSwapRequest.bidID,
                                                                       db, &delta);
    if (bidFrame == nullptr)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (!bidFrame->hasQuoteAsset(aSwapRequest.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::QUOTE_ASSET_NOT_FOUND);
        return false;
    }

    // TODO: move asset requirements check to separate method
    auto baseAssetFrame = AssetHelper::Instance()->loadAsset(bidFrame->getBaseAsset(),
                                                             bidFrame->getOwnerID(), db);
    if (baseAssetFrame == nullptr)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected base asset to exist, asset code: "
                   << bidFrame->getBaseAsset();
        throw runtime_error("Unexpected state: expected base asset to exist");
    }

    auto& sourceAccount = getSourceAccount();

    if (baseAssetFrame->isRequireVerification() &&
        sourceAccount.getAccountType() == AccountType::NOT_VERIFIED)
    {
        innerResult().code(CreateASwapRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    if (baseAssetFrame->isRequireKYC() &&
        (sourceAccount.getAccountType() == AccountType::NOT_VERIFIED ||
         sourceAccount.getAccountType() == AccountType::VERIFIED))
    {
        innerResult().code(CreateASwapRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    if (!bidFrame->tryLockAmount(aSwapRequest.baseAmount))
    {
        innerResult().code(CreateASwapRequestResultCode::BID_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                          app.getMasterID(), nullptr,
                                                          ledgerManager.getCloseTime());

    auto& requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::ATOMIC_SWAP);
    requestEntry.body.aSwapRequest() = mCreateASwapRequest.request;

    uint32_t allTasks = 0;
    if (!tryGetAtomicSwapTasks(db, allTasks))
    {
        return false;
    }
    requestEntry.ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    requestEntry.ext.tasksExt().allTasks = allTasks;
    requestEntry.ext.tasksExt().pendingTasks = allTasks;

    requestFrame->recalculateHashRejectReason();

    EntryHelperProvider::storeAddEntry(delta, db, requestFrame->mEntry);

    innerResult().code(CreateASwapRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().bidOwnerID = bidFrame->getOwnerID();

    return true;
}

bool
CreateASwapRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateASwapRequest.request.bidID == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::BID_NOT_FOUND);
        return false;
    }

    if (mCreateASwapRequest.request.baseAmount == 0)
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_BASE_AMOUNT);
        return false;
    }

    if (!AssetFrame::isAssetCodeValid(mCreateASwapRequest.request.quoteAsset))
    {
        innerResult().code(CreateASwapRequestResultCode::INVALID_QUOTE_ASSET);
        return false;
    }

    return true;
}

}
