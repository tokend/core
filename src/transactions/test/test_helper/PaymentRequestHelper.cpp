// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "PaymentRequestHelper.h"
#include "ReviewPaymentRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
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
    CreatePaymentRequestResultCode expectedResult)
{
    auto reviewableRequestHelper = ReviewableRequestHelper::Instance();
    auto reviewableRequestCountBeforeTx = reviewableRequestHelper->countObjects(
        mTestManager->getDB().getSession());

    auto txFrame = createPaymentRequestTx(source, request, allTasks);
    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = CreatePaymentRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    auto reviewableRequestCountAfterTx = reviewableRequestHelper->countObjects(
        mTestManager->getDB().getSession());
    if (expectedResult != CreatePaymentRequestResultCode::SUCCESS)
    {
        REQUIRE(reviewableRequestCountBeforeTx ==
                reviewableRequestCountAfterTx);
        return opResult.tr().createPaymentRequestResult();
    }

    return opResult.tr().createPaymentRequestResult();
}
CreatePaymentRequest
PaymentRequestHelper::createPaymentRequest(
    BalanceID source, int64_t amount, PaymentDestinationType destinationType,
    std::string receiver, std::string reference, std::string subject,
    PaymentFeeData feeData)
{

    PaymentOp payment;
    payment.amount = amount;
    payment.reference = reference;
    payment.feeData = feeData;
    payment.sourceBalanceID = source;
    payment.subject = subject;
    payment.destination.type(destinationType);

    switch (destinationType)
    {
    case PaymentDestinationType::BALANCE:
    {
        payment.destination.balanceID() = BalanceKeyUtils::fromStrKey(receiver);
        break;
    }
    case PaymentDestinationType::ACCOUNT:
    {
        payment.destination.accountID() = PubKeyUtils::fromStrKey(receiver);
        break;
    }
    }

    CreatePaymentRequest request;
    request.paymentOp = payment;
    return request;
}

TransactionFramePtr
PaymentRequestHelper::createPaymentRequestTx(Account& source,
                                             const CreatePaymentRequest request,
                                             uint32_t* allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_PAYMENT_REQUEST);
    auto& op = baseOp.body.createPaymentRequestOp();
    op.request = request;
    if (allTasks)
        op.allTasks.activate() = *allTasks;
    op.ext.v(LedgerVersion::EMPTY_VERSION);
    return txFromOperation(source, baseOp, nullptr);
}
}
}
