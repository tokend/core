#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LicenseHelper.h"
#include "database/Database.h"

namespace stellar
{
    class StatementContext;

    class LicenseHelperImpl : public LicenseHelper, NonCopyable {
        StorageHelper& mStorageHelper;

    public:
        explicit LicenseHelperImpl(StorageHelper& storageHelper);
    private:
        LedgerKey getLedgerKey(LedgerEntry const &from) override;
        EntryFrame::pointer fromXDR(LedgerEntry const &from) override;
        Database &getDatabase() override;
        bool exists(LedgerKey const &key) override;
        void storeAdd(LedgerEntry const &entry) override;
        void storeDelete(LedgerKey const &key) override;
        void storeChange(LedgerEntry const& entry) override;
        EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey) override;
        LicenseFrame::pointer loadCurrentLicense() override;
        uint64_t getAllowedAdmins(Application& app) override;
        uint64_t countObjects() override;
        EntryFrame::pointer loadLicense(LedgerKey const &key) override;
        void dropAll() override;
        LedgerDelta*
        getLedgerDelta() override
        {
            return mStorageHelper.getLedgerDelta();
        }
    };
}
