// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/StatisticsHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ledger/ReviewableRequestHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "transactions/CreateWithdrawalRequestOpFrame.h"
#include "database/Database.h"
#include "main/Application.h"
#include "medida/metrics_registry.h"
#include "xdrpp/printer.h"
#include "StatisticsV2Processor.h"
#include "ManageKeyValueOpFrame.h"

namespace stellar
{
using xdr::operator==;


std::unordered_map<AccountID, CounterpartyDetails>
CreateWithdrawalRequestOpFrame::getCounterpartyDetails(
    Database& db, LedgerDelta* delta) const
{
    // source account is only counterparty
    return {};
}

SourceDetails CreateWithdrawalRequestOpFrame::getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                                                      int32_t ledgerVersion)
const
{
    return SourceDetails({
                             AccountType::GENERAL, AccountType::SYNDICATE,
                             AccountType::OPERATIONAL, AccountType::EXCHANGE, AccountType::NOT_VERIFIED,
                             AccountType::ACCREDITED_INVESTOR, AccountType::INSTITUTIONAL_INVESTOR,
                             AccountType::VERIFIED
                         }, mSourceAccount->getMediumThreshold(),
                         static_cast<int32_t>(SignerType::BALANCE_MANAGER),
                         static_cast<int32_t>(BlockReasons::TOO_MANY_KYC_UPDATE_REQUESTS));
}

BalanceFrame::pointer CreateWithdrawalRequestOpFrame::tryLoadBalance(StorageHelper &storageHelper) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.loadBalance(mCreateWithdrawalRequest.request.balance);
    if (!balanceFrame || !(balanceFrame->getAccountID() == getSourceID()))
    {
        return nullptr;
    }

    return balanceFrame;
}

bool CreateWithdrawalRequestOpFrame::isFeeMatches(
    AccountManager& accountManager, BalanceFrame::pointer balance) const
{
    return accountManager.isFeeMatches(mSourceAccount, mCreateWithdrawalRequest.request.fee, FeeType::WITHDRAWAL_FEE,
        FeeFrame::SUBTYPE_ANY, balance->getAsset(), mCreateWithdrawalRequest.request.amount);
}

bool CreateWithdrawalRequestOpFrame::tryLockBalance(
    BalanceFrame::pointer balance)
{
    uint64_t totalAmountToBeLocked = 0;
    auto& request = mCreateWithdrawalRequest.request;
    if (!safeSum(totalAmountToBeLocked, { request.amount, request.fee.fixed, request.fee.percent }))
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
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected balance lock result for create withdrawal request: " << balanceLockResult;
            throw std::runtime_error("Unexpected result on balance lock");
        }
    }
}

CreateWithdrawalRequestOpFrame::CreateWithdrawalRequestOpFrame(
    Operation const& op, OperationResult& res,
    TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCreateWithdrawalRequest(mOperation.body.createWithdrawalRequestOp())
{
}


ReviewableRequestFrame::pointer
CreateWithdrawalRequestOpFrame::createRequest(LedgerDelta& delta, LedgerManager& ledgerManager,
                                              Database& db, const AssetFrame::pointer assetFrame,
                                              const uint64_t universalAmount)
{
    auto request = ReviewableRequestFrame::createNew(delta, getSourceID(), assetFrame->getOwner(), nullptr,
                                                     ledgerManager.getCloseTime());
    ReviewableRequestEntry &requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::WITHDRAW);
    requestEntry.body.withdrawalRequest() = mCreateWithdrawalRequest.request;
    requestEntry.body.withdrawalRequest().universalAmount = universalAmount;

    request->recalculateHashRejectReason();
    ReviewableRequestHelper::Instance()->storeAdd(delta, db, request->mEntry);
    return request;
}

ReviewableRequestFrame::pointer
CreateWithdrawalRequestOpFrame::tryCreateWithdrawalRequest(Application& app,
                                                            StorageHelper &storageHelper,
                                                            LedgerManager& ledgerManager,
                                                            BalanceFrame::pointer balanceFrame,
                                                            AssetFrame::pointer assetFrame)
{
    auto& db = app.getDatabase();
    auto delta = storageHelper.getLedgerDelta();

    if (!assetFrame->isPolicySet(AssetPolicy::WITHDRAWABLE))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::ASSET_IS_NOT_WITHDRAWABLE);
        return nullptr;
    }

    auto code = assetFrame->getAsset().code;
    if (!exceedsLowerBound(db, code))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::LOWER_BOUND_NOT_EXCEEDED);
        return nullptr;
    }

    AccountManager accountManager(app, db, *delta, ledgerManager);
    if (!isFeeMatches(accountManager, balanceFrame))
    {
        innerResult().code(CreateWithdrawalRequestResultCode::FEE_MISMATCHED);
        return nullptr;
    }


    if (!tryLockBalance(balanceFrame))
    {
        return nullptr;
    }


    uint64_t universalAmount = 0;
    auto request = ReviewableRequestFrame::createNew(*delta, getSourceID(), assetFrame->getOwner(), nullptr,
                                                     ledgerManager.getCloseTime());
    ReviewableRequestEntry &requestEntry = request->getRequestEntry();

    requestEntry.body.type(ReviewableRequestType::WITHDRAW);
    requestEntry.body.withdrawalRequest() = mCreateWithdrawalRequest.request;
    requestEntry.body.withdrawalRequest().universalAmount = universalAmount;

    request->recalculateHashRejectReason();
    EntryHelperProvider::storeAddEntry(*delta, db, request->mEntry);
    storageHelper.getBalanceHelper().storeChange(balanceFrame->mEntry);

    if (!processStatistics(accountManager, db, *delta, ledgerManager, balanceFrame,
                           mCreateWithdrawalRequest.request.amount, universalAmount, request->getRequestID()))
    {
        return nullptr;
    }
    storeChangeRequest(*delta, request, db, universalAmount);

    return request;

}

void
CreateWithdrawalRequestOpFrame::storeChangeRequest(LedgerDelta& delta, ReviewableRequestFrame::pointer request,
                                                   Database& db, const uint64_t universalAmount)
{
    request->getRequestEntry().body.withdrawalRequest().universalAmount = universalAmount;

    request->recalculateHashRejectReason();
    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);
}

ReviewableRequestFrame::pointer
CreateWithdrawalRequestOpFrame::approveRequest(AccountManager& accountManager, LedgerDelta& delta,
                                               LedgerManager& ledgerManager, Database& db,
                                               const AssetFrame::pointer assetFrame,
                                               const BalanceFrame::pointer balanceFrame)
{
    uint64_t universalAmount = 0;
    auto request = createRequest(delta, ledgerManager, db, assetFrame, universalAmount);

    if (!processStatistics(accountManager, db, delta, ledgerManager, balanceFrame,
                           mCreateWithdrawalRequest.request.amount, universalAmount, request->getRequestID()))
    {
        return nullptr;
    }
    storeChangeRequest(delta, request, db, universalAmount);

    return request;
}

bool CreateWithdrawalRequestOpFrame::doApply(Application &app, StorageHelper &storageHelper,
                                             LedgerManager &ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto delta = storageHelper.getLedgerDelta();
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

    uint32_t allTasks = 0;
    if (!loadTasks(storageHelper, allTasks, nullptr))
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
    EntryHelperProvider::storeChangeEntry(*delta, db, request->mEntry);

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

    if (!isExternalDetailsValid(app, mCreateWithdrawalRequest.request.externalDetails)) {
        innerResult().code(CreateWithdrawalRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}

bool CreateWithdrawalRequestOpFrame::isExternalDetailsValid(Application &app, const std::string &externalDetails) {
    if (!isValidJson(externalDetails))
        return false;

    return externalDetails.size() <= app.getWithdrawalDetailsMaxLength();
}

bool CreateWithdrawalRequestOpFrame::processStatistics(AccountManager& accountManager, Database& db,
                                                       LedgerDelta& delta, LedgerManager& ledgerManager,
                                                       BalanceFrame::pointer balanceFrame, const uint64_t amountToAdd,
                                                       uint64_t& universalAmount, const uint64_t requestID)
{
    if (!ledgerManager.shouldUse(LedgerVersion::CREATE_ONLY_STATISTICS_V2))
    {
        if (!tryAddStats(accountManager, balanceFrame, amountToAdd, universalAmount))
            return false;
    }

    StatisticsV2Processor statisticsV2Processor(db, delta, ledgerManager);
    return tryAddStatsV2(statisticsV2Processor, balanceFrame, amountToAdd, universalAmount, requestID);
}

bool CreateWithdrawalRequestOpFrame::tryAddStats(AccountManager& accountManager, const BalanceFrame::pointer balance,
                                                 const uint64_t amountToAdd, uint64_t& universalAmount)
{
    const auto result = accountManager.addStats(mSourceAccount, balance, amountToAdd, universalAmount);
    switch (result) {
        case AccountManager::SUCCESS:
            return true;
        case AccountManager::STATS_OVERFLOW:
            innerResult().code(CreateWithdrawalRequestResultCode::STATS_OVERFLOW);
            return false;
        case AccountManager::LIMITS_EXCEEDED:
            innerResult().code(CreateWithdrawalRequestResultCode::LIMITS_EXCEEDED);
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpeced result from accountManager when updating stats:" << result;
            throw std::runtime_error("Unexpected state from accountManager when updating stats");
    }
}

bool CreateWithdrawalRequestOpFrame::tryAddStatsV2(StatisticsV2Processor& statisticsV2Processor,
                                                   const BalanceFrame::pointer balance, const uint64_t amountToAdd,
                                                   uint64_t& universalAmount, uint64_t requestID)
{
    const auto result = statisticsV2Processor.addStatsV2(StatisticsV2Processor::SpendType::WITHDRAW, amountToAdd,
                                                         universalAmount, mSourceAccount, balance, &requestID);
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
                    << "Unexpeced result from statisticsV2Processor when updating statsV2:" << result;
            throw std::runtime_error("Unexpected state from statisticsV2Processor when updating statsV2");
    }

}

bool CreateWithdrawalRequestOpFrame::exceedsLowerBound(Database& db, AssetCode& code)
{
    xdr::xstring<256> key = ManageKeyValueOpFrame::makeWithdrawLowerBoundKey(code);
    auto lowerBound = KeyValueHelperLegacy::Instance()->loadKeyValue(key, db);
    if (!lowerBound) {
        return true;
    }

    if (lowerBound.get()->getKeyValue().value.type() != KeyValueEntryType::UINT64) {
        CLOG(WARNING, Logging::OPERATION_LOGGER)
                << "AssetCode: " << code
                << "KeyValueEntryType: "
                << "Key: " << key.c_str()
                << std::to_string(
                        static_cast<int32>(lowerBound.get()->getKeyValue().value.type()));
        return true;
    }

    auto &request = mCreateWithdrawalRequest.request;
    return lowerBound.get()->getKeyValue().value.ui64Value() <= request.amount;
}

std::vector<longstring>
CreateWithdrawalRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper)
{
    auto balanceFrame = storageHelper.getBalanceHelper().loadBalance(mCreateWithdrawalRequest.request.balance);
    if (!balanceFrame){
        throw std::runtime_error("Withdrawer balance not found");
    }
    return std::vector<longstring> {
        ManageKeyValueOpFrame::makeWithdrawalTasksKey(balanceFrame->getAsset()),
        ManageKeyValueOpFrame::makeWithdrawalTasksKey("*")
    };
}

}
