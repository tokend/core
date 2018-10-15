#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/SaleFrame.h>
#include "overlay/StellarXDR.h"
#include "ledger/StatisticsFrame.h"
#include "ledger/AccountFrame.h"
#include "ledger/BalanceFrame.h"
#include "StatisticsV2Processor.h"


namespace medida
{
class MetricsRegistry;
}

namespace stellar
{
class Application;
class Database;

class AccountManager
{
protected:
    Application& mApp;
    Database& mDb;
    LedgerDelta& mDelta;
    LedgerManager& mLm;

public:
    void createStats(AccountFrame::pointer account);

    enum Result
    {
        SUCCESS,
        LINE_FULL,
        UNDERFUNDED,
        STATS_OVERFLOW,
        LIMITS_EXCEEDED,
        REQUIRED_KYC,
        REQUIRED_VERIFICATION,
        BALANCE_NOT_FOUND,
        INCORRECT_PRECISION
    };

    AccountManager(Application& app, Database& db, LedgerDelta& delta,
                   LedgerManager& lm);

    [[deprecated]]
    Result processTransfer(AccountFrame::pointer account,
                           BalanceFrame::pointer balance, int64 amount,
                           int64& universalAmount, bool requireReview = false,
                           bool ignoreLimits = false);

    struct ProcessTransferResult {
        Result result;
        uint64_t universalAmount;

        ProcessTransferResult(Result result, uint64_t universalAmount) {
            this->result = result;
            this->universalAmount = universalAmount;
        }
    };

    bool calculateUniversalAmount(AssetCode transferAsset, uint64_t amount, uint64_t& universalAmount);

    ProcessTransferResult processTransferV2(AccountFrame::pointer from, BalanceFrame::pointer fromBalance, BalanceFrame::pointer toBalance,
        uint64_t amount, bool noIncludeIntoStats = false);

    ProcessTransferResult processStatistics(AccountFrame::pointer from, BalanceFrame::pointer fromBalance,
                                            uint64_t amount, uint64_t& universalAmount);

    bool revertRequest(AccountFrame::pointer account,
                       BalanceFrame::pointer balance, int64 amount,
                       int64 universalAmount, time_t timePerformed);


    bool validateStats(AccountFrame::pointer account,
                       BalanceFrame::pointer balance,
                       StatisticsFrame::pointer statsFrame);

    Limits getDefaultLimits(AccountType accountType);

    bool isFeeMatches(AccountFrame::pointer account, Fee fee, FeeType feeType, int64_t subtype, AssetCode assetCode, uint64_t amount) const;

    Result addStats(AccountFrame::pointer account, BalanceFrame::pointer balance, uint64_t amountToAdd,
                    uint64_t &universalAmount);

    Result tryAddStatsV2(const AccountFrame::pointer account, const BalanceFrame::pointer balance,
                         const uint64_t amountToAdd, uint64_t& universalAmount);

    void revertStats(AccountID account, uint64_t universalAmount, time_t timePerformed);

    void transferFee(AssetCode asset, uint64_t totalFee);

    void transferFee(AssetCode asset, Fee fee);

    BalanceID loadOrCreateBalanceForAsset(AccountID const& account, AssetCode const& asset) const;
    static BalanceID loadOrCreateBalanceForAsset(AccountID const& account, AssetCode const& asset, Database& db, LedgerDelta& delta);
    static BalanceFrame::pointer loadOrCreateBalanceFrameForAsset(AccountID const& account, AssetCode const& asset, Database& db, LedgerDelta& delta);

    static Result isAllowedToReceive(BalanceID receivingBalance, Database& db);

    static Result isAllowedToReceive(BalanceFrame::pointer balanceFrame, Database& db);

    static Result isAllowedToReceive(AccountFrame::pointer account, BalanceFrame::pointer balance, Database& db);

    static void unlockPendingIssuanceForSale(const SaleFrame::pointer sale, LedgerDelta &delta, Database &db,
                                             LedgerManager &lm);
};
}
