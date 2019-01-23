#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"
#include "LicenseFrame.h"

namespace stellar
{
    class StatementContext;

    class LicenseHelper : EntryHelper {
        StorageHelper& mStorageHelper;

    public:
        LicenseHelper(StorageHelper& storageHelper);

        static void dropAll(Database& db);

        LedgerKey getLedgerKey(LedgerEntry const &from) override;
        EntryFrame::pointer fromXDR(LedgerEntry const &from) override;
        Database &getDatabase() override;
        bool exists(LedgerKey const &key) override;
        void storeAdd(LedgerEntry const &entry) override;
        void storeDelete(LedgerKey const &key) override;
        EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey) override;
        EntryFrame::pointer loadCurrentLicense();
        uint64_t getAllowedAdmins(Application& app);
    private:
        uint64_t countObjects() override;
        EntryFrame::pointer loadLicense(LedgerKey const &key);
        void loadLicenses(StatementContext& prep,
        std::function<void(LedgerEntry const&)> license);
        void dropAll() override;
        void storeChange(LedgerEntry const &entry) override;
    };
}