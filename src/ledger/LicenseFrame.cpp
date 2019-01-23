#include "LicenseFrame.h"
#include "crypto/SHA.h"
#include "xdrpp/marshal.h"
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
                                              uint64_t dueDate, xdr::xvector<DecoratedSignature, 2> signatures)
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
    auto contentsHash = sha256(xdr::xdr_to_opaque(
            mLicense.adminCount, mLicense.dueDate,
            mLicense.ledgerHash, mLicense.prevLicenseHash
            ));

    SignatureValidatorImpl signatureValidator(contentsHash, {mLicense.signatures[0], mLicense.signatures[1]});

    const int VALID_SIGNATURES_REQUIRED = 2;
    const auto config = app.getConfig();
    auto keys = config.getWiredKeys();

    SignatureValidator::Result result =
            signatureValidator.check(keys,
                                     VALID_SIGNATURES_REQUIRED,
                                     LedgerVersion(app.getLedgerManager().getCurrentLedgerHeader().ledgerVersion));
    return result == SignatureValidator::Result::SUCCESS;
}

bool LicenseFrame::isExpired(Application &app)
{
    return app.timeNow() > mLicense.dueDate;
}

}
