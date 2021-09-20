#include "BalanceManager.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerManager.h"
#include "ledger/KeyValueHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/AssetPairHelper.h"
#include "main/Application.h"
#include "transactions/managers/StatisticsV2Processor.h"

namespace stellar
{
BalanceManager::BalanceManager(Application& app, StorageHelper& sh)
    : mApp(app), mLm(app.getLedgerManager()), mSh(sh)
{
    mUniversalAmount = 0;
}

BalanceFrame::pointer
BalanceManager::loadOrCreateBalance(const AccountID& account, const AssetCode& asset)
{
    BalanceFrame::pointer balance;
    if(mLm.shouldUse(LedgerVersion::FIX_UNORDERED_FEE_DESTINATION)){
        balance = mSh.getBalanceHelper().loadFirstBalance(account, asset);
    } else {
        balance = mSh.getBalanceHelper().loadBalance(account, asset);
    }

    if (balance)
    {
        return balance;
    }

    if (!mSh.getAssetHelper().existActive(asset))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state: "
                                               << "expected asset to exist: " << asset;
        throw std::runtime_error("Unexpected db state: expected asset to exist");
    }

    auto sequentialID = mSh.mustGetLedgerDelta().getHeaderFrame()
        .generateID(LedgerEntryType::BALANCE);
    auto balanceID = BalanceKeyUtils::forAccount(account, sequentialID);
    balance = BalanceFrame::createNew(balanceID, account, asset, sequentialID);

    mSh.getBalanceHelper().storeAdd(balance->mEntry);

    return balance;
}

BalanceFrame::pointer
BalanceManager::loadOrCreateBalanceForAdmin(const AssetCode& assetCode)
{
    return loadOrCreateBalance(mApp.getAdminID(), assetCode);
}

void
BalanceManager::transferFee(AssetCode const& assetCode, uint64_t totalFee)
{
    BalanceFrame::pointer commissionBalance;
    if(mLm.shouldUse(LedgerVersion::ADD_DEFAULT_FEE_RECEIVER_BALANCE_KV)){
        auto& keyValueHelper = mSh.getKeyValueHelper();
        PublicKey commissionBalanceID;
        keyValueHelper.loadBalanceID(commissionBalanceID, makeTasksKeyVector(assetCode));
        commissionBalance = mSh.getBalanceHelper().loadBalance(commissionBalanceID);
    }

    if(!commissionBalance){
        commissionBalance = loadOrCreateBalanceForAdmin(assetCode);
    }

    if (totalFee == 0)
    {
        return;
    }

    // load commission balance and transfer fee

    const auto result = commissionBalance->tryFundAccount(totalFee);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        std::string strBalanceID = PubKeyUtils::toStrKey(commissionBalance->getBalanceID());
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to fund commission balance with fee, reason " << result
            << ". balanceID: " << strBalanceID;
        throw std::runtime_error("Failed to fund commission balance with fee");
    }

    mSh.getBalanceHelper().storeChange(commissionBalance->mEntry);
}

BalanceManager::Result
BalanceManager::transfer(AccountFrame::pointer from,
                         BalanceFrame::pointer fromBalance,
                         BalanceFrame::pointer toBalance,
                         uint64_t amount, bool noIncludeIntoStats)
{
    // charge sender
    const auto fromBalanceChargeResult = fromBalance->tryCharge(amount);
    if (fromBalanceChargeResult != BalanceFrame::Result::SUCCESS)
    {
        return convertToResult(fromBalanceChargeResult);
    }

    auto& balanceHelper = mSh.getBalanceHelper();
    balanceHelper.storeChange(fromBalance->mEntry);

    const auto toBalanceFundResult = toBalance->tryFundAccount(amount);
    if (toBalanceFundResult != BalanceFrame::Result::SUCCESS)
    {
        return convertToResult(toBalanceFundResult);
    }

    balanceHelper.storeChange(toBalance->mEntry);

    if (!mLm.shouldUse(LedgerVersion::FIX_PAYMENT_STATS))
    {
        if (!calculateUniversalAmount(fromBalance->getAsset(), amount))
        {
            return Result::STATS_OVERFLOW;
        }

        if (mUniversalAmount == 0)
        {
            return Result::SUCCESS;
        }
    }

    if (noIncludeIntoStats)
    {
        return Result::SUCCESS;
    }

    return processStatistics(from, fromBalance, amount);
}

BalanceManager::Result
BalanceManager::processStatistics(AccountFrame::pointer from,
                                  BalanceFrame::pointer fromBalance, uint64_t amount)
{
    mUniversalAmount = 0;
    StatisticsV2Processor statisticsV2Processor(mSh, mLm);

    const auto result = statisticsV2Processor.addStatsV2(StatisticsV2Processor::SpendType::PAYMENT, amount,
                                                         mUniversalAmount, from, fromBalance);
    switch (result)
    {
        case StatisticsV2Processor::SUCCESS:
            return BalanceManager::SUCCESS;
        case StatisticsV2Processor::STATS_V2_OVERFLOW:
            return BalanceManager::STATS_OVERFLOW;
        case StatisticsV2Processor::LIMITS_V2_EXCEEDED:
            return BalanceManager::LIMITS_EXCEEDED;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result from "
                                                   << "statisticsV2Processor when updating statsV2:" << result;
            throw std::runtime_error("Unexpected state from statisticsV2Processor when updating statsV2");
    }
}

BalanceManager::Result
BalanceManager::convertToResult(BalanceFrame::Result balanceResult)
{
    switch (balanceResult)
    {
        case BalanceFrame::Result::SUCCESS:
            return SUCCESS;
        case BalanceFrame::Result::NONMATCHING_PRECISION:
            return INCORRECT_PRECISION;
        case BalanceFrame::Result::LINE_FULL:
            return LINE_FULL;
        case BalanceFrame::Result::UNDERFUNDED:
            return UNDERFUNDED;
        default:
            throw std::runtime_error("Unknown balance result type");
    }
}

bool
BalanceManager::calculateUniversalAmount(AssetCode transferAsset, uint64_t amount)
{
    mUniversalAmount = 0;

    auto statsAssetFrame = mSh.getAssetHelper().loadStatsAsset();
    if (!statsAssetFrame)
    {
        return true;
    }

    if (transferAsset == statsAssetFrame->getCode())
    {
        mUniversalAmount = amount;
        return true;
    }

    auto assetPairFrame = mSh.getAssetPairHelper().tryLoadAssetPairForAssets(
        transferAsset, statsAssetFrame->getCode());
    if (!assetPairFrame)
    {
        return true;
    }

    return mSh.getAssetPairHelper().convertAmount(assetPairFrame, transferAsset,
                                                      amount, Rounding::ROUND_UP, mUniversalAmount);
}

std::vector<std::string>
BalanceManager::makeTasksKeyVector(AssetCode const& code)
{
    return
        {
            ManageKeyValueOpFrame::makeFeeCollectionBalanceKey(code),
            ManageKeyValueOpFrame::makeFeeCollectionBalanceKey("*")
        };
}

}
