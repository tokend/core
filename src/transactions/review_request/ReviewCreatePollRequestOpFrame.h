#pragma once

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewCreatePollRequestOpFrame : public ReviewRequestOpFrame {

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    ReviewCreatePollRequestOpFrame(Operation const &op, OperationResult &res,
                                   TransactionFrame &parentTx);


protected:
    bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool
    handleReject(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                 ReviewableRequestFrame::pointer request) override;
};
}
