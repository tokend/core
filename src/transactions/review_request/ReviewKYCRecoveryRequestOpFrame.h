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

    void
    removeRecoverySigner(Application& app, StorageHelper& storageHelper, KYCRecoveryRequest request, AccountFrame::pointer account);

    bool
    createSigners(Application& app, StorageHelper& storageHelper, KYCRecoveryRequest request, AccountFrame::pointer account);

    bool
    handleSigners(Application &app, StorageHelper& storageHelper, ReviewableRequestFrame::pointer request);

public:
    ReviewKYCRecoveryRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
