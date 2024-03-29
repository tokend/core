// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "database/Database.h"
#include "DatabaseConnectionString.h"
#include "bucket/BucketManager.h"
#include "herder/Herder.h"
#include "herder/HerderPersistence.h"
#include "herder/Upgrades.h"
#include "history/HistoryManager.h"
#include "ledger/AccountSpecificRuleHelper.h"
#include "ledger/AtomicSwapAskHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "ledger/LedgerHeaderUtils.h"
#include "ledger/PollHelper.h"
#include "ledger/ReferenceHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/SwapHelper.h"
#include "ledger/VoteHelper.h"
#include "ledger/DataHelperImpl.h"
#include "main/Application.h"
#include "main/Config.h"
#include "main/ExternalQueue.h"
#include "main/PersistentState.h"
#include "medida/metrics_registry.h"
#include "overlay/BanManager.h"
#include "overlay/OverlayManager.h"
#include "transactions/TransactionFrame.h"
#include "util/GlobalChecks.h"
#include "util/Logging.h"
#include <ledger/AccountKYCHelper.h>
#include <ledger/AssetHelperImpl.h>
#include <ledger/ContractHelper.h>
#include <ledger/KeyValueHelper.h>
#include <ledger/LimitsV2Helper.h>
#include <ledger/DeferredPaymentHelper.h>
#include <ledger/PendingStatisticsHelper.h>
#include <ledger/ReviewableRequestHelper.h>
#include <ledger/StatisticsV2Helper.h>
#include <ledger/LiquidityPoolHelper.h>
#include "xdr/ledger-entries.h"

// NOTE: soci will just crash and not throw
//  if you misname a column in a query. yay!

namespace stellar
{

using namespace soci;
using namespace std;

bool DatabaseImpl::gDriversRegistered = false;

enum databaseSchemaVersion : unsigned long
{
    DROP_SCP = 2,
    DROP_BAN = 3,
    REFERENCE_VERSION = 4,
    ADD_ACCOUNT_KYC = 5,
    EXTERNAL_POOL_FIX_MIGRATION = 6,
    KEY_VALUE_FIX_MIGRATION = 7,
    EXTERNAL_POOL_FIX_PARENT_DB_TYPE = 8,
    ADD_LIMITS_V2 = 9,
    ADD_REVIEWABLE_REQUEST_TASKS = 10,
    ADD_CONTRACTS = 11,
    ADD_CUSTOMER_DETAILS_TO_CONTRACT = 12,
    ADD_ATOMIC_SWAP_BID = 13,
    ADD_ASSET_CUSTOM_PRECISION = 14,
    ADD_VOTING = 15,
    ADD_PEER_TYPE = 16,
    ADD_SPECIFIC_RULES = 17,
    FIX_HISTORY_UPGRADES = 18,
    ENABLE_ATOMIC_SWAP = 19,
    SWAPS = 20,
    ASSET_STATE = 21,
    DEFERRED_PAYMENTS = 22,
    DATA = 23,
    LIQUIDITY_POOL = 24
};

static unsigned long const SCHEMA_VERSION = databaseSchemaVersion::LIQUIDITY_POOL;

static void
setSerializable(soci::session& sess)
{
    sess << "SET SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL "
            "SERIALIZABLE";
}

void
DatabaseImpl::registerDrivers()
{
    if (!gDriversRegistered)
    {
        register_factory_sqlite3();
#ifdef USE_POSTGRES
        register_factory_postgresql();
#endif
        gDriversRegistered = true;
    }
}

DatabaseImpl::DatabaseImpl(Application& app)
    : mApp(app)
    , mQueryMeter(
          app.getMetrics().NewMeter({"database", "query", "exec"}, "query"))
    , mStatementsSize(
          app.getMetrics().NewCounter({"database", "memory", "statements"}))
    , mEntryCache(4096)
    , mExcludedQueryTime(0)
    , mExcludedTotalTime(0)
    , mLastIdleQueryTime(0)
    , mLastIdleTotalTime(app.getClock().now())
{
    registerDrivers();
    CLOG(INFO, "Database") << "Connecting to: "
                           << removePasswordFromConnectionString(
                                  app.getConfig().DATABASE.value);
    mSession.open(app.getConfig().DATABASE.value);

    if (isSqlite())
    {
        mSession << "PRAGMA journal_mode = WAL";
        // busy_timeout gives room for external processes
        // that may lock the database for some time
        mSession << "PRAGMA busy_timeout = 10000";
    }
    else
    {
        setSerializable(mSession);
    }
}

void
DatabaseImpl::applySchemaUpgrade(unsigned long vers)
{
    clearPreparedStatementCache();

    StorageHelperImpl storageHelper(*this, nullptr);
    StorageHelper& sh = storageHelper;
    switch (vers) {
        case databaseSchemaVersion::DROP_SCP:
            HerderPersistence::dropAll(*this);
            break;
        case databaseSchemaVersion::DROP_BAN:
            BanManager::dropAll(*this);
            break;
        case REFERENCE_VERSION:
            sh.getReferenceHelper().addVersion();
            break;
        case databaseSchemaVersion::ADD_ACCOUNT_KYC:
            sh.getAccountKYCHelper().dropAll();
            break;
        case databaseSchemaVersion::EXTERNAL_POOL_FIX_MIGRATION:
            sh.getExternalSystemAccountIDPoolEntryHelper().dropAll();
            break;
        case databaseSchemaVersion::KEY_VALUE_FIX_MIGRATION:
            sh.getKeyValueHelper().dropAll();
            break;
        case databaseSchemaVersion::EXTERNAL_POOL_FIX_PARENT_DB_TYPE:
            sh.getExternalSystemAccountIDPoolEntryHelper().parentToNumeric();
            break;
        case databaseSchemaVersion::ADD_LIMITS_V2:
            sh.getLimitsV2Helper().dropAll();
            sh.getStatisticsV2Helper().dropAll();
            sh.getPendingStatisticsHelper().dropAll();
            break;
        case databaseSchemaVersion::ADD_REVIEWABLE_REQUEST_TASKS:
            sh.getPendingStatisticsHelper().restrictUpdateDelete();
            break;
        case databaseSchemaVersion::ADD_CONTRACTS:
            sh.getContractHelper().dropAll();
            break;
        case databaseSchemaVersion::ADD_CUSTOMER_DETAILS_TO_CONTRACT:
            sh.getContractHelper().addCustomerDetails();
            break;
        case databaseSchemaVersion::ADD_ATOMIC_SWAP_BID:
            sh.getAtomicSwapAskHelper().dropAll();
            break;
        case databaseSchemaVersion::ADD_ASSET_CUSTOM_PRECISION:
            std::unique_ptr<AssetHelper>(new AssetHelperImpl(storageHelper))->addTrailingDigits();
            break;
        case databaseSchemaVersion::ADD_VOTING:
            sh.getPollHelper().createIfNotExists();
            sh.getVoteHelper().createIfNotExists();
            sh.getPollHelper().permissionTypeMigration();
            break;
        case ADD_PEER_TYPE:
            mSession << "ALTER TABLE peers ADD type INT NOT NULL DEFAULT 0";
            mSession << "CREATE INDEX scpquorumsbyseq ON scpquorums(lastledgerseq)";
            break;
        case ADD_SPECIFIC_RULES:
            sh.getAccountSpecificRuleHelper().dropAll();
            break;
        case FIX_HISTORY_UPGRADES:
            Upgrades::createIfNotExists(*this);
            break;
        case ENABLE_ATOMIC_SWAP:
            sh.getAtomicSwapAskHelper().dropAll();
            break;
        case SWAPS:
            sh.getSwapHelper().dropAll();
            break;
        case ASSET_STATE:
            sh.getAssetHelper().addAssetState();
            break;
        case DEFERRED_PAYMENTS:
            sh.getDeferredPaymentHelper().createIfNotExists();
            break;
        case DATA:
            sh.getDataHelper().createIfNotExists();
            break;
        case LIQUIDITY_POOL:
            sh.getLiquidityPoolHelper().dropAll();
            break;
        default:
            CLOG(ERROR, "Database") << "Unknown DB schema version: " << vers;
            throw std::runtime_error("Unknown DB schema version");
    }
}

void
DatabaseImpl::upgradeToCurrentSchema()
{
    auto vers = getDBSchemaVersion();
    if (vers > SCHEMA_VERSION)
    {
        std::string s = ("DB schema version " + std::to_string(vers) +
                         " is newer than application schema " +
                         std::to_string(SCHEMA_VERSION));
        throw std::runtime_error(s);
    }
    while (vers < SCHEMA_VERSION)
    {
        ++vers;
        CLOG(INFO, "Database")
            << "Applying DB schema upgrade to version " << vers;
        applySchemaUpgrade(vers);
        putSchemaVersion(vers);
    }
    assert(vers == SCHEMA_VERSION);
}

void
DatabaseImpl::putSchemaVersion(unsigned long vers)
{
    mApp.getPersistentState().setState(PersistentState::kDatabaseSchema,
                                       std::to_string(vers));
}

unsigned long
DatabaseImpl::getDBSchemaVersion()
{
    auto vstr =
        mApp.getPersistentState().getState(PersistentState::kDatabaseSchema);
    unsigned long vers = 0;
    try
    {
        vers = std::stoul(vstr);
    }
    catch (...)
    {
    }
    if (vers == 0)
    {
        throw std::runtime_error("No DB schema version found, try --newdb");
    }
    return vers;
}

unsigned long
DatabaseImpl::getAppSchemaVersion()
{
    return SCHEMA_VERSION;
}

medida::TimerContext
DatabaseImpl::getInsertTimer(std::string const& entityName)
{
    mEntityTypes.insert(entityName);
    mQueryMeter.Mark();
    return mApp.getMetrics()
        .NewTimer({"database", "insert", entityName})
        .TimeScope();
}

medida::TimerContext
DatabaseImpl::getSelectTimer(std::string const& entityName)
{
    mEntityTypes.insert(entityName);
    mQueryMeter.Mark();
    return mApp.getMetrics()
        .NewTimer({"database", "select", entityName})
        .TimeScope();
}

medida::TimerContext
DatabaseImpl::getDeleteTimer(std::string const& entityName)
{
    mEntityTypes.insert(entityName);
    mQueryMeter.Mark();
    return mApp.getMetrics()
        .NewTimer({"database", "delete", entityName})
        .TimeScope();
}

medida::TimerContext
DatabaseImpl::getUpdateTimer(std::string const& entityName)
{
    mEntityTypes.insert(entityName);
    mQueryMeter.Mark();
    return mApp.getMetrics()
        .NewTimer({"database", "update", entityName})
        .TimeScope();
}

medida::TimerContext
DatabaseImpl::getUpsertTimer(std::string const& entityName)
{
    mEntityTypes.insert(entityName);
    mQueryMeter.Mark();
    return mApp.getMetrics()
        .NewTimer({"database", "upsert", entityName})
        .TimeScope();
}

void
DatabaseImpl::setCurrentTransactionReadOnly()
{
    if (!isSqlite())
    {
        auto prep = getPreparedStatement("SET TRANSACTION READ ONLY");
        auto& st = prep.statement();
        st.define_and_bind();
        st.execute(false);
    }
}

bool
DatabaseImpl::isSqlite() const
{
    return mApp.getConfig().DATABASE.value.find("sqlite3:") !=
           std::string::npos;
}

bool
DatabaseImpl::canUsePool() const
{
    return !(mApp.getConfig().DATABASE.value == ("sqlite3://:memory:"));
}

void
DatabaseImpl::clearPreparedStatementCache()
{
    // Flush all prepared statements; in sqlite they represent open cursors
    // and will conflict with any DROP TABLE commands issued below
    for (auto st : mStatements)
    {
        st.second->clean_up(true);
    }
    mStatements.clear();
    mStatementsSize.set_count(mStatements.size());
}

void
DatabaseImpl::initialize()
{
    clearPreparedStatementCache();
    // normally you do not want to touch this section as
    // schema updates are done in applySchemaUpgrade

    // only time this section should be modified is when
    // consolidating changes found in applySchemaUpgrade here
    StorageHelperImpl storageHelperImpl(*this, nullptr);
    StorageHelper& storageHelper = storageHelperImpl;
    auto helpers = storageHelper.getEntryHelpers();
    for (auto& helper : helpers)
    {
        helper->dropAll();
    }

    OverlayManager::dropAll(*this);
    PersistentState::dropAll(*this);
    ExternalQueue::dropAll(*this);
    LedgerHeaderUtils::dropAll(*this);
    TransactionFrame::dropAll(*this);
    HistoryManager::dropAll(*this);
    mApp.getBucketManager().dropAll();
    HerderPersistence::dropAll(*this);
    BanManager::dropAll(*this);
    Upgrades::dropAll(*this);
    putSchemaVersion(1);
}

soci::session&
DatabaseImpl::getSession()
{
    // global session can only be used from the main thread
    assertThreadIsMain();
    return mSession;
}

soci::connection_pool&
DatabaseImpl::getPool()
{
    if (!mPool)
    {
        auto const& c = mApp.getConfig().DATABASE;
        if (!canUsePool())
        {
            std::string s("Can't create connection pool to ");
            s += removePasswordFromConnectionString(c.value);
            throw std::runtime_error(s);
        }
        size_t n = std::thread::hardware_concurrency();
        LOG(INFO) << "Establishing " << n << "-entry connection pool to: "
                  << removePasswordFromConnectionString(c.value);
        mPool = std::make_unique<soci::connection_pool>(n);
        for (size_t i = 0; i < n; ++i)
        {
            LOG(DEBUG) << "Opening pool entry " << i;
            soci::session& sess = mPool->at(i);
            sess.open(c.value);
            if (!isSqlite())
            {
                setSerializable(sess);
            }
        }
    }
    assert(mPool);
    return *mPool;
}

cache::lru_cache<std::string, std::shared_ptr<LedgerEntry const>>&
DatabaseImpl::getEntryCache()
{
    return mEntryCache;
}

class SQLLogContext : NonCopyable
{
    std::string mName;
    soci::session& mSess;
    std::ostringstream mCapture;

  public:
    SQLLogContext(std::string const& name, soci::session& sess)
        : mName(name), mSess(sess)
    {
        mSess.set_log_stream(&mCapture);
    }
    ~SQLLogContext()
    {
        mSess.set_log_stream(nullptr);
        std::string captured = mCapture.str();
        std::istringstream rd(captured);
        std::string buf;
        CLOG(INFO, "Database") << "";
        CLOG(INFO, "Database") << "";
        CLOG(INFO, "Database") << "[SQL] -----------------------";
        CLOG(INFO, "Database") << "[SQL] begin capture: " << mName;
        CLOG(INFO, "Database") << "[SQL] -----------------------";
        while (std::getline(rd, buf))
        {
            CLOG(INFO, "Database") << "[SQL:" << mName << "] " << buf;
            buf.clear();
        }
        CLOG(INFO, "Database") << "[SQL] -----------------------";
        CLOG(INFO, "Database") << "[SQL] end capture: " << mName;
        CLOG(INFO, "Database") << "[SQL] -----------------------";
        CLOG(INFO, "Database") << "";
        CLOG(INFO, "Database") << "";
    }
};

StatementContext
DatabaseImpl::getPreparedStatement(std::string const& query)
{
    auto i = mStatements.find(query);
    std::shared_ptr<soci::statement> p;
    if (i == mStatements.end())
    {
        p = std::make_shared<soci::statement>(mSession);
        p->alloc();
        p->prepare(query);
        mStatements.insert(std::make_pair(query, p));
        mStatementsSize.set_count(mStatements.size());
    }
    else
    {
        p = i->second;
    }
    StatementContext sc(p);
    return sc;
}

std::shared_ptr<SQLLogContext>
DatabaseImpl::captureAndLogSQL(std::string contextName)
{
    return make_shared<SQLLogContext>(contextName, mSession);
}

medida::Meter&
DatabaseImpl::getQueryMeter()
{
    return mQueryMeter;
}

std::chrono::nanoseconds
DatabaseImpl::totalQueryTime() const
{
    std::vector<std::string> qtypes = {"insert", "delete", "select", "update"};
    std::chrono::nanoseconds nsq(0);
    for (auto const& q : qtypes)
    {
        for (auto const& e : mEntityTypes)
        {
            auto& timer = mApp.getMetrics().NewTimer({"database", q, e});
            uint64_t sumns = static_cast<uint64_t>(
                timer.sum() *
                static_cast<double>(timer.duration_unit().count()));
            nsq += std::chrono::nanoseconds(sumns);
        }
    }
    return nsq;
}

void
DatabaseImpl::excludeTime(std::chrono::nanoseconds const& queryTime,
                          std::chrono::nanoseconds const& totalTime)
{
    mExcludedQueryTime += queryTime;
    mExcludedTotalTime += totalTime;
}

uint32_t
DatabaseImpl::recentIdleDbPercent()
{
    std::chrono::nanoseconds query = totalQueryTime();
    query -= mLastIdleQueryTime;
    query -= mExcludedQueryTime;

    std::chrono::nanoseconds total = mApp.getClock().now() - mLastIdleTotalTime;
    total -= mExcludedTotalTime;

    if (total == std::chrono::nanoseconds::zero())
    {
        return 100;
    }

    uint32_t queryPercent =
        static_cast<uint32_t>((100 * query.count()) / total.count());
    uint32_t idlePercent = 100 - queryPercent;
    if (idlePercent > 100)
    {
        // This should never happen, but clocks are not perfectly well behaved.
        CLOG(WARNING, "Database") << "DB idle percent (" << idlePercent
                                  << ") over 100, limiting to 100";
        idlePercent = 100;
    }

    CLOG(DEBUG, "Database") << "Estimated DB idle: " << idlePercent << "%"
                            << " (query=" << query.count() << "ns"
                            << ", total=" << total.count() << "ns)";

    mLastIdleQueryTime = totalQueryTime();
    mLastIdleTotalTime = mApp.getClock().now();
    mExcludedQueryTime = std::chrono::nanoseconds(0);
    mExcludedTotalTime = std::chrono::nanoseconds(0);
    return idlePercent;
}

DBTimeExcluder::DBTimeExcluder(Application& app)
    : mApp(app)
    , mStartQueryTime(app.getDatabase().totalQueryTime())
    , mStartTotalTime(app.getClock().now())
{
}

DBTimeExcluder::~DBTimeExcluder()
{
    auto deltaQ = mApp.getDatabase().totalQueryTime() - mStartQueryTime;
    auto deltaT = mApp.getClock().now() - mStartTotalTime;
    mApp.getDatabase().excludeTime(deltaQ, deltaT);
}
}
