#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
    class StatementContext;

    class LicenseSignatureHelper : EntryHelper {
    public:
        virtual void storeAdd(LedgerEntry const& entry) = 0;
        virtual void storeChange(LedgerEntry const& entry) = 0;
        virtual void storeDelete(LedgerKey const& key) = 0;
        virtual bool exists(LedgerKey const& key) = 0;
        virtual LedgerKey getLedgerKey(LedgerEntry const& from) = 0;
        virtual EntryFrame::pointer fromXDR(LedgerEntry const& from) = 0;
        virtual EntryFrame::pointer storeLoad(LedgerKey const& ledgerKey) = 0;
        virtual Database &getDatabase() = 0;
        virtual void storeAdd(std::string licenseHash, uint8_t  ID, DecoratedSignature sig) = 0;
        virtual xdr::xvector<DecoratedSignature> loadSignatures(std::string licenseHash) = 0;
        virtual void dropAll() = 0;
        virtual void loadSignatures(StatementContext& prep,
        std::function<void(DecoratedSignature const&)> processor) = 0;
        virtual uint64_t countObjects() = 0;
    };
}
