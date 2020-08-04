#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewCreateDataRequestOpFrame : public ReviewRequestOpFrame {

protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;


public:
    ReviewCreateDataRequestOpFrame(Operation const& op, OperationResult& res,
                                 TransactionFrame& parentTx);

};
}
