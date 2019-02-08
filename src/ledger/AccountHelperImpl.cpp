#include "AccountHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"

using namespace soci;

namespace stellar
{

AccountHelperImpl::AccountHelperImpl(StorageHelper& storageHelper)
        : mStorageHelper(storageHelper)
{
    mAccountColumnSelector = "SELECT account_id, referrer, sequential_id, "
                             "       role_id, version, lastmodified "
                             " FROM  accounts";
}

void
AccountHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS accounts;";
    db.getSession() << "CREATE TABLE accounts"
                       "("
                       "account_id          VARCHAR(56) NOT NULL PRIMARY KEY,"
                       "referrer            VARCHAR(56) DEFAULT NULL,"
                       "sequential_id       BIGINT      UNIQUE NOT NULL,"
                       "role_id             BIGINT      NOT NULL,"
                       "version             INT         NOT NULL    DEFAULT 0,"
                       "lastmodified        INT         NOT NULL"
                       ");";
}

void
AccountHelperImpl::storeUpdate(LedgerEntry const& entry, bool insert)
{
    auto accountFrame = std::make_shared<AccountFrame>(entry);
    auto accountEntry = accountFrame->getAccount();

    accountFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = accountFrame->getKey();
    flushCachedEntry(key);

    std::string actIDStrKey = PubKeyUtils::toStrKey(accountFrame->getID());
    int32_t newAccountVersion = static_cast<int32_t>(accountFrame->getAccount().ext.v());

    std::string referrerStr;
    indicator referrerInd = i_null;
    AccountID* referrer = accountFrame->getReferrer();
    if (referrer != nullptr)
    {
        referrerStr = PubKeyUtils::toStrKey(*referrer);
        referrerInd = i_ok;
    }


    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO accounts (account_id, referrer, sequential_id, "
              "                      role_id, version, lastmodified) "
              "VALUES (:id, :ref, :seq_id, :r_id, :v, :lm)";
    }
    else
    {
        sql = "UPDATE accounts SET referrer = :ref, sequential_id = :seq_id, "
              "       role_id = :r_id, version=:v,  lastmodified=:lm "
              " WHERE account_id=:id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);

    {
        soci::statement& st = prep.statement();
        st.exchange(use(actIDStrKey, "id"));
        st.exchange(use(referrerStr, referrerInd, "ref"));
        st.exchange(use(accountEntry.sequentialID, "seq_id"));
        st.exchange(use(accountEntry.roleID, "r_id"));
        st.exchange(use(newAccountVersion, "v"));
        st.exchange(use(accountFrame->mEntry.lastModifiedLedgerSeq, "lm"));

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
            mStorageHelper.mustGetLedgerDelta().addEntry(*accountFrame);
        }
        else
        {
            mStorageHelper.mustGetLedgerDelta().modEntry(*accountFrame);
        }
    }
}

void
AccountHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdate(entry, true);
}

void
AccountHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdate(entry, false);
}

void
AccountHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);

    std::string actIDStrKey = PubKeyUtils::toStrKey(key.account().accountID);

    {
        Database& db = getDatabase();
        auto timer = db.getDeleteTimer("account");
        auto prep = db.getPreparedStatement("DELETE FROM accounts "
                                            "WHERE       account_id=:v1");
        auto& st = prep.statement();
        st.exchange(soci::use(actIDStrKey));
        st.define_and_bind();
        st.execute(true);
    }

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

bool
AccountHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.account().accountID);
}

LedgerKey
AccountHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey(from.data.type());
    ledgerKey.account().accountID = from.data.account().accountID;

    return ledgerKey;
}

EntryFrame::pointer
AccountHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadAccount(key.account().accountID);
}

EntryFrame::pointer
AccountHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AccountFrame>(from);
}

uint64_t
AccountHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM accounts;", into(count);

    return count;
}

AccountFrame::pointer
AccountHelperImpl::mustLoadAccount(AccountID const& accountID)
{
    auto accountFrame = loadAccount(accountID);

    if (!accountFrame)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Expected account to exist: "
                                           << PubKeyUtils::toStrKey(accountID);
        throw std::runtime_error("Expected account to exist");
    }

    return accountFrame;
}

AccountFrame::pointer
AccountHelperImpl::loadAccount(AccountID const& accountID)
{
    LedgerKey key;
    key.type(LedgerEntryType::ACCOUNT);
    key.account().accountID = accountID;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<AccountFrame>(*p) : nullptr;
    }

    std::string actIDStrKey = PubKeyUtils::toStrKey(accountID);

    Database& db = getDatabase();
    std::string sql = mAccountColumnSelector;
    sql += " WHERE account_id = :acc_id";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(actIDStrKey, "acc_id"));

    AccountFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<AccountFrame>(entry);
    });

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);

    return result;
}

void
AccountHelperImpl::load(StatementContext &prep,
                        std::function<void(LedgerEntry const &)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::ACCOUNT);
        auto& accountEntry = le.data.account();

        std::string accountID;
        std::string referrer;
        indicator referrerInd = i_null;
        int32_t version;

        auto& st = prep.statement();
        st.exchange(into(accountID));
        st.exchange(into(referrer, referrerInd));
        st.exchange(into(accountEntry.sequentialID));
        st.exchange(into(accountEntry.roleID));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            accountEntry.accountID = PubKeyUtils::fromStrKey(accountID);
            accountEntry.ext.v(static_cast<LedgerVersion>(version));

            if (referrerInd == i_ok)
            {
                accountEntry.referrer.activate() = PubKeyUtils::fromStrKey(referrer);
            }

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load account"));
    }
}

bool
AccountHelperImpl::exists(AccountID const &rawAccountID)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("account-exists");
        auto prep =
                db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM accounts "
                                        "WHERE account_id=:v1)");
        auto& st = prep.statement();
        auto accountID = PubKeyUtils::toStrKey(rawAccountID);
        st.exchange(use(accountID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }
    return exists != 0;
}

bool
AccountHelperImpl::isRoleIDUsed(uint64_t roleID)
{
    int exists = 0;
    {
        Database& db = getDatabase();

        auto timer = db.getSelectTimer("account-role-used");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM accounts "
                                            "WHERE role_id = :v1)");
        auto& st = prep.statement();
        st.exchange(use(roleID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

Database&
AccountHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

}
