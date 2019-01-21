#include "LicenseSignatureHelper.h"
#include "ledger/LedgerDelta.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"
#include "crypto/StrKey.h"

using namespace soci;
using namespace std;

namespace stellar
{

    const char* selectorSignatures = "SELECT signature FROM license_signatures";

    LicenseSignatureHelper::LicenseSignatureHelper(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }

    void LicenseSignatureHelper::dropAll(Database& db) {
        db.getSession() << "DROP TABLE IF EXISTS license_signatures;";
        db.getSession() << "CREATE TABLE license_signatures"
                           "("
                           "license_id     BIGINT NOT NULL CHECK (id >= 0),"
                           "signature      VARCHAR(256) NOT NULL,"
                           "PRIMARY KEY (license_id, signature)"
                           ");";
    }
    
    Database &LicenseSignatureHelper::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    void LicenseSignatureHelper::storeAdd(uint64_t licenseID, DecoratedSignature sig) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();

        auto sql = "INSERT INTO license_signatures (license_id, signature) "
                   "VALUES (:license_id, :signature)";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        st.exchange(use(licenseID));
        st.exchange(use(strKey::toStrKey(strKey::STRKEY_PUBKEY_ED25519, sig.signature)));
        st.define_and_bind();
        st.execute(true);
    }

    xdr::xvector<DecoratedSignature> LicenseSignatureHelper::loadSignatures(uint64_t licenseID) {
        auto &db = getDatabase();

        string sql = selectorSignatures;
        sql += "WHERE license_id = :id";
        auto prep = db.getPreparedStatement(sql);
        auto &st = prep.statement();
        st.exchange(use(licenseID));

        auto timer = db.getSelectTimer("load-license-signature");
        xdr::xvector<DecoratedSignature> signatures;
        loadSignatures(prep, [&signatures](DecoratedSignature const &signature) {
            signatures.emplace_back(signature);
        });
        return signatures;
    }



    void
    LicenseSignatureHelper::loadSignatures(StatementContext& prep,
                                function<void(DecoratedSignature const&)> processor)
    {
        DecoratedSignature sig;
        string signature;
        uint8_t versionByte = strKey::STRKEY_PUBKEY_ED25519;
        auto st = prep.statement();
        st.exchange(into(signature));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            strKey::fromStrKey(signature, versionByte, sig.signature);

            processor(sig);
            st.fetch();
        }
    }

    void LicenseSignatureHelper::deleteForLicense(uint64_t licenseID) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();
        auto timer = db.getDeleteTimer("license-signatures");
        auto prep = db.getPreparedStatement("DELETE FROM license_signatures WHERE license_id=:license_id");
        auto& st = prep.statement();
        st.exchange(use(licenseID));
        st.define_and_bind();
        st.execute(true);
    }

}

