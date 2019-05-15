#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewKYCRecoveryRequestOpFrame : public ReviewRequestOpFrame {
protected:
    bool handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool
    handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request);

    bool
    createSigners(Application& app, StorageHelper& storageHelper, ReviewableRequestFrame::pointer request);

public:
    ReviewKYCRecoveryRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
