#include "bucket/LedgerCmp.h"

namespace stellar
{
LedgerVersion LedgerEntryIdCmp::currVersion = LedgerVersion::EMPTY_VERSION;

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
