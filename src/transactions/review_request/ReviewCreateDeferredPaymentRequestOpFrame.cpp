// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewCreateDeferredPaymentRequestOpFrame.h"
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
ReviewCreateDeferredPaymentRequestOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result,
    LedgerManager& lm) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(
        mReviewRequest.requestID);
    if (!request ||
        (request->getType() != ReviewableRequestType::CREATE_DEFERRED_PAYMENT))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    AssetFrame::pointer asset;
    BalanceFrame::pointer balance;

    balance = balanceHelper.loadBalance(request->getRequestEntry()
                                            .body.createDeferredPaymentRequest()
                                            .sourceBalance);
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
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    resource.reviewableRequest().details.createDeferredPayment().assetCode =
        asset->getCode();
    resource.reviewableRequest().details.createDeferredPayment().assetType =
        asset->getType();
    resource.reviewableRequest().tasksToAdd =
        mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove =
        mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool
ReviewCreateDeferredPaymentRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_DEFERRED_PAYMENT);

    auto& createDeferredPayment =
        request->getRequestEntry().body.createDeferredPaymentRequest();
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

    auto srcBalance = storageHelper.getBalanceHelper().loadBalance(
        createDeferredPayment.sourceBalance);

    requestHelper.storeDelete(request->getKey());

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto newPaymentID =
        delta.getHeaderFrame().generateID(LedgerEntryType::DEFERRED_PAYMENT);

    auto deferredPaymentFrame = DeferredPaymentFrame::createNew(
        newPaymentID,
        request->getRequestEntry().body.createDeferredPaymentRequest(),
        srcBalance->getAccountID());

    storageHelper.getDeferredPaymentHelper().storeAdd(
        deferredPaymentFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    innerResult()
        .success()
        .typeExt.createDeferredPaymentResult()
        .deferredPaymentID = newPaymentID;
    innerResult().success().typeExt.createDeferredPaymentResult().destination =
        createDeferredPayment.destination;
    innerResult().success().typeExt.createDeferredPaymentResult().source =
        srcBalance->getAccountID();

    return true;
}

ReviewCreateDeferredPaymentRequestOpFrame::
    ReviewCreateDeferredPaymentRequestOpFrame(Operation const& op,
                                              OperationResult& res,
                                              TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewCreateDeferredPaymentRequestOpFrame::handlePermanentReject(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_DEFERRED_PAYMENT);

    auto& createDeferredPaymentRequest =
        request->getRequestEntry().body.createDeferredPaymentRequest();

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto srcBalance =
        balanceHelper.loadBalance(createDeferredPaymentRequest.sourceBalance);

    const auto result = srcBalance->unlock(createDeferredPaymentRequest.amount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(result == BalanceFrame::Result::NONMATCHING_PRECISION
                               ? ReviewRequestResultCode::INCORRECT_PRECISION
                               : ReviewRequestResultCode::LINE_FULL);
        return false;
    }

    balanceHelper.storeChange(srcBalance->mEntry);

    return ReviewRequestOpFrame::handlePermanentReject(app, storageHelper,
                                                       ledgerManager, request);
}

bool
ReviewCreateDeferredPaymentRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return ReviewRequestOpFrame::doCheckValid(app);
}

}
