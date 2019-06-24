#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewChangeRoleRequestOpFrame : public ReviewRequestOpFrame
{
protected:
    bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool handleReject(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

public:
    ReviewChangeRoleRequestOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

    bool doCheckValid(Application &app) override;
};
}
