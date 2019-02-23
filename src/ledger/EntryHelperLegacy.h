#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "overlay/StellarXDR.h"
#include "bucket/LedgerCmp.h"
#include "util/NonCopyable.h"
#include "util/Logging.h"
#include "crypto/SecretKey.h"
#include "EntryFrame.h"
#include "database/Database.h"

/*
Helper
Parent of AccountHelperLegacy, AssetHelperLegacy etc.
*/

namespace stellar
{
	class Database;
	class LedgerDelta;

	class EntryHelperLegacy {
	public:
		virtual void dropAll(Database& db) = 0;

		virtual void storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry) = 0;
		virtual void storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry) = 0;
		virtual void storeDelete(LedgerDelta& delta, Database& db, LedgerKey const& key) = 0;
		virtual bool exists(Database& db, LedgerKey const& key) = 0;
		virtual LedgerKey getLedgerKey(LedgerEntry const& from) = 0;
		virtual EntryFrame::pointer fromXDR(LedgerEntry const &from) = 0;
		virtual EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey, Database &db) = 0;
		virtual uint64_t countObjects(soci::session& sess) = 0;
		virtual uint64_t countObjects(Database& db);

		void flushCachedEntry(LedgerKey const& key, Database& db);
		bool cachedEntryExists(LedgerKey const& key, Database& db);

	protected:
		std::shared_ptr<LedgerEntry const> getCachedEntry(LedgerKey const& key, Database& db);
		void putCachedEntry(LedgerKey const& key, std::shared_ptr<LedgerEntry const> p, Database& db, LedgerDelta* delta = nullptr);
	};

	class EntryHelperProvider {
	public:
        static EntryHelperLegacy* getHelper(LedgerEntryType type)
        {
            auto foundHelperIt = helpers.find(type);
            if (foundHelperIt == helpers.end())
            {
            	CLOG(ERROR, Logging::ENTRY_LOGGER) << "Expected helper to exists, entry type: "
												   << xdr::xdr_traits<LedgerEntryType>::enum_name(type);
            	throw std::runtime_error("Expected helper to exists");
            }

            return foundHelperIt->second;
        }

		static void dropAll(Database &db);

		// Providers for appropriate methods of adding/deleting etc.
		static void storeAddEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry);
		static void storeChangeEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry);
		static void storeDeleteEntry(LedgerDelta& delta, Database& db, LedgerKey const& key);
		static bool existsEntry(Database& db, LedgerKey const& key);
		static EntryFrame::pointer storeLoadEntry(LedgerKey const& key, Database& db);
		static uint64_t countObjectsEntry(Database& db, LedgerEntryType const& type);

		[[deprecated]]
		static void storeAddOrChangeEntry(LedgerDelta& delta, Database& db, LedgerEntry const& entry);

		static void checkAgainstDatabase(LedgerEntry const& entry, Database& db);

	private:
		typedef std::map<LedgerEntryType, EntryHelperLegacy*> helperMap;
		static helperMap helpers;
	};

}