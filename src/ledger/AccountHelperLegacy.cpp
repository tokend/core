// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ledger/AccountHelperLegacy.h"
#include "LedgerDelta.h"
#include "util/types.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void
AccountHelperLegacy::storeUpdate(LedgerDelta& delta, Database& db, bool insert, LedgerEntry const& entry)
{
    auto accountFrame = make_shared<AccountFrame>(entry);
    auto accountEntry = accountFrame->getAccount();

    accountFrame->touch(delta);

    LedgerKey const& key = accountFrame->getKey();
    flushCachedEntry(key, db);

    std::string actIDStrKey = PubKeyUtils::toStrKey(accountFrame->getID());

    int32_t newAccountVersion = static_cast<int32_t>(accountFrame->getAccount().ext.v());

    std::string sql;

    if (insert)
    {
        sql = std::string(
            "INSERT INTO accounts (accountid, recoveryid, thresholds, lastmodified, account_type, account_role,"
            "block_reasons, referrer, policies, kyc_level, version, sequential_id) "
            "VALUES (:id, :rid, :th, :lm, :type, :ar, :br, :ref, :p, :kyc, :v, :seqid)");
    }
    else
    {
        sql = std::string(
            "UPDATE accounts "
            "SET    recoveryid=:rid, thresholds=:th, lastmodified=:lm, account_type=:type, account_role=:ar, "
            "       block_reasons=:br, referrer=:ref, policies=:p, kyc_level=:kyc, version=:v, sequential_id = :seqid "
            "WHERE  accountid=:id");
    }

    auto prep = db.getPreparedStatement(sql);


    {
        soci::statement& st = prep.statement();
        st.exchange(use(actIDStrKey, "id"));
        st.exchange(use(accountFrame->mEntry.lastModifiedLedgerSeq, "lm"));
        st.exchange(use(newAccountVersion, "v"));
        st.exchange(use(accountEntry.sequentialID, "seqid"));
        st.exchange(use(accountEntry.roleID, "ar"));

        st.define_and_bind();
        {
            auto timer = insert ? db.getInsertTimer("account")
                : db.getUpdateTimer("account");
            st.execute(true);
        }

        if (st.get_affected_rows() != 1)
        {
            throw std::runtime_error("Could not update data in SQL");
        }
        if (insert)
        {
            delta.addEntry(*accountFrame);
        }
        else
        {
            delta.modEntry(*accountFrame);
        }
    }
}

void
AccountHelperLegacy::dropAll(Database& db)
{
    db.getSession() << "DROP TABLE IF EXISTS accounts;";

    db.getSession() << "CREATE TABLE accounts"
        "("
        "account_id          VARCHAR(56)  PRIMARY KEY,"
        "sequential_id      BIGINT       UNIQUE NOT NULL"
        "role_id BIGINT NOT NULL,"
        "version            INT          NOT NULL           DEFAULT 0,"
        "lastmodified       INT          NOT NULL,"
        ");";
}

void
AccountHelperLegacy::storeAdd(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    storeUpdate(delta, db, true, entry);
}

void
AccountHelperLegacy::storeChange(LedgerDelta& delta, Database& db, LedgerEntry const& entry)
{
    storeUpdate(delta, db, false, entry);
}

void
AccountHelperLegacy::storeDelete(LedgerDelta& delta, Database& db,
        LedgerKey const& key)
{
    flushCachedEntry(key, db);

    std::string actIDStrKey = PubKeyUtils::toStrKey(key.account().accountID);
    {
        auto timer = db.getDeleteTimer("account");
        auto prep = db.getPreparedStatement("DELETE FROM accounts "
            "WHERE       accountid=:v1");
        auto& st = prep.statement();
        st.exchange(soci::use(actIDStrKey));
        st.define_and_bind();
        st.execute(true);
    }
    {
        auto timer = db.getDeleteTimer("signer");
        auto prep =
            db.getPreparedStatement("DELETE FROM signers "
                "WHERE       accountid=:v1");
        auto& st = prep.statement();
        st.exchange(soci::use(actIDStrKey));
        st.define_and_bind();
        st.execute(true);
    }
    delta.deleteEntry(key);
}

bool
AccountHelperLegacy::exists(Database& db, LedgerKey const& key)
{
    if (cachedEntryExists(key, db) && getCachedEntry(key, db) != nullptr)
    {
        return true;
    }

    return exists(key.account().accountID, db);
}

LedgerKey
AccountHelperLegacy::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.account().accountID = from.data.account().accountID;
    return ledgerKey;
}

EntryFrame::pointer AccountHelperLegacy::storeLoad(LedgerKey const& key, Database& db)
{
    return loadAccount(key.account().accountID, db);
}

EntryFrame::pointer
AccountHelperLegacy::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AccountFrame>(from);
}

uint64_t
AccountHelperLegacy::countObjects(soci::session& sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM accounts;", into(count);
    return count;
}

AccountFrame::pointer
AccountHelperLegacy::loadAccount(AccountID const& accountID, Database& db, LedgerDelta* delta)
{
    LedgerKey key;
    key.type(LedgerEntryType::ACCOUNT);
    key.account().accountID = accountID;
    if (cachedEntryExists(key, db))
    {
        auto p = getCachedEntry(key, db);
        return p ? std::make_shared<AccountFrame>(*p) : nullptr;
    }

    std::string actIDStrKey = PubKeyUtils::toStrKey(accountID);

    std::string publicKey, creditAuthKey, referrer;
    std::string thresholds;

    AccountFrame::pointer res = make_shared<AccountFrame>(accountID);
    AccountEntry& account = res->getAccount();

    int32 accountType;
    uint32 accountPolicies;
    uint32 kycLevel;
    int32_t accountVersion;
    auto prep =
        db.getPreparedStatement("SELECT recoveryid, thresholds, lastmodified, account_type, account_role, "
            "block_reasons, referrer, policies, kyc_level, version, sequential_id "
            "FROM   accounts "
            "WHERE  accountid=:v1");
    auto& st = prep.statement();
    st.exchange(into(thresholds));
    st.exchange(into(res->mEntry.lastModifiedLedgerSeq));
    st.exchange(into(accountType));
    st.exchange(into(account.roleID));
    st.exchange(into(referrer));
    st.exchange(into(accountPolicies));
    st.exchange(into(kycLevel));
    st.exchange(into(accountVersion));
            st.exchange(into(account.sequentialID));
    st.exchange(use(actIDStrKey));
    st.define_and_bind();
    {
        auto timer = db.getSelectTimer("account");
        st.execute(true);
    }

    if (!st.got_data())
    {
        putCachedEntry(key, nullptr, db);
        return nullptr;
    }

    account.ext.v((LedgerVersion)accountVersion);

    std::shared_ptr<LedgerEntry const> pEntry = std::make_shared<LedgerEntry const>(res->mEntry);
    putCachedEntry(key, pEntry, db);
    return res;
}

AccountFrame::pointer
AccountHelperLegacy::loadAccount(LedgerDelta& delta, AccountID const& accountID,
        Database& db)
{
    auto a = loadAccount(accountID, db);
    if (a)
    {
        delta.recordEntry(*a);
    }
    return a;
}

AccountFrame::pointer
AccountHelperLegacy::mustLoadAccount(AccountID const& accountID, Database& db)
{
    auto accountFrame = loadAccount(accountID, db);

    if (!accountFrame)
    {
        throw new::runtime_error("Expect account to exist");
    }

    return accountFrame;
}

bool AccountHelperLegacy::exists(AccountID const &rawAccountID, Database &db) {
    int exists = 0;
    {
        auto timer = db.getSelectTimer("account-exists");
        auto prep =
                db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM accounts "
                                                "WHERE accountid=:v1)");
        auto& st = prep.statement();
                    auto accountID = PubKeyUtils::toStrKey(rawAccountID);
        st.exchange(use(accountID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }
    return exists != 0;
}

void AccountHelperLegacy::ensureExists(AccountID const &accountID, Database &db) {
    if (!exists(accountID, db))
    {
        auto accountIdStr = PubKeyUtils::toStrKey(accountID);
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: account not found in database, accountID: "
                                               << accountIdStr;
        throw runtime_error("Unexpected state: failed to found account in database, accountID: " + accountIdStr);
    }
}
}