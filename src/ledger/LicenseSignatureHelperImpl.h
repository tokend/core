#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LicenseSignatureHelper.h"

namespace stellar
{
    class StatementContext;

    class LicenseSignatureHelperImpl : public LicenseSignatureHelper, NonCopyable {
        StorageHelper& mStorageHelper;

    public:
        explicit LicenseSignatureHelperImpl(StorageHelper& storageHelper);

    private:
        Database &getDatabase() override;
        void storeAdd(std::string licenseHash, uint8_t  ID, DecoratedSignature sig) override;
        xdr::xvector<DecoratedSignature> loadSignatures(std::string licenseHash) override;
        void dropAll() override;
        void loadSignatures(StatementContext& prep,
        std::function<void(DecoratedSignature const&)> processor) override ;
        void storeAdd(LedgerEntry const& entry) override;
        void storeChange(LedgerEntry const& entry) override;
        void storeDelete(LedgerKey const& key) override;
        bool exists(LedgerKey const& key) override;
        LedgerKey getLedgerKey(LedgerEntry const& from) override;
        EntryFrame::pointer fromXDR(LedgerEntry const& from) override;
        EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) override;
        uint64_t countObjects() override;
        LedgerDelta*
        getLedgerDelta() override
        {
            return mStorageHelper.getLedgerDelta();
        }

        std::string const
        getTableName() const override;
    };
}
