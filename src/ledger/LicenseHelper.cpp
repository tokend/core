#include "LicenseHelper.h"
#include "LicenseSignatureHelper.h"
#include "xdrpp/printer.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"
#include "crypto/StrKey.h"

using namespace soci;
using namespace std;

namespace stellar
{

    const char* selectorLicense = "SELECT id, admin_count, due_date, ledger_hash, prev_hash FROM license";

    LicenseHelper::LicenseHelper(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }

    void LicenseHelper::dropAll(Database& db) {
        db.getSession() << "DROP TABLE IF EXISTS license;";
        db.getSession() << "CREATE TABLE license"
                           "("
                           "id             BIGINT NOT NULL CHECK (id >= 0),"
                           "admin_count    BIGINT NOT NULL,"
                           "due_date       BIGINT NOT NULL,"
                           "ledger_hash    VARCHAR(64) NOT NULL,"
                           "prev_hash      VARCHAR(64) NOT NULL,"
                           "hash           VARCHAR(64) NOT NULL,"
                           "PRIMARY KEY (hash)"
                           ");";
    }

    LedgerKey LicenseHelper::getLedgerKey(LedgerEntry const &from) {
            LedgerKey ledgerKey;
            ledgerKey.type(from.data.type());
            auto& le = from.data.license();
            auto hash = sha256(xdr::xdr_to_opaque(le.adminCount, le.dueDate, le.ledgerHash, le.prevLicenseHash, le.signatures));
            ledgerKey.license().licenseHash = hash;
            return ledgerKey;
    }

    EntryFrame::pointer LicenseHelper::fromXDR(LedgerEntry const &from) {
        return std::make_shared<LicenseFrame>(from);
    }

    uint64_t LicenseHelper::countObjects() {
        auto& db = getDatabase();
        auto& sess = db.getSession();
        uint64_t count = 0;
        sess << "SELECT COUNT(*) FROM license;", into(count);
        return count;
    }

    Database &LicenseHelper::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    bool LicenseHelper::exists(LedgerKey const &key) {
        auto& db = getDatabase();
        auto timer = db.getSelectTimer("license_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM license WHERE hash=:hash)");
        auto& st = prep.statement();
        st.exchange(use(xdr::xdr_to_string(key.license().licenseHash)));
        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    void LicenseHelper::storeAdd(LedgerEntry const &entry) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();

        LicenseSignatureHelper sigHelper(mStorageHelper);
        auto licenseFrame = make_shared<LicenseFrame>(entry);
        licenseFrame->touch(*delta);

        const auto le = licenseFrame->getLicenseEntry();

        auto sql = "INSERT INTO license (id, admin_count, due_date, ledger_hash, prev_hash, hash) "
                   "VALUES (:id, :admin_count, :due_date, :ledger_hash, :prev_hash, :hash)";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        auto ID = delta->getHeaderFrame().generateID(LedgerEntryType::LICENSE);
        auto hash = sha256(xdr::xdr_to_opaque(le.adminCount, le.dueDate, le.ledgerHash, le.prevLicenseHash, le.signatures));

        st.exchange(use(ID));
        st.exchange(use(le.adminCount));
        st.exchange(use(le.dueDate));
        st.exchange(use(binToHex(le.ledgerHash)));
        st.exchange(use(binToHex(le.prevLicenseHash)));
        st.exchange(use(binToHex(hash)));
        st.define_and_bind();
        st.execute(true);

        for(DecoratedSignature sig : le.signatures)
        {
            sigHelper.storeAdd(ID, sig);
        }
    }

    EntryFrame::pointer LicenseHelper::storeLoad(LedgerKey const &ledgerKey)
    {
        return loadLicense(ledgerKey);
    }

    EntryFrame::pointer LicenseHelper::loadLicense(LedgerKey const &ledgerKey) {
        auto &db = getDatabase();

        string sql = selectorLicense;
        sql += "WHERE hash = :hash";
        auto prep = db.getPreparedStatement(sql);
        auto &st = prep.statement();
        st.exchange(use(xdr::xdr_to_string(ledgerKey.license().licenseHash)));

        auto timer = db.getSelectTimer("load-license");
        LicenseFrame::pointer retLicense;
        loadLicenses(prep, [&retLicense](LedgerEntry const &entry) {
            retLicense = make_shared<LicenseFrame>(entry);
        });
        return retLicense;
    }



    void
    LicenseHelper::loadLicenses(StatementContext& prep,
                                function<void(LedgerEntry const&)> licenseProcessor)
    {
        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LICENSE);
        auto& le = entry.data.license();

        LicenseSignatureHelper sigHelper(mStorageHelper);

        string ledgerHash, prevLicenseHash;
        uint64_t id;
        auto st = prep.statement();
        st.exchange(into(id));
        st.exchange(into(le.adminCount));
        st.exchange(into(le.dueDate));
        st.exchange(into(ledgerHash));
        st.exchange(into(prevLicenseHash));
        st.define_and_bind();
        st.execute(true);

        while (st.got_data())
        {
            auto signatures = sigHelper.loadSignatures(id);
            le.ledgerHash = hexToBin256(ledgerHash);
            le.prevLicenseHash = hexToBin256(prevLicenseHash);

            licenseProcessor(entry);
            st.fetch();
        }
    }

    void LicenseHelper::dropAll() {

    }

    void LicenseHelper::storeChange(LedgerEntry const &entry) {

    }

    void LicenseHelper::storeDelete(LedgerKey const &key) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();
        auto timer = db.getDeleteTimer("license");
        auto prep = db.getPreparedStatement("DELETE FROM license WHERE hash=:hash");
        auto& st = prep.statement();
        st.exchange(use(binToHex(key.license().licenseHash)));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    EntryFrame::pointer LicenseHelper::loadCurrentLicense()
    {
        auto& db = getDatabase();
        string sql = selectorLicense;
        sql += "ORDER BY id DESC LIMIT 1";

        auto prep = db.getPreparedStatement(sql);
        LicenseFrame::pointer retLicense;
        loadLicenses(prep, [&retLicense](LedgerEntry const &entry) {
            retLicense = make_shared<LicenseFrame>(entry);
        });
        return retLicense;
    }

    uint64_t LicenseHelper::getAllowedAdmins(Application& app)
    {
        const uint64_t DEFAULT_ADMIN_COUNT = 2;

        auto licenseEntry = loadCurrentLicense();
        if(!licenseEntry){
            return DEFAULT_ADMIN_COUNT;
        }

        auto licenseFrame = std::make_shared<LicenseFrame>(licenseEntry->mEntry);

        if(!licenseFrame->isSignatureValid(app) || licenseFrame->isExpired(app))
        {
            return DEFAULT_ADMIN_COUNT;
        }

        return licenseFrame->mEntry.data.license().adminCount;
    }
}

