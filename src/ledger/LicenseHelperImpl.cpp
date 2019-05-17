#include "LicenseHelperImpl.h"
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

    const char* selectorLicense = "SELECT admin_count, due_date, ledger_hash, prev_hash, hash FROM license";

    LicenseHelperImpl::LicenseHelperImpl(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }

    LedgerKey LicenseHelperImpl::getLedgerKey(LedgerEntry const &from) {
            LedgerKey ledgerKey;
            ledgerKey.type(from.data.type());
            auto licenseFrame = std::make_shared<LicenseFrame>(from);
            auto hash = licenseFrame->getFullHash();
            ledgerKey.license().licenseHash = hash;
            return ledgerKey;
    }

    EntryFrame::pointer LicenseHelperImpl::fromXDR(LedgerEntry const &from) {
        return std::make_shared<LicenseFrame>(from);
    }

    uint64_t LicenseHelperImpl::countObjects() {
        auto& db = getDatabase();
        auto& sess = db.getSession();
        uint64_t count = 0;
        sess << "SELECT COUNT(*) FROM license;", into(count);
        return count;
    }

    Database &LicenseHelperImpl::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    bool LicenseHelperImpl::exists(LedgerKey const &key) {
        auto& db = getDatabase();
        auto timer = db.getSelectTimer("license_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM license WHERE hash=:hash)");
        auto& st = prep.statement();
        auto hash = binToHex(key.license().licenseHash);
        st.exchange(use(hash, "hash"));
        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    void LicenseHelperImpl::storeAdd(LedgerEntry const &entry) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();

        auto& sigHelper = mStorageHelper.getLicenseSignatureHelper();
        auto licenseFrame = make_shared<LicenseFrame>(entry);

        const auto le = licenseFrame->getLicenseEntry();

        auto sql = "INSERT INTO license (id, admin_count, due_date, ledger_hash, prev_hash, hash) "
                   "VALUES (:id, :admin_count, :due_date, :ledger_hash, :prev_hash, :hash)";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        auto fullHash = licenseFrame->getFullHash();
        const uint64 licenseID = delta->getHeaderFrame().
            generateID(LedgerEntryType::LICENSE);

        st.exchange(use(licenseID, "id"));
        st.exchange(use(le.adminCount, "admin_count"));
        st.exchange(use(le.dueDate, "due_date"));
        auto ledgerHash = binToHex(le.ledgerHash);
        st.exchange(use(ledgerHash, "ledger_hash"));
        auto licenseHash = binToHex(le.prevLicenseHash);
        st.exchange(use(licenseHash, "prev_hash"));
        auto hash = binToHex(fullHash);
        st.exchange(use(hash, "hash"));
        st.define_and_bind();
        st.execute(true);

        for(int i = 0; i < le.signatures.size(); i++)
        {
            sigHelper.storeAdd(hash, i, le.signatures[i]);
        }
        delta->addEntry(*licenseFrame);
    }

    EntryFrame::pointer LicenseHelperImpl::storeLoad(LedgerKey const &ledgerKey)
    {
        return loadLicense(ledgerKey);
    }

    EntryFrame::pointer LicenseHelperImpl::loadLicense(LedgerKey const &ledgerKey) {
        auto &db = getDatabase();

        string sql = selectorLicense;
        sql += " WHERE hash = :hash";
        auto prep = db.getPreparedStatement(sql);
        auto &st = prep.statement();
        auto hash = binToHex(ledgerKey.license().licenseHash);
        st.exchange(use(hash, "hash"));

        auto timer = db.getSelectTimer("load-license");

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LICENSE);
        auto& le = entry.data.license();
        string ledgerHash, prevLicenseHash, licenseHash;

        st.exchange(into(le.adminCount));
        st.exchange(into(le.dueDate));
        st.exchange(into(ledgerHash));
        st.exchange(into(prevLicenseHash));
        st.exchange(into(hash));
        st.define_and_bind();
        st.execute(true);

        if (!st.got_data())
        {
            return nullptr;
        }

        auto& sigHelper = mStorageHelper.getLicenseSignatureHelper();

        auto signatures = sigHelper.loadSignatures(hash);
        le.ledgerHash = hexToBin256(ledgerHash);
        le.prevLicenseHash = hexToBin256(prevLicenseHash);
        le.signatures = signatures;

        auto retLicense = make_shared<LicenseFrame>(entry);
        return retLicense;
    }


    void LicenseHelperImpl::dropAll() {
        auto& db = getDatabase();
        db.getSession() << "DROP TABLE IF EXISTS license CASCADE";
        db.getSession() << "CREATE TABLE license"
                           "("
                           "id             BIGINT NOT NULL,"
                           "admin_count    BIGINT NOT NULL,"
                           "due_date       BIGINT NOT NULL,"
                           "ledger_hash    VARCHAR(64) NOT NULL,"
                           "prev_hash      VARCHAR(64) NOT NULL,"
                           "hash           VARCHAR(64) NOT NULL,"
                           "PRIMARY KEY (hash)"
                           ");";
        mStorageHelper.getLicenseSignatureHelper().dropAll();
    }

    void LicenseHelperImpl::storeDelete(LedgerKey const &key) {
        auto& db = getDatabase();
        auto delta = mStorageHelper.getLedgerDelta();
        auto timer = db.getDeleteTimer("license");
        auto prep = db.getPreparedStatement("DELETE FROM license WHERE hash=:hash");
        auto& st = prep.statement();
        auto hash = binToHex(key.license().licenseHash);
        st.exchange(use(hash, "hash"));
        st.define_and_bind();
        st.execute(true);
        delta->deleteEntry(key);
    }

    LicenseFrame::pointer LicenseHelperImpl::loadCurrentLicense()
    {
        auto& db = getDatabase();
        string sql = selectorLicense;
        sql += " ORDER BY id DESC LIMIT 1 ";
        auto prep = db.getPreparedStatement(sql);

        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LICENSE);
        auto& le = entry.data.license();
        string ledgerHash, prevLicenseHash, hash;

        auto st = prep.statement();
        st.exchange(into(le.adminCount));
        st.exchange(into(le.dueDate));
        st.exchange(into(ledgerHash));
        st.exchange(into(prevLicenseHash));
        st.exchange(into(hash));
        st.define_and_bind();
        st.execute(true);

        if (!st.got_data())
        {
            return nullptr;
        }

        auto& sigHelper = mStorageHelper.getLicenseSignatureHelper();

        auto signatures = sigHelper.loadSignatures(hash);
        le.ledgerHash = hexToBin256(ledgerHash);
        le.prevLicenseHash = hexToBin256(prevLicenseHash);
        le.signatures = signatures;
        auto retLicense = make_shared<LicenseFrame>(entry);
        return retLicense;
    }

    uint64_t LicenseHelperImpl::getAllowedAdmins(Application& app)
    {
        auto lastLedgerSeq = app.getLedgerManager().getLastClosedLedgerHeader().header.ledgerSeq;

        uint64_t freeAdminCount = 0;
        if (app.getLedgerManager().shouldUse(LedgerVersion::UNLIMITED_ADMIN_COUNT)) {
            freeAdminCount = UINT64_MAX;
        }

        uint64_t DEFAULT_ADMIN_COUNT =
            lastLedgerSeq < app.getConfig().LICENSE_FREE_PERIOD_NUM_BLOCKS
                ? freeAdminCount
                : 0;

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
void LicenseHelperImpl::storeChange(LedgerEntry const& entry)
{
    throw runtime_error("Cannot change license");
}
}

