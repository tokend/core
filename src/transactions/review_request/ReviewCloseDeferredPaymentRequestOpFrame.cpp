// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewCloseDeferredPaymentRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/DeferredPaymentFrame.h"
#include "ledger/DeferredPaymentHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include "xdrpp/printer.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewCloseDeferredPaymentRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result,
    LedgerManager& lm) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mReviewRequest.requestID);
    if (!request ||
        (request->getType() != ReviewableRequestType::CLOSE_DEFERRED_PAYMENT))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto deferredPayment =
        storageHelper.getDeferredPaymentHelper().loadDeferredPayment(
            request->getRequestEntry()
                .body.closeDeferredPaymentRequest()
                .deferredPaymentID);

    if (!deferredPayment)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::DEFERRED_PAYMENT;
        return false;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    AssetFrame::pointer asset;
    BalanceFrame::pointer balance;

    balance = balanceHelper.loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);
    if (!balance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }
    asset = assetHelper.loadAsset(balance->getAsset());
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.closeDeferredPayment().assetCode =
        asset->getCode();
    resource.reviewableRequest().details.closeDeferredPayment().assetType =
        asset->getType();
    resource.reviewableRequest().tasksToAdd =
        mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove =
        mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = request->getAllTasks();

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool
ReviewCloseDeferredPaymentRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() !=
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected request type. Expected CLOSE_DEFERRED_PAYMENT, but "
               "got "
            << xdr::xdr_traits<ReviewableRequestType>::enum_name(
                   request->getRequestType());
        throw invalid_argument("Unexpected request type for review close "
                               "deferred payment request");
    }

    auto& closeDeferredPayment =
        request->getRequestEntry().body.closeDeferredPaymentRequest();
    auto& requestEntry = request->getRequestEntry();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
        innerResult().success().typeExt.requestType(
            ReviewableRequestType::NONE);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& deferredPaymentHelper = storageHelper.getDeferredPaymentHelper();

    auto deferredPayment = deferredPaymentHelper.loadDeferredPayment(
        closeDeferredPayment.deferredPaymentID);

    auto srcBalance = storageHelper.getBalanceHelper().loadBalance(
        deferredPayment->getDeferredPayment().sourceBalance);

    auto destinationBalance = storageHelper.getBalanceHelper().loadBalance(
        closeDeferredPayment.destinationBalance);

    requestHelper.storeDelete(request->getKey());

    auto result = srcBalance->tryChargeFromLocked(closeDeferredPayment.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {

        switch (result)
        {
        case BalanceFrame::Result::NONMATCHING_PRECISION:
            innerResult().code(ReviewRequestResultCode::INCORRECT_PRECISION);
            return false;
        case BalanceFrame::Result::LINE_FULL:
            innerResult().code(ReviewRequestResultCode::LINE_FULL);
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge source on deferred "
                   "payment close, "
                   "id: "
                << deferredPayment->getDeferredPayment().id;
            throw std::runtime_error(
                "Unexpected state: failed to charge source "
                "on deferred payment close ");
        }
    }

    result = destinationBalance->tryFundAccount(closeDeferredPayment.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {

        switch (result)
        {
        case BalanceFrame::Result::NONMATCHING_PRECISION:
            innerResult().code(ReviewRequestResultCode::INCORRECT_PRECISION);
            return false;
        case BalanceFrame::Result::LINE_FULL:
            innerResult().code(ReviewRequestResultCode::LINE_FULL);
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to fund destination on deferred "
                   "payment close, "
                   "id: "
                << deferredPayment->getDeferredPayment().id;
            throw std::runtime_error("Unexpected state: failed to fund "
                                     "destination on deferred payment close ");
        }
    }

    deferredPayment->getDeferredPayment().amount -= closeDeferredPayment.amount;

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(
        ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);
    innerResult()
        .success()
        .typeExt.closeDeferredPaymentResult()
        .deferredPaymentID = deferredPayment->getDeferredPayment().id;
    innerResult()
        .success()
        .typeExt.closeDeferredPaymentResult()
        .destinationBalance = closeDeferredPayment.destinationBalance;
    innerResult().success().typeExt.closeDeferredPaymentResult().destination =
        destinationBalance->getAccountID();
    innerResult().success().typeExt.closeDeferredPaymentResult().totalAmount =
        closeDeferredPayment.amount;
    innerResult().success().typeExt.closeDeferredPaymentResult().totalFee = 0;

    if (deferredPayment->getDeferredPayment().amount == 0)
    {
        deferredPaymentHelper.storeDelete(deferredPayment->getKey());
        innerResult().success().typeExt.closeDeferredPaymentResult().effect =
            CloseDeferredPaymentEffect::DELETED;
    }
    else
    {
        deferredPaymentHelper.storeChange(deferredPayment->mEntry);
        innerResult().success().typeExt.closeDeferredPaymentResult().effect =
            CloseDeferredPaymentEffect::CHARGED;
    }
    innerResult()
        .success()
        .typeExt.closeDeferredPaymentResult()
        .deferredPaymentRemainder =
        deferredPayment->getDeferredPayment().amount;

    return true;
}

ReviewCloseDeferredPaymentRequestOpFrame::
    ReviewCloseDeferredPaymentRequestOpFrame(Operation const& op,
                                             OperationResult& res,
                                             TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewCloseDeferredPaymentRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return ReviewRequestOpFrame::doCheckValid(app);
}

}
