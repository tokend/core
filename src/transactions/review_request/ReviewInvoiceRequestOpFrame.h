#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewRequestOpFrame.h"

namespace stellar
{
class ReviewInvoiceRequestOpFrame : public ReviewRequestOpFrame
{

    std::map<PaymentResultCode, ReviewRequestResultCode> paymentCodeToReviewRequestCode =
    {
        {PaymentResultCode::MALFORMED, ReviewRequestResultCode::PAYMENT_V2_MALFORMED},
        {PaymentResultCode::UNDERFUNDED, ReviewRequestResultCode::UNDERFUNDED},
        {PaymentResultCode::LINE_FULL, ReviewRequestResultCode::LINE_FULL},
        {PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND, ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND},
        {PaymentResultCode::INVALID_DESTINATION_FEE, ReviewRequestResultCode::INVALID_DESTINATION_FEE},
        {PaymentResultCode::BALANCE_ASSETS_MISMATCHED, ReviewRequestResultCode::BALANCE_ASSETS_MISMATCHED},
        {PaymentResultCode::SRC_BALANCE_NOT_FOUND, ReviewRequestResultCode::SRC_BALANCE_NOT_FOUND},
        {PaymentResultCode::REFERENCE_DUPLICATION, ReviewRequestResultCode::REFERENCE_DUPLICATION},
        {PaymentResultCode::STATS_OVERFLOW, ReviewRequestResultCode::STATS_OVERFLOW},
        {PaymentResultCode::LIMITS_EXCEEDED, ReviewRequestResultCode::LIMITS_EXCEEDED},
        {PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY, ReviewRequestResultCode::NOT_ALLOWED_BY_ASSET_POLICY},
        {PaymentResultCode::INSUFFICIENT_FEE_AMOUNT, ReviewRequestResultCode::INSUFFICIENT_FEE_AMOUNT},
        {PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE, ReviewRequestResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE},
        {PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND, ReviewRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND},
    };

    bool checkPaymentDetails(ReviewableRequestEntry& requestEntry,
                             BalanceID receiverBalance, BalanceID senderBalance);

    bool processPaymentV2(Application &app, StorageHelper& storageHelper, LedgerManager &ledgerManager);

    bool tryLockAmount(BalanceFrame::pointer balance, uint64_t amount);

    void trySetErrorCode(PaymentResultCode paymentResult);

protected:
    bool handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                       ReviewableRequestFrame::pointer request) override;

    bool handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                      ReviewableRequestFrame::pointer request) override;

    bool handlePermanentReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                               ReviewableRequestFrame::pointer request) override;

public:
    ReviewInvoiceRequestOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx);

};
}
