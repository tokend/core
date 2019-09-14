#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{

class ReviewASwapBidRequestOpFrame : public ReviewRequestOpFrame {
public:
    ReviewASwapBidRequestOpFrame(Operation const& op, OperationResult& res,
                                 TransactionFrame& parentTx);

protected:

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

    bool canRemoveAsk(AtomicSwapAskFrame::pointer ask);

    void removeAsk(StorageHelper& storageHelper,
                   BalanceFrame::pointer bidOwnerBalance,
                   AtomicSwapAskFrame::pointer ask);

    bool handlePermanentReject(Application& app, StorageHelper& storageHelper,
                               LedgerManager& ledgerManager,
                               ReviewableRequestFrame::pointer request) override;

    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;
};

}
