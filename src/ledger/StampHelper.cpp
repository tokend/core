#include "StampHelper.h"
#include "xdrpp/printer.h"

using namespace soci;
using namespace std;

namespace stellar
{
    StampHelper::StampHelper(StorageHelper &storageHelper)
            : mStorageHelper(storageHelper)
    {
    }

    void StampHelper::dropAll(Database& db)
    {
        db.getSession() << "DROP TABLE IF EXISTS stamp;";
        db.getSession() << "CREATE TABLE stamp"
                           "("
                           "ledger_hash           VARCHAR(256) NOT NULL,"
                           "license_hash           VARCHAR(256)"
                           ");";
    }

    LedgerKey StampHelper::getLedgerKey(LedgerEntry const &from) {
        LedgerKey ledgerKey;
        ledgerKey.type(from.data.type());
        ledgerKey.stamp().licenseHash = from.data.stamp().licenseHash;
        ledgerKey.stamp().ledgerHash = from.data.stamp().ledgerHash;
        return ledgerKey;
    }

    void StampHelper::storeAdd(LedgerEntry const &entry)
    {
        auto delta = mStorageHelper.getLedgerDelta();
        auto& db = getDatabase();

        auto stampFrame = make_shared<StampFrame>(entry);
        stampFrame->touch(*delta);

        const auto stampEntry = stampFrame->getStampEntry();
        auto sql = "INSERT INTO stamp (ledger_hash, license_hash) VALUES (:ledger_hash, :license_hash)";
        auto prep = db.getPreparedStatement(sql);
        auto& st = prep.statement();
        auto ledgerHash = binToHex(stampEntry.ledgerHash);
        auto licenseHash = binToHex(stampEntry.licenseHash);
        st.exchange(use(ledgerHash, "ledger_hash"));
        st.exchange(use(licenseHash, "license_hash"));
        st.define_and_bind();
        st.execute(true);
    }

    bool StampHelper::exists(Hash ledgerHash, Hash licenseHash)
    {
        auto entry = StampFrame::createNew(ledgerHash, licenseHash);
        auto key = getLedgerKey(entry->mEntry);

        return exists(key);
    }
    bool StampHelper::exists(LedgerKey const &key)
    {
        auto& db = mStorageHelper.getDatabase();

        auto timer = db.getSelectTimer("stamp_exists");
        auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM stamp WHERE ledger_hash=:ledger_hash and license_hash=:license_hash)");
        auto& st = prep.statement();
        st.exchange(use(binToHex(key.stamp().ledgerHash), "ledger_hash"));
        st.exchange(use(binToHex(key.stamp().licenseHash), "license_hash"));
        auto exists = 0;
        st.exchange(into(exists));
        st.define_and_bind();
        st.execute(true);

        return exists != 0;
    }

    uint64_t StampHelper::countObjects()
    {
        auto& db = getDatabase();
        auto& sess = db.getSession();
        uint64_t count = 0;
        sess << "SELECT COUNT(*) FROM stamp;", into(count);
        return count;
    }

    void StampHelper::clearAll(Database &db)
    {
        auto timer = db.getDeleteTimer("stamp");
        auto prep = db.getPreparedStatement("DELETE FROM stamp");
        auto& st = prep.statement();
        st.define_and_bind();
        st.execute(true);
    }

    EntryFrame::pointer StampHelper::fromXDR(LedgerEntry const &from) {
        return std::make_shared<StampFrame>(from);
    }

    Database &StampHelper::getDatabase() {
        return mStorageHelper.getDatabase();
    }

    void StampHelper::storeDelete(LedgerKey const &key) {

    }

    void StampHelper::dropAll() {

    }

    void StampHelper::storeChange(LedgerEntry const &entry) {
    }

    EntryFrame::pointer StampHelper::storeLoad(LedgerKey const &ledgerKey) {
        return stellar::EntryFrame::pointer();
    }
}

