// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewPaymentRequestHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
PaymentReviewChecker::PaymentReviewChecker(
    const TestManager::pointer testManager, const uint64_t requestID,
    PaymentDelta* delta)
    : ReviewChecker(testManager), delta(delta)
{
    auto request = mTestManager->getStorageHelper()
                       .getReviewableRequestHelper()
                       .loadRequest(requestID);
    if (!request || request->getType() != ReviewableRequestType::CREATE_PAYMENT)
    {
        return;
    }

    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    paymentRequest = std::make_shared<CreatePaymentRequest>(
        request->getRequestEntry().body.createPaymentRequest());
    sourceBalanceBefore =
        balanceHelper.loadBalance(request->getRequestEntry()
                                      .body.createPaymentRequest()
                                      .paymentOp.sourceBalanceID);

    auto destination = request->getRequestEntry()
                           .body.createPaymentRequest()
                           .paymentOp.destination;
    if (destination.type() == PaymentDestinationType::BALANCE)
    {
        destBalanceBefore = balanceHelper.loadBalance(destination.balanceID());
    }

    balanceHelper.loadBalances(mTestManager->getApp().getAdminID(),
                               commissionBalancesBefore);
    for (auto& balanceFrame : commissionBalancesBefore)
    {
        commissionBalancesBeforeTxByAsset[balanceFrame->getAsset()] =
            balanceFrame;
    }
}

void
PaymentReviewChecker::checkApprove(ReviewableRequestFrame::pointer request)
{
    REQUIRE(!!paymentRequest);
    REQUIRE(!!sourceBalanceBefore);

    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    auto sourceBalanceAfter =
        balanceHelper.loadBalance(paymentRequest->paymentOp.sourceBalanceID);

    if (!delta)
        return;

    REQUIRE(delta->source.size() < 3);
    REQUIRE(delta->destination.size() < 2);
    REQUIRE(delta->commission.size() < 3);

    auto sourceDelta = delta->source;
    auto destDelta = delta->destination;
    auto commissionDelta = delta->commission;

    auto destination = paymentRequest->paymentOp.destination;

    for (auto& item : sourceDelta)
    {
        if (item.asset == sourceBalanceBefore->getAsset())
        {
            auto sourceBalanceAfterTx =
                balanceHelper.loadBalance(sourceBalanceBefore->getBalanceID());
            REQUIRE(sourceBalanceAfterTx->getAmount() ==
                    sourceBalanceBefore->getAmount() + item.amountDelta);
            continue;
        }

        throw std::runtime_error("Unexpected asset code");
    }

    for (auto& item : destDelta)
    {
        BalanceFrame::pointer destBalanceAfterTx;

        switch (destination.type())
        {
        case PaymentDestinationType::ACCOUNT:
        {
            destBalanceAfterTx =
                balanceHelper.loadBalance(destination.accountID(), item.asset);
            break;
        }
        case PaymentDestinationType::BALANCE:
        {
            destBalanceAfterTx =
                balanceHelper.loadBalance(destination.balanceID());
            break;
        }
        }

        REQUIRE(!!destBalanceAfterTx);
        if (!destBalanceBefore)
        {
            REQUIRE(destBalanceAfterTx->getAmount() == item.amountDelta);
            continue;
        }
        REQUIRE(destBalanceAfterTx->getAmount() ==
                destBalanceBefore->getAmount() + item.amountDelta);
    }

    for (auto& item : commissionDelta)
    {
        BalanceFrame::pointer commissionBalanceBeforeTx;

        if (commissionBalancesBeforeTxByAsset.count(item.asset) > 0)
            commissionBalanceBeforeTx =
                commissionBalancesBeforeTxByAsset[item.asset];

        auto commissionBalanceAfterTx = balanceHelper.loadBalance(
            mTestManager->getApp().getAdminID(), item.asset);
        if (!commissionBalanceBeforeTx)
        {
            REQUIRE(commissionBalanceAfterTx->getAmount() == item.amountDelta);
            continue;
        }
        REQUIRE(commissionBalanceAfterTx->getAmount() ==
                commissionBalanceBeforeTx->getAmount() + item.amountDelta);
    }
}

ReviewPaymentRequestHelper::ReviewPaymentRequestHelper(
    TestManager::pointer testManager)
    : ReviewRequestHelper(testManager)
{
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTx(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult)
{
    auto checker = PaymentReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTx(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker);
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTxWithTasks(
    Account& source, uint64_t requestID, Hash requestHash,
    ReviewableRequestType requestType, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult,
    uint32_t* tasksToAdd, uint32_t* tasksToRemove)
{
    auto checker = PaymentReviewChecker(mTestManager, requestID);
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(
        source, requestID, requestHash, requestType, action, rejectReason,
        expectedResult, checker, tasksToAdd, tasksToRemove);
}

ReviewRequestResult
ReviewPaymentRequestHelper::applyReviewRequestTxWithTasks(
    Account& source, uint64_t requestID, ReviewRequestOpAction action,
    std::string rejectReason, ReviewRequestResultCode expectedResult,
    uint32_t* tasksToAdd, uint32_t* tasksToRemove)
{
    return ReviewRequestHelper::applyReviewRequestTxWithTasks(
        source, requestID, action, rejectReason, expectedResult, tasksToAdd,
        tasksToRemove);
}
}
}
