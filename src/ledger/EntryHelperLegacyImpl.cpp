#include <main/ApplicationImpl.h>
#include "transactions/test/mocks/MockDatabase.h"
#include "EntryHelperLegacyImpl.h"
#include "StorageHelperImpl.h"
#include "EntryHelper.h"

namespace stellar
{
EntryHelperLegacyImpl::EntryHelperLegacyImpl(LedgerEntryType entryType)
        : mEntryType(entryType)
{
}

void EntryHelperLegacyImpl::dropAll(Database &db)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(mEntryType)->dropAll();
}

void
EntryHelperLegacyImpl::storeChange(LedgerDelta &delta, Database &db,
                                   LedgerEntry const &entry)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, &delta);
    return storageHelper->getHelper(entry.data.type())->storeChange(entry);
}

void
EntryHelperLegacyImpl::storeAdd(LedgerDelta &delta, Database &db,
                                LedgerEntry const &entry)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, &delta);
    return storageHelper->getHelper(entry.data.type())->storeAdd(entry);
}

void
EntryHelperLegacyImpl::storeDelete(LedgerDelta &delta, Database &db,
                                   LedgerKey const &key)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, &delta);
    return storageHelper->getHelper(key.type())->storeDelete(key);
}

EntryFrame::pointer
EntryHelperLegacyImpl::storeLoad(LedgerKey const &key, Database &db)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(key.type())->storeLoad(key);
}

LedgerKey
EntryHelperLegacyImpl::getLedgerKey(LedgerEntry const &from)
{
    MockDatabase db;
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(from.data.type())->getLedgerKey(from);
}

EntryFrame::pointer
EntryHelperLegacyImpl::fromXDR(LedgerEntry const &from)
{
    MockDatabase db;
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(from.data.type())->fromXDR(from);
}

bool
EntryHelperLegacyImpl::exists(Database &db, LedgerKey const &key)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(key.type())->exists(key);
}

uint64_t
EntryHelperLegacyImpl::countObjects(soci::session &sess)
{
    throw std::runtime_error("Unexpected call. Use method with db");
}

uint64_t
EntryHelperLegacyImpl::countObjects(Database& db)
{
    std::unique_ptr<StorageHelper> storageHelper = std::make_unique<StorageHelperImpl>(db, nullptr);
    return storageHelper->getHelper(mEntryType)->countObjects();
}

}