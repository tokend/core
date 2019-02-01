#include "SignerRoleHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"

namespace stellar
{

using namespace soci;

SignerRoleHelperImpl::SignerRoleHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
    mSignerRoleColumnSelector = "SELECT     ";
}

void
SignerRoleHelperImpl::dropAll()
{
    Database& db = getDatabase();

    db.getSession() << "DROP TABLE IF EXISTS signers";
    db.getSession() << "CREATE TABLE signers"
                       "("
                       "account_id      VARCHAR(56)    NOT NULL,"
                       "public_key      VARCHAR(56)    NOT NULL,"
                       "weight          INT            NOT NULL,"
                       "role_id         BIGINT         NOT NULL,"
                       "identity        INT            NOT NULL,"
                       "details         VARCHAR(256)   NOT NULL DEFAULT '{}',"
                       "version         INT            NOT NULL DEFAULT 0,"
                       "lastmodified    INT            NOT NULL DEFAULT 0,"
                       "PRIMARY KEY (public_key)"
                       ");";
    db.getSession() << "CREATE INDEX account_signers ON signers (account_id)";
}

void
SignerRoleHelperImpl::storeUpdate(LedgerEntry const &entry, bool insert)
{
    auto signerFrame = std::make_shared<SignerRoleFrame>(entry);
    auto signerEntry = signerFrame->getEntry();


    auto version = static_cast<int32_t>(signerEntry.ext.v());

    std::string sql;
    if (insert)
    {
        sql = "INSERT INTO signers (account_id, public_key, weight, role_id,"
              "                     identity, details, version, lastmodified) "
              "VALUES (:acc, :pub, :w, :r, :ide, :det, :v, :lm)";
    }
    else
    {
        sql = "UPDATE signers SET account_id = :acc, public_key = :pub, "
              " weight = :w, role_id = :r, identity = :ide, details = :det, "
              " version = :v, lastmodified = :lm "
              "WHERE public_key = :pub";
    }

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();


/*    st.exchange(use(signerEntry.weight, "w"));
    st.exchange(use(signerEntry.roleID, "r"));
    st.exchange(use(signerEntry.identity, "ide"));*/
    st.exchange(use(signerEntry.details, "det"));
    st.exchange(use(version, "v"));
    st.exchange(use(signerFrame->mEntry.lastModifiedLedgerSeq, "lm"));

    st.define_and_bind();

    auto timer = insert ? db.getInsertTimer("insert-signer")
                        : db.getUpdateTimer("update-signer");

    st.execute(true);

    if (st.get_affected_rows() != 1) {
        throw std::runtime_error("could not update SQL");
    }

    if (insert)
    {
        mStorageHelper.mustGetLedgerDelta().addEntry(*signerFrame);
    }
    else
    {
        mStorageHelper.mustGetLedgerDelta().modEntry(*signerFrame);
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

    std::string sql = mSignerRoleColumnSelector;
    sql += " WHERE account_id = :id";

    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(roleID, "id"));

    std::vector<SignerRoleFrame::pointer> result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result.emplace_back(std::make_shared<SignerRoleFrame>(entry));
    });

    return result[0];
}

void
SignerRoleHelperImpl::storeDelete(LedgerKey const &key)
{
    auto pubKey = key.signer().pubKey;
    std::string signerStrKey = PubKeyUtils::toStrKey(pubKey);

    Database& db = getDatabase();
    auto prep = db.getPreparedStatement("DELETE FROM signers "
                                        "WHERE public_key = :pub");
    auto& st = prep.statement();
    st.exchange(use(signerStrKey));
    st.define_and_bind();
    {
        auto timer = db.getDeleteTimer("signer");
        st.execute(true);
    }

    if (st.get_affected_rows() != 1)
    {
        throw std::runtime_error("Could not update data in SQL");
    }
}

bool
SignerRoleHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.signer().pubKey);
}

bool
SignerRoleHelperImpl::exists(PublicKey const &rawPubKey)
{
    int exists = 0;
    {
        Database& db = getDatabase();
        auto timer = db.getSelectTimer("signer-exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL "
                                            "FROM signers WHERE public_key = :v1)");
        auto& st = prep.statement();
        auto accountID = PubKeyUtils::toStrKey(rawPubKey);
        st.exchange(use(accountID));
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
    ledgerKey.signer().pubKey = from.data.signer().pubKey;

    return ledgerKey;
}

EntryFrame::pointer
SignerRoleHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadSignerRole(0);
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
    sess << "SELECT COUNT(*) FROM signers;", into(count);

    return count;
}
/*

SignerRoleFrame::pointer
SignerRoleHelperImpl::loadSigner(PublicKey const &publicKey)
{
    LedgerKey key(LedgerEntryType::SIGNER);
    key.signer().pubKey = publicKey;

    if (cachedEntryExists(key))
    {
        auto p = getCachedEntry(key);
        return p ? std::make_shared<SignerFrame>(*p) : nullptr;
    }

    std::string actIDStrKey = PubKeyUtils::toStrKey(publicKey);

    Database& db = getDatabase();
    std::string sql = mSignerColumnSelector;
    sql += " WHERE public_key = :pub_k";

    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(actIDStrKey, "pub_k"));

    SignerFrame::pointer result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result = std::make_shared<SignerFrame>(entry);
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
*/

void
SignerRoleHelperImpl::load(StatementContext& prep,
                       std::function<void(LedgerEntry const&)> processor)
{
    try
    {
        LedgerEntry le;
        le.data.type(LedgerEntryType::SIGNER);
        auto& signerEntry = le.data.signer();

        std::string accountIDStr;
        std::string publicKeyStr;
        int32_t version;

        auto& st = prep.statement();
        st.exchange(into(accountIDStr));
        st.exchange(into(publicKeyStr));
        st.exchange(into(signerEntry.weight));
        st.exchange(into(signerEntry.roleID));
        st.exchange(into(signerEntry.identity));
        st.exchange(into(signerEntry.details));
        st.exchange(into(version));
        st.exchange(into(le.lastModifiedLedgerSeq));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            signerEntry.accountID = PubKeyUtils::fromStrKey(accountIDStr);
            signerEntry.pubKey = PubKeyUtils::fromStrKey(publicKeyStr);
            signerEntry.ext.v(static_cast<LedgerVersion>(version));

            processor(le);
            st.fetch();
        }
    }
    catch (std::exception& e)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << e.what();
        std::throw_with_nested(std::runtime_error("Failed to load signer"));
    }
}

Database&
SignerRoleHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}
}
