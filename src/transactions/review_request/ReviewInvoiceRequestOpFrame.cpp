// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/payment/PaymentOpFrame.h"
#include "ledger/StorageHelper.h"
#include "util/asio.h"
#include "ReviewInvoiceRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelper.h"
#include "ledger/ContractHelper.h"
#include "ledger/BalanceHelper.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewInvoiceRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                           LedgerManager& ledgerManager,
                                           ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_INVOICE)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected INVOICE, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw invalid_argument("Unexpected request type for review invoice request");
    }

    auto& requestEntry = request->getRequestEntry();
    auto& invoiceRequest = requestEntry.body.invoiceRequest();

    if (invoiceRequest.isApproved)
    {
        innerResult().code(ReviewRequestResultCode::INVOICE_ALREADY_APPROVED);
        return false;
    }

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalance = balanceHelper.mustLoadBalance(invoiceRequest.senderBalance);
    auto receiverBalance = balanceHelper.mustLoadBalance(invoiceRequest.receiverBalance);

    if (!checkPaymentDetails(requestEntry, receiverBalance->getBalanceID(), senderBalance->getBalanceID()))
        return false;

    if (!processPaymentV2(app, storageHelper, ledgerManager))
        return false;

    if (!invoiceRequest.contractID)
    {
        requestHelper.storeDelete(request->getKey());
        return true;
    }

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto& db = storageHelper.getDatabase();
    auto contractHelper = ContractHelper::Instance();
    auto contractFrame = contractHelper->loadContract(*invoiceRequest.contractID, db, &delta);

    if (!contractFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected database state. Expected contract to exists "
                                               << to_string(*invoiceRequest.contractID);
        throw runtime_error("Unexpected database state. Expected contract to exists");
    }

    invoiceRequest.isApproved = true;
    request->recalculateHashRejectReason();
    requestHelper.storeChange(request->mEntry);

    receiverBalance = balanceHelper.mustLoadBalance(receiverBalance->getBalanceID());

    if (!tryLockAmount(receiverBalance, invoiceRequest.amount))
        return false;

    balanceHelper.storeChange(receiverBalance->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewInvoiceRequestOpFrame::tryLockAmount(BalanceFrame::pointer balance, uint64_t amount)
{
    auto lockResult = balance->tryLock(amount);

    switch (lockResult)
    {
        case BalanceFrame::Result::SUCCESS:
        {
            return true;
        }
        case BalanceFrame::Result::LINE_FULL:
        {
            innerResult().code(ReviewRequestResultCode::INVOICE_RECEIVER_BALANCE_LOCK_AMOUNT_OVERFLOW);
            return false;
        }
        case BalanceFrame::Result::UNDERFUNDED:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. There must be enough amount "
                                                   << "actual: " << to_string(balance->getAmount())
                                                   << "expected: " << to_string(amount);
            throw std::runtime_error("Unexpected state. There must be enough amount");
        }
        case BalanceFrame::Result::NONMATCHING_PRECISION:
        {
            innerResult().code(ReviewRequestResultCode::INCORRECT_PRECISION);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from tryLock method: "
                                                   << static_cast<int>(lockResult);
            throw std::runtime_error("Unexpected result code from tryLock method");
        }
    }
}

bool
ReviewInvoiceRequestOpFrame::checkPaymentDetails(ReviewableRequestEntry& requestEntry,
                                                 BalanceID receiverBalance, BalanceID senderBalance)
{
    auto invoiceRequest = requestEntry.body.invoiceRequest();
    auto paymentDetails = mReviewRequest.requestDetails.billPay().paymentDetails;
    switch (paymentDetails.destination.type())
    {
        case PaymentDestinationType::BALANCE:
        {
            if (!(receiverBalance == paymentDetails.destination.balanceID()))
            {
                innerResult().code(ReviewRequestResultCode::DESTINATION_BALANCE_MISMATCHED);
                return false;
            }
            break;
        }
        case PaymentDestinationType::ACCOUNT:
        {

            innerResult().code(ReviewRequestResultCode::NOT_ALLOWED_ACCOUNT_DESTINATION);
            return false;
        }
        default:
            throw std::runtime_error("Unexpected payment v2 destination type in BillPay");
    }

    if (invoiceRequest.amount != paymentDetails.amount)
    {
        innerResult().code(ReviewRequestResultCode::AMOUNT_MISMATCHED);
        return false;
    }

    if (!(paymentDetails.sourceBalanceID == senderBalance))
    {
        innerResult().code(ReviewRequestResultCode::SOURCE_BALANCE_MISMATCHED);
        return false;
    }

    if (!paymentDetails.feeData.sourcePaysForDest)
    {
        innerResult().code(ReviewRequestResultCode::REQUIRED_SOURCE_PAY_FOR_DESTINATION);
        return false;
    }

    return true;
}

bool
ReviewInvoiceRequestOpFrame::processPaymentV2(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    Operation op;
    op.body.type(OperationType::PAYMENT);
    op.body.paymentOp() = mReviewRequest.requestDetails.billPay().paymentDetails;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::PAYMENT);
    PaymentOpFrame paymentOpV2Frame(op, opRes, mParentTx);

    paymentOpV2Frame.setSourceAccountPtr(mSourceAccount);

    if (!paymentOpV2Frame.doCheckValid(app) || !paymentOpV2Frame.doApply(app, storageHelper, ledgerManager))
    {
        auto resultCode = PaymentOpFrame::getInnerCode(opRes);
        trySetErrorCode(resultCode);
        return false;
    }

    return true;
}

void
ReviewInvoiceRequestOpFrame::trySetErrorCode(PaymentResultCode paymentResult)
{
    try
    {
        innerResult().code(paymentCodeToReviewRequestCode[paymentResult]);
    }
    catch (...)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from payment v2 operation: "
                                               << xdr::xdr_traits<PaymentResultCode>::enum_name(paymentResult);
        throw std::runtime_error("Unexpected result code from payment v2 operation");
    }
}

bool
ReviewInvoiceRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                          ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool
ReviewInvoiceRequestOpFrame::handlePermanentReject(Application& app,
                                                   StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                   ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_INVOICE);

    if (request->getRequestEntry().body.invoiceRequest().isApproved)
    {
        innerResult().code(ReviewRequestResultCode::INVOICE_ALREADY_APPROVED);
        return false;
    }

    return ReviewRequestOpFrame::handlePermanentReject(app, storageHelper,
                                                       ledgerManager, request);
}

ReviewInvoiceRequestOpFrame::ReviewInvoiceRequestOpFrame(Operation const& op, OperationResult& res,
                                                         TransactionFrame& parentTx) :
    ReviewRequestOpFrame(op, res, parentTx)
{
}

}
