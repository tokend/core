#include <lib/xdrpp/xdrpp/marshal.h>
#include <util/Decoder.h>
#include "AccountSpecificRuleHelperImpl.h"
#include "StorageHelper.h"
#include "database/Database.h"
#include "LedgerDelta.h"

using namespace soci;

namespace stellar
{
AccountSpecificRuleHelperImpl::AccountSpecificRuleHelperImpl(StorageHelper& sh)
        : mStorageHelper(sh)
{
    mRuleColumnSelector = "SELECT id, ledger_key, account_id, forbids, "
                          "       version, lastmodified "
                          "FROM   account_specific_rules ";
}

void
AccountSpecificRuleHelperImpl::dropAll()
{
    Database& db = getDatabase();
    db.getSession() << "DROP TABLE IF EXISTS account_specific_rules;";
    db.getSession() << "CREATE TABLE account_specific_rules"
                       "("
                       "id           BIGINT      NOT NULL,"
                       "ledger_key   TEXT        NOT NULL,"
                       "account_id   VARCHAR(56), "
                       "forbids      BOOLEAN     NOT NULL,"
                       "version      INT         NOT NULL,"
                       "lastmodified INT         NOT NULL,"
                       "PRIMARY KEY (id),"
                       "UNIQUE (ledger_key, account_id)"
                       ")";
}

void
AccountSpecificRuleHelperImpl::storeUpdate(LedgerEntry const& le, bool insert)
{
    auto frame = std::make_shared<AccountSpecificRuleFrame>(le);
    auto const& entry = frame->getEntry();

    frame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = frame->getKey();
    flushCachedEntry(key);

    indicator accountInd = i_null;
    std::string accountID;
    if (entry.accountID)
    {
        accountID = PubKeyUtils::toStrKey(*entry.accountID);
        accountInd = i_ok;
    }

    auto version = static_cast<int32_t>(entry.ext.v());
    auto ledgerKeyBytes = xdr::xdr_to_opaque(entry.ledgerKey);
    std::string ledgerKeyStr = decoder::encode_b64(ledgerKeyBytes);
    const int forbids = entry.forbids ? 1 : 0;

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO account_specific_rules "
              "           (id, ledger_key, account_id, forbids, "
              "            version, lastmodified) "
              "VALUES (:id, :lk, :acc, :f, :v, :lm)";
    }
    else
    {
        sql = "UPDATE account_specific_rules SET ledger_key = :lk, "
              " account_id = :acc, forbids = :f, "
              " version = :v, lastmodified = :lm "
              "WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(entry.id, "id"));
    st.exchange(use(ledgerKeyStr, "lk"));
    st.exchange(use(accountID, accountInd, "acc"));
    st.exchange(use(forbids, "f"));
    st.exchange(use(version, "v"));
    st.exchange(use(frame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-acc-spec-rule")
                        : db.getUpdateTimer("update-acc-spec-rule");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*frame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*frame);
    }
}

void
AccountSpecificRuleHelperImpl::storeAdd(const LedgerEntry &entry)
{
    storeUpdate(entry, true);
}

void
AccountSpecificRuleHelperImpl::storeChange(const LedgerEntry &entry)
{
    storeUpdate(entry, false);
}

void
AccountSpecificRuleHelperImpl::storeDelete(const LedgerKey &key)
{
    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM account_specific_rules "
                                        "WHERE id = :id ");
    auto& st = prep.statement();
    const uint64_t id = key.accountSpecificRule().id;
    st.exchange(use(id, "id"));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("account_specific_rules");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);

    mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
}

void
AccountSpecificRuleHelperImpl::deleteRulesForEntry(LedgerKey const& saleKey)
{
    auto ledgerKeyBytes = xdr::xdr_to_opaque(saleKey);
    std::string ledgerKeyStr = decoder::encode_b64(ledgerKeyBytes);

    Database& db = getDatabase();
    std::string sql = "DELETE from account_specific_rules WHERE ledger_key = :lk returning id";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    uint64_t ruleID;
    st.exchange(into(ruleID));
    st.exchange(use(ledgerKeyStr, "lk"));
    st.define_and_bind();
    st.execute(true);

    LedgerDelta& delta = mStorageHelper.mustGetLedgerDelta();

    while (st.got_data())
    {
        LedgerKey key(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);
        key.accountSpecificRule().id = ruleID;

        flushCachedEntry(key);
        delta.deleteEntry(key);

        st.fetch();
    }
}

bool AccountSpecificRuleHelperImpl::exists(uint64_t const id)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("account_specific_rules-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM account_specific_rules "
                                            "WHERE id = :id)");
        auto& st = prep.statement();
        st.exchange(use(id, "id"));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

bool
AccountSpecificRuleHelperImpl::exists(const LedgerKey &key)
{
    return exists(key.accountSpecificRule().id);
}

void
AccountSpecificRuleHelperImpl::load(StatementContext &prep,
        std::function<void(const LedgerEntry &)> processor)
{
    try
    {
        LedgerEntry le(0, LedgerEntryType::ACCOUNT_SPECIFIC_RULE, LedgerVersion::EMPTY_VERSION);
        auto& entry = le.data.accountSpecificRule();

        std::string accountID, ledgerKey;
        indicator accountInd;
        int32_t version;
        int forbids;

        auto& st = prep.statement();
        st.exchange(into(entry.id));
        st.exchange(into(ledgerKey));
        st.exchange(into(accountID, accountInd));
        st.exchange(into(forbids));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            // unmarshal ledgerKey
            std::vector<uint8_t> decoded;
            decoder::decode_b64(ledgerKey, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, entry.ledgerKey);
            unmarshaler.done();

            entry.ext.v(static_cast<LedgerVersion>(version));
            entry.forbids = forbids > 0;

            if (accountInd == i_ok)
            {
                entry.accountID.activate() = PubKeyUtils::fromStrKey(accountID);
            }

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load account specific rule"));
    }
}

AccountSpecificRuleFrame::pointer
AccountSpecificRuleHelperImpl::loadRule(uint64_t const id)
{
    Database& db = getDatabase();
    std::string sql(mRuleColumnSelector);
    sql += " WHERE id = :id ";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(id, "id"));

    AccountSpecificRuleFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<AccountSpecificRuleFrame>(entry);
    });

    if (!result)
    {
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    return result;
}

AccountSpecificRuleFrame::pointer
AccountSpecificRuleHelperImpl::loadRule(const LedgerKey &ledgerKey, AccountID const* accountID)
{
    std::string whereCondition = " WHERE ledger_key = :key AND "
                                 "(account_id = :acc_id OR "
                                 "(:acc_id::text is null and account_id is null))";

    return loadRule(ledgerKey, accountID, whereCondition);
}

AccountSpecificRuleFrame::pointer
AccountSpecificRuleHelperImpl::loadRule(const LedgerKey &ledgerKey, AccountID const& accountID)
{
    std::string whereCondition = " WHERE ledger_key = :key AND "
                                 "(account_id = :acc_id OR account_id is null) "
                                 " order by account_id = :acc_id limit 1";

    return loadRule(ledgerKey, &accountID, whereCondition);
}

AccountSpecificRuleFrame::pointer
AccountSpecificRuleHelperImpl::loadRule(const LedgerKey &ledgerKey,
        AccountID const* accountID, std::string const& whereCondition)
{
    Database& db = getDatabase();
    std::string sql = std::string(mRuleColumnSelector) + whereCondition;

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();

    auto ledgerKeyBytes = xdr::xdr_to_opaque(ledgerKey);
    std::string ledgerKeyStr = decoder::encode_b64(ledgerKeyBytes);

    std::string accountIDStr;
    indicator accountIDIndicator = i_null;
    if (accountID != nullptr)
    {
        accountIDStr = PubKeyUtils::toStrKey(*accountID);
        accountIDIndicator = i_ok;
    }

    st.exchange(use(ledgerKeyStr, "key"));
    st.exchange(use(accountIDStr, accountIDIndicator, "acc_id"));

    AccountSpecificRuleFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<AccountSpecificRuleFrame>(entry);
    });

    if (!result)
    {
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().recordEntry(*result);
    }

    return result;
}

EntryFrame::pointer
AccountSpecificRuleHelperImpl::storeLoad(const LedgerKey &key)
{
    return loadRule(key.accountSpecificRule().id);
}

AccountSpecificRuleFrame::pointer
AccountSpecificRuleHelperImpl::mustLoadRule(uint64_t const id)
{
    auto rule = loadRule(id);

    if (!rule)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to load account specific rule from db, by id: "
                                           << id;
        throw std::runtime_error("Expected account specific rule to exists in db");
    }

    return rule;
}

uint64_t
AccountSpecificRuleHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM account_specific_rules;", into(count);

    return count;
}

LedgerKey
AccountSpecificRuleHelperImpl::getLedgerKey(const LedgerEntry &entry)
{
    return AccountSpecificRuleFrame(entry).getKey();
}

EntryFrame::pointer
AccountSpecificRuleHelperImpl::fromXDR(const LedgerEntry &entry)
{
    return std::make_shared<AccountSpecificRuleFrame>(entry);
}

Database&
AccountSpecificRuleHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
AccountSpecificRuleHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}

}