#include "main/Application.h"
#include <database/Database.h>
#include <ledger/AtomicSwapBidHelper.h>
#include "CancelASwapBidOpFrame.h"

using namespace std;

namespace stellar
{

CancelASwapBidOpFrame::CancelASwapBidOpFrame(Operation const &op, OperationResult &opRes,
                                             TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx),
          mCancelASwapBid(mOperation.body.cancelASwapBidOp())
{
}

unordered_map<AccountID, CounterpartyDetails>
CancelASwapBidOpFrame::getCounterpartyDetails(Database &db, LedgerDelta *delta) const
{
    // no counterparties
    return {};
}

SourceDetails CancelASwapBidOpFrame::getSourceAccountDetails(
        unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const
{
    return SourceDetails(getAllAccountTypes(), mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::ATOMIC_SWAP_MANAGER));
}

bool CancelASwapBidOpFrame::doApply(Application &app, LedgerDelta &delta,
                                    LedgerManager &ledgerManager)
{
    Database& db = app.getDatabase();

    auto bidFrame = AtomicSwapBidHelper::Instance()->loadAtomicSwapBid(
            getSourceID(), mCancelASwapBid.bidID, db, &delta);
    if (bidFrame == nullptr)
    {
        innerResult().code(CancelASwapBidResultCode::NOT_FOUND);
        return false;
    }

    EntryHelperProvider::storeDeleteEntry(delta, db, bidFrame->getKey());

    innerResult().code(CancelASwapBidResultCode::SUCCESS);
    innerResult().success().bidID = bidFrame->getBidID();
    return true;
}

bool CancelASwapBidOpFrame::doCheckValid(Application &app)
{
    if (mCancelASwapBid.bidID == 0)
    {
        innerResult().code(CancelASwapBidResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

}