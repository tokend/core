#pragma once

#include "ReviewRequestOpFrame.h"

namespace stellar {
    class ReviewUpdateSaleDetailsRequestOpFrame : public ReviewRequestOpFrame {
    protected:
        bool handleApprove(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager,
                           ReviewableRequestFrame::pointer request) override;



    public:
        ReviewUpdateSaleDetailsRequestOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);
    };
}