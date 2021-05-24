#include "CancelCreateDeferredPaymentRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "transactions/payment/CancelDeferredPaymentCreationRequestOpFrame.h"

namespace stellar
{
namespace txtest
{
CancelCreateDeferredPaymentRequestHelper::
    CancelCreateDeferredPaymentRequestHelper(
        txtest::TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

CancelDeferredPaymentCreationRequestResult
CancelCreateDeferredPaymentRequestHelper::
    applyCancelCreateDeferredPaymentRequest(
        txtest::Account& source, uint64_t requestID,
        CancelDeferredPaymentCreationRequestResultCode expectedResult)
{
    auto& reviewableRequestHelper =
        mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto reviewableRequestCountBeforeTx =
        reviewableRequestHelper.countObjects();

    auto txFrame = cancelCreateDeferredPaymentRequest(source, requestID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    auto actualResultCode =
        CancelDeferredPaymentCreationRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper.countObjects();
    if (expectedResult !=
        CancelDeferredPaymentCreationRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx ==
                reviewableRequestCountAfterTx);
        return CancelDeferredPaymentCreationRequestResult{};
    }

    REQUIRE(reviewableRequestCountBeforeTx ==
            reviewableRequestCountAfterTx + 1);

    return opResult.tr().cancelDeferredPaymentCreationRequestResult();
}

TransactionFramePtr
CancelCreateDeferredPaymentRequestHelper::cancelCreateDeferredPaymentRequest(
    txtest::Account& source, uint64_t requestID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_DEFERRED_PAYMENT_CREATION_REQUEST);
    auto& op = baseOp.body.cancelDeferredPaymentCreationRequestOp();
    op.requestID = requestID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
