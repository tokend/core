#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{

class ReviewASwapRequestOpFrame : public ReviewRequestOpFrame
{
public:
    ReviewASwapRequestOpFrame(Operation const &op, OperationResult &res,
                              TransactionFrame &parentTx);

protected:

bool
tryGetSignerRequirements(StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                  ReviewableRequestFrame::pointer request) override;

bool canRemoveBid(AtomicSwapBidFrame::pointer bid);

void removeBid(Database &db, LedgerDelta &delta,
               BalanceFrame::pointer bidOwnerBalance, AtomicSwapBidFrame::pointer bid);

bool handlePermanentReject(Application& app, LedgerDelta& delta,
                           LedgerManager& ledgerManager,
                           ReviewableRequestFrame::pointer request) override;

bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                   ReviewableRequestFrame::pointer request) override;
};


}