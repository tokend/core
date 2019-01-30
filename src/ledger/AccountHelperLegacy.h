#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/EntryHelperLegacy.h"
#include <functional>
#include "map"
#include <unordered_map>
#include "xdr/Stellar-ledger-entries-account.h"
#include "AccountFrame.h"

namespace soci
{
	class session;
	namespace details
	{
		class prepare_temp_type;
	}
}

namespace stellar
{
	class LedgerManager;

	class AccountHelperLegacy : public EntryHelperLegacy {
	public:
		AccountHelperLegacy(AccountHelperLegacy const&) = delete;
		AccountHelperLegacy &operator=(AccountHelperLegacy const&) = delete;

		static AccountHelperLegacy* Instance() {
			static AccountHelperLegacy singleton;
			return &singleton;
		}

		void dropAll(Database& db) override;

		void storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
		void storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry) override;
		void storeDelete(LedgerDelta& delta, Database& db, LedgerKey const& key) override;
		bool exists(Database& db, LedgerKey const& key) override;
		bool exists(AccountID const& accountID, Database& db);
		void ensureExists(AccountID const &accountID, Database &db);
		LedgerKey getLedgerKey(LedgerEntry const& from) override;
		EntryFrame::pointer storeLoad(LedgerKey const& key, Database& db) override;
		EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
		uint64_t countObjects(soci::session& sess) override;

		AccountFrame::pointer loadAccount(AccountID const& accountID, Database& db, LedgerDelta* delta = nullptr);

		AccountFrame::pointer loadAccount(LedgerDelta& delta, AccountID const& accountID, Database& db);

		AccountFrame::pointer mustLoadAccount(AccountID const& accountID, Database& db);

		bool isRoleIDUsed(uint64_t roleID, Database& db);

	private:
		AccountHelperLegacy() { ; }
		~AccountHelperLegacy() { ; }

		void storeUpdate(LedgerDelta& delta, Database& db, bool insert, LedgerEntry const& entry);
	};


}