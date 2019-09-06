#pragma once

#include <ledger/ReviewableRequestFrame.h>
#include <transactions/TransactionFrame.h>
#include "main/Application.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerManager.h"
#include "database/Database.h"
#include <lib/soci/src/core/transaction.h>
#include <xdrpp/printer.h>

namespace stellar
{

class ReviewRequestHelper {
private:
    Application& mApp;
    StorageHelper& mStorageHelper;
    LedgerManager& mLedgerManager;
    ReviewableRequestFrame::pointer mRequest;

    std::pair<bool, ReviewRequestResult> tryReviewRequest(TransactionFrame& parentTx);

    ReviewRequestHelper(Application& app, LedgerManager& ledgerManager, StorageHelper& storageHelper,
                        ReviewableRequestFrame::pointer reviewableRequest);

    ReviewRequestResult tryApproveRequest(TransactionFrame& parentTx);

public:

    static ReviewRequestResultCode tryApproveRequest(TransactionFrame& parentTx, Application& app,
                                                     LedgerManager& ledgerManager, StorageHelper& storageHelper,
                                                     ReviewableRequestFrame::pointer reviewableRequest);

    static ReviewRequestResult tryApproveRequestWithResult(TransactionFrame& parentTx, Application& app,
                                                           LedgerManager& ledgerManager, StorageHelper& storageHelper,
                                                           ReviewableRequestFrame::pointer reviewableRequest);
};

}
