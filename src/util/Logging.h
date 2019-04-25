#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#define ELPP_THREAD_SAFE
#define ELPP_DISABLE_DEFAULT_CRASH_HANDLING
#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_NO_CHECK_MACROS
#define ELPP_NO_DEBUG_MACROS
#define ELPP_DISABLE_PERFORMANCE_TRACKING
#define ELPP_WINSOCK2
#define ELPP_DEBUG_ERRORS

// NOTE: Nothing else should include easylogging directly include this file
// instead Please think carefully modifying this file, and potentially using
// synchronization primitives. It is easy to introduce data races and deadlocks,
// so it is recommended to use valgrind --tool=helgrind to detect potential
// problems.
#include "util/asio.h"
#include "util/crow.h"
#include "lib/util/easylogging++.h"

namespace stellar
{
using nlohmann::crow;

class Logging
{
    static el::Configurations gDefaultConf;

  public:
	  static const char* ENTRY_LOGGER;
	  static const char* OPERATION_LOGGER;


    static void init();
    static void setFmt(std::string const& peerID, bool timestamps = true);
    static void setLoggingToFile(std::string const& filename);
    static void setLoggingToSentry(std::string const& dsn, el::Level logLevel = el::Level::Warning);
    static void setLogLevel(el::Level level, const char* partition);
    static el::Level getLLfromString(std::string const& levelName);
    static el::Level getLogLevel(std::string const& partition);
    static std::string getStringFromLL(el::Level);
    static bool logDebug(std::string const& partition);
    static bool logTrace(std::string const& partition);
    static void rotate();
};

class SentryClient {
public:
    SentryClient(const std::string &dsn) {
        mCrowClient = new crow(dsn);
#ifndef CORE_REVISION
#define CORE_REVISION "core_revision_was_not_provided"
#endif
        json attributes = {
            {"revision", CORE_REVISION},
        };
        mCrowClient->add_tags_context(attributes);
    }

    void send(const std::string &msg);
private:
    crow* mCrowClient;
};

class SentryLogCallback : public el::LogDispatchCallback {
public:
    void setClient(std::string sentryDSN, el::Level minLevel);
    void handle(const el::LogDispatchData* data) noexcept override;

private:
    std::unique_ptr<SentryClient> mClient;
    const el::LogDispatchData* mData;
    el::Level mMinimalLevelToSend;

    void dispatch(el::base::type::string_t&& logLine);
};
}
