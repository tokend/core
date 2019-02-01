#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewWithdrawalRequestOpFrame : public ReviewRequestOpFrame
{
protected:
	bool handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) override;
	bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request) override;

	// returns total fee to pay, throws exception if overflow
	uint64_t getTotalFee(const uint64_t requestID, WithdrawalRequest& withdrawalRequest);
	// returns total amount to be charged, throws exception if overflow
	uint64_t getTotalAmountToCharge(const uint64_t requestID, WithdrawalRequest& withdrawalRequest);

    bool rejectWithdrawalRequest(Application& app, LedgerDelta& delta,
                                 LedgerManager& ledgerManager,
                                 ReviewableRequestFrame::pointer request,
                                 WithdrawalRequest& withdrawRequest);

public:

	  ReviewWithdrawalRequestOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx);

      bool doCheckValid(Application &app) override;

protected:
    bool handlePermanentReject(Application& app, LedgerDelta& delta,
        LedgerManager& ledgerManager,
        ReviewableRequestFrame::pointer request) override;

    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                          int32_t ledgerVersion) const override;
};
}
