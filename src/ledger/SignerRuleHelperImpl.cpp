#include <lib/xdrpp/xdrpp/marshal.h>
#include <lib/util/basen.h>
#include "SignerRuleHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"
#include "database/Database.h"

namespace stellar
{

using namespace soci;

SignerRuleHelperImpl::SignerRuleHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
    mSignerRuleColumnSelector = "SELECT id, resource, action, owner_id, "
                                "       forbids, is_default, details, "
                                "       version, lastmodified "
                                " FROM  signer_rules";
}

void
SignerRuleHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS signer_rules";
    db.getSession() << "CREATE TABLE signer_rules"
                       "("
                       "id              BIGINT         NOT NULL,"
                       "resource        TEXT           NOT NULL, "
                       "action          INT            NOT NULL,"
                       "owner_id        VARCHAR(56)    NOT NULL,"
                       "forbids         BOOLEAN        NOT NULL,"
                       "is_default      BOOLEAN        NOT NULL,"
                       "details         TEXT           NOT NULL DEFAULT '{}',"
                       "version         INT            NOT NULL DEFAULT 0,"
                       "lastmodified    INT            NOT NULL DEFAULT 0,"
                       "PRIMARY KEY (id)"
                       ");";
}

void
SignerRuleHelperImpl::storeUpdate(LedgerEntry const &entry, bool insert)
{
    auto signerRuleFrame = std::make_shared<SignerRuleFrame>(entry);
    auto signerRuleEntry = signerRuleFrame->getEntry();

    signerRuleFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = signerRuleFrame->getKey();
    flushCachedEntry(key);

    auto resourceBody = xdr::xdr_to_opaque(signerRuleFrame->getResource());
    std::string strResource = bn::encode_b64(resourceBody);
    std::string ownerID = PubKeyUtils::toStrKey(signerRuleEntry.ownerID);
    int isForbid = signerRuleFrame->forbids() ? 1 : 0;
    int isDefault = signerRuleFrame->isDefault() ? 1 : 0;
    auto version = static_cast<int32_t>(signerRuleEntry.ext.v());
    auto const action = static_cast<int32_t>(signerRuleEntry.action);

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO signer_rules "
              "(id, resource, action, owner_id, forbids, is_default, "
              " details, version, lastmodified) "
              "VALUES (:id, :res, :act, :own, :is_f, :is_d, :det, :v, :lm)";
    }
    else
    {
        sql = "UPDATE signer_rules SET resource = :res, action = :act, "
              " owner_id = :own, forbids = :is_f, is_default = :is_d, "
              " details = :det, version = :v, lastmodified = :lm "
              "WHERE id = :id";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(signerRuleEntry.id, "id"));
    st.exchange(use(strResource, "res"));
    st.exchange(use(action, "act"));
    st.exchange(use(ownerID, "own"));
    st.exchange(use(isForbid, "is_f"));
    st.exchange(use(isDefault, "is_d"));
    st.exchange(use(signerRuleEntry.details, "det"));
    st.exchange(use(version, "v"));
    st.exchange(use(signerRuleFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-signer")
                        : db.getUpdateTimer("update-signer");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*signerRuleFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*signerRuleFrame);
    }
}

void
SignerRuleHelperImpl::storeAdd(LedgerEntry const &entry)
{
    storeUpdate(entry, true);
}

void
SignerRuleHelperImpl::storeChange(LedgerEntry const &entry)
{
    storeUpdate(entry, false);
}

std::vector<SignerRuleFrame::pointer>
SignerRuleHelperImpl::loadSignerRules(std::vector<uint64_t> const ruleIDs)
{
    std::string sql = mSignerRuleColumnSelector;
    sql += " WHERE id IN (" + obtainSqlIDsString(ruleIDs) + ")";

    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    auto timer = getDatabase().getSelectTimer("signer_rules");

    std::vector<SignerRuleFrame::pointer> result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result.emplace_back(std::make_shared<SignerRuleFrame>(entry));
    });

    return result;
}

void
SignerRuleHelperImpl::storeDelete(LedgerKey const &key)
{
    uint64_t id = key.signerRule().id;

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM signer_rules "
                                        " WHERE id = :id");
    auto& st = prep.statement();
    st.exchange(use(id));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("signer_rule");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }

    flushCachedEntry(key);

    if (mStorageHelper.getLedgerDelta() != nullptr)
    {
        mStorageHelper.mustGetLedgerDelta().deleteEntry(key);
    }
}

bool
SignerRuleHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.signerRule().id);
}

bool
SignerRuleHelperImpl::exists(uint64_t const ruleID)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("signer-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM signer_rules WHERE id = :v1)");
        auto& st = prep.statement();
        st.exchange(use(ruleID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

LedgerKey
SignerRuleHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey(from.data.type());
    ledgerKey.signerRule().id = from.data.signerRule().id;

    return ledgerKey;
}

EntryFrame::pointer
SignerRuleHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadSignerRule(key.signerRule().id);
}

EntryFrame::pointer
SignerRuleHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<SignerRuleFrame>(from);
}

uint64_t
SignerRuleHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM signer_rules;", into(count);

    return count;
}

SignerRuleFrame::pointer
SignerRuleHelperImpl::loadSignerRule(uint64_t  const ruleID)
{
    LedgerKey key(LedgerEntryType::SIGNER_RULE);
    key.signerRule().id = ruleID;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<SignerRuleFrame>(*p) : nullptr;
    }

    Database& db = getDatabase();
    std::string sql = mSignerRuleColumnSelector;
    sql += " WHERE id = :id";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(ruleID, "id"));

    SignerRuleFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
    result = std::make_shared<SignerRuleFrame>(entry);
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
SignerRuleHelperImpl::load(StatementContext& prep,
                           std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::SIGNER_RULE);
        auto& signerRule = le.data.signerRule();

        std::string accountIDStr;
        std::string resource;
        int32_t isForbid;
        int32_t isDefault;
        int32_t version;
        int32_t action;

        auto& st = prep.statement();
        st.exchange(into(signerRule.id));
        st.exchange(into(resource));
        st.exchange(into(action));
        st.exchange(into(accountIDStr));
        st.exchange(into(isForbid));
        st.exchange(into(isDefault));
        st.exchange(into(signerRule.details));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            std::vector<uint8_t> decoded;
            bn::decode_b64(resource, decoded);
            xdr::xdr_get unmarshaler(&decoded.front(), &decoded.back() + 1);
            xdr::xdr_argpack_archive(unmarshaler, signerRule.resource);
            unmarshaler.done();

            signerRule.ownerID = PubKeyUtils::fromStrKey(accountIDStr);
            signerRule.forbids = isForbid > 0;
            signerRule.isDefault = isDefault > 0;
            signerRule.action = static_cast<SignerRuleAction>(action);
            signerRule.ext.v(static_cast<LedgerVersion>(version));

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load signer rule"));
    }
}

std::vector<uint64_t>
SignerRuleHelperImpl::loadDefaultRuleIDs()
{
    std::string sql = "SELECT id from signer_rules WHERE is_default ";

    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    auto timer = getDatabase().getSelectTimer("signer_rules");

    std::vector<uint64_t> result;
    uint64_t id;

    st.exchange(into(id));
    st.define_and_bind();
    st.execute(true);

    while (st.got_data())
    {
        result.emplace_back(id);

        st.fetch();
    }

    return result;
}

Database&
SignerRuleHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

LedgerDelta*
SignerRuleHelperImpl::getLedgerDelta()
{
    return mStorageHelper.getLedgerDelta();
}

std::string
const SignerRuleHelperImpl::getTableName() const
{
    return "signer_rules";
}
}
