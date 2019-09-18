#include "OpenSwapHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/SwapHelper.h"
#include "test/test_marshaler.h"
#include "transactions/swap/OpenSwapOpFrame.h"

namespace stellar
{
namespace txtest
{
OpenSwapTestHelper::OpenSwapTestHelper(TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

OpenSwapOp::_destination_t
OpenSwapTestHelper::createDestinationForAccount(AccountID destAccountID)
{
    OpenSwapOp::_destination_t destination;
    destination.type(PaymentDestinationType::ACCOUNT);
    destination.accountID() = destAccountID;
    return destination;
}

OpenSwapOp::_destination_t
OpenSwapTestHelper::createDestinationForBalance(BalanceID destBalanceID)
{
    OpenSwapOp::_destination_t destination;
    destination.type(PaymentDestinationType::BALANCE);
    destination.balanceID() = destBalanceID;
    return destination;
}

Fee
OpenSwapTestHelper::createFeeData(uint64 amount, uint64 fixedFee,
                                  uint64 openSwapFee, uint64 minAmount)
{
    Fee feeData;

    feeData.fixed = fixedFee;

    REQUIRE(bigDivide(feeData.percent, amount, openSwapFee, 100 * ONE, ROUND_UP,
                      minAmount));

    return feeData;
}

PaymentFeeData
OpenSwapTestHelper::createPaymentFeeData(Fee sourceFeeData, Fee destFeeData,
                                         bool sourcePaysForDest)
{
    PaymentFeeData paymentFeeData;

    paymentFeeData.sourceFee = sourceFeeData;
    paymentFeeData.destinationFee = destFeeData;
    paymentFeeData.sourcePaysForDest = sourcePaysForDest;

    return paymentFeeData;
}

TransactionFramePtr
OpenSwapTestHelper::createOpenSwapTx(Account& source, BalanceID sourceBalanceID,
                                     OpenSwapOp::_destination_t destination,
                                     uint64_t amount, PaymentFeeData feeData,
                                     std::string details, Hash secretHash,
                                     int64_t lockTime)
{
    Operation baseOp;
    baseOp.body.type(OperationType::OPEN_SWAP);
    baseOp.body.openSwapOp() =
        makeOpenSwap(sourceBalanceID, destination, amount, feeData, details,
                     secretHash, lockTime);

    return txFromOperation(source, baseOp, nullptr);
}

OpenSwapOp
OpenSwapTestHelper::makeOpenSwap(BalanceID sourceBalanceID,
                                 OpenSwapOp::_destination_t destination,
                                 uint64_t amount, PaymentFeeData feeData,
                                 std::string details, Hash secretHash,
                                 int64_t lockTime)
{
    OpenSwapOp op;
    op.sourceBalance = sourceBalanceID;
    op.destination = destination;
    op.amount = amount;
    op.feeData = feeData;
    op.details = details;
    op.secretHash = secretHash;
    op.lockTime = lockTime;
    return op;
}

OpenSwapResult
OpenSwapTestHelper::applyOpenSwapTx(Account& source, BalanceID sourceBalanceID,
                                    OpenSwapOp::_destination_t destination,
                                    uint64_t amount, PaymentFeeData feeData,
                                    std::string details, Hash secretHash,
                                    int64_t lockTime,
                                    OpenSwapResultCode expectedResultCode,
                                    OperationResultCode expectedOpResultCode)
{
    auto& sh = mTestManager->getStorageHelper();
    auto& balanceHelper = sh.getBalanceHelper();

    auto sourceBalanceBeforeTx = balanceHelper.loadBalance(sourceBalanceID);

    TransactionFramePtr txFrame;

    txFrame = createOpenSwapTx(source, sourceBalanceID, destination, amount,
                               feeData, details, secretHash, lockTime);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == expectedOpResultCode);
    if (expectedOpResultCode != OperationResultCode::opINNER)
    {
        return OpenSwapResult();
    }

    auto actualResultCode = OpenSwapOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);

    auto actualOpenSwapResult = opResult.tr().openSwapResult();

    if (expectedResultCode != OpenSwapResultCode::SUCCESS)
    {
        return actualOpenSwapResult;
    }

    auto swap =
        sh.getSwapHelper().mustLoadSwap(actualOpenSwapResult.success().swapID);
    auto swapEntry = swap->getSwapEntry();
    auto actualTotalAmount = swapEntry.amount + swapEntry.fee;

    auto sourceBalanceAfterTx = balanceHelper.loadBalance(sourceBalanceID);
    REQUIRE(sourceBalanceAfterTx->getAmount() + actualTotalAmount ==
            sourceBalanceBeforeTx->getAmount());

    REQUIRE(sourceBalanceAfterTx->getLocked() ==
            sourceBalanceBeforeTx->getLocked() + actualTotalAmount);

    return actualOpenSwapResult;
}
}
}
