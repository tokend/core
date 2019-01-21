#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
    class StatementContext;

    class LicenseSignatureHelper {
        StorageHelper& mStorageHelper;

    public:
        LicenseSignatureHelper(StorageHelper& storageHelper);

        static void dropAll(Database& db);

        Database &getDatabase();
        void storeAdd(uint64_t licenseID, DecoratedSignature sig);
        void deleteForLicense(uint64_t licenseID);
        xdr::xvector<DecoratedSignature> loadSignatures(uint64_t licenseID);
    private:
        void loadSignatures(StatementContext& prep,
        std::function<void(DecoratedSignature const&)> processor);
    };
}