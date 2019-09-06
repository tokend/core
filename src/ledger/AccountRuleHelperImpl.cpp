#include "AccountRuleHelperImpl.h"
#include "LedgerDelta.h"
#include <xdrpp/marshal.h>
#include "util/basen.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar
{

using xdr::operator<;

void
AccountRuleHelperImpl::dropAll()
{
    mDb.getSession() << "DROP TABLE IF EXISTS account_rules;";
    mDb.getSession() << "CREATE TABLE account_rules"
           "("
           "id              BIGINT          NOT NULL CHECK (id > 0),"
           "resource        TEXT            NOT NULL,"
           "action          INT             NOT NULL,"
           "forbids         BOOLEAN         NOT NULL,"
           "details         TEXT            NOT NULL,"
           "lastmodified    INT             NOT NULL,"
           "version         INT             NOT NULL,"
           "PRIMARY KEY(id) "
           ");";
}

AccountRuleHelperImpl::AccountRuleHelperImpl(
    StorageHelper& storageHelper)
    : mDb(storageHelper.getDatabase())
    , mLedgerDelta(storageHelper.getLedgerDelta())
{
    mAccountRuleSelector = "SELECT id, resource, action, forbids, details, "
                           "       lastmodified, version "
                           "FROM   account_rules ";
}

void
AccountRuleHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdate(entry, true);
}

void
AccountRuleHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdate(entry, false);
}

void
AccountRuleHelperImpl::storeDelete(LedgerKey const& key)
{
    flushCachedEntry(key);

    auto timer = mDb.getDeleteTimer("account_role_permission");
    auto prep = mDb.getPreparedStatement(
        "DELETE FROM account_rules WHERE id=:id");
    auto& st = prep.statement();

    st.exchange(use(key.accountRule().id));
    st.define_and_bind();
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);

    if (mLedgerDelta)
    {
        mLedgerDelta->deleteEntry(key);
    }
}

void
AccountRuleHelperImpl::storeUpdate(LedgerEntry const& entry, bool insert)
{
    const auto accountRuleFrame = make_shared<AccountRuleFrame>(entry);
    const auto accountRuleEntry = accountRuleFrame->getRuleEntry();

    accountRuleFrame->ensureValid();
    if (mLedgerDelta)
    {
        accountRuleFrame->touch(*mLedgerDelta);
    }

    LedgerKey const& key = getLedgerKey(entry);
    flushCachedEntry(key);

    auto resourceBody = xdr::xdr_to_opaque(accountRuleFrame->getResource());
    std::string strResource = bn::encode_b64(resourceBody);
    int isForbid = accountRuleFrame->forbids() ? 1 : 0;
    const auto version = static_cast<int32_t>(accountRuleEntry.ext.v());
    const auto action = static_cast<int32_t>(accountRuleEntry.action);

    std::string sql;

    if (insert)
    {
        sql = std::string("INSERT INTO account_rules (id, resource, action, "
                          "forbids, details, lastmodified, version) "
                          "VALUES (:id, :res, :act, :is_f, :det, :lm, :v)");
    }
    else
    {
        sql = std::string("UPDATE account_rules "
                          "SET    resource=:res, action=:act, "
                          "       forbids=:is_f, details=:det, "
                          "       lastmodified=:lm, version=:v "
                          "WHERE  id=:id");
    }

    auto prep = mDb.getPreparedStatement(sql);

    soci::statement& st = prep.statement();
    st.exchange(use(accountRuleEntry.id, "id"));
    st.exchange(use(strResource, "res"));
    st.exchange(use(action, "act"));
    st.exchange(use(isForbid, "is_f"));
    st.exchange(use(accountRuleEntry.details, "det"));
    st.exchange(use(accountRuleFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(version, "v"));

    st.define_and_bind();

    auto timer = insert ? mDb.getInsertTimer("account_role_permission")
                        : mDb.getUpdateTimer("account_role_permission");
    st.execute(true);

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update Ledger");
    }

    if (mLedgerDelta)
    {
        if (insert)
        {
            mLedgerDelta->addEntry(*accountRuleFrame);
        }
        else
        {
            mLedgerDelta->modEntry(*accountRuleFrame);
        }
    }
}

bool
AccountRuleHelperImpl::exists(LedgerKey const& key)
{
    int exists = 0;
    auto timer = mDb.getSelectTimer("account_role_permission_exists");
    auto prep = mDb.getPreparedStatement(
        "SELECT EXISTS (SELECT NULL FROM account_rules "
        "WHERE id=:id)");
    auto& st = prep.statement();

    st.exchange(use(key.accountRule().id));
    st.exchange(into(exists));

    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

LedgerKey
AccountRuleHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    if (from.data.type() != LedgerEntryType::ACCOUNT_RULE)
    {
        throw std::runtime_error("Not a role permission entry.");
    }

    LedgerKey ledgerKey;
    ledgerKey.type(LedgerEntryType::ACCOUNT_RULE);
    ledgerKey.accountRule().id = from.data.accountRule().id;
    return ledgerKey;
}

EntryFrame::pointer
AccountRuleHelperImpl::fromXDR(LedgerEntry const& from)
{
    return make_shared<AccountRuleFrame>(from);
}

EntryFrame::pointer
AccountRuleHelperImpl::storeLoad(LedgerKey const& key)
{
    if (key.type() != LedgerEntryType::ACCOUNT_RULE)
    {
        throw std::runtime_error("Not a role permission entry.");
    }

    if (cachedEntryExists(key))
    {
        auto cachedEntry = getCachedEntry(key);
        return cachedEntry ? std::make_shared<AccountRuleFrame>(*cachedEntry)
                           : nullptr;
    }

    std::string sql = mAccountRuleSelector;
    sql += "WHERE id =:id";
    auto prep = mDb.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(key.accountRule().id));

    AccountRuleFrame::pointer result;
    auto timer = mDb.getSelectTimer("select_account_rule");
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = make_shared<AccountRuleFrame>(entry);
    });

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mLedgerDelta)
    {
        mLedgerDelta->recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);
    return result;
}

std::vector<AccountRuleFrame::pointer>
AccountRuleHelperImpl::loadAccountRules(std::vector<uint64_t> const ruleIDs)
{
    if (ruleIDs.empty())
    {
        return {};
    }

    std::string sql = mAccountRuleSelector;

    sql += " WHERE id IN (" + obtainSqlIDsString(ruleIDs) + ")";

    auto prep = mDb.getPreparedStatement(sql);
    auto timer = mDb.getSelectTimer("select_account_rules");

    std::vector<AccountRuleFrame::pointer> result;
    result.reserve(ruleIDs.size());
    load(prep, [&result](LedgerEntry const& entry)
    {
        result.emplace_back(make_shared<AccountRuleFrame>(entry));
    });

    return result;
}

void
AccountRuleHelperImpl::load(StatementContext &prep,
                            function<void(LedgerEntry const &)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::ACCOUNT_RULE);
        auto& accountRuleEntry = le.data.accountRule();

        string strResource;
        int32_t isForbid;
        int32_t version;
        int32_t action;

        auto& st = prep.statement();
        st.exchange(into(accountRuleEntry.id));
        st.exchange(into(strResource));
        st.exchange(into(action));
        st.exchange(into(isForbid));
        st.exchange(into(accountRuleEntry.details));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.exchange(into(version));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            std::vector<uint8_t> decoded;
            bn::decode_b64(strResource, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, accountRuleEntry.resource);
            unmarshaler.done();

            accountRuleEntry.forbids = isForbid > 0;
            accountRuleEntry.action = static_cast<AccountRuleAction>(action);
            accountRuleEntry.ext.v(static_cast<LedgerVersion>(version));

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        throw_with_nested(runtime_error("Failed to load account rule"));
    }
}

uint64_t
AccountRuleHelperImpl::countObjects()
{
    auto timer = mDb.getSelectTimer("account_role_permission_count");
    auto prep = mDb.getPreparedStatement("SELECT COUNT(*) FROM account_rules");
    auto& st = prep.statement();

    uint64_t count;
    st.exchange(into(count));
    st.define_and_bind();
    st.execute(true);

    return count;
}

Database&
AccountRuleHelperImpl::getDatabase()
{
    return mDb;
}

LedgerDelta*
AccountRuleHelperImpl::getLedgerDelta()
{
    return mLedgerDelta;
}
} // namespace stellar