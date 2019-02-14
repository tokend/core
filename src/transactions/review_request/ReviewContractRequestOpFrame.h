#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewContractRequestOpFrame : public ReviewRequestOpFrame
{

protected:
    bool handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

    bool checkCustomerDetailsLength(Application& app, Database& db, LedgerDelta& delta);

public:
    ReviewContractRequestOpFrame(Operation const& op, OperationResult& res,
                                 TransactionFrame& parentTx);

};
}