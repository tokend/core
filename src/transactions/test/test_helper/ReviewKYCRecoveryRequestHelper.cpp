#include "ReviewKYCRecoveryRequestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/SignerHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{
namespace txtest
{
void KycRecoveryReviewChecker::checkApproval(KYCRecoveryRequest const& request,
                                     AccountID const& requestor)
{
}

void KycRecoveryReviewChecker::checkPermanentReject(KYCRecoveryRequest const& request,
                                            AccountID const& requestor)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto signers = storageHelper.getSignerHelper().loadSigners(request.targetAccount);
    REQUIRE(signers.size() == 1);
}

void KycRecoveryReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    if (request->getType() != ReviewableRequestType::KYC_RECOVERY)
    {
        throw std::runtime_error("Expected kyc recovery request type");
    }

    return checkApproval(request->getRequestEntry().body.kycRecoveryRequest(), request->getRequestor());
}

void KycRecoveryReviewChecker::checkPermanentReject(ReviewableRequestFrame::pointer request)
{
    if (request->getType() != ReviewableRequestType::KYC_RECOVERY)
    {
        throw std::runtime_error("Expected kyc recovery request type");
    }

    return checkPermanentReject(request->getRequestEntry().body.kycRecoveryRequest(), request->getRequestor());
}

ReviewKycRecoveryHelper::ReviewKycRecoveryHelper(TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult ReviewKycRecoveryHelper::applyReviewRequestTx(Account& source,
                                                               uint64_t requestID, Hash requestHash, ReviewableRequestType requestType,
                                                               ReviewRequestOpAction action, std::string rejectReason,
                                                               ReviewRequestResultCode expectedResult)
{
    auto kycRecoveryReviewChecker = KycRecoveryReviewChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
                                                     requestHash, requestType,
                                                     action, rejectReason,
                                                     expectedResult,
                                                     kycRecoveryReviewChecker);
}

ReviewRequestResult
ReviewKycRecoveryHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                    ReviewableRequestType requestType, ReviewRequestOpAction action,
                                                    std::string rejectReason,
                                                    ReviewRequestResultCode expectedResult, uint32_t *tasksToAdd,
                                                    uint32_t *tasksToRemove) {
    auto checker = KycRecoveryReviewChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                              requestHash, requestType,
                                                              action, rejectReason,
                                                              expectedResult,
                                                              checker,
                                                              tasksToAdd,
                                                              tasksToRemove
    );
}

ReviewRequestResult ReviewKycRecoveryHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
                                                                        ReviewRequestOpAction action,
                                                                        std::string rejectReason,
                                                                        ReviewRequestResultCode expectedResult,
                                                                        uint32_t *tasksToAdd,
                                                                        uint32_t *tasksToRemove) {
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID, action, rejectReason,
                                                              expectedResult, tasksToAdd, tasksToRemove);
}
}
}
