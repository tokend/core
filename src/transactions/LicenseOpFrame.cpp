#include "transactions/LicenseOpFrame.h"
#include "database/Database.h"
#include "SignatureValidatorImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/LicenseHelper.h"
#include "ledger/StampHelper.h"
#include "ledger/StampFrame.h"
#include "main/Application.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"

namespace stellar
{

using namespace std;

unordered_map<AccountID, CounterpartyDetails>
LicenseOpFrame::getCounterpartyDetails(
    Database& db, LedgerDelta* delta) const
{
    // no counterparties
    return std::unordered_map<AccountID, CounterpartyDetails>();
}

SourceDetails
LicenseOpFrame::getSourceAccountDetails(
    unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
    int32_t ledgerVersion) const
{
//    return SourceDetails();
}

LicenseOpFrame::LicenseOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mLicense(
          mOperation.body.licenseOp())
{
}

bool
LicenseOpFrame::doApply(Application& app,
                                            StorageHelper& storageHelper,
                                            LedgerManager& ledgerManager)
{
    StampHelper stampHelper(storageHelper);
    LicenseHelper licenseHelper(storageHelper);

    if (!stampHelper.exists(mLicense.blockHash, mLicense.oldLicenseHash))
    {
        innerResult().code(LicenseResultCode::INVALID_STAMP);
        return false;
    }

    auto oldLicenseEntry = licenseHelper.loadCurrentLicense();
    auto le = oldLicenseEntry->mEntry.data.license();
    if (le.dueDate > app.timeNow() &&
        le.adminCount > mLicense.adminCount)
    {
        innerResult().code(LicenseResultCode::DOWNGRADE_NOT_ALLOWED);
        return false;
    }


    if(!isSignatureValid(app, ledgerManager)){
        innerResult().code(LicenseResultCode::INVALID_SIGNATURE);
        return false;
    }

    auto prevLicenseKey = licenseHelper.getLedgerKey(oldLicenseEntry->mEntry);
    licenseHelper.storeDelete(prevLicenseKey);

    auto newLicense = LicenseFrame::createNew(mLicense.blockHash,
            mLicense.oldLicenseHash, mLicense.adminCount, mLicense.dueDate, mLicense.signatures);

    licenseHelper.storeAdd(newLicense->mEntry);
    return true;
}


bool
LicenseOpFrame::doCheckValid(Application& app)
{
    if (app.timeNow() >= mLicense.dueDate)
    {
        innerResult().code(LicenseResultCode::INVALID_DUE_DATE);
        return false;
    }

    return true;
}

bool LicenseOpFrame::isSignatureValid(Application& app, LedgerManager& lm)
{
    auto choppedLicenseHash = sha256(xdr::xdr_to_opaque(mLicense.adminCount,
                                                        mLicense.dueDate, mLicense.blockHash, mLicense.oldLicenseHash));

    SignatureValidatorImpl signatureValidator(choppedLicenseHash, {mLicense.signatures[0], mLicense.signatures[1]});

    const int VALID_SIGNATURES_REQUIRED = 2;
    SignatureValidator::Result result =
            signatureValidator.check({app.getConfig().firstLicenseID, app.getConfig().secondLicenseID},
                                                                  VALID_SIGNATURES_REQUIRED,
                                                                  LedgerVersion(lm.getCurrentLedgerHeader().ledgerVersion));
    return result == SignatureValidator::Result::SUCCESS;
}

} // namespace stellar
