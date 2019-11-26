#include "PaymentTestHelper.h"
#include "test/test_marshaler.h"
#include <ledger/BalanceHelper.h>
#include <transactions/payment/PaymentOpFrame.h>
#include "ledger/StorageHelper.h"

namespace stellar
{
namespace txtest
{
PaymentTestHelper::PaymentTestHelper(TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

PaymentOp::_destination_t
PaymentTestHelper::createDestinationForAccount(AccountID destAccountID)
{
    PaymentOp::_destination_t destination;
    destination.type(PaymentDestinationType::ACCOUNT);
    destination.accountID() = destAccountID;
    return destination;
}

PaymentOp::_destination_t
PaymentTestHelper::createDestinationForBalance(BalanceID destBalanceID)
{
    PaymentOp::_destination_t destination;
    destination.type(PaymentDestinationType::BALANCE);
    destination.balanceID() = destBalanceID;
    return destination;
}

Fee
PaymentTestHelper::createFeeData(uint64 fixedFee, uint64 paymentFee)
{
    Fee feeData;

    feeData.fixed = fixedFee;
    feeData.percent = paymentFee;

    return feeData;
}

PaymentFeeData
PaymentTestHelper::createPaymentFeeData(Fee sourceFeeData, Fee destFeeData,
                                        bool sourcePaysForDest)
{
    PaymentFeeData paymentFeeData;

    paymentFeeData.sourceFee = sourceFeeData;
    paymentFeeData.destinationFee = destFeeData;
    paymentFeeData.sourcePaysForDest = sourcePaysForDest;

    return paymentFeeData;
}

TransactionFramePtr
PaymentTestHelper::createPaymentTx(Account& source, BalanceID sourceBalanceID,
                                   PaymentOp::_destination_t destination,
                                   uint64_t amount, PaymentFeeData feeData,
                                   std::string subject, std::string reference)
{
    Operation baseOp;
    baseOp.body.type(OperationType::PAYMENT);
    baseOp.body.paymentOp() = makePayment(sourceBalanceID, destination, amount,
                                          feeData, subject, reference);

    return txFromOperation(source, baseOp, nullptr);
}

PaymentOp
PaymentTestHelper::makePayment(BalanceID sourceBalanceID,
                               PaymentOp::_destination_t destination,
                               uint64_t amount, PaymentFeeData feeData,
                               std::string subject, std::string reference)
{
    PaymentOp op;
    op.sourceBalanceID = sourceBalanceID;
    op.destination = destination;
    op.amount = amount;
    op.feeData = feeData;
    op.subject = subject;
    op.reference = reference;
    return op;
}

PaymentResult
PaymentTestHelper::applyPaymentTx(Account& source, BalanceID sourceBalanceID,
                                  PaymentOp::_destination_t destination,
                                  uint64_t amount, PaymentFeeData feeData,
                                  std::string subject, std::string reference,
                                  PaymentDelta* paymentDelta,
                                  PaymentResultCode expectedResultCode,
                                  OperationResultCode expectedOpResultCode)
{
    auto& db = mTestManager->getDB();
    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    auto sourceBalanceBeforeTx =
        balanceHelper.loadBalance(sourceBalanceID);

    BalanceFrame::pointer destBalanceBeforeTx;
    if (destination.type() == PaymentDestinationType::BALANCE)
    {
        destBalanceBeforeTx =
            balanceHelper.loadBalance(destination.balanceID());
    }

    std::vector<BalanceFrame::pointer> commissionBalancesBeforeTx;
    balanceHelper.loadBalances(mTestManager->getApp().getAdminID(),
                                commissionBalancesBeforeTx);

    std::unordered_map<std::string, BalanceFrame::pointer>
        commissionBalancesBeforeTxByAsset;
    for (auto& balanceFrame : commissionBalancesBeforeTx)
    {
        commissionBalancesBeforeTxByAsset[balanceFrame->getAsset()] =
            balanceFrame;
    }

    TransactionFramePtr txFrame;

    txFrame = createPaymentTx(source, sourceBalanceID, destination, amount,
                              feeData, subject, reference);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpResultCode);
    if (expectedOpResultCode != OperationResultCode::opINNER)
    {
        return PaymentResult();
    }

    auto actualResultCode = PaymentOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);

    auto actualPaymentResult = opResult.tr().paymentResult();

    if (expectedResultCode != PaymentResultCode::SUCCESS)
    {
        return actualPaymentResult;
    }

    if (!paymentDelta)
        return actualPaymentResult;

    REQUIRE(paymentDelta->source.size() < 3);
    REQUIRE(paymentDelta->destination.size() < 2);
    REQUIRE(paymentDelta->commission.size() < 3);

    auto sourceDelta = paymentDelta->source;
    auto destDelta = paymentDelta->destination;
    auto commissionDelta = paymentDelta->commission;

    for (auto& item : sourceDelta)
    {
        if (item.asset == sourceBalanceBeforeTx->getAsset())
        {
            auto sourceBalanceAfterTx =
                balanceHelper.loadBalance(sourceBalanceID);
            REQUIRE(sourceBalanceAfterTx->getAmount() ==
                    sourceBalanceBeforeTx->getAmount() + item.amountDelta);
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
            destBalanceAfterTx = balanceHelper.loadBalance(
                destination.accountID(), item.asset);
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
        if (!destBalanceBeforeTx)
        {
            REQUIRE(destBalanceAfterTx->getAmount() == item.amountDelta);
            continue;
        }
        REQUIRE(destBalanceAfterTx->getAmount() ==
                destBalanceBeforeTx->getAmount() + item.amountDelta);
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
    return actualPaymentResult;
}
}
}
