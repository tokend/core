#pragma once

#include "ledger/BalanceFrame.h"
#include "ledger/AccountFrame.h"

namespace stellar
{
class Application;
class StorageHelper;
class LedgerManager;

class BalanceManager
{
public:
    enum Result
    {
        SUCCESS,
        LINE_FULL,
        UNDERFUNDED,
        STATS_OVERFLOW,
        LIMITS_EXCEEDED,
        BALANCE_NOT_FOUND,
        INCORRECT_PRECISION
    };

    BalanceManager(Application& app, StorageHelper& sh);

    BalanceFrame::pointer
    loadOrCreateBalanceForAdmin(AssetCode const& assetCode);

    // result in not null
    BalanceFrame::pointer
    loadOrCreateBalance(AccountID const& account, AssetCode const& asset);

    Result
    transfer(AccountFrame::pointer from, BalanceFrame::pointer fromBalance,
             BalanceFrame::pointer toBalance, uint64_t amount,
             bool noIncludeIntoStats = false);

    // fund admin with fee amount
    void
    transferFee(AssetCode const& assetCode, uint64_t totalFee);

    [[deprecated]]
    uint64_t const
    getUniversalAmount() const
    {
        return mUniversalAmount;
    }

private:
    LedgerManager& mLm;
    Application& mApp;
    StorageHelper& mSh;
    uint64_t mUniversalAmount; //deprecated

    Result
    convertToResult(BalanceFrame::Result balanceResult);

    Result
    processStatistics(AccountFrame::pointer from, BalanceFrame::pointer fromBalance,
            uint64_t amount);

    [[deprecated]]
    bool
    calculateUniversalAmount(AssetCode transferAsset, uint64_t amount);
};
}
