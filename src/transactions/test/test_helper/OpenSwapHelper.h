#pragma once

#include "TxHelper.h"

namespace stellar
{
namespace txtest
{

class OpenSwapTestHelper : TxHelper
{
  public:
    explicit OpenSwapTestHelper(TestManager::pointer testManager);

    OpenSwapOp makeOpenSwap(BalanceID sourceBalanceID,
                            OpenSwapOp::_destination_t destination,
                            uint64_t amount, PaymentFeeData feeData,
                            std::string details, Hash secretHash,
                            int64_t lockTime);
    TransactionFramePtr
    createOpenSwapTx(Account& source, BalanceID sourceBalanceID,
                     OpenSwapOp::_destination_t destination, uint64_t amount,
                     PaymentFeeData feeData, std::string details,
                     Hash secretHash, int64_t lockTime);

    OpenSwapResult applyOpenSwapTx(
        Account& source, BalanceID sourceBalanceID,
        OpenSwapOp::_destination_t destination, uint64_t amount,
        PaymentFeeData feeData, std::string details, Hash secretHash,
        int64_t lockTime,
        OpenSwapResultCode expectedResultCode = OpenSwapResultCode::SUCCESS,
        OperationResultCode expectedOpResultCode =
            OperationResultCode::opINNER);

    OpenSwapOp::_destination_t
    createDestinationForAccount(AccountID destAccountID);

    OpenSwapOp::_destination_t
    createDestinationForBalance(BalanceID destBalanceID);

    Fee createFeeData(uint64 amount, uint64 fixedFee, uint64 openSwapFee,
                      uint64 minAmount);

    PaymentFeeData createPaymentFeeData(Fee sourceFeeData, Fee destFeeData,
                                        bool sourcePaysForDest);
};
}
}