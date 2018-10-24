#include "ledger/BalanceHelperLegacy.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/BalanceHelper.h"

using namespace soci;
using namespace std;

namespace stellar
{
using xdr::operator<;

void
BalanceHelperLegacy::dropAll(Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().dropAll();
}

void
BalanceHelperLegacy::storeAdd(LedgerDelta& delta, Database& db,
                              LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().storeAdd(entry);
}

void
BalanceHelperLegacy::storeChange(LedgerDelta& delta, Database& db,
                                 LedgerEntry const& entry)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().storeChange(entry);
}

void
BalanceHelperLegacy::storeDelete(LedgerDelta& delta, Database& db,
                                 LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, &delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().storeDelete(key);
}

bool
BalanceHelperLegacy::exists(Database& db, LedgerKey const& key)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().exists(key);
}

LedgerKey
BalanceHelperLegacy::getLedgerKey(LedgerEntry const& from)
{
    LedgerKey ledgerKey;
    ledgerKey.type(from.data.type());
    ledgerKey.balance().balanceID = from.data.balance().balanceID;
    return ledgerKey;
}

EntryFrame::pointer
BalanceHelperLegacy::storeLoad(LedgerKey const& key, Database& db)
{
    auto const &balance = key.balance();
    return loadBalance(balance.balanceID, db);
}

EntryFrame::pointer
BalanceHelperLegacy::fromXDR(LedgerEntry const& from)
{
    return std::make_shared<BalanceFrame>(from);
}

uint64_t
BalanceHelperLegacy::countObjects(soci::session& sess)
{
    uint64_t count = 0;
    sess << "SELECT COUNT(*) FROM balance;", into(count);
    return count;
}

BalanceFrame::pointer
BalanceHelperLegacy::loadBalance(AccountID accountID, BalanceID balanceID,
                                 Database &db, LedgerDelta *delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadBalance(balanceID, accountID);
}

BalanceFrame::pointer
BalanceHelperLegacy::loadBalance(BalanceID balanceID, Database& db,
                                 LedgerDelta* delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadBalance(balanceID);
}

BalanceFrame::pointer
BalanceHelperLegacy::loadBalance(AccountID account, AssetCode asset,
                                 Database& db, LedgerDelta* delta)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, delta));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadBalance(account, asset);
}

void
BalanceHelperLegacy::loadBalances(AccountID const& accountID,
                            std::vector<BalanceFrame::pointer>& retBalances,
                            Database& db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    storageHelper->getBalanceHelper().loadBalances(accountID, retBalances);
}

bool
BalanceHelperLegacy::exists(Database& db, BalanceID balanceID)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().exists(balanceID);
}

std::vector<BalanceFrame::pointer>
BalanceHelperLegacy::loadAssetHolders(AssetCode assetCode, AccountID ownerID,
                                uint64_t minTotalAmount, Database &db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadAssetHolders(assetCode, ownerID, minTotalAmount);
}

vector<BalanceFrame::pointer>
BalanceHelperLegacy::loadBalances(AccountID account, AssetCode asset,
                            Database &db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadBalances(account, asset);
}

vector<BalanceFrame::pointer>
BalanceHelperLegacy::loadBalances(std::vector<AccountID> accountIDs,
                                  AssetCode assetCode, Database &db)
{
    auto storageHelper = std::unique_ptr<StorageHelper>(new StorageHelperImpl(db, nullptr));
    storageHelper->release();
    return storageHelper->getBalanceHelper().loadBalances(accountIDs, assetCode);
}
}