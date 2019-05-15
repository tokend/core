#pragma once

#include <ledger/AtomicSwapBidFrame.h>
#include "ReviewRequestOpFrame.h"

namespace stellar
{

class ReviewASwapBidCreationRequestOpFrame : public ReviewRequestOpFrame
{
public:
ReviewASwapBidCreationRequestOpFrame(Operation const &op, OperationResult &res,
                                     TransactionFrame &parentTx);

protected:

bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                  ReviewableRequestFrame::pointer request) override;

bool handleAllAssetsValidationResultCode(CreateAtomicSwapBidCreationRequestResultCode code);

AtomicSwapBidFrame::pointer
buildNewBid(AccountID ownerID, AssetCode baseAsset, uint64_t ledgerCloseTime,
            AtomicSwapBidCreationRequest request, LedgerDelta& delta);

bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                   ReviewableRequestFrame::pointer request) override;

bool handlePermanentReject(Application& app, LedgerDelta& delta,
                           LedgerManager& ledgerManager,
                           ReviewableRequestFrame::pointer request) override;
};

}