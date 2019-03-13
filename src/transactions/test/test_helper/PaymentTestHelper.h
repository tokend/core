#pragma once

#include "TxHelper.h"

namespace stellar {
    namespace txtest {
        struct BalanceDelta {
            AssetCode asset;
            int64_t amountDelta;
        };

        struct PaymentDelta {
            std::vector<BalanceDelta> source;
            std::vector<BalanceDelta> destination;
            std::vector<BalanceDelta> commission;
        };

        class PaymentTestHelper : TxHelper {
        public:
            explicit PaymentTestHelper(TestManager::pointer testManager);

            TransactionFramePtr createPaymentTx(Account &source, BalanceID sourceBalanceID,
                                                  PaymentOp::_destination_t destination, uint64_t amount,
                                                  PaymentFeeData feeData, std::string subject, std::string reference);

            PaymentResult applyPaymentTx(Account &source, BalanceID sourceBalanceID,
                                             PaymentOp::_destination_t destination, uint64_t amount,
                                             PaymentFeeData feeData, std::string subject, std::string reference,
                                             PaymentDelta *paymentDelta = nullptr,
                                             PaymentResultCode expectedResultCode = PaymentResultCode::SUCCESS,
                                             OperationResultCode expectedOpResultCode = OperationResultCode::opINNER);

            PaymentOp::_destination_t createDestinationForAccount(AccountID destAccountID);

            PaymentOp::_destination_t createDestinationForBalance(BalanceID destBalanceID);

            Fee createFeeData(uint64 fixedFee, uint64 paymentFee);

            PaymentFeeData createPaymentFeeData(Fee sourceFeeData, Fee destFeeData,
                                                  bool sourcePaysForDest);
        };
    }
}