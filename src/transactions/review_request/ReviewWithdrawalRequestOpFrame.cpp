// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/asio.h"
#include "ReviewWithdrawalRequestOpFrame.h"
#include "util/Logging.h"
#include "util/types.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/PendingStatisticsHelper.h"
#include "transactions/CreateWithdrawalRequestOpFrame.h"
#include "main/Application.h"
#include "xdrpp/printer.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool ReviewWithdrawalRequestOpFrame::handleApprove(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (ledgerManager.shouldUse(LedgerVersion::WITHDRAWAL_TASKS) &&
        mReviewRequest.ext.v() == LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST &&
        request->getRequestEntry().ext.v() == LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST)
    {
        return handleApproveV2(app, delta, ledgerManager, request);
    }
    return handleApproveV1(app, delta, ledgerManager, request);
}

bool ReviewWithdrawalRequestOpFrame::handleApproveV1(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::WITHDRAW)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
            "Unexpected request type. Expected WITHDRAW, but got " << xdr::
            xdr_traits<ReviewableRequestType>::
            enum_name(request->getRequestType());
        throw
            invalid_argument("Unexpected request type for review withdraw request");
    }

    auto& withdrawRequest = request->getRequestEntry().body.withdrawalRequest();

    Database& db = ledgerManager.getDatabase();
    //Delete pending_statistics entries before reviwable_request due to constraint change
    auto reqID = request->getRequestID();
    auto pendingStats = PendingStatisticsHelper::Instance()->loadPendingStatistics(reqID, db, delta);
    for (auto& pending : pendingStats){
        auto lk = request->getKey();
        lk = lk.type(LedgerEntryType::PENDING_STATISTICS);
        lk.pendingStatistics().statisticsID = pending->getStatsID();
        lk.pendingStatistics().requestID = reqID;
        PendingStatisticsHelper::Instance()->storeDelete(delta, db, lk);
    }
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());
 
    auto balance = BalanceHelperLegacy::Instance()->mustLoadBalance(withdrawRequest.balance, db, &delta);
    const auto totalAmountToCharge = getTotalAmountToCharge(request->getRequestID(), withdrawRequest);
    if (balance->tryChargeFromLocked(totalAmountToCharge) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state. Failed to charge from locked amount which must be locked. requestID: " << request->getRequestID();
        throw runtime_error("Unexected db state. Failed to charge from locked");
    }
    EntryHelperProvider::storeChangeEntry(delta, db, balance->mEntry);

    const uint64_t totalFee = getTotalFee(request->getRequestID(), withdrawRequest);
    AccountManager accountManager(app, db, delta, ledgerManager);
    accountManager.transferFee(balance->getAsset(), totalFee);

    auto assetFrame = AssetHelperLegacy::Instance()->loadAsset(balance->getAsset(), db, &delta);
    if (!assetFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to load asset for withdrawal request" << request->getRequestID();
        throw runtime_error("Failed to load asset for withdrawal request");
    }

    if (!assetFrame->tryWithdraw(withdrawRequest.amount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to withdraw from asset for request: " << request->getRequestID();
        throw runtime_error("Failed to withdraw from asset");
    }

    AssetHelperLegacy::Instance()->storeChange(delta, db, assetFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

bool ReviewWithdrawalRequestOpFrame::handleApproveV2(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::WITHDRAW)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
            "Unexpected request type. Expected WITHDRAW, but got " << xdr::
            xdr_traits<ReviewableRequestType>::
            enum_name(request->getRequestType());
        throw
            invalid_argument("Unexpected request type for review withdraw request");
    }
    Database& db = ledgerManager.getDatabase();

    auto& withdrawRequest = request->getRequestEntry().body.withdrawalRequest();
    auto& requestEntry = request->getRequestEntry();

    if (removingNotSetTask(requestEntry)){
        innerResult().code(ReviewRequestResultCode::REMOVING_NOT_SET_TASKS);
        return false;
    }

    requestEntry.tasks.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.pendingTasks &= ~mReviewRequest.reviewDetails.tasksToRemove;
    requestEntry.tasks.pendingTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.externalDetails.emplace_back(mReviewRequest.reviewDetails.externalDetails);
    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    if (!request->canBeFulfilled(ledgerManager)){
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
        innerResult().success().extendedResult.typeExt.requestType(ReviewableRequestType::NONE);
        innerResult().success().extendedResult.fulfilled = false;
        return true;
    }

    //Delete pending_statistics entries before reviewable request due to constraint change
    auto reqID = request->getRequestID();
    auto pendingStats = PendingStatisticsHelper::Instance()->loadPendingStatistics(reqID, db, delta);
    for (auto& pending : pendingStats){
        auto lk = request->getKey();
        lk = lk.type(LedgerEntryType::PENDING_STATISTICS);
        lk.pendingStatistics().statisticsID = pending->getStatsID();
        lk.pendingStatistics().requestID = reqID;
        PendingStatisticsHelper::Instance()->storeDelete(delta, db, lk);
    }
    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    auto balance = BalanceHelperLegacy::Instance()->mustLoadBalance(withdrawRequest.balance, db, &delta);
    const auto totalAmountToCharge = getTotalAmountToCharge(request->getRequestID(), withdrawRequest);
    if (balance->tryChargeFromLocked(totalAmountToCharge) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state. Failed to charge from locked amount which must be locked. requestID: "
                                               << request->getRequestID();
        throw runtime_error("Unexpected db state. Failed to charge from locked");
    }
    EntryHelperProvider::storeChangeEntry(delta, db, balance->mEntry);

    const uint64_t totalFee = getTotalFee(request->getRequestID(), withdrawRequest);
    AccountManager accountManager(app, db, delta, ledgerManager);
    accountManager.transferFee(balance->getAsset(), totalFee);

    auto assetFrame = AssetHelperLegacy::Instance()->loadAsset(balance->getAsset(), db, &delta);
    if (!assetFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to load asset for withdrawal request" << request->getRequestID();
        throw runtime_error("Failed to load asset for withdrawal request");
    }

    if (!assetFrame->tryWithdraw(withdrawRequest.amount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to withdraw from asset for request: " << request->getRequestID();
        throw runtime_error("Failed to withdraw from asset");
    }

    AssetHelperLegacy::Instance()->storeChange(delta, db, assetFrame->mEntry);
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().ext.v(LedgerVersion::ADD_TASKS_TO_REVIEWABLE_REQUEST);
    innerResult().success().extendedResult.fulfilled = true;
    innerResult().success().extendedResult.typeExt.requestType(ReviewableRequestType::NONE);
    return true;
}

bool ReviewWithdrawalRequestOpFrame::handleReject(
    Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
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
    LedgerDelta& delta, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::WITHDRAW)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
            "Unexpected request type. Expected WITHDRAW, but got " << xdr::
            xdr_traits<ReviewableRequestType>::
            enum_name(request->getRequestType());
        throw
            invalid_argument("Unexpected request type for review withdraw request");
    }

    auto& withdrawalRequest = request->getRequestEntry().body.withdrawalRequest();
    return rejectWithdrawalRequest(app, delta, ledgerManager, request, withdrawalRequest);
}

bool ReviewWithdrawalRequestOpFrame::doCheckValid(Application &app)
{
    auto withdrawalRequest  = mReviewRequest.requestDetails.withdrawal();

    if (!CreateWithdrawalRequestOpFrame::isExternalDetailsValid(app, withdrawalRequest.externalDetails)) {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return ReviewRequestOpFrame::doCheckValid(app);
}
bool ReviewWithdrawalRequestOpFrame::removingNotSetTask(ReviewableRequestEntry &requestEntry) {
    return !(requestEntry.tasks.pendingTasks & mReviewRequest.reviewDetails.tasksToRemove);
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


bool ReviewWithdrawalRequestOpFrame::rejectWithdrawalRequest(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request, WithdrawalRequest& withdrawRequest)
{
    Database& db = app.getDatabase();
    auto balance = BalanceHelperLegacy::Instance()->mustLoadBalance(withdrawRequest.balance, db, &delta);
    const auto totalAmountToCharge = getTotalAmountToCharge(request->getRequestID(), withdrawRequest);
    if (balance->unlock(totalAmountToCharge) != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state. Failed to unlock locked amount. requestID: " << request->getRequestID();
        throw runtime_error("Unexpected db state. Failed to unlock locked amount");
    }

    const uint64_t universalAmount = withdrawRequest.universalAmount;
    if (universalAmount > 0)
    {
        if (!ledgerManager.shouldUse(LedgerVersion::CREATE_ONLY_STATISTICS_V2))
        {
            AccountManager accountManager(app, ledgerManager.getDatabase(), delta, ledgerManager);
            const AccountID requestor = request->getRequestor();
            const time_t timePerformed = request->getCreatedAt();
            accountManager.revertStats(requestor, universalAmount, timePerformed);
        }
        else
        {
            StatisticsV2Processor statisticsV2Processor(ledgerManager.getDatabase(), delta, ledgerManager);
            statisticsV2Processor.revertStatsV2(request->getRequestID());
        }
    }

    EntryHelperProvider::storeChangeEntry(delta, db, balance->mEntry);
    return ReviewRequestOpFrame::handlePermanentReject(app, delta, ledgerManager, request);
}


uint64_t ReviewWithdrawalRequestOpFrame::getTotalAmountToCharge(
        const uint64_t requestID, WithdrawalRequest& withdrawalRequest)
{
    const auto totalFee = getTotalFee(requestID, withdrawalRequest);
    uint64_t totalAmountToCharge;
    if (!safeSum(withdrawalRequest.amount, totalFee, totalAmountToCharge))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate total amount ot be charged for withdrawal request: " << requestID;
        throw runtime_error("Failed to calculate total amount to be charged for withdrawal request");
    }

    return totalAmountToCharge;
}

}
