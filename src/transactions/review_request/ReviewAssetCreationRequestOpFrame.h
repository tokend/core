#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewAssetCreationRequestOpFrame : public ReviewRequestOpFrame
{
protected:
	bool handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) override;

	virtual SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails) const override;

    void createSystemBalances(AssetCode assetCode, Application &app, LedgerDelta &delta, uint64_t ledgerCloseTime);
  public:

	  ReviewAssetCreationRequestOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx);
};
}
