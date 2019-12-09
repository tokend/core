#pragma once

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/SaleFrame.h"

namespace stellar
{
    class ReviewRedemptionRequestOpFrame : public ReviewRequestOpFrame
    {
    public:

        ReviewRedemptionRequestOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx);

    protected:
        bool
        handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

        bool
        handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                     ReviewableRequestFrame::pointer request) override;

        bool
        handlePermanentReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                              ReviewableRequestFrame::pointer request) override;


        static RedemptionRequest getRedemption(ReviewableRequestFrame::pointer request);
    };
}

