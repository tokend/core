#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "TxHelper.h"
#include "overlay/StellarXDR.h"

namespace stellar
{
namespace txtest
{
class PaymentRequestHelper : TxHelper
{
  public:
    PaymentRequestHelper(TestManager::pointer testManager);

    ReviewRequestResult createApprovedPayment(Account& root, Account& source,
                                              CreatePaymentRequest request);

    CreatePaymentRequestResult applyCreatePaymentRequest(
        Account& source, const CreatePaymentRequest request, uint32_t* allTasks,
        OperationResultCode operationResultCode = OperationResultCode ::opINNER,
        CreatePaymentRequestResultCode expectedResult =
            CreatePaymentRequestResultCode::SUCCESS,
        PaymentResultCode paymentResultCode = PaymentResultCode::SUCCESS);

    CreatePaymentRequest createPaymentRequest(
        BalanceID source, PaymentOp::_destination_t destination, int64_t amount,
        PaymentFeeData feeData, std::string reference, std::string subject);

    TransactionFramePtr createPaymentRequestTx(Account& source,
                                               CreatePaymentRequest request,
                                               uint32_t* allTasks = nullptr);
};
}
}
