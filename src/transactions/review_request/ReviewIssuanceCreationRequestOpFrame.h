#pragma once

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewIssuanceCreationRequestOpFrame : public ReviewRequestOpFrame {
    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result,
                             LedgerManager& lm) const override;

protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

    bool addStatistics(StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       AccountFrame::pointer accountFrame,
                       BalanceFrame::pointer balanceFrame,
                       uint64_t amountToAdd,
                       uint64_t& universalAmount);

    uint32_t getSystemTasksToAdd(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                 ReviewableRequestFrame::pointer request);

public:

    ReviewIssuanceCreationRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;
};
}
