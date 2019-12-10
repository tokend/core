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

        virtual LicenseFrame::pointer loadCurrentLicense() = 0;
        virtual uint64_t getAllowedAdmins(Application& app) = 0;
        virtual EntryFrame::pointer loadLicense(LedgerKey const &key) = 0;

    };
}
