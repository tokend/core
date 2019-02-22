#include "StampHelperImpl.h"

using namespace soci;
using namespace std;

namespace stellar
{
StampHelperImpl::StampHelperImpl(StorageHelper& storageHelper)
    : mStorageHelper(storageHelper)
{
}

void StampHelperImpl::dropAll()
{
    auto& db = getDatabase();
    db.getSession() << "DROP TABLE IF EXISTS stamp;";
    db.getSession() << "CREATE TABLE stamp"
                       "("
                       "ledger_hash           VARCHAR(64) NOT NULL,"
                       "license_hash          VARCHAR(64)"
                       ");";
}

LedgerKey StampHelperImpl::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.stamp().licenseHash = from.data.stamp().licenseHash;
    ledgerKey.stamp().ledgerHash = from.data.stamp().ledgerHash;
    return ledgerKey;
}

void StampHelperImpl::storeAdd(LedgerEntry const& entry)
{
    auto key = getLedgerKey(entry);
    if (exists(key))
    {
        return;
    }
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

bool StampHelperImpl::exists(Hash ledgerHash, Hash licenseHash)
{
    auto entry = StampFrame::createNew(ledgerHash, licenseHash);
    auto key = getLedgerKey(entry->mEntry);

    return exists(key);
}
bool StampHelperImpl::exists(LedgerKey const& key)
{
    auto& db = mStorageHelper.getDatabase();

    auto timer = db.getSelectTimer("stamp_exists");
    auto prep = db.getPreparedStatement("SELECT EXISTS (SELECT NULL FROM stamp WHERE ledger_hash=:ledger_hash and license_hash=:license_hash)");
    auto& st = prep.statement();
    std::string ledgerHash = binToHex(key.stamp().ledgerHash);
    st.exchange(use(ledgerHash, "ledger_hash"));
    std::string licenseHash = binToHex(key.stamp().licenseHash);
    st.exchange(use(licenseHash, "license_hash"));
    auto exists = 0;
    st.exchange(into(exists));
    st.define_and_bind();
    st.execute(true);

    return exists != 0;
}

uint64_t StampHelperImpl::countObjects()
{
    auto& db = getDatabase();
    auto& sess = db.getSession();
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM stamp;", into(count);
    return count;
}

void StampHelperImpl::clearAll()
{
    auto& db = getDatabase();
    auto timer = db.getDeleteTimer("stamp");
    auto prep = db.getPreparedStatement("DELETE FROM stamp");
    auto& st = prep.statement();
    st.define_and_bind();
    st.execute(true);
}

EntryFrame::pointer StampHelperImpl::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<StampFrame>(from);
}

Database& StampHelperImpl::getDatabase()
{
    return mStorageHelper.getDatabase();
}
void StampHelperImpl::storeChange(LedgerEntry const& entry)
{
    throw runtime_error("Cannot change Stamp");
}
void StampHelperImpl::storeLoad(LedgerEntry const& entry)
{
    throw runtime_error("Cannot load Stamp");
}
void StampHelperImpl::storeDelete(LedgerEntry const& entry)
{
    throw runtime_error("Cannot delete Stamp");

}
void StampHelperImpl::storeDelete(LedgerKey const& key)
{
    throw runtime_error("Cannot delete Stamp");
}
EntryFrame::pointer StampHelperImpl::storeLoad(LedgerKey const& ledgerKey)
{
    throw runtime_error("Cannot load Stamp");
}
}

