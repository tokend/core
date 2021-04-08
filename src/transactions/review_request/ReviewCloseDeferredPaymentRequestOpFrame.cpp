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
#include "transactions/managers/BalanceManager.h"
#include "ledger/AccountHelper.h"

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
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

BalanceFrame::pointer
ReviewCloseDeferredPaymentRequestOpFrame::tryLoadDestinationBalance(AssetCode asset, CloseDeferredPaymentRequest& request,
                                          StorageHelper& storageHelper, Application& app)
{
    switch (request.destination.type())
    {
        case CloseDeferredPaymentDestinationType::BALANCE:
        {
            auto dest = storageHelper.getBalanceHelper().loadBalance(request.destination.balanceID());
            if (!dest)
            {
                innerResult().code(ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND);
                return nullptr;
            }

            if (dest->getAsset() != asset)
            {
                innerResult().code(ReviewRequestResultCode::BALANCE_ASSETS_MISMATCHED);
                return nullptr;
            }

            return dest;
        }
        case CloseDeferredPaymentDestinationType::ACCOUNT:
        {
            if (!storageHelper.getAccountHelper().exists(request.destination.accountID()))
            {
                innerResult().code(ReviewRequestResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
                return nullptr;
            }

            BalanceManager balanceManager(app, storageHelper);
            return balanceManager.loadOrCreateBalance(request.destination.accountID(), asset);
        }
        default:
            throw std::runtime_error("Unexpected destination type on payment");
    }
}

bool
ReviewCloseDeferredPaymentRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CLOSE_DEFERRED_PAYMENT);

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

    auto destinationBalance = tryLoadDestinationBalance(srcBalance->getAsset(), closeDeferredPayment, storageHelper, app);

    if (deferredPayment->getDeferredPayment().amount < closeDeferredPayment.amount) {
        innerResult().code(ReviewRequestResultCode::UNDERFUNDED);
    }

    requestHelper.storeDelete(request->getKey());

    if (srcBalance->getBalanceID() == destinationBalance->getBalanceID()) {
        auto result = srcBalance->unlock(closeDeferredPayment.amount); // store changes after else
        if (result != BalanceFrame::Result::SUCCESS)
        {
            handleBalanceChangeResult(result, deferredPayment->getDeferredPayment().id, "unlock source");
            return false;
        }
    }
    else 
    {
        auto result = srcBalance->tryChargeFromLocked(closeDeferredPayment.amount);
        if (result != BalanceFrame::Result::SUCCESS)
        {
            handleBalanceChangeResult(result, deferredPayment->getDeferredPayment().id, "charge source");
            return false;
        }

        result = destinationBalance->tryFundAccount(closeDeferredPayment.amount);
        if (result != BalanceFrame::Result::SUCCESS)
        {
            handleBalanceChangeResult(result, deferredPayment->getDeferredPayment().id, "fund destination");
            return false;
        }
        storageHelper.getBalanceHelper().storeChange(destinationBalance->mEntry);
    }
    storageHelper.getBalanceHelper().storeChange(srcBalance->mEntry);

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
        .destinationBalance = destinationBalance->getBalanceID();
    innerResult().success().typeExt.closeDeferredPaymentResult().destination =
        destinationBalance->getAccountID();

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

void
ReviewCloseDeferredPaymentRequestOpFrame::handleBalanceChangeResult(BalanceFrame::Result result, uint64 id, std::string op)
{
    switch (result)
    {
    case BalanceFrame::Result::NONMATCHING_PRECISION:
        innerResult().code(ReviewRequestResultCode::INCORRECT_PRECISION);
        return;
    case BalanceFrame::Result::LINE_FULL:
        innerResult().code(ReviewRequestResultCode::LINE_FULL);
        return;
    default:
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to "
                << op
                << " on deferred payment close, id: "
                << id;
        throw std::runtime_error("Unexpected state: failed to " + op + " on deferred payment close");
    }
}

}
