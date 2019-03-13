#include "LicenseSignatureHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"
#include "crypto/StrKey.h"
#include "database/Database.h"

using namespace soci;
using namespace std;

namespace stellar
{

const char *selectorSignatures = "SELECT signature, hint FROM license_signatures";

LicenseSignatureHelperImpl::LicenseSignatureHelperImpl(StorageHelper& storageHelper)
    : mStorageHelper(storageHelper)
{
}

void LicenseSignatureHelperImpl::dropAll()
{
    auto& db = getDatabase();
    db.getSession() << "DROP TABLE IF EXISTS license_signatures;";
    db.getSession() << "CREATE TABLE license_signatures"
                       "("
                       "id                  INT NOT NULL,"
                       "license_hash        VARCHAR(64) NOT NULL,"
                       "signature           VARCHAR(256) NOT NULL,"
                       "hint                VARCHAR(8) NOT NULL,"
                       "PRIMARY KEY (license_hash, signature),"
                       "FOREIGN KEY(license_hash) REFERENCES license(hash) ON DELETE CASCADE"
                       ");";
}

Database& LicenseSignatureHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}

void LicenseSignatureHelperImpl::storeAdd(std::string licenseHash, uint8_t ID, DecoratedSignature sig)
{
    auto& db = getDatabase();
    auto sql = "INSERT INTO license_signatures (id, license_hash, signature, hint) "
               "VALUES (:id, :license_hash, :signature, :hint)";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(ID, "id"));
    st.exchange(use(licenseHash, "license_hash"));
    auto signature = binToHex(sig.signature);
    st.exchange(use(signature, "signature"));
    auto hint = binToHex(sig.hint);
    st.exchange(use(hint, "hint"));
    st.define_and_bind();
    st.execute(true);
}

xdr::xvector<DecoratedSignature> LicenseSignatureHelperImpl::loadSignatures(std::string licenseHash)
{
    auto& db = getDatabase();

    string sql = selectorSignatures;
    sql += " WHERE license_hash = :license_hash ORDER BY id ASC";
    auto prep = db.getPreparedStatement(sql);
    auto& st = prep.statement();
    st.exchange(use(licenseHash, "license_hash"));
    auto timer = db.getSelectTimer("load-license-signature");
    xdr::xvector<DecoratedSignature> signatures;
    loadSignatures(prep, [&signatures](DecoratedSignature const& signature)
    {
        signatures.emplace_back(signature);
    });
    return signatures;
}

void
LicenseSignatureHelperImpl::loadSignatures(StatementContext& prep,
                                           function<void(DecoratedSignature const&)> processor)
{
    DecoratedSignature sig;
    string signature, hint;
    auto st = prep.statement();
    st.exchange(into(signature));
    st.exchange(into(hint));
    st.define_and_bind();
    st.execute(true);

    while (st.got_data())
    {
        auto temp = hexToBin(signature);
        xdr::xvector<uint8_t, 64> s;
        s.append(temp.data(), temp.size());
        temp = hexToBin(hint);
        xdr::opaque_array<4> h;
        for (int i = 0; i < temp.size(); i++)
            h[i] = temp[i];

        sig.signature = Signature(s);
        sig.hint = SignatureHint(h);

        processor(sig);
        st.fetch();
    }
}
void LicenseSignatureHelperImpl::storeAdd(LedgerEntry const& entry)
{
    throw runtime_error("Cannot add signature");
}
void LicenseSignatureHelperImpl::storeChange(LedgerEntry const& entry)
{
    throw runtime_error("Cannot change signature");
}
void LicenseSignatureHelperImpl::storeDelete(LedgerKey const& key)
{
    throw runtime_error("Cannot delete signature");
}
bool LicenseSignatureHelperImpl::exists(LedgerKey const& key)
{
    throw runtime_error("Cannot check for signature");
}
LedgerKey LicenseSignatureHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    throw runtime_error("Cannot get key for signature");
}
EntryFrame::pointer LicenseSignatureHelperImpl::fromXDR(LedgerEntry const& from)
{
    throw runtime_error("Cannot get from XDR");
}
EntryFrame::pointer LicenseSignatureHelperImpl::storeLoad(LedgerKey const& ledgerKey)
{
    throw runtime_error("Cannot load signature");
}
uint64_t LicenseSignatureHelperImpl::countObjects()
{
    throw runtime_error("Cannot count signatures");
}

}

