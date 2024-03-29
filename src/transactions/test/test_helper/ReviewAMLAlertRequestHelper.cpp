#include "ReviewAMLAlertRequestHelper.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "ledger/BalanceHelper.h"


namespace stellar
{
namespace txtest
{
void AmlReviewChecker::checkApproval(AMLAlertRequest const& request,
    AccountID const& requestor)
{
    auto& assetHelper = mTestManager->getStorageHelper().getAssetHelper();

    auto balanceBeforeTx = mStateBeforeTxHelper.getBalance(request.balanceID);
    REQUIRE(!!balanceBeforeTx);
    auto balanceAfterTx = mTestManager->getStorageHelper().getBalanceHelper().loadBalance(request.balanceID);
    REQUIRE(!!balanceAfterTx);
    REQUIRE(balanceBeforeTx->getAmount() == balanceAfterTx->getAmount());
    REQUIRE(balanceBeforeTx->getLocked() - request.amount == balanceAfterTx->getLocked());

    auto assetBeforeTx = mStateBeforeTxHelper.getAssetEntry(balanceBeforeTx->getAsset());
    auto assetFrameAfterTx = assetHelper.loadAsset(balanceBeforeTx->getAsset());
    auto assetAfterTx = assetFrameAfterTx->getAsset();
    REQUIRE(assetBeforeTx.availableForIssueance == assetAfterTx.availableForIssueance);
    REQUIRE(assetBeforeTx.maxIssuanceAmount == assetAfterTx.maxIssuanceAmount);
    REQUIRE(assetBeforeTx.issued - request.amount == assetAfterTx.issued);
}

void AmlReviewChecker::checkPermanentReject(AMLAlertRequest const& request,
    AccountID const& requestor)
{
    auto balanceBeforeTx = mStateBeforeTxHelper.getBalance(request.balanceID);
    REQUIRE(balanceBeforeTx);
    auto balanceAfterTx =mTestManager->getStorageHelper().getBalanceHelper().loadBalance(request.balanceID);
    REQUIRE(balanceAfterTx);
    REQUIRE(balanceBeforeTx->getAmount() + request.amount == balanceAfterTx->getAmount());
    REQUIRE(balanceBeforeTx->getLocked() - request.amount == balanceAfterTx->getLocked());
}

void AmlReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    if (request->getType() != ReviewableRequestType::CREATE_AML_ALERT)
    {
        throw std::runtime_error("Expected aml alert request type");
    }

    return checkApproval(request->getRequestEntry().body.amlAlertRequest(), request->getRequestor());
}

void AmlReviewChecker::checkPermanentReject(ReviewableRequestFrame::pointer request)
{
    if (request->getType() != ReviewableRequestType::CREATE_AML_ALERT)
    {
        throw std::runtime_error("Expected aml alert request type");
    }

    return checkPermanentReject(request->getRequestEntry().body.amlAlertRequest(), request->getRequestor());
}

ReviewAmlAlertHelper::ReviewAmlAlertHelper(TestManager::pointer testManager) : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult ReviewAmlAlertHelper::applyReviewRequestTx(Account& source,
    uint64_t requestID, Hash requestHash, ReviewableRequestType requestType,
    ReviewRequestOpAction action, std::string rejectReason,
    ReviewRequestResultCode expectedResult)
{
    auto amlReviewChecker = AmlReviewChecker(mTestManager);
    return ReviewRequestHelper::applyReviewRequestTx(source, requestID,
        requestHash, requestType,
        action, rejectReason,
        expectedResult,
        amlReviewChecker);
}

    ReviewRequestResult
    ReviewAmlAlertHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID, Hash requestHash,
                                                        ReviewableRequestType requestType, ReviewRequestOpAction action,
                                                        std::string rejectReason,
                                                        ReviewRequestResultCode expectedResult, uint32_t *tasksToAdd,
                                                        uint32_t *tasksToRemove) {
        auto checker = AmlReviewChecker(mTestManager);
        return ReviewRequestHelper::applyReviewRequestTxWithTasks(source, requestID,
                                                                  requestHash, requestType,
                                                                  action, rejectReason,
                                                                  expectedResult,
                                                                  checker,
                                                                  tasksToAdd,
                                                                  tasksToRemove
        );
    }

    ReviewRequestResult ReviewAmlAlertHelper::applyReviewRequestTxWithTasks(Account &source, uint64_t requestID,
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
