#include <transactions/issuance/CreateIssuanceRequestOpFrame.h>
#include "transactions/managers/StatisticsV2Processor.h"
#include "transactions/managers/BalanceManager.h"
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/PendingStatisticsHelper.h>
#include "ledger/LedgerDeltaImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AccountHelper.h"
#include "main/Application.h"
#include "xdrpp/printer.h"
#include "ReviewRequestHelper.h"
#include "ledger/StorageHelperImpl.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewIssuanceCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                               std::vector<SignerRequirement>& result,
                                                               LedgerManager& lm) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(mReviewRequest.requestID);
    if (!request || (request->getType() != ReviewableRequestType::CREATE_ISSUANCE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    AssetFrame::pointer asset;
    if (!lm.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED)){
        asset = assetHelper.mustLoadAsset(
            request->getRequestEntry().body.issuanceRequest().asset);
    }
    else {
        asset = assetHelper.loadActiveAsset(
            request->getRequestEntry().body.issuanceRequest().asset);
        if (!asset)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::ASSET;
            return false;
        }

    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ISSUANCE);
    resource.reviewableRequest().details.createIssuance().assetCode = asset->getCode();
    resource.reviewableRequest().details.createIssuance().assetType = asset->getType();
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool ReviewIssuanceCreationRequestOpFrame::
handleApprove(Application& app, StorageHelper& storageHelper,
              LedgerManager& ledgerManager,
              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_ISSUANCE);

    auto& issuanceRequest = request->getRequestEntry().body.issuanceRequest();
    auto& db = storageHelper.getDatabase();

    auto& assetHelper = storageHelper.getAssetHelper();

    AssetFrame::pointer asset;
    if (ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        if (!storageHelper.getAssetHelper().existActive(issuanceRequest.asset))
        {
            innerResult().code(ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS);
            return false;
        }
    }

    asset = assetHelper.mustLoadAsset(issuanceRequest.asset);
    if (asset->willExceedMaxIssuanceAmount(issuanceRequest.amount))
    {
        innerResult().code(ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED);
        return false;
    }

    auto& requestEntry = request->getRequestEntry();

    auto systemTasksToAdd = getSystemTasksToAdd(app, storageHelper, ledgerManager, request);
    int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
                          CreateIssuanceRequestOpFrame::ISSUANCE_MANUAL_REVIEW_REQUIRED |
                          CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
    if ((systemTasksToAdd & ~systemTasks) != 0)
    {
        throw std::runtime_error("Expected only system tasks, got more");
    }

    requestEntry.tasks.allTasks |= systemTasksToAdd;
    requestEntry.tasks.pendingTasks |= systemTasksToAdd;

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    createReference(storageHelper, request->getRequestor(), request->getReference());

    requestHelper.storeDelete(request->getKey());

    if (!asset->tryIssue(issuanceRequest.amount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. Failed to fulfill request: "
                                               << xdr::xdr_to_string(request->getRequestEntry());
        throw std::runtime_error("Unexpected issuance result. Expected to be able to issue");
    }

    assetHelper.storeChange(asset->mEntry);

    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto receiver = balanceHelper.mustLoadBalance(issuanceRequest.receiver);

    uint64_t totalFee = 0;
    if (!safeSum(issuanceRequest.fee.fixed, issuanceRequest.fee.percent, totalFee))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "totalFee overflows uint64 for request: " << request->getRequestID();
        throw std::runtime_error("totalFee overflows uint64");
    }

    if (totalFee >= issuanceRequest.amount)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. totalFee exceeds amount for request: "
                                               << request->getRequestID();
        throw std::runtime_error("Unexpected state. totalFee exceeds amount");
    }

    //transfer fee
    BalanceManager balanceManager(app, storageHelper);
    balanceManager.transferFee(issuanceRequest.asset, totalFee);

    const uint64_t destinationReceive = issuanceRequest.amount - totalFee;
    const BalanceFrame::Result fundResult = receiver->tryFundAccount(destinationReceive);
    if (fundResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(fundResult == BalanceFrame::Result::LINE_FULL ?
                           ReviewRequestResultCode::FULL_LINE :
                           ReviewRequestResultCode::INCORRECT_PRECISION);
        return false;
    }

    balanceHelper.storeChange(receiver->mEntry);
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::NONE);
    return true;
}

bool
ReviewIssuanceCreationRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                   ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewIssuanceCreationRequestOpFrame::ReviewIssuanceCreationRequestOpFrame(Operation const& op, OperationResult& res,
                                                                           TransactionFrame& parentTx) :
    ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewIssuanceCreationRequestOpFrame::doCheckValid(Application& app)
{
    int32_t systemTasks = CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT |
                          CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;

    if ((mReviewRequest.reviewDetails.tasksToAdd & systemTasks) != 0 ||
        (mReviewRequest.reviewDetails.tasksToRemove & systemTasks) != 0)
    {
        innerResult().code(ReviewRequestResultCode::SYSTEM_TASKS_NOT_ALLOWED);
        return false;
    }

    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}

bool ReviewIssuanceCreationRequestOpFrame::addStatistics(StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                         const AccountFrame::pointer account,
                                                         const BalanceFrame::pointer balance, const uint64_t amountToAdd,
                                                         uint64_t& universalAmount)
{
    StatisticsV2Processor statisticsV2Processor(storageHelper, ledgerManager);
    const auto result = statisticsV2Processor.addStatsV2(StatisticsV2Processor::SpendType::DEPOSIT, amountToAdd,
                                                         universalAmount, account, balance, nullptr);
    switch (result)
    {
        case StatisticsV2Processor::SUCCESS:
            return true;
        case StatisticsV2Processor::STATS_V2_OVERFLOW:
            return false;
        case StatisticsV2Processor::LIMITS_V2_EXCEEDED:
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpeced result from statisticsV2Processor when updating statsV2:" << result;
            throw std::runtime_error("Unexpected state from statisticsV2Processor when updating statsV2");
    }

}

uint32_t ReviewIssuanceCreationRequestOpFrame::getSystemTasksToAdd(Application& app, StorageHelper& storageHelper,
                                                                   LedgerManager& ledgerManager,
                                                                   ReviewableRequestFrame::pointer request)
{
    // shield outer scope of any side effects by using
    // a sql transaction for ledger state and LedgerDelta
    LedgerDeltaImpl localDeltaImpl(storageHelper.mustGetLedgerDelta());
    LedgerDelta& localDelta = localDeltaImpl;
    StorageHelperImpl storageHelperImpl(storageHelper.getDatabase(), &localDelta);
    StorageHelper& localHelper = storageHelperImpl;
    localHelper.begin();

    auto& assetHelper = localHelper.getAssetHelper();

    request->checkRequestType(ReviewableRequestType::CREATE_ISSUANCE);
    auto& requestEntry = request->getRequestEntry();
    auto& issuanceRequest = request->getRequestEntry().body.issuanceRequest();
    auto asset = assetHelper.mustLoadAsset(issuanceRequest.asset);

    uint32_t allTasks = 0;

    uint64_t universalAmount = 0;
    auto& balanceHelper = localHelper.getBalanceHelper();
    auto& accountHelper = localHelper.getAccountHelper();

    auto balanceFrame = balanceHelper.mustLoadBalance(issuanceRequest.receiver);
    auto accountFrame = accountHelper.mustLoadAccount(balanceFrame->getAccountID());

    if (!asset->isAvailableForIssuanceAmountSufficient(issuanceRequest.amount))
    {
        allTasks |= CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
    }
    else
    {
        requestEntry.tasks.pendingTasks &= ~CreateIssuanceRequestOpFrame::INSUFFICIENT_AVAILABLE_FOR_ISSUANCE_AMOUNT;
    }

    auto& db = localHelper.getDatabase();
    if (!ledgerManager.shouldUse(LedgerVersion::FIX_DEPOSIT_STATS))
    {
        BalanceManager balanceManager(app, localHelper);
        balanceFrame = balanceManager.loadOrCreateBalance(requestEntry.requestor, issuanceRequest.asset);
        accountFrame = mSourceAccount;
    }

    if (!addStatistics(localHelper, ledgerManager,
                       accountFrame,
                       balanceFrame, issuanceRequest.amount,
                       universalAmount))
    {
        allTasks |= CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
    }
    else
    {
        requestEntry.tasks.pendingTasks &= ~CreateIssuanceRequestOpFrame::DEPOSIT_LIMIT_EXCEEDED;
    }

    if (allTasks == 0)
    {
        localHelper.commit();
        return allTasks;
    }

    return allTasks;
}
}
