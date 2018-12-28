#include <ledger/SaleHelper.h>
#include <lib/catch.hpp>
#include "ReviewUpdateSaleDetailsRequestHelper.h"

namespace stellar {
    namespace txtest {
        ReviewUpdateSaleDetailsRequestChecker::ReviewUpdateSaleDetailsRequestChecker(TestManager::pointer testManager)
                : ReviewChecker(testManager) {

        }

        void ReviewUpdateSaleDetailsRequestChecker::checkApprove(ReviewableRequestFrame::pointer request) {
            auto updateSaleDetailsRequest = request->getRequestEntry().body.updateSaleDetailsRequest();
            auto saleAfterTx = SaleHelper::Instance()->loadSale(updateSaleDetailsRequest.saleID, mTestManager->getDB());
            REQUIRE(!!saleAfterTx);
            REQUIRE(saleAfterTx->getSaleEntry().details == updateSaleDetailsRequest.newDetails);
        }


        ReviewUpdateSaleDetailsRequestTestHelper::ReviewUpdateSaleDetailsRequestTestHelper(
                TestManager::pointer testManager) : ReviewRequestHelper(testManager) {

        }

        ReviewRequestResult
        ReviewUpdateSaleDetailsRequestTestHelper::applyReviewRequestTx(Account &source, uint64_t requestID,
                                                                       Hash requestHash,
                                                                       ReviewableRequestType requestType,
                                                                       ReviewRequestOpAction action,
                                                                       std::string rejectReason,
                                                                       ReviewRequestResultCode expectedResult) {
            auto checker = ReviewUpdateSaleDetailsRequestChecker(mTestManager);
            return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                             requestHash, requestType,
                                                             action, rejectReason,
                                                             expectedResult,
                                                             checker);
        }

        ReviewRequestResult
        ReviewUpdateSaleDetailsRequestTestHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
                                                                                Hash requestHash,
                                                                                ReviewableRequestType requestType,
                                                                                ReviewRequestOpAction action,
                                                                                std::string rejectReason,
                                                                                ReviewRequestResultCode expectedResult,
                                                                                uint32_t *tasksToAdd,
                                                                                uint32_t *tasksToRemove) {
            auto checker = ReviewUpdateSaleDetailsRequestChecker(mTestManager);
            return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                             requestHash, requestType,
                                                             action, rejectReason,
                                                             expectedResult,
                                                             checker, tasksToAdd, tasksToRemove);
        }
    }
}