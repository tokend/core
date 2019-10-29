// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/asio.h"
#include "ReviewWithdrawalRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/PendingStatisticsHelper.h"
#include "transactions/CreateWithdrawalRequestOpFrame.h"
#include "main/Application.h"
#include "xdrpp/printer.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "transactions/managers/BalanceManager.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewWithdrawalRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                         std::vector<SignerRequirement>& result,
                                                         LedgerManager& lm) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(mReviewRequest.requestID);
    if (!request || (request->getType() != ReviewableRequestType::CREATE_WITHDRAW))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();
    AssetFrame::pointer asset;
    BalanceFrame::pointer balance;
    if (!lm.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED)){
        balance = balanceHelper.mustLoadBalance(
            request->getRequestEntry().body.withdrawalRequest().balance);
        asset = assetHelper.mustLoadAsset(balance->getAsset());
    }
    else {
        balance = balanceHelper.mustLoadBalance(
            request->getRequestEntry().body.withdrawalRequest().balance);
        if (!balance)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;
            return false;
        }
        asset = assetHelper.mustLoadAsset(balance->getAsset());
        if (!asset)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::ASSET;
            return false;
        }

    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_WITHDRAW);
    resource.reviewableRequest().details.createWithdraw().assetCode = asset->getCode();
    resource.reviewableRequest().details.createWithdraw().assetType = asset->getType();
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool ReviewWithdrawalRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_WITHDRAW)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
                                               "Unexpected request type. Expected WITHDRAW, but got " << xdr::
                                               xdr_traits<ReviewableRequestType>::
                                               enum_name(request->getRequestType());
        throw
            invalid_argument("Unexpected request type for review withdraw request");
    }

    auto& withdrawRequest = request->getRequestEntry().body.withdrawalRequest();
    auto& requestEntry = request->getRequestEntry();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
        innerResult().success().typeExt.requestType(ReviewableRequestType::NONE);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    //Delete pending_statistics entries before reviewable request due to constraint change
    auto reqID = request->getRequestID();
    auto pendingStats = PendingStatisticsHelper::Instance()->loadPendingStatistics(reqID, db, delta);
    for (auto& pending : pendingStats)
    {
        auto lk = request->getKey();
        lk = lk.type(LedgerEntryType::PENDING_STATISTICS);
        lk.pendingStatistics().statisticsID = pending->getStatsID();
        lk.pendingStatistics().requestID = reqID;
        PendingStatisticsHelper::Instance()->storeDelete(delta, db, lk);
    }
    requestHelper.storeDelete(request->getKey());

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.mustLoadBalance(withdrawRequest.balance);

    const auto totalAmountToCharge = getTotalAmountToCharge(request->getRequestID(), withdrawRequest);
    if (balance->tryChargeFromLocked(totalAmountToCharge) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected db state. Failed to charge from locked amount which must be locked. requestID: "
            << request->getRequestID();
        throw runtime_error("Unexpected db state. Failed to charge from locked");
    }
    balanceHelper.storeChange(balance->mEntry);

    const uint64_t totalFee = getTotalFee(request->getRequestID(), withdrawRequest);
    BalanceManager balanceManager(app, storageHelper);
    balanceManager.transferFee(balance->getAsset(), totalFee);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.loadAsset(balance->getAsset());
    if (!assetFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to load asset for withdrawal request"
                                               << request->getRequestID();
        throw runtime_error("Failed to load asset for withdrawal request");
    }

    if (!assetFrame->tryWithdraw(withdrawRequest.amount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to withdraw from asset for request: "
                                               << request->getRequestID();
        throw runtime_error("Failed to withdraw from asset");
    }

    assetHelper.storeChange(assetFrame->mEntry);
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::NONE);
    return true;
}

bool ReviewWithdrawalRequestOpFrame::handleReject(
    Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewWithdrawalRequestOpFrame::ReviewWithdrawalRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewWithdrawalRequestOpFrame::handlePermanentReject(Application& app,
                                                           StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                           ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_WITHDRAW)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
                                               "Unexpected request type. Expected WITHDRAW, but got " << xdr::
                                               xdr_traits<ReviewableRequestType>::
                                               enum_name(request->getRequestType());
        throw
            invalid_argument("Unexpected request type for review withdraw request");
    }

    auto& withdrawalRequest = request->getRequestEntry().body.withdrawalRequest();
    return rejectWithdrawalRequest(app, storageHelper, ledgerManager, request, withdrawalRequest);
}

bool ReviewWithdrawalRequestOpFrame::doCheckValid(Application& app)
{
    auto withdrawalRequest = mReviewRequest.requestDetails.withdrawal();

    if (!CreateWithdrawalRequestOpFrame::isExternalDetailsValid(app, withdrawalRequest.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return ReviewRequestOpFrame::doCheckValid(app);
}

uint64_t ReviewWithdrawalRequestOpFrame::getTotalFee(const uint64_t requestID, WithdrawalRequest& withdrawRequest)
{
    uint64_t totalFee;
    if (!safeSum(withdrawRequest.fee.percent, withdrawRequest.fee.fixed, totalFee))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate total fee for withdrawal request: " << requestID;
        throw runtime_error("Failed to calculate total fee for withdrawal request");
    }

    return totalFee;
}

bool
ReviewWithdrawalRequestOpFrame::rejectWithdrawalRequest(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request, WithdrawalRequest& withdrawRequest)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.mustLoadBalance(withdrawRequest.balance);
    const auto totalAmountToCharge = getTotalAmountToCharge(request->getRequestID(), withdrawRequest);
    if (balance->unlock(totalAmountToCharge) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state. Failed to unlock locked amount. requestID: "
                                               << request->getRequestID();
        throw runtime_error("Unexpected db state. Failed to unlock locked amount");
    }

    const uint64_t universalAmount = withdrawRequest.universalAmount;
    if (universalAmount > 0)
    {
        StatisticsV2Processor statisticsV2Processor(storageHelper, ledgerManager);
        statisticsV2Processor.revertStatsV2(request->getRequestID());
    }

    balanceHelper.storeChange(balance->mEntry);
    return ReviewRequestOpFrame::handlePermanentReject(app, storageHelper, ledgerManager, request);
}

uint64_t ReviewWithdrawalRequestOpFrame::getTotalAmountToCharge(
    const uint64_t requestID, WithdrawalRequest& withdrawalRequest)
{
    const auto totalFee = getTotalFee(requestID, withdrawalRequest);
    uint64_t totalAmountToCharge;
    if (!safeSum(withdrawalRequest.amount, totalFee, totalAmountToCharge))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate total amount ot be charged for withdrawal request: " << requestID;
        throw runtime_error("Failed to calculate total amount to be charged for withdrawal request");
    }

    return totalAmountToCharge;
}

}
