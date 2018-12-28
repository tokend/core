#pragma once

#include "ReviewRequestTestHelper.h"

namespace stellar {
    namespace txtest {
        class ReviewUpdateSaleDetailsRequestChecker : public ReviewChecker {
        public:
            explicit ReviewUpdateSaleDetailsRequestChecker(TestManager::pointer testManager);

            void checkApprove(ReviewableRequestFrame::pointer request) override;
        };

        class ReviewUpdateSaleDetailsRequestTestHelper : public ReviewRequestHelper {
        public:
            explicit ReviewUpdateSaleDetailsRequestTestHelper(TestManager::pointer testManager);

            ReviewRequestResult
            applyReviewRequestTx(Account &source, uint64_t requestID, Hash requestHash,
                                 ReviewableRequestType requestType,
                                 ReviewRequestOpAction action, std::string rejectReason,
                                 ReviewRequestResultCode expectedResult) override;

            ReviewRequestResult applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                              ReviewableRequestType requestType,
                                                              ReviewRequestOpAction action, std::string rejectReason,
                                                              ReviewRequestResultCode expectedResult,
                                                              uint32_t *tasksToAdd, uint32_t *tasksToRemove) override;

            using ReviewRequestHelper::applyReviewRequestTx;
        };
    }
}