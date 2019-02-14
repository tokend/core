#include "AccountRoleHelperImpl.h"
#include "LedgerDelta.h"
#include "StorageHelper.h"
#include "database/Database.h"

using namespace soci;

namespace stellar
{
using xdr::operator<;

void
AccountRoleHelperImpl::dropAll()
{
    Database& db = mStorageHelper.getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS account_roles;";
    db.getSession() << "CREATE TABLE account_roles "
           "("
           "id                 BIGINT      NOT NULL CHECK (id >= 0), "
           "details            TEXT        NOT NULL, "
           "lastmodified       INT         NOT NULL, "
           "version            INT         NOT NULL DEFAULT 0, "
           "PRIMARY KEY (id)"
           ");";

    mAccountRoleRulesHelper.dropAll();
}

AccountRoleHelperImpl::AccountRoleHelperImpl(StorageHelper& storageHelper)
    : mStorageHelper(storageHelper), mAccountRoleRulesHelper(storageHelper)
{
    mAccountRoleSelector = "SELECT id, details, lastmodified, version "
                           "FROM   account_roles ";
}

void
AccountRoleHelperImpl::storeUpdate(LedgerEntry const& entry, bool insert)
{
    auto accountRoleFrame = std::make_shared<AccountRoleFrame>(entry);
    auto& accountRoleEntry = accountRoleFrame->getAccountRole();

    if (mStorageHelper.getLedgerDelta())
    {
        accountRoleFrame->touch(*mStorageHelper.getLedgerDelta());
    }

    LedgerKey const& key = accountRoleFrame->getKey();
    flushCachedEntry(key);
    accountRoleFrame->ensureValid();

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO account_roles (id, details, lastmodified, version) "
              "VALUES (:id, :det, :lm, :v)";
    }
    else
    {
        sql = "UPDATE account_roles "
              "SET id = :id, details = :det,"
              "lastmodified = :lm, version = :v "
              "WHERE id = :id";
    }

    auto prep = mStorageHelper.getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();

    uint64_t accountRoleID = accountRoleFrame->getID();
    auto version = static_cast<int32_t>(accountRoleEntry.ext.v());

    st.exchange(use(accountRoleID, "id"));
    st.exchange(use(accountRoleEntry.details, "det"));
    st.exchange(use(accountRoleFrame->mEntry.lastModifiedLedgerSeq, "lm"));
    st.exchange(use(version, "v"));
    st.define_and_bind();

    auto timer = insert ? getDatabase().getInsertTimer("account-role")
                        : getDatabase().getUpdateTimer("account-role");
    st.execute(true);

    if (st.get_affected_rows() != 1)
        throw std::runtime_error("could not update SQL");

    sort(accountRoleEntry.ruleIDs.begin(), accountRoleEntry.ruleIDs.end());
    mAccountRoleRulesHelper.storeUpdate(accountRoleID, accountRoleEntry.ruleIDs, insert);

    if (mStorageHelper.getLedgerDelta())
    {
        if (insert)
            mStorageHelper.getLedgerDelta()->addEntry(*accountRoleFrame);
        else
            mStorageHelper.getLedgerDelta()->modEntry(*accountRoleFrame);
    }
}

void
AccountRoleHelperImpl::storeAdd(LedgerEntry const& entry)
{
    storeUpdate(entry, true);
}

void
AccountRoleHelperImpl::storeChange(LedgerEntry const& entry)
{
    storeUpdate(entry, false);
}

void
AccountRoleHelperImpl::storeDelete(LedgerKey const& key)
{
    Database& db = mStorageHelper.getDatabase();

    auto timer = db.getDeleteTimer("account-role");
    auto prep = db.getPreparedStatement(
        "DELETE FROM account_roles WHERE id = :id");
    auto& st = prep.statement();
    auto accountRoleID = key.accountRole().id;
    st.exchange(use(accountRoleID, "id"));
    st.define_and_bind();
    st.execute(true);

    flushCachedEntry(key);

    mAccountRoleRulesHelper.storeDelete(accountRoleID);

    if (mStorageHelper.getLedgerDelta())
    {
        mStorageHelper.getLedgerDelta()->deleteEntry(key);
    }
}

bool
AccountRoleHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key))
    {
        return true;
    }

    Database& db = mStorageHelper.getDatabase();

    int exists = 0;
    auto timer = db.getSelectTimer("account-role-exists");
    auto prep = db.getPreparedStatement(
        "SELECT EXISTS (SELECT NULL FROM account_roles WHERE "
        "id = :id)");
    auto& st = prep.statement();
    uint64 accountRoleID = key.accountRole().id;
    st.exchange(use(accountRoleID, "id"));
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

LedgerKey
stellar::AccountRoleHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    if (from.data.type() != LedgerEntryType::ACCOUNT_ROLE)
    {
        throw std::runtime_error("Not an account role entry.");
    }

    LedgerKey ledgerKey;
    ledgerKey.type(LedgerEntryType::ACCOUNT_ROLE);
    ledgerKey.accountRole().id = from.data.accountRole().id;
    return ledgerKey;
}

AccountRoleFrame::pointer
AccountRoleHelperImpl::loadAccountRole(uint64_t const roleID)
{
    std::string sql = mAccountRoleSelector;
    sql += " WHERE id = :id";
    auto prep = mStorageHelper.getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();

    st.exchange(use(roleID, "id"));

    AccountRoleFrame::pointer result;
    auto timer = getDatabase().getSelectTimer("select_account_role");
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<AccountRoleFrame>(entry);
    });

    LedgerKey key(LedgerEntryType::ACCOUNT_ROLE);
    key.accountRole().id = roleID;

    if (!result)
    {
        putCachedEntry(key, nullptr);
        return nullptr;
    }

    if (mStorageHelper.getLedgerDelta())
    {
        mStorageHelper.getLedgerDelta()->recordEntry(*result);
    }

    auto pEntry = std::make_shared<LedgerEntry>(result->mEntry);
    putCachedEntry(key, pEntry);
    return result;
}

void
AccountRoleHelperImpl::load(StatementContext &prep,
                            std::function<void(LedgerEntry const &)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::ACCOUNT_ROLE);
        auto& accountRoleEntry = le.data.accountRole();

        int32_t version;

        auto& st = prep.statement();
        st.exchange(into(accountRoleEntry.id));
        st.exchange(into(accountRoleEntry.details));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.exchange(into(version));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            auto ruleIDs = mAccountRoleRulesHelper.loadRuleIDs(accountRoleEntry.id);
            sort(ruleIDs.begin(), ruleIDs.end());
            accountRoleEntry.ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());

            accountRoleEntry.ext.v(static_cast<LedgerVersion>(version));

            processor(le);
            st.fetch();
        }
    }
    catch (...)
    {
        std::throw_with_nested(std::runtime_error("Failed to load account role"));
    }
}


EntryFrame::pointer
AccountRoleHelperImpl::storeLoad(LedgerKey const& key)
{
    auto const& accountRoleID = key.accountRole().id;
    return loadAccountRole(accountRoleID);
}

Database&
AccountRoleHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

EntryFrame::pointer
AccountRoleHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AccountRoleFrame>(from);
}

uint64_t
AccountRoleHelperImpl::countObjects()
{
    uint64_t count = 0;
    getDatabase().getSession() << "SELECT COUNT(*) FROM account_roles;",
        into(count);

    return count;
}

std::vector<uint64_t>
AccountRoleHelperImpl::loadRoleIDsByRule(uint64_t const ruleID)
{
    return  mAccountRoleRulesHelper.loadRolesByRule(ruleID);
}
} // namespace stellar