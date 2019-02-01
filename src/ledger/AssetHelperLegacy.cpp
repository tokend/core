#include "AssetHelperLegacy.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AssetHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void AssetHelperLegacy::dropAll(Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    storageHelper->getAssetHelper().dropAll();
}

void AssetHelperLegacy::storeAdd(LedgerDelta& delta, Database& db,
                           LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getAssetHelper().storeAdd(entry);
}

void AssetHelperLegacy::storeChange(LedgerDelta& delta, Database& db,
                              LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getAssetHelper().storeChange(entry);
}

void AssetHelperLegacy::storeDelete(LedgerDelta& delta, Database& db,
                              LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    storageHelper->getAssetHelper().storeDelete(key);
}

bool AssetHelperLegacy::exists(Database& db, LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getAssetHelper().exists(key);
}

bool AssetHelperLegacy::exists(Database& db, const AssetCode code)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getAssetHelper().exists(code);
}

LedgerKey AssetHelperLegacy::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.asset().code = from.data.asset().code;
    return ledgerKey;
}

EntryFrame::pointer AssetHelperLegacy::storeLoad(LedgerKey const& key, Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getAssetHelper().storeLoad(key);
}

EntryFrame::pointer AssetHelperLegacy::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<AssetFrame>(from);
}

uint64_t AssetHelperLegacy::countObjects(soci::session& sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM asset;", into(count);
    return count;
}

AssetFrame::pointer
AssetHelperLegacy::loadAsset(AssetCode code, Database& db,
                             LedgerDelta* delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getAssetHelper().loadAsset(code);
}

AssetFrame::pointer AssetHelperLegacy::mustLoadAsset(AssetCode code, Database& db,
    LedgerDelta* delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getAssetHelper().mustLoadAsset(code);
}

AssetFrame::pointer AssetHelperLegacy::loadAsset(AssetCode code,
                                                 AccountID const& owner, Database& db,
                                                 LedgerDelta* delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getAssetHelper().loadAsset(code, owner);
}

AssetFrame::pointer AssetHelperLegacy::loadStatsAsset(Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getAssetHelper().loadStatsAsset();
}

void AssetHelperLegacy::loadBaseAssets(std::vector<AssetFrame::pointer>& retAssets,
                                       Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getAssetHelper().loadBaseAssets(retAssets);
}

std::map<AssetCode, uint64_t>
AssetHelperLegacy::loadIssuedForAssets(Database &db)
{
    uint64_t issued = 0;
    AssetCode assetCode;

    std::map<AssetCode, uint64_t> result;

    auto timer = db.getSelectTimer("issued-for-asset");
    auto prep = db.getPreparedStatement("SELECT code, issued FROM asset");
    auto& st = prep.statement();
    st.exchange(into(assetCode));
    st.exchange(into(issued));
    st.define_and_bind();
    st.execute(true);
    while(st.got_data())
    {
        result[assetCode] = issued;
        st.fetch();
    }

    return result;
}

}
