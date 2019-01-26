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
        void storeAdd(std::string licenseHash, DecoratedSignature sig);
        xdr::xvector<DecoratedSignature> loadSignatures(std::string licenseHash);
    private:
        void loadSignatures(StatementContext& prep,
        std::function<void(DecoratedSignature const&)> processor);
    };
}