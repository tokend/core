// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "PaymentRequestHelper.h"
#include "ReviewPaymentRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include "transactions/payment/CreatePaymentRequestOpFrame.h"

namespace stellar
{
namespace txtest
{
PaymentRequestHelper::PaymentRequestHelper(
    const TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ReviewRequestResult
PaymentRequestHelper::createApprovedPayment(Account& root, Account& source,
                                            const CreatePaymentRequest request)
{
    uint32_t zeroTasks = 0;
    auto requestCreationResult =
        applyCreatePaymentRequest(source, request, &zeroTasks);
    if (requestCreationResult.code() ==
            CreatePaymentRequestResultCode::SUCCESS &&
        requestCreationResult.success().fulfilled)
    {
        auto result = ReviewRequestResult{};
        result.code(ReviewRequestResultCode::SUCCESS);
        result.success().fulfilled = true;
        result.success().typeExt.requestType(
            ReviewableRequestType::CREATE_PAYMENT);
        REQUIRE(requestCreationResult.success().paymentResult);
        result.success().typeExt.paymentResult() =
            requestCreationResult.success().paymentResult.activate();
        return result;
    }

    auto reviewer = ReviewPaymentRequestHelper(mTestManager);
    return reviewer.applyReviewRequestTx(
        root, requestCreationResult.success().requestID,
        ReviewRequestOpAction::APPROVE, "");
}

CreatePaymentRequestResult
PaymentRequestHelper::applyCreatePaymentRequest(
    Account& source, const CreatePaymentRequest request, uint32_t* allTasks,
    OperationResultCode operationResultCode,
    CreatePaymentRequestResultCode expectedResult,
    PaymentResultCode paymentResultCode)
{
    auto& reviewableRequestHelper =
        mTestManager->getStorageHelper().getReviewableRequestHelper();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper.countObjects();

    auto txFrame = createPaymentRequestTx(source, request, allTasks);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == operationResultCode);
    if (operationResultCode != OperationResultCode::opINNER)
    {
        return CreatePaymentRequestResult{};
    }

    auto actualResultCode = CreatePaymentRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper.countObjects();
    if (expectedResult != CreatePaymentRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx ==
                reviewableRequestCountAfterTx);

        if (expectedResult == CreatePaymentRequestResultCode::INVALID_PAYMENT)
        {
            REQUIRE(opResult.tr().createPaymentRequestResult().paymentCode() ==
                    paymentResultCode);
        }
        return opResult.tr().createPaymentRequestResult();
    }

    return opResult.tr().createPaymentRequestResult();
}
CreatePaymentRequest
PaymentRequestHelper::createPaymentRequest(
    BalanceID source, PaymentOp::_destination_t destination, int64_t amount,
    PaymentFeeData feeData, std::string reference, std::string subject,
    longstring* creatorDetails)
{

    PaymentOp payment;
    payment.amount = amount;
    payment.reference = reference;
    payment.feeData = feeData;
    payment.sourceBalanceID = source;
    payment.subject = subject;
    payment.destination = destination;

    CreatePaymentRequest request;
    request.paymentOp = payment;
    if (creatorDetails != nullptr) {
        request.ext.v(LedgerVersion::MOVEMENT_REQUESTS_DETAILS);
        request.ext.creatorDetails() = *creatorDetails;
    }
    return request;
}

TransactionFramePtr
PaymentRequestHelper::createPaymentRequestTx(Account& source,
                                             const CreatePaymentRequest request,
                                             uint32_t* allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_PAYMENT_REQUEST);
    baseOp.body.createPaymentRequestOp().request = request;
    if (allTasks)
        baseOp.body.createPaymentRequestOp().allTasks.activate() = *allTasks;
    baseOp.body.createPaymentRequestOp().ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
