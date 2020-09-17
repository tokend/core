#include "CancelCloseDeferredPaymentRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "transactions/CancelCloseDeferredPaymentRequestOpFrame.h"

namespace stellar
{
namespace txtest
{
CancelCloseDeferredPaymentRequestHelper::
    CancelCloseDeferredPaymentRequestHelper(
        txtest::TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

CancelCloseDeferredPaymentRequestResult
CancelCloseDeferredPaymentRequestHelper::applyCancelCloseDeferredPaymentRequest(
    txtest::Account& source, uint64_t requestID,
    CancelCloseDeferredPaymentRequestResultCode expectedResult)
{
    auto& reviewableRequestHelper =
        mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto reviewableRequestCountBeforeTx =
        reviewableRequestHelper.countObjects();

    auto txFrame = cancelCloseDeferredPaymentRequest(source, requestID);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    auto actualResultCode =
        CancelCloseDeferredPaymentRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper.countObjects();
    if (expectedResult != CancelCloseDeferredPaymentRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx ==
                reviewableRequestCountAfterTx);
        return CancelCloseDeferredPaymentRequestResult{};
    }

    REQUIRE(reviewableRequestCountBeforeTx ==
            reviewableRequestCountAfterTx + 1);

    return opResult.tr().cancelCloseDeferredPaymentRequestResult();
}

TransactionFramePtr
CancelCloseDeferredPaymentRequestHelper::cancelCloseDeferredPaymentRequest(
    txtest::Account& source, uint64_t requestID)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CANCEL_CLOSE_DEFERRED_PAYMENT_REQUEST);
    auto& op = baseOp.body.cancelCloseDeferredPaymentRequestOp();
    op.requestID = requestID;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
