#include "SignerHelperImpl.h"
#include "StorageHelper.h"
#include "LedgerDelta.h"

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
                       "details         VARCHAR(256)   NOT NULL DEFAULT '{}',"
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
SignerHelperImpl::loadAccountSigners(AccountID const& accountID)
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