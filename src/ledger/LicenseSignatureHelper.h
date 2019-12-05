#pragma once

#include "ledger/LedgerManager.h"
#include "ledger/EntryHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
class StatementContext;

class LicenseSignatureHelper : public EntryHelper {
public:
    virtual void storeAdd(std::string licenseHash, uint8_t  ID, DecoratedSignature sig) = 0;
    virtual xdr::xvector<DecoratedSignature> loadSignatures(std::string licenseHash) = 0;
    virtual void loadSignatures(StatementContext& prep,
    std::function<void(DecoratedSignature const&)> processor) = 0;
};
}