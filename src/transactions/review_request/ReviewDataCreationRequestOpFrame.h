#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewDataCreationRequestOpFrame : public ReviewRequestOpFrame {
    bool
    tryGetSignerRequirements(StorageHelper& sh,
                             std::vector<SignerRequirement>& result, LedgerManager& lm) const override;

protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool
    handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) override;

public:
    ReviewDataCreationRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
