#include "ledger/StorageHelperImpl.h"
#include "ledger/ExternalSystemAccountIDHelperLegacy.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelperLegacy.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ledger/LedgerDelta.h"

namespace stellar
{

StorageHelperImpl::StorageHelperImpl(Database& db, LedgerDelta& ledgerDelta)
    : mDatabase(db)
    , mLedgerDelta(ledgerDelta)
    , mTransaction(new soci::transaction(db.getSession()))
{
}

StorageHelperImpl::~StorageHelperImpl()
{
    if (mTransaction)
    {
        try
        {
            mTransaction->rollback();
        }
        catch (...)
        {
        }
    }
}

Database&
StorageHelperImpl::getDatabase()
{
    return mDatabase;
}
const Database&
StorageHelperImpl::getDatabase() const
{
    return mDatabase;
}
LedgerDelta&
StorageHelperImpl::getLedgerDelta()
{
    return mLedgerDelta;
}
const LedgerDelta&
StorageHelperImpl::getLedgerDelta() const
{
    return mLedgerDelta;
}

void
StorageHelperImpl::commit()
{
    mLedgerDelta.commit();
    if (mTransaction)
    {
        mTransaction->commit();
        mTransaction = nullptr;
    }
}
void
StorageHelperImpl::rollback()
{
    mLedgerDelta.rollback();
    if (mTransaction)
    {
        mTransaction->rollback();
        mTransaction = nullptr;
    }
}

std::unique_ptr<StorageHelper>
StorageHelperImpl::startNestedTransaction()
{
    if (mNestedDelta && mNestedDelta->isStateActive())
    {
        throw std::runtime_error("Invalid operation: this StorageHelper "
                                 "already has an active nested StorageHelper");
    }
    mNestedDelta = std::make_unique<LedgerDelta>(mLedgerDelta);
    return std::make_unique<StorageHelperImpl>(mDatabase, *mNestedDelta);
}

KeyValueHelperLegacy&
StorageHelperImpl::getKeyValueHelper()
{
    if (!mKeyValueHelper)
    {
        mKeyValueHelper = std::make_unique<KeyValueHelperLegacy>();
    }
    return *mKeyValueHelper;
}
ExternalSystemAccountIDHelperLegacy&
StorageHelperImpl::getExternalSystemAccountIDHelper()
{
    if (!mExternalSystemAccountIDHelper)
    {
        mExternalSystemAccountIDHelper =
            std::make_unique<ExternalSystemAccountIDHelperLegacy>();
    }
    return *mExternalSystemAccountIDHelper;
}
ExternalSystemAccountIDPoolEntryHelperLegacy&
StorageHelperImpl::getExternalSystemAccountIDPoolEntryHelper()
{
    if (!mExternalSystemAccountIDPoolEntryHelper)
    {
        mExternalSystemAccountIDPoolEntryHelper =
            std::make_unique<ExternalSystemAccountIDPoolEntryHelperLegacy>();
    }
    return *mExternalSystemAccountIDPoolEntryHelper;
}

} // namespace stellar