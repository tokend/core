#pragma once

#include "TxHelper.h"

namespace stellar
{

namespace txtest
{

class LicenseTestHelper : TxHelper {
public:
    explicit LicenseTestHelper(TestManager::pointer testManager);

    TransactionFramePtr createLicenseOp(Account& source,
                                        SecretKey& wiredKey,
                                        Hash ledgerHash,
                                        Hash prevLicenseHash,
                                        uint64_t adminCount,
                                        uint64_t dueDate);

    DecoratedSignature createLicenseSignature(SecretKey& wiredKey, Hash signatureData);

    LicenseResult applyLicenseOp(Account& source,
                                 SecretKey& wiredKey,
                                 Hash ledgerHash,
                                 Hash prevLicenseHash,
                                 uint64_t adminCount,
                                 uint64_t dueDate,
                                 LicenseResultCode expectedResult =
                                 LicenseResultCode::SUCCESS);
};

}

}
