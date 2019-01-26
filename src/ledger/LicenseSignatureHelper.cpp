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
                           "license_hash           VARCHAR(64) NOT NULL,"
                           "signature      VARCHAR(256) NOT NULL,"
                           "PRIMARY KEY (license_hash, signature),"
                           "FOREIGN KEY(license_hash) REFERENCES license(hash) ON DELETE CASCADE"
                           ");";
    }
    
    Database &LicenseSignatureHelper::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    void LicenseSignatureHelper::storeAdd(std::string licenseHash, DecoratedSignature sig) {
        auto& db = getDatabase();
        auto sql = "INSERT INTO license_signatures (license_hash, signature) "
                   "VALUES (:license_hash, :signature)";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();

        st.exchange(use(licenseHash, "license_hash"));
        auto signature = binToHex(sig.signature);
        st.exchange(use(signature, "signature"));
        st.define_and_bind();
        st.execute(true);
    }

    xdr::xvector<DecoratedSignature> LicenseSignatureHelper::loadSignatures(std::string licenseHash) {
        auto &db = getDatabase();

        string sql = selectorSignatures;
        sql += " WHERE license_hash = :license_hash";
        auto prep = db.getPreparedStatement(sql);
        auto &st = prep.statement();
        st.exchange(use(licenseHash, "license_hash"));
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
        auto st = prep.statement();
        st.exchange(into(signature));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            auto temp = hexToBin(signature);
            xdr::xvector<uint8_t, 64> s;
            for(uint8_t byte : temp)
            {
                s.push_back(byte);
            }
            sig.signature = Signature(s);

            processor(sig);
            st.fetch();
        }
    }

}

