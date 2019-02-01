#include "SignerRoleHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"

namespace stellar
{

using namespace soci;

SignerRoleHelperImpl::SignerRoleHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper), mSignerRoleRulesHelper(storageHelper)
{
    mSignerRoleColumnSelector = "SELECT id, owner_id, details, version, "
                                " lastmodified FROM signer_roles ";
}

void
SignerRoleHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS signer_roles";
    db.getSession() << "CREATE TABLE signer_roles"
                       "("
                       "id              BIGINT         NOT NULL,"
                       "owner_id        VARCHAR(56)    NOT NULL,"
                       "details         TEXT           NOT NULL DEFAULT '{}',"
                       "version         INT            NOT NULL DEFAULT 0,"
                       "lastmodified    INT            NOT NULL DEFAULT 0,"
                       "PRIMARY KEY (id)"
                       ");";

    mSignerRoleRulesHelper.dropAll();
}

void
SignerRoleHelperImpl::storeUpdate(LedgerEntry const &entry, bool insert)
{
    auto signerRoleFrame = std::make_shared<SignerRoleFrame>(entry);
    auto signerRoleEntry = signerRoleFrame->getEntry();

    signerRoleFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = signerRoleFrame->getKey();
    flushCachedEntry(key);

    std::string accountIDStr = PubKeyUtils::toStrKey(signerRoleEntry.ownerID);
    auto version = static_cast<int32_t>(signerRoleEntry.ext.v());

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO signer_roles (id, owner_id, details, version, "
              "                          lastmodified) "
              "VALUES (:id, :own, :det, :v, :lm)";
    }
    else
    {
        sql = "UPDATE signer_roles SET owner_id = :own, "
              "details = :det, version = :v, lastmodified = :lm "
              "WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(signerRoleEntry.id, "id"));
    st.exchange(use(accountIDStr, "own"));
    st.exchange(use(signerRoleEntry.details, "det"));
    st.exchange(use(version, "v"));
    st.exchange(use(signerRoleFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-signer-role")
                        : db.getUpdateTimer("update-signer-role");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    std::sort(signerRoleEntry.ruleIDs.begin(), signerRoleEntry.ruleIDs.end());
    mSignerRoleRulesHelper.storeUpdate(signerRoleEntry.id, signerRoleEntry.ruleIDs, insert);

    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*signerRoleFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*signerRoleFrame);
    }
}

void
SignerRoleHelperImpl::storeAdd(LedgerEntry const &entry)
{
    storeUpdate(entry, true);
}

void
SignerRoleHelperImpl::storeChange(LedgerEntry const &entry)
{
    storeUpdate(entry, false);
}

SignerRoleFrame::pointer
SignerRoleHelperImpl::loadSignerRole(uint64_t const roleID)
{
    LedgerKey key(LedgerEntryType::SIGNER_ROLE);
    key.signerRole().id = roleID;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<SignerRoleFrame>(*p) : nullptr;
    }

    std::string sql = mSignerRoleColumnSelector;
    sql += " WHERE id = :id";

    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(roleID, "id"));

    SignerRoleFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<SignerRoleFrame>(entry);
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
SignerRoleHelperImpl::storeDelete(LedgerKey const &key)
{
    auto pubKey = key.signer().pubKey;
    std::string signerStrKey = PubKeyUtils::toStrKey(pubKey);

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM signer_roles "
                                        "WHERE id = :id");
    auto& st = prep.statement();
    st.exchange(use(signerStrKey));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("signer-role");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);
}

bool
SignerRoleHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.signerRole().id);
}

bool
SignerRoleHelperImpl::exists(uint64_t const roleID)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("signer-role-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM signer_roles WHERE id = :v1)");
        auto& st = prep.statement();
        st.exchange(use(roleID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

LedgerKey
SignerRoleHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey(from.data.type());
    ledgerKey.signerRole().id = from.data.signerRole().id;

    return ledgerKey;
}

EntryFrame::pointer
SignerRoleHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadSignerRole(key.signerRole().id);
}

EntryFrame::pointer
SignerRoleHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<SignerRoleFrame>(from);
}

uint64_t
SignerRoleHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM signer_roles;", into(count);

    return count;
}

void
SignerRoleHelperImpl::load(StatementContext& prep,
                       std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::SIGNER_ROLE);
        auto& signerRole = le.data.signerRole();

        std::string accountIDStr;
        int32_t version;

        auto& st = prep.statement();
        st.exchange(into(signerRole.id));
        st.exchange(into(accountIDStr));
        st.exchange(into(signerRole.details));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            signerRole.ownerID = PubKeyUtils::fromStrKey(accountIDStr);
            signerRole.ext.v(static_cast<LedgerVersion>(version));

            auto ruleIDs = mSignerRoleRulesHelper.loadRuleIDs(signerRole.id);
            sort(ruleIDs.begin(), ruleIDs.end());
            signerRole.ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load signer role"));
    }
}

Database&
SignerRoleHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}
}
