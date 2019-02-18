#pragma once

#include "ReviewRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class ReviewIssuanceCreationRequestOpFrame : public ReviewRequestOpFrame
{
protected:
	bool handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
					   ReviewableRequestFrame::pointer request) override;

	bool handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
					  ReviewableRequestFrame::pointer request) override;
    bool tryAddStatsV2(StatisticsV2Processor& statisticsV2Processor,
                                                             const BalanceFrame::pointer balance, const uint64_t amountToAdd,
                                                             uint64_t& universalAmount);
    bool addStatistics(Database& db,
					 LedgerDelta& delta, LedgerManager& ledgerManager,
					 BalanceFrame::pointer balanceFrame, const uint64_t amountToAdd,
					 uint64_t& universalAmount);

    uint32_t getSystemTasksToAdd( Application &app, Database& db, LedgerDelta &delta, LedgerManager &ledgerManager,
            ReviewableRequestFrame::pointer request);
public:

    ReviewIssuanceCreationRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doCheckValid(Application &app) override;
};
}
