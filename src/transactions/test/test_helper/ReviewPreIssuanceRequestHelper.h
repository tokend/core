#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "ReviewRequestTestHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/AssetFrame.h"

namespace stellar
{
namespace txtest 
{	
    class ReviewPreIssuanceChecker : public ReviewChecker
    {
    public:
        ReviewPreIssuanceChecker(
            const TestManager::pointer& testManager, const uint64_t requestID);

        ReviewPreIssuanceChecker(const TestManager::pointer& testManager,
                                 std::shared_ptr<PreIssuanceRequest> preIssuanceRequest);

        void checkApprove(ReviewableRequestFrame::pointer) override;
    protected:
        std::shared_ptr<PreIssuanceRequest> preIssuanceRequest;
        AssetFrame::pointer assetFrameBeforeTx;

    };
	class ReviewPreIssuanceRequestHelper : public ReviewRequestHelper
	{
		uint32_t mTasksToRemove = 0;
	public:
		ReviewPreIssuanceRequestHelper(TestManager::pointer testManager);

		ReviewRequestResult applyReviewRequestTx(Account & source, uint64_t requestID, Hash requestHash, ReviewableRequestType requestType,
			ReviewRequestOpAction action, std::string rejectReason,
			ReviewRequestResultCode expectedResult = ReviewRequestResultCode::SUCCESS) override;

		ReviewRequestResult applyReviewRequestTx(Account & source, uint64_t requestID, ReviewRequestOpAction action, std::string rejectReason,
			ReviewRequestResultCode expectedResult = ReviewRequestResultCode::SUCCESS);

		ReviewRequestResult
		applyReviewRequestTxWithTasks(Account & source, uint64_t requestID, ReviewRequestOpAction action,
							 std::string rejectReason, uint32_t tasksToRemove, ReviewRequestResultCode expectedResult =
							 		ReviewRequestResultCode::SUCCESS);

		TransactionFramePtr
		createReviewRequestTx(Account &source, uint64_t requestID, Hash requestHash,
							  ReviewableRequestType requestType, ReviewRequestOpAction action,
							  std::string rejectReason) override;
	};
}
}
