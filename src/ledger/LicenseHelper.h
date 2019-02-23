#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LicenseFrame.h"

namespace stellar
{
    class StatementContext;

    class LicenseHelper : public EntryHelper {

    public:
        virtual LedgerKey getLedgerKey(LedgerEntry const &from) = 0;
        virtual EntryFrame::pointer fromXDR(LedgerEntry const &from) = 0;
        virtual Database &getDatabase() = 0;
        virtual bool exists(LedgerKey const &key) = 0;
        virtual void storeAdd(LedgerEntry const &entry) = 0;
        virtual void storeDelete(LedgerKey const &key) = 0;
        virtual EntryFrame::pointer storeLoad(LedgerKey const &ledgerKey) = 0;
        virtual LicenseFrame::pointer loadCurrentLicense() = 0;
        virtual uint64_t getAllowedAdmins(Application& app) = 0;
        virtual uint64_t countObjects() = 0;
        virtual EntryFrame::pointer loadLicense(LedgerKey const &key) = 0;
        virtual void dropAll() = 0;

    };
}
