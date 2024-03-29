#pragma once
// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/SecretKey.h"
#include "lib/util/cpptoml.h"
#include "overlay/StellarXDR.h"
#include "util/SecretValue.h"
#include "util/Timer.h"
#include "util/optional.h"

#include <map>
#include <memory>
#include <string>
#include <set>

#define DEFAULT_PEER_PORT 11625

namespace stellar
{
struct HistoryArchiveConfiguration
{
    std::string mName;
    std::string mGetCmd;
    std::string mPutCmd;
    std::string mMkdirCmd;
};

class Config : public std::enable_shared_from_this<Config>
{
    void loadQset(std::shared_ptr<cpptoml::toml_group> group,
                  SCPQuorumSet& qset, int level);
		
    void parseNodeID(std::string configStr, PublicKey& retKey);
    void parseNodeID(std::string configStr, PublicKey& retKey, SecretKey& sKey,
                     bool isSeed);

    std::string expandNodeID(std::string const& s) const;


  public:
    static const uint32_t CURRENT_LEDGER_PROTOCOL_VERSION;
    
    typedef std::shared_ptr<Config> pointer;

    std::vector<PublicKey> getWiredKeys(LedgerVersion ledgerVersion) const;
    std::vector<PublicKey> getDevKeys() const;
    void validateConfig();

    enum TestDbMode
    {
        TESTDB_DEFAULT,
        TESTDB_IN_MEMORY_SQLITE,
        TESTDB_ON_DISK_SQLITE,
#ifdef USE_POSTGRES
        TESTDB_POSTGRESQL,
#endif
        TESTDB_MODES
    };

    // application config

    // The default way stellar-core starts is to load the state from disk and
    // catch
    // up to the network before starting SCP.
    // If you need different behavior you need to use --newdb or --force-scp
    // which sets the following flags:

    // SCP will start running immediately using the current local state to
    // participate in consensus. DO NOT INCLUDE THIS IN A CONFIG FILE
    bool FORCE_SCP;

    // This is a mode for testing. It prevents you from trying to connect to
    // other peers
    bool RUN_STANDALONE;

    // Mode for testing. Ledger will only close when told to over http
    bool MANUAL_CLOSE;

    // Whether to catchup "completely" (replaying all history); default is
    // false,
    // meaning catchup "minimally", using deltas to the most recent snapshot.
    bool CATCHUP_COMPLETE;

    // Number of "recent" ledgers before the current ledger to include in a
    // "minimal" catchup. Default is 0, and if CATCHUP_COMPLETE is set to
    // true, this is ignored.
    //
    // If you want, say, a week of history, set this to 120000.
    uint32_t CATCHUP_RECENT;

    // Interval between automatic maintenance executions
    std::chrono::seconds AUTOMATIC_MAINTENANCE_PERIOD;

    // Number of unneeded rows in each table that will be removed during one
    // maintenance run
    uint32_t AUTOMATIC_MAINTENANCE_COUNT;

    // A config parameter that enables synthetic load generation on demand,
    // using the `generateload` runtime command (see CommandHandler.cpp). This
    // option only exists for stress-testing and should not be enabled in
    // production networks.
    bool ARTIFICIALLY_GENERATE_LOAD_FOR_TESTING;

    // A config parameter that reduces ledger close time to 1s and checkpoint
    // frequency to every 8 ledgers. Do not ever set this in production, as it
    // will make your history archives incompatible with those of anyone else.
    bool ARTIFICIALLY_ACCELERATE_TIME_FOR_TESTING;

    // A config parameter to override the close time (in seconds). Do not use
    // in production as it may render the network unstable.
    uint32 ARTIFICIALLY_SET_CLOSE_TIME_FOR_TESTING;

    // A config parameter that avoids resolving FutureBuckets before writing
    // them to the database's persistent state; this option exists only
    // for stress-testing the ability to resume from an interrupted merge,
    // and should be false in all normal cases.
    bool ARTIFICIALLY_PESSIMIZE_MERGES_FOR_TESTING;

    // A config to allow connections to localhost
    // this should only be enabled when testing as it's a security issue
    bool ALLOW_LOCALHOST_FOR_TESTING;

    // Set to use config file values for genesis ledger
    // not setable in config file - only tests are allowed to do this
    bool USE_CONFIG_FOR_GENESIS;

    // This is the number of failures you want to be able to tolerate.
    // You will need at least 3f+1 nodes in your quorum set.
    // If you don't have enough in your quorum set to tolerate the level you
    //  set here stellar-core won't run.
    int32_t FAILURE_SAFETY;

    // If set to true allows you to specify an unsafe quorum set.
    // Otherwise it won't start if you have your threshold % set too low.
    // You might want to set this if you are running your own network and
    //  aren't concerned with byzantine failures.
    bool UNSAFE_QUORUM;

    // If set to true, bucket GC will not be performed. It can lead to massive
    // disk usage, but it is useful for recovering of nodes.
    bool DISABLE_BUCKET_GC;

    // Set of cursors added at each startup with value '1'.
    std::vector<std::string> KNOWN_CURSORS;

    uint32_t LEDGER_PROTOCOL_VERSION;
    VirtualClock::time_point TESTING_UPGRADE_DATETIME;

    // note: all versions in the range
    // [OVERLAY_PROTOCOL_MIN_VERSION, OVERLAY_PROTOCOL_VERSION] must be handled
    uint32_t OVERLAY_PROTOCOL_MIN_VERSION; // min overlay version understood
    uint32_t OVERLAY_PROTOCOL_VERSION;     // max overlay version understood
    std::string VERSION_STR;
    std::string LOG_FILE_PATH;
    std::string BUCKET_DIR_PATH;
    uint32_t TESTING_UPGRADE_DESIRED_FEE; // in stroops
    uint32_t TESTING_UPGRADE_RESERVE;     // in stroops
    uint32_t DESIRED_MAX_TX_PER_LEDGER;
    unsigned short HTTP_PORT; // what port to listen for commands
    bool PUBLIC_HTTP_PORT;    // if you accept commands from not localhost
    int HTTP_MAX_CLIENT;      // maximum number of http clients, i.e backlog
    std::string NETWORK_PASSPHRASE; // identifier for the network

	PublicKey masterID; // account id of master account
    uint64_t adminRoleID;

    std::string BASE_EXCHANGE_NAME;
    int64_t TX_EXPIRATION_PERIOD;
    int64 TX_EXPIRATION_PERIOD_WINDOW = 60*60;
    
    uint64 MAX_INVOICES_FOR_RECEIVER_ACCOUNT = 20;
    uint64 MAX_INVOICE_DETAIL_LENGTH = 256;
    uint64 MAX_CONTRACTS_FOR_CONTRACTOR = 20;
    uint64 MAX_CONTRACT_DETAIL_LENGTH = 256;
    uint64 MAX_CONTRACT_INITIAL_DETAIL_LENGTH = 1000;
    uint32 MAX_SIGNS = 1024;

    uint64 LICENSE_FREE_PERIOD_NUM_BLOCKS = 600000;

    int32 KYC_SUPER_ADMIN_MASK = 1;

    size_t mSignerRuleIDsMaxCount = 128;

    uint32_t mMaxSaleRulesLength = 150;

    // overlay config
    unsigned short PEER_PORT;
    unsigned short TARGET_PEER_CONNECTIONS;
    unsigned short MAX_PENDING_CONNECTIONS;
    int MAX_ADDITIONAL_PEER_CONNECTIONS;
    unsigned short MAX_INBOUND_PENDING_CONNECTIONS;
    unsigned short MAX_OUTBOUND_PENDING_CONNECTIONS;
    unsigned short PEER_AUTHENTICATION_TIMEOUT;
    unsigned short PEER_TIMEOUT;
    unsigned short PEER_STRAGGLER_TIMEOUT;
    static constexpr auto const POSSIBLY_PREFERRED_EXTRA = 2;
    // Peers we will always try to stay connected to
    std::vector<std::string> PREFERRED_PEERS;
    std::vector<std::string> KNOWN_PEERS;

    std::set<std::string> TX_INTERNAL_ERROR;
    // set of txs for which we need to skip signatures checks - used for forking
    // TODO: should also handle enabling it from specific block
    std::set<std::string> TX_SKIP_SIG_CHECK;

    // Preference can also be expressed by peer pubkey
    std::vector<std::string> PREFERRED_PEER_KEYS;

    // Whether to exclude peers that are not preferred.
    bool PREFERRED_PEERS_ONLY;

    // Percentage, between 0 and 100, of system activity (measured in terms
    // of both event-loop cycles and database time) below-which the system
    // will consider itself "loaded" and attempt to shed load. Set this
    // number low and the system will be tolerant of overloading. Set it
    // high and the system will be intolerant. By default it is 0, meaning
    // totally insensitive to overloading.
    uint32_t MINIMUM_IDLE_PERCENT;

    // process-management config
    size_t MAX_CONCURRENT_SUBPROCESSES;

    // SCP config
    SecretKey NODE_SEED;
    bool NODE_IS_VALIDATOR;
    stellar::SCPQuorumSet QUORUM_SET;

    // Invariants
    std::vector<std::string> INVARIANT_CHECKS;

    std::map<std::string, std::string> VALIDATOR_NAMES;

    // History config
    std::map<std::string, HistoryArchiveConfiguration> HISTORY;

    // Database config
    SecretValue DATABASE;

    std::vector<std::string> COMMANDS;
    std::vector<std::string> REPORT_METRICS;

    // Data layer cache configuration
    // - ENTRY_CACHE_SIZE controls the maximum number of LedgerEntry objects
    //   that will be stored in the cache
    // - BEST_OFFERS_CACHE_SIZE controls the maximum number of Asset pairs that
    //   will be stored in the cache, although many LedgerEntry objects may be
    //   associated with a single Asset pair
    size_t ENTRY_CACHE_SIZE;
    size_t BEST_OFFERS_CACHE_SIZE;

    std::string SENTRY_DSN;
    std::string MIN_LEVEL_FOR_SENTRY = "warning";

    std::vector<PublicKey> WIRED_KEYS;
    std::vector<PublicKey> DEV_LICENSE_KEYS;

    Config();

    void load(std::string const& filename);

    // fixes values of connection-relates settings
    void adjust();

    std::string toShortString(PublicKey const& pk) const;
    std::string toStrKey(PublicKey const& pk, bool& isAlias) const;
    std::string toStrKey(PublicKey const& pk) const;
    bool resolveNodeID(std::string const& s, PublicKey& retKey) const;


    std::chrono::seconds getExpectedLedgerCloseTime() const;

    void logBasicInfo();
    void setNoListen();

	std::vector<PublicKey> getSystemAccounts() const {
		return{ masterID };
	}

	uint64_t const
    getAdminRoleID() const
    {
        return adminRoleID;
    }

};
}
