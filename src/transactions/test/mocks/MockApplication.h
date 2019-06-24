#pragma once

#include "main/Application.h"

namespace medida
{
class MetricsRegistry;
}

namespace stellar
{
class Config;
class VirtualClock;
class TmpDirManager;
class LedgerManager;
class BucketManager;
class HistoryManager;
class ProcessManager;
class Herder;
class InvariantManager;
class OverlayManager;
class Database;
class PersistentState;
class LoadGenerator;
class CommandHandler;
class WorkManager;
class BanManager;
class StatusManager;

class MockApplication : public Application
{
  public:
    MOCK_METHOD0(initialize,
                 void());
    MOCK_METHOD0(timeNow,
                 uint64_t());
    MOCK_METHOD0(getConfig,
                 const Config&());
    MOCK_CONST_METHOD0(getState,
                       State());
    MOCK_CONST_METHOD0(getStateHuman,
                       std::string());
    MOCK_CONST_METHOD0(isStopping,
                       bool());
    MOCK_METHOD0(getClock,
                 VirtualClock&());
    MOCK_METHOD0(getMetrics,
                 medida::MetricsRegistry&());
    MOCK_METHOD0(syncOwnMetrics,
                 void());
    MOCK_METHOD0(syncAllMetrics,
                 void());
    MOCK_METHOD1(clearMetrics,
                 void(std::string const& domain));
    MOCK_METHOD0(getTmpDirManager,
                 TmpDirManager&());
    MOCK_METHOD0(getLedgerManager,
                 LedgerManager&());
    MOCK_METHOD0(getBucketManager,
                 BucketManager&());
    MOCK_METHOD0(getCatchupManager,
                 CatchupManager&());
    MOCK_METHOD0(getHistoryArchiveManager,
                 HistoryArchiveManager&());
    MOCK_METHOD0(getHistoryManager,
                 HistoryManager&());
    MOCK_METHOD0(getMaintainer,
                 Maintainer&());
    MOCK_METHOD0(getProcessManager,
                 ProcessManager&());
    MOCK_METHOD0(getHerder,
                 Herder&());
    MOCK_METHOD0(getHerderPersistence,
                 HerderPersistence&());
    MOCK_METHOD0(getInvariantManager,
                 InvariantManager&());
    MOCK_METHOD0(getOverlayManager,
                 OverlayManager&());
    MOCK_CONST_METHOD0(getDatabase,
                       Database&());
    MOCK_METHOD0(getPersistentState,
                 PersistentState&());
    MOCK_METHOD0(getCommandHandler,
                 CommandHandler&());
    MOCK_METHOD0(getWorkManager,
                 WorkManager&());
    MOCK_METHOD0(getBanManager,
                 BanManager&());
    MOCK_METHOD0(getStatusManager,
                 StatusManager&());
    MOCK_METHOD0(getWorkerIOService,
                 asio::io_service&());
    MOCK_METHOD2(postOnMainThread,
                 void(std::function<void()>&& f, std::string jobName));
    MOCK_METHOD2(postOnMainThreadWithDelay,
                 void(std::function<void()>&& f, std::string jobName));
    MOCK_METHOD2(postOnBackgroundThread,
                 void(std::function<void()>&& f, std::string jobName));
    MOCK_METHOD0(start,
                 void());
    MOCK_METHOD0(gracefulStop,
                 void());
    MOCK_METHOD0(joinAllThreads,
                 void());
    MOCK_METHOD0(manualClose,
                 bool());
    MOCK_METHOD7(generateLoad,
                 void(bool isCreate, uint32_t nAccounts, uint32_t offset, uint32_t nTxs, uint32_t txRate, uint32_t batchSize, bool autoRate));
    MOCK_METHOD0(getLoadGenerator,
                 LoadGenerator&());
    MOCK_METHOD0(checkDB,
                 void());
    MOCK_METHOD0(checkDBSync,
                 void());
    MOCK_METHOD0(maintenance,
                 void());
    MOCK_METHOD0(applyCfgCommands,
                 void());
    MOCK_METHOD0(reportCfgMetrics,
                 void());
    MOCK_METHOD0(getJsonInfo,
                 Json::Value());
    MOCK_METHOD0(reportInfo,
                 void());
    MOCK_CONST_METHOD0(getNetworkID,
                       const Hash&());
    MOCK_METHOD0(newDB,
                 void());
    MOCK_CONST_METHOD0(getAdminID,
                       AccountID());
    MOCK_CONST_METHOD0(getBaseExchangeName,
                       std::string());
    MOCK_CONST_METHOD0(getTxExpirationPeriod,
                       uint64());
    MOCK_CONST_METHOD0(getWithdrawalDetailsMaxLength,
                       uint64());
    MOCK_CONST_METHOD0(getIssuanceDetailsMaxLength,
                       uint64());
    MOCK_CONST_METHOD0(getRejectReasonMaxLength,
                       uint64());
    MOCK_CONST_METHOD0(getMaxContractDetailLength,
                       uint64());
    MOCK_CONST_METHOD0(getMaxContractInitialDetailLength,
                       uint64());
    MOCK_CONST_METHOD0(getMaxContractsForContractor,
                       uint64());
    MOCK_CONST_METHOD0(getMaxSaleRulesLength,
                       uint32());
    MOCK_CONST_METHOD0(getMaxInvoiceDetailLength,
                       uint64());
    MOCK_CONST_METHOD0(getMaxInvoicesForReceiverAccount,
                       int64());
    MOCK_CONST_METHOD0(getKYCSuperAdminMask,
                       int32());
    MOCK_CONST_METHOD0(getSignerRuleIDsMaxCount,
                       size_t());
    MOCK_CONST_METHOD0(isCheckingPolicies,
                       bool());
    MOCK_METHOD0(stopCheckingPolicies,
                 void());
    MOCK_METHOD0(resumeCheckingPolicies,
                 void());
};
} // namespace stellar