#pragma once

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/SaleFrame.h"

namespace stellar
{
class ReviewAMLAlertRequestOpFrame : public ReviewRequestOpFrame
{
public:

    ReviewAMLAlertRequestOpFrame(Operation const& op, OperationResult& res,
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


    static AMLAlertRequest getAmlAlert(ReviewableRequestFrame::pointer request);
};
}

