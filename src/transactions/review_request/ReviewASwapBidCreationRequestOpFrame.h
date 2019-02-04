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
SourceDetails getSourceAccountDetails(
        std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
        int32_t ledgerVersion) const override;

bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                  ReviewableRequestFrame::pointer request) override;

bool handleAllAssetsValidationResultCode(CreateASwapBidCreationRequestResultCode code);

AtomicSwapBidFrame::pointer
buildNewBid(AccountID ownerID, AssetCode baseAsset, uint64_t ledgerCloseTime,
            ASwapBidCreationRequest request, LedgerDelta& delta);

bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                   ReviewableRequestFrame::pointer request) override;

bool handlePermanentReject(Application& app, LedgerDelta& delta,
                           LedgerManager& ledgerManager,
                           ReviewableRequestFrame::pointer request) override;
};

}