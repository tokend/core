#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0
#include "util/asio.h"

#include "history/HistoryManager.h"
#include "ledger/LedgerManager.h"
#include "ledger/SyncingLedgerChain.h"
#include "main/PersistentState.h"
#include "transactions/TransactionFrame.h"
#include "xdr/Tokend-ledger.h"
#include "LedgerHeaderFrame.h"
#include <string>

/*
Holds the current ledger
Applies the tx set to the last ledger to get the next one
Hands the old ledger off to the history
*/

namespace medida
{
class Timer;
class Counter;
class Histogram;
}

namespace stellar
{
class AbstractLedgerTxn;
class Application;
class Database;
class LedgerTxnHeader;

class LedgerManagerImpl : public LedgerManager
{
    LedgerHeaderHistoryEntry mLastClosedLedger;
    LedgerHeaderFrame::pointer mCurrentLedger;

    Application& mApp;
    medida::Timer& mTransactionApply;
    medida::Histogram& mTransactionCount;
    medida::Histogram& mOperationCount;
    medida::Counter& mInternalErrorCount;
    medida::Timer& mLedgerClose;
    medida::Timer& mLedgerAgeClosed;
    medida::Counter& mLedgerAge;
    VirtualClock::time_point mLastClose;

    medida::Counter& mSyncingLedgersSize;
    uint32_t mCatchupTriggerLedger{0};

    CatchupState mCatchupState{CatchupState::NONE};

    void addToSyncingLedgers(LedgerCloseData const& ledgerData);
    void startCatchupIf(uint32_t lastReceivedLedgerSeq);

    void historyCaughtup(asio::error_code const& ec,
                         CatchupWork::ProgressState progressState,
                         LedgerHeaderHistoryEntry const& lastClosed);

    void processFeesSeqNums(std::vector<TransactionFramePtr>& txs,
                            LedgerDelta& ltxOuter);

    void applyTransactions(std::vector<TransactionFramePtr>& txs,
                           LedgerDelta& ltx,
                           TransactionResultSet& txResultSet);

    void ledgerClosed(LedgerDelta const& ltx);

    void storeCurrentLedger();

    enum class CloseLedgerIfResult
    {
        CLOSED,
        TOO_OLD,
        TOO_NEW
    };
    CloseLedgerIfResult closeLedgerIf(LedgerCloseData const& ledgerData);

    // returns account roleID
    uint64_t createAdminRole(StorageHelper& storageHelper);

    // returns signer role id
    uint64_t
    createAdminSigner(StorageHelper& storageHelper);

    void createDefaultSignerRules(StorageHelper& storageHelper,
                                  uint64_t const ownerRoleID);

    State mState;
    AccountID mNotExistingAccount;
    void setState(State s);

protected:
    SyncingLedgerChain mSyncingLedgers;

    void applyBufferedLedgers();
    void setCatchupState(CatchupState s);
    void advanceLedgerPointers();

    void initializeCatchup(LedgerCloseData const& ledgerData);
    void continueCatchup(LedgerCloseData const& ledgerData);
    void finalizeCatchup(LedgerCloseData const& ledgerData);

  public:
    LedgerManagerImpl(Application& app);

    void bootstrap() override;
    State getState() const override;
    CatchupState getCatchupState() const override;
    std::string getStateHuman() const override;

    void valueExternalized(LedgerCloseData const& ledgerData) override;

    uint32_t getLastMaxTxSetSize() const override;
    int64_t getLastMinBalance(uint32_t ownerCount) const override;
    uint32_t getLastReserve() const override;
    uint32_t getLastTxFee() const override;

    uint32_t getLastClosedLedgerNum() const override;
    uint64 getTxExpirationPeriod() const override;

    uint64_t getCloseTime() const override;
    tm getTmCloseTime() const override;

    uint64_t secondsSinceLastLedgerClose() const override;
    void syncMetrics() override;

    void startNewLedger() override;
    void loadLastKnownLedger(
        std::function<void(asio::error_code const& ec)> handler) override;

    LedgerHeaderHistoryEntry const& getLastClosedLedgerHeader() const override;
    LedgerHeader& getCurrentLedgerHeader() override;

    HistoryArchiveState getLastClosedLedgerHAS() override;

    Database& getDatabase() override;

    void startCatchup(CatchupConfiguration configuration,
                      bool manualCatchup) override;

    void closeLedger(LedgerCloseData const& ledgerData) override;
    void deleteOldEntries(Database& db, uint32_t ledgerSeq,
                            uint32_t count) override;

    bool shouldUse(const LedgerVersion version);
    LedgerVersion getLedgerVersion();
    AccountID getNotExistingAccountID() override;
};
}
