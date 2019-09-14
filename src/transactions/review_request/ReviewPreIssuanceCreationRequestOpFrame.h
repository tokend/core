#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewPreIssuanceCreationRequestOpFrame : public ReviewRequestOpFrame
{
protected:
	bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
					   ReviewableRequestFrame::pointer request) override;
	bool handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
					  ReviewableRequestFrame::pointer request) override;

public:

  	ReviewPreIssuanceCreationRequestOpFrame(Operation const& op, OperationResult& res,
				   TransactionFrame& parentTx);
};
}
