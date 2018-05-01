// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/AssetFrame.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AccountHelper.h>
#include "transactions/AccountManager.h"
#include "main/Application.h"
#include "ledger/AssetPairFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AccountLimitsFrame.h"
#include "ledger/AccountLimitsHelper.h"
#include "ledger/AccountTypeLimitsFrame.h"
#include "ledger/AccountTypeLimitsHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/EntryHelper.h"
#include "ledger/StatisticsHelper.h"
#include "ledger/FeeHelper.h"

namespace stellar
{
using namespace std;

AccountManager::AccountManager(Application& app, Database& db,
                               LedgerDelta& delta, LedgerManager& lm)
    : mApp(app)
    , mDb(db)
    , mDelta(delta)
    , mLm(lm)
{
}

void AccountManager::createStats(AccountFrame::pointer account)
{
    auto statsFrame = make_shared<StatisticsFrame>();
    auto& stats = statsFrame->getStatistics();
    stats.accountID = account->getID();
    stats.dailyOutcome = 0;
    stats.weeklyOutcome = 0;
    stats.monthlyOutcome = 0;
    stats.annualOutcome = 0;
    EntryHelperProvider::storeAddEntry(mDelta, mDb, statsFrame->mEntry);
}

AccountManager::Result AccountManager::processTransfer(
    AccountFrame::pointer account, BalanceFrame::pointer balance, int64 amount,
    int64& universalAmount, bool requireReview, bool ignoreLimits)
{
    if (requireReview)
    {
        auto addResult = balance->lockBalance(amount);
        if (addResult == BalanceFrame::Result::UNDERFUNDED)
            return UNDERFUNDED;
        else if (addResult == BalanceFrame::Result::LINE_FULL)
            return LINE_FULL;
    }
    else
    {
        if (!balance->addBalance(-amount))
            return UNDERFUNDED;
    }

    auto statsAssetFrame = AssetHelper::Instance()->loadStatsAsset(mDb);
    if (!statsAssetFrame)
        return SUCCESS;

    auto assetPairFrame = AssetPairHelper::Instance()->loadAssetPair(balance->getAsset(), statsAssetFrame->getCode(),
                                                                     mDb, &mDelta);
    if (!assetPairFrame)
        return SUCCESS;

    if (!bigDivide(universalAmount, amount, assetPairFrame->getCurrentPrice(),
                   ONE, ROUND_UP))
    {
        return STATS_OVERFLOW;
    }

    auto stats = StatisticsHelper::Instance()->mustLoadStatistics(balance->getAccountID(), mDb, &mDelta);

    auto now = mLm.getCloseTime();
    if (!stats->add(universalAmount, now))
    {
        return STATS_OVERFLOW;
    }

    if (!ignoreLimits && !validateStats(account, balance, stats))
    {
        return LIMITS_EXCEEDED;
    }

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, stats->mEntry);
    return SUCCESS;
}

AccountManager::ProcessTransferResult AccountManager::processTransferV2(AccountFrame::pointer from, BalanceFrame::pointer fromBalance,
    BalanceFrame::pointer toBalance, uint64_t amount, bool noIncludeIntoStats)
{
    // charge sender
    if (!fromBalance->tryCharge(amount)) {
        return ProcessTransferResult(Result::UNDERFUNDED, 0);
    }

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, fromBalance->mEntry);

    if (!toBalance->tryFundAccount(amount)) {
        return ProcessTransferResult(Result::LINE_FULL, 0);
    }

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, toBalance->mEntry);

    auto statsAssetFrame = AssetHelper::Instance()->loadStatsAsset(mDb);
    if (!statsAssetFrame) {
        return ProcessTransferResult(Result::SUCCESS, 0);
    }

    auto assetPairFrame = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(fromBalance->getAsset(), statsAssetFrame->getCode(),
        mDb, &mDelta);
    if (!assetPairFrame) {
        return ProcessTransferResult(Result::SUCCESS, 0);
    }

    uint64_t universalAmount;
    if (!assetPairFrame->convertAmount(fromBalance->getAsset(), amount, Rounding::ROUND_UP, universalAmount)) {
        return ProcessTransferResult(Result::STATS_OVERFLOW, 0);
    }

    auto result = ProcessTransferResult(Result::STATS_OVERFLOW, universalAmount);
    if (noIncludeIntoStats) {
        return result;
    }

    auto stats = StatisticsHelper::Instance()->mustLoadStatistics(fromBalance->getAccountID(), mDb, &mDelta);

    auto now = mLm.getCloseTime();
    if (!stats->add(universalAmount, now))
    {
        return ProcessTransferResult(Result::STATS_OVERFLOW, 0);
    }

    if (!validateStats(from, fromBalance, stats))
    {
        return ProcessTransferResult(Result::LIMITS_EXCEEDED, 0);
    }

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, stats->mEntry);
    return result;

}

bool AccountManager::revertRequest(AccountFrame::pointer account,
                                   BalanceFrame::pointer balance, int64 amount,
                                   int64 universalAmount, time_t timePerformed)
{
    if (balance->lockBalance(-amount) != BalanceFrame::Result::SUCCESS)
    {
        return false;
    }

    auto statisticsHelper = StatisticsHelper::Instance();
    auto stats = statisticsHelper->mustLoadStatistics(balance->getAccountID(),
                                                      mDb, &mDelta);
    uint64_t now = mLm.getCloseTime();

    auto accIdStrKey = PubKeyUtils::toStrKey(balance->getAccountID());
    stats->revert(universalAmount, now, timePerformed);

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, stats->mEntry);
    return true;
}

bool AccountManager::validateStats(AccountFrame::pointer account,
                                   BalanceFrame::pointer balance,
                                   StatisticsFrame::pointer statsFrame)
{
    auto stats = statsFrame->getStatistics();
    auto accountLimitsHelper = AccountLimitsHelper::Instance();
    auto accountLimits = accountLimitsHelper->
        loadLimits(balance->getAccountID(), mDb);

    Limits limits;

    if (accountLimits)
        limits = accountLimits->getLimits();
    else
    {
        limits = getDefaultLimits(account->getAccountType());
    }
    if (stats.dailyOutcome > limits.dailyOut)
        return false;
    if (stats.weeklyOutcome > limits.weeklyOut)
        return false;
    if (stats.monthlyOutcome > limits.monthlyOut)
        return false;
    if (stats.annualOutcome > limits.annualOut)
        return false;
    return true;
}

Limits AccountManager::getDefaultLimits(AccountType accountType)
{
    auto accountTypeLimitsHelper = AccountTypeLimitsHelper::Instance();
    auto defaultLimitsFrame = accountTypeLimitsHelper->loadLimits(
                                                                  accountType,
                                                                  mDb);
    Limits limits;

    if (defaultLimitsFrame)
        limits = defaultLimitsFrame->getLimits();
    else
    {
        limits.dailyOut = INT64_MAX;
        limits.weeklyOut = INT64_MAX;
        limits.monthlyOut = INT64_MAX;
        limits.annualOut = INT64_MAX;
    }
    return limits;
}

bool AccountManager::isFeeMatches(const AccountFrame::pointer account, const Fee fee,
                                  const FeeType feeType, const int64_t subtype, const AssetCode assetCode, const uint64_t amount) const
{
    if (isSystemAccountType(account->getAccountType()))
    {
        return fee.fixed == 0 && fee.percent == 0;
    }
    
    auto feeFrame = FeeHelper::Instance()->loadForAccount(feeType, assetCode, subtype, account, amount, mDb);
    if (!feeFrame)
    {
        return fee.fixed == 0 && fee.percent == 0;
    }

    if (feeFrame->getFee().fixedFee != fee.fixed)
    {
        return false;
    }

    // if we have overflow - fee does not match
    uint64_t expectedPercentFee = 0;
    if (!feeFrame->calculatePercentFee(amount, expectedPercentFee, Rounding::ROUND_UP))
    {
        return false;
    }

    return fee.percent == expectedPercentFee;
}

AccountManager::Result AccountManager::addStats(AccountFrame::pointer account,
                                                BalanceFrame::pointer balance,
                                                uint64_t amountToAdd, uint64_t &universalAmount) {
    universalAmount = 0;
    auto statsAssetFrame = AssetHelper::Instance()->loadStatsAsset(mDb);
    if (!statsAssetFrame)
        return SUCCESS;

    AssetCode baseAsset = balance->getAsset();
    auto statsAssetPair = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(baseAsset, statsAssetFrame->getCode(), mDb);
    if (!statsAssetPair)
        return SUCCESS;

    if (!statsAssetPair->convertAmount(statsAssetFrame->getCode(), amountToAdd, ROUND_UP, universalAmount))
        return STATS_OVERFLOW;

    auto statsFrame = StatisticsHelper::Instance()->mustLoadStatistics(account->getID(), mDb);
    time_t currentTime = mLm.getCloseTime();
    if (!statsFrame->add(universalAmount, currentTime))
        return STATS_OVERFLOW;

    if (!validateStats(account, balance, statsFrame))
        return LIMITS_EXCEEDED;

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, statsFrame->mEntry);
    return SUCCESS;
}

void AccountManager::revertStats(AccountID account, uint64_t universalAmount, time_t timePerformed)
{
    auto statsFrame = StatisticsHelper::Instance()->mustLoadStatistics(account, mDb);
    time_t now = mLm.getCloseTime();
    auto accIdStr = PubKeyUtils::toStrKey(account);

    statsFrame->revert(universalAmount, now, timePerformed);

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, statsFrame->mEntry);
}

void AccountManager::transferFee(AssetCode asset, uint64_t totalFee)
{
    if (totalFee == 0)
        return;

    // load commission balance and transfer fee
    auto commissionBalance = loadOrCreateBalanceFrameForAsset(mApp.getCommissionID(), asset, mDb, mDelta);

    if (!commissionBalance->tryFundAccount(totalFee)) {
        std::string strBalanceID = PubKeyUtils::toStrKey(commissionBalance->getBalanceID());
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to fund commission balance with fee - overflow. balanceID:"
                                               << strBalanceID;
        throw runtime_error("Failed to fund commission balance with fee");
    }

    EntryHelperProvider::storeChangeEntry(mDelta, mDb, commissionBalance->mEntry);
}

void AccountManager::transferFee(AssetCode asset, Fee fee)
{
    uint64_t totalFee = 0;
    if (!safeSum(fee.fixed, fee.percent, totalFee))
        throw std::runtime_error("totalFee overflows uin64");

    transferFee(asset, totalFee);
}

BalanceID AccountManager::loadOrCreateBalanceForAsset(AccountID const& account,
    AssetCode const& asset) const
{
    return loadOrCreateBalanceForAsset(account, asset, mDb, mDelta);
}

BalanceID AccountManager::loadOrCreateBalanceForAsset(AccountID const& account,
    AssetCode const& asset, Database& db, LedgerDelta& delta)
{
    auto balance = loadOrCreateBalanceFrameForAsset(account, asset, db, delta);
    return balance->getBalanceID();
}

BalanceFrame::pointer AccountManager::loadOrCreateBalanceFrameForAsset(
    AccountID const& account, AssetCode const& asset, Database& db,
    LedgerDelta& delta)
{
    auto balance = BalanceHelper::Instance()->loadBalance(account, asset, db, &delta);
    if (!!balance)
    {
        return balance;
    }

    if (!AssetHelper::Instance()->exists(db, asset))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state: expected asset to exist: " << asset;
        throw runtime_error("Unexpected db state: expected asset to exist");
    }

    auto newBalanceID = BalanceKeyUtils::forAccount(account, delta.getHeaderFrame().generateID(LedgerEntryType::BALANCE));
    balance = BalanceFrame::createNew(newBalanceID, account, asset);
    EntryHelperProvider::storeAddEntry(delta, db, balance->mEntry);
    return balance;
}

[[deprecated]]
bool AccountManager::isAllowedToReceive(BalanceID receivingBalance, Database &db)
{
    auto balanceFrame = BalanceHelper::Instance()->loadBalance(receivingBalance, db);
    if (!balanceFrame)
        return false;

    auto receiver = AccountHelper::Instance()->mustLoadAccount(balanceFrame->getAccountID(), db);
    auto receivingAsset = AssetHelper::Instance()->mustLoadAsset(balanceFrame->getAsset(), db);

    if (receiver->getAccountType() == AccountType::NOT_VERIFIED && receivingAsset->isRequireKYC())
        return false;

    return true;
}
}
