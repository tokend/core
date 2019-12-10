#include "LicenseFrame.h"
#include "crypto/SHA.h"
#include "xdrpp/marshal.h"
#include "crypto/StrKey.h"
#include "transactions/SignatureValidatorImpl.h"

using namespace soci;
using namespace std;

namespace stellar {
using xdr::operator<;

LicenseFrame::LicenseFrame() : EntryFrame(LedgerEntryType::LICENSE), mLicense(mEntry.data.license())
{
}

LicenseFrame::LicenseFrame(const LedgerEntry &from)
: EntryFrame(from), mLicense(mEntry.data.license())
{
}
LicenseFrame::LicenseFrame(const LicenseFrame &from) : LicenseFrame(from.mEntry)
{
}

LicenseFrame& LicenseFrame::operator=(const LicenseFrame &other)
{
    if (&other != this)
    {
        mLicense = other.mLicense;
        mKey = other.mKey;
        mKeyCalculated = other.mKeyCalculated;
    }
    return *this;
}

LicenseEntry& LicenseFrame::getLicenseEntry()
{
    return mLicense;
}

LicenseFrame::pointer LicenseFrame::createNew(stellar::Hash ledgerHash, stellar::Hash licenseHash, uint64_t adminCount,
                                              uint64_t dueDate, xdr::xvector<DecoratedSignature> signatures)
{
    try
    {
        LedgerEntry entry;
        entry.data.type(LedgerEntryType::LICENSE);
        entry.data.license().ledgerHash = ledgerHash;
        entry.data.license().prevLicenseHash = licenseHash;
        entry.data.license().adminCount = adminCount;
        entry.data.license().dueDate = dueDate;
        entry.data.license().signatures = signatures;
        return std::make_shared<LicenseFrame>(entry);
    } catch (...)
    {
        CLOG(ERROR, Logging::ENTRY_LOGGER) << "Failed to create license frame";
        throw_with_nested(runtime_error("Failed to create license frame"));
    }

}

bool LicenseFrame::isSignatureValid(Application &app)
{
    const int VALID_SIGNATURES_REQUIRED = 1;

    auto contentsHash = getSignatureData(mLicense.ledgerHash, mLicense.prevLicenseHash, mLicense.adminCount, mLicense.dueDate);
    xdr::xvector<DecoratedSignature, 20> signatures;
    signatures.append(mLicense.signatures.data(), mLicense.signatures.size());

    SignatureValidatorImpl signatureValidator(contentsHash, signatures);

    auto ledgerVersion = LedgerVersion(app.getLedgerManager().getCurrentLedgerHeader().ledgerVersion);
    auto keys = getLicenseKeys(app);

    SignatureValidator::Result result =
            signatureValidator.check(keys,
                                     VALID_SIGNATURES_REQUIRED,
                                     ledgerVersion);
    return result == SignatureValidator::Result::SUCCESS;
}

std::vector<PublicKey>
LicenseFrame::getLicenseKeys(Application& app) {
    const auto config = app.getConfig();
    std::vector<PublicKey> keys;
    auto& header = app.getLedgerManager().getCurrentLedgerHeader();
    if (header.ledgerSeq <= config.LICENSE_FREE_PERIOD_NUM_BLOCKS){
        auto devKeys = config.getDevKeys();
        keys.insert(keys.end(), devKeys.begin(), devKeys.end());
    }

    LedgerVersion ledgerVersion = LedgerVersion(header.ledgerVersion);
    auto wiredKeys = config.getWiredKeys(ledgerVersion);
    keys.insert(keys.end(), wiredKeys.begin(), wiredKeys.end());

    return keys;
}

bool LicenseFrame::isExpired(Application &app)
{
    return app.getLedgerManager().getCloseTime() > mLicense.dueDate;
}

Hash LicenseFrame::getFullHash()
{
    return getLicenseHash(mLicense);
}

Hash LicenseFrame::getSignatureData(Hash rawLedgerHash, Hash rawPrevLicenseHash, uint64_t adminCount, uint64_t dueDate)
{
    std::string ledgerHash = binToHex(rawLedgerHash);
    std::string prevLicenseHash = binToHex(rawPrevLicenseHash);

    std::string rawSignatureData = std::to_string(adminCount)
            + ":" + std::to_string(dueDate)
            + ":" + ledgerHash
            + ":" + prevLicenseHash;

    return Hash(sha256(rawSignatureData));
}

LedgerKey const &
LicenseFrame::getKey() const
{
    if (!mKeyCalculated) {
        mKey = LedgerKey(LedgerEntryType::LICENSE);
        mKey.license().licenseHash = mLicense.ledgerHash;
        mKeyCalculated = true;
    }
    return mKey;
}

}