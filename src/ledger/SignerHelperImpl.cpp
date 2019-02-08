#include "SignerHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"
#include "database/Database.h"

using namespace soci;

namespace stellar
{

SignerHelperImpl::SignerHelperImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
    mSignerColumnSelector = "SELECT account_id, public_key, weight, role_id, "
                            "identity, details, version, lastmodified "
                            "FROM signers ";
}

void
SignerHelperImpl::dropAll()
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
                       "details         TEXT           NOT NULL DEFAULT '{}',"
                       "version         INT            NOT NULL DEFAULT 0,"
                       "lastmodified    INT            NOT NULL DEFAULT 0,"
                       "PRIMARY KEY (public_key)"
                       ");";
    db.getSession() << "CREATE INDEX account_signers ON signers (account_id)";
}

void
SignerHelperImpl::storeUpdate(LedgerEntry const &entry, bool insert)
{
    auto signerFrame = std::make_shared<SignerFrame>(entry);
    auto signerEntry = signerFrame->getEntry();

    signerFrame->touch(mStorageHelper.mustGetLedgerDelta());

    LedgerKey const& key = signerFrame->getKey();
    flushCachedEntry(key);

    std::string accountIDStr = PubKeyUtils::toStrKey(signerEntry.accountID);
    std::string pubKeyStr = PubKeyUtils::toStrKey(signerEntry.pubKey);
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

    st.exchange(use(accountIDStr, "acc"));
    st.exchange(use(pubKeyStr, "pub"));
    st.exchange(use(signerEntry.weight, "w"));
    st.exchange(use(signerEntry.roleID, "r"));
    st.exchange(use(signerEntry.identity, "ide"));
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
SignerHelperImpl::storeAdd(LedgerEntry const &entry)
{
    storeUpdate(entry, true);
}

void
SignerHelperImpl::storeChange(LedgerEntry const &entry)
{
    storeUpdate(entry, false);
}

std::vector<SignerFrame::pointer>
SignerHelperImpl::loadSigners(AccountID const& accountID)
{
    std::string const accountIDStr = PubKeyUtils::toStrKey(accountID);

    std::string sql = mSignerColumnSelector;
    sql += " WHERE account_id = :id";

    auto prep = getDatabase().getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(accountIDStr, "id"));

    std::vector<SignerFrame::pointer> result;
    load(prep, [&result](LedgerEntry const& entry)
    {
        result.emplace_back(std::make_shared<SignerFrame>(entry));
    });

    return result;
}

void
SignerHelperImpl::storeDelete(LedgerKey const &key)
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

    flushCachedEntry(key);
}

bool
SignerHelperImpl::exists(LedgerKey const& key)
{
    if (cachedEntryExists(key) && getCachedEntry(key) != nullptr)
    {
        return true;
    }

    return exists(key.signer().pubKey);
}

bool
SignerHelperImpl::exists(PublicKey const &rawPubKey)
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

bool
SignerHelperImpl::isRoleIDUsed(uint64_t roleID)
{
    int exists = 0;
    {
        Database& db = getDatabase();

        auto timer = db.getSelectTimer("signer-role-used");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM signers "
                                            "WHERE role_id = :v1)");
        auto& st = prep.statement();
        st.exchange(use(roleID));
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);
    }

    return exists != 0;
}

LedgerKey
SignerHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey(from.data.type());
    ledgerKey.signer().pubKey = from.data.signer().pubKey;

    return ledgerKey;
}

EntryFrame::pointer
SignerHelperImpl::storeLoad(LedgerKey const& key)
{
    return loadSigner(key.signer().pubKey);
}

EntryFrame::pointer
SignerHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<SignerFrame>(from);
}

uint64_t
SignerHelperImpl::countObjects()
{
    soci::session& sess = getDatabase().getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM signers;", into(count);

    return count;
}

SignerFrame::pointer
SignerHelperImpl::loadSigner(PublicKey const &publicKey)
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

void
SignerHelperImpl::load(StatementContext& prep,
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
SignerHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}
}