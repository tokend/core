// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/CreateWithdrawalRequestOpFrame.h"
#include "transactions/managers/FeeManager.h"

namespace stellar
{
using xdr::operator==;

bool
CreateWithdrawalRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                          std::vector<OperationCondition>& result) const
{
    auto balance = storageHelper.getBalanceHelper().loadBalance(mCreateWithdrawalRequest.request.balance);
    if (!balance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(balance->getAsset());

    AccountRuleResource assetResource(LedgerEntryType::ASSET);
    assetResource.asset().assetType = asset->getAsset().type;
    assetResource.asset().assetCode = asset->getCode();

    result.emplace_back(assetResource, AccountRuleAction::WITHDRAW, mSourceAccount);

    return true;
}

bool
CreateWithdrawalRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                         std::vector<SignerRequirement>& result) const
{
    auto balance = storageHelper.getBalanceHelper().mustLoadBalance(
        mCreateWithdrawalRequest.request.balance);
    auto asset = storageHelper.getAssetHelper().mustLoadAsset(balance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_WITHDRAW);
    resource.reviewableRequest().details.createWithdraw().assetCode = asset->getCode();
    resource.reviewableRequest().details.createWithdraw().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateWithdrawalRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateWithdrawalRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

BalanceFrame::pointer CreateWithdrawalRequestOpFrame::tryLoadBalance(StorageHelper& storageHelper) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.loadBalance(mCreateWithdrawalRequest.request.balance);
    if (!balanceFrame || !(balanceFrame->getAccountID() == getSourceID()))
    {
        return nullptr;
    }

    return balanceFrame;
}

bool
CreateWithdrawalRequestOpFrame::isFeeMatches(Application& app, StorageHelper& sh, BalanceFrame::pointer balance) const
{
    FeeManager feeManager(app, sh);

    return feeManager.isFeeMatches(mSourceAccount, mCreateWithdrawalRequest.request.fee,
                                   FeeType::WITHDRAWAL_FEE, FeeFrame::SUBTYPE_ANY, balance->getAsset(),
                                   mCreateWithdrawalRequest.request.amount);
}

bool CreateWithdrawalRequestOpFrame::tryLockBalance(
    BalanceFrame::pointer balance)
{
    uint64_t totalAmountToBeLocked = 0;
    auto& request = mCreateWithdrawalRequest.request;
    if (!safeSum(totalAmountToBeLocked, {request.amount, request.fee.fixed, request.fee.percent}))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::BALANCE_LOCK_OVERFLOW);
        return false;
    }

    const auto balanceLockResult = balance->tryLock(totalAmountToBeLocked);
    switch (balanceLockResult)
    {
        case BalanceFrame::Result::SUCCESS:
            return true;
        case BalanceFrame::Result::LINE_FULL:
        {
            innerResult().code(CreateWithdrawalRequestResultCode::BALANCE_LOCK_OVERFLOW);
            return false;
        }
        case BalanceFrame::Result::UNDERFUNDED:
        {
            innerResult().code(CreateWithdrawalRequestResultCode::UNDERFUNDED);
            return false;
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected balance lock result for create withdrawal request: "
                                                   << balanceLockResult;
            throw std::runtime_error("Unexpected result on balance lock");
        }
    }
}

CreateWithdrawalRequestOpFrame::CreateWithdrawalRequestOpFrame(
    Operation const& op, OperationResult& res,
    TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateWithdrawalRequest(mOperation.body.createWithdrawalRequestOp())
{
}

ReviewableRequestFrame::pointer
CreateWithdrawalRequestOpFrame::tryCreateWithdrawalRequest(Application& app,
                                                           StorageHelper& storageHelper,
                                                           LedgerManager& ledgerManager,
                                                           BalanceFrame::pointer balanceFrame,
                                                           AssetFrame::pointer assetFrame)
{
    auto& delta = storageHelper.mustGetLedgerDelta();

    if (!assetFrame->isPolicySet(AssetPolicy::WITHDRAWABLE))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::ASSET_IS_NOT_WITHDRAWABLE);
        return nullptr;
    }

    auto code = assetFrame->getAsset().code;
    if (!exceedsLowerBound(storageHelper, code))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED);
        return nullptr;
    }

    if (!isFeeMatches(app, storageHelper, balanceFrame))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::FEE_MISMATCHED);
        return nullptr;
    }


    if (!tryLockBalance(balanceFrame))
    {
        return nullptr;
    }


    uint64_t universalAmount = 0;
    auto request = ReviewableRequestFrame::createNew(delta, getSourceID(), assetFrame->getOwner(), nullptr,
                                                     ledgerManager.getCloseTime());
    ReviewableRequestEntry& requestEntry = request->getRequestEntry();

    requestEntry.body.type(ReviewableRequestType::CREATE_WITHDRAW);
    requestEntry.body.withdrawalRequest() = mCreateWithdrawalRequest.request;
    requestEntry.body.withdrawalRequest().universalAmount = universalAmount;

    request->recalculateHashRejectReason();
    storageHelper.getReviewableRequestHelper().storeAdd(request->mEntry);
    storageHelper.getBalanceHelper().storeChange(balanceFrame->mEntry);

    if (!processStatistics(storageHelper, ledgerManager, balanceFrame,
                           mCreateWithdrawalRequest.request.amount,
                           universalAmount, request->getRequestID()))
    {
        return nullptr;
    }
    storeChangeRequest(storageHelper, request, universalAmount);

    return request;

}

void
CreateWithdrawalRequestOpFrame::storeChangeRequest(StorageHelper& storageHelper, ReviewableRequestFrame::pointer request,
                                                   const uint64_t universalAmount)
{
    request->getRequestEntry().body.withdrawalRequest().universalAmount = universalAmount;

    request->recalculateHashRejectReason();
    storageHelper.getReviewableRequestHelper().storeChange(request->mEntry);
}

bool CreateWithdrawalRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager)
{
    auto balanceFrame = tryLoadBalance(storageHelper);
    if (!balanceFrame)
    {
        innerResult().code(CreateWithdrawalRequestResultCode::BALANCE_NOT_FOUND);
        return false;
    }

    const auto assetFrame = storageHelper.getAssetHelper().mustLoadAsset(balanceFrame->getAsset());

    auto request = tryCreateWithdrawalRequest(app, storageHelper, ledgerManager, balanceFrame, assetFrame);
    if (!request)
    {
        return false;
    }

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks = 0;
    if (!keyValueHelper.loadTasks(allTasks, {makeTasksKeyVector(assetFrame->getCode())}))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::WITHDRAWAL_TASKS_NOT_FOUND);
        return false;
    }

    if (allTasks == 0)
    {
        innerResult().code(CreateWithdrawalRequestResultCode::WITHDRAWAL_ZERO_TASKS_NOT_ALLOWED);
        return false;
    }

    request->setTasks(allTasks);
    storageHelper.getReviewableRequestHelper().storeChange(request->mEntry);

    innerResult().code(CreateWithdrawalRequestResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().ext.v(LedgerVersion::EMPTY_VERSION);
    innerResult().success().fulfilled = false;
    return true;
}

bool CreateWithdrawalRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateWithdrawalRequest.allTasks)
    {
        innerResult().code(CreateWithdrawalRequestResultCode::NOT_ALLOWED_TO_SET_WITHDRAWAL_TASKS);
        return false;
    }

    if (mCreateWithdrawalRequest.request.amount == 0)
    {
        innerResult().code(CreateWithdrawalRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (mCreateWithdrawalRequest.request.universalAmount != 0)
    {
        innerResult().code(CreateWithdrawalRequestResultCode::INVALID_UNIVERSAL_AMOUNT);
        return false;
    }

    if (!isExternalDetailsValid(app, mCreateWithdrawalRequest.request.creatorDetails))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

bool CreateWithdrawalRequestOpFrame::isExternalDetailsValid(Application& app, const std::string& externalDetails)
{
    if (!isValidJson(externalDetails))
        return false;

    return externalDetails.size() <= app.getWithdrawalDetailsMaxLength();
}

bool
CreateWithdrawalRequestOpFrame::processStatistics(StorageHelper& storageHelper,
                                                  LedgerManager& ledgerManager, BalanceFrame::pointer balanceFrame,
                                                  const uint64_t amountToAdd, uint64_t& universalAmount, uint64_t requestID)
{
    StatisticsV2Processor statisticsV2Processor(storageHelper, ledgerManager);

    const auto result = statisticsV2Processor.addStatsV2(StatisticsV2Processor::SpendType::WITHDRAW,
                                                         amountToAdd, universalAmount, mSourceAccount, balanceFrame, &requestID);
    switch (result)
    {
        case StatisticsV2Processor::SUCCESS:
            return true;
        case StatisticsV2Processor::STATS_V2_OVERFLOW:
            innerResult().code(CreateWithdrawalRequestResultCode::STATS_OVERFLOW);
            return false;
        case StatisticsV2Processor::LIMITS_V2_EXCEEDED:
            innerResult().code(CreateWithdrawalRequestResultCode::LIMITS_EXCEEDED);
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected result from statisticsV2Processor when updating statsV2:" << result;
            throw std::runtime_error("Unexpected state from statisticsV2Processor when updating statsV2");
    }
}

bool CreateWithdrawalRequestOpFrame::exceedsLowerBound(StorageHelper& storageHelper, AssetCode& code)
{
    xdr::xstring<256> key = ManageKeyValueOpFrame::makeWithdrawLowerBoundKey(code);
    auto lowerBound = storageHelper.getKeyValueHelper().loadKeyValue(key);
    if (!lowerBound)
    {
        return true;
    }

    if (lowerBound.get()->getKeyValue().value.type() != KeyValueEntryType::UINT64)
    {
        CLOG(WARNING, Logging::OPERATION_LOGGER)
            << "AssetCode: " << code
            << "KeyValueEntryType: "
            << "Key: " << key.c_str()
            << std::to_string(
                static_cast<int32>(lowerBound.get()->getKeyValue().value.type()));
        return true;
    }

    auto& request = mCreateWithdrawalRequest.request;
    return lowerBound.get()->getKeyValue().value.ui64Value() <= request.amount;
}

std::vector<std::string>
CreateWithdrawalRequestOpFrame::makeTasksKeyVector(AssetCode const& code)
{
    return
        {
            ManageKeyValueOpFrame::makeWithdrawalTasksKey(code),
            ManageKeyValueOpFrame::makeWithdrawalTasksKey("*")
        };
}

}
