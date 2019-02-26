#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "bucket/LedgerCmp.h"

namespace stellar
{
Hash
getLicenseHash(LicenseEntry mLicense)
{
    std::string ledgerHash = binToHex(mLicense.ledgerHash);
    std::string prevLicenseHash = binToHex(mLicense.prevLicenseHash);
    std::string fullData = std::to_string(mLicense.adminCount) + ":" +
                           std::to_string(mLicense.dueDate) + ":" + ledgerHash +
                           ":" + prevLicenseHash;
    for (DecoratedSignature s : mLicense.signatures)
    {
        std::string sig = binToHex(s.signature);
        fullData += ":" + sig;
    }

    return Hash(sha256(fullData));
}

Hash
getLicenseHash(LedgerKey::_license_t key)
{
    return key.licenseHash;
}
} // namespace stellar
