#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewDataUpdateRequestOpFrame : public ReviewRequestOpFrame {
protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool
    handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) override;

public:
    ReviewDataUpdateRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
