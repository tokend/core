#include "transactions/StampOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/StampHelper.h"
#include "ledger/StampFrame.h"
#include "ledger/LicenseHelper.h"
#include "main/Application.h"
#include "xdrpp/marshal.h"
#include "crypto/SHA.h"

namespace stellar
{

using namespace std;

std::unordered_map<AccountID, CounterpartyDetails>
StampOpFrame::getCounterpartyDetails(
    Database& db, LedgerDelta* delta) const
{
    // no counterparties
    return std::unordered_map<AccountID, CounterpartyDetails>();
}

SourceDetails
StampOpFrame::getSourceAccountDetails(
    std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
    int32_t ledgerVersion) const
{
//    return SourceDetails();
}

StampOpFrame::StampOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mStamp(
          mOperation.body.stampOp())
{
}

bool
StampOpFrame::doApply(Application& app,
                                            StorageHelper& storageHelper,
                                            LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    StampHelper stampHelper(storageHelper);
    LicenseHelper licenseHelper(storageHelper);

    auto ledgerHash = ledgerManager.getLastClosedLedgerHeader().hash;
    Hash oldLicenseHash = sha256(xdr::xdr_to_opaque());
    auto license = licenseHelper.loadCurrentLicense();
    if (license)
    {
        auto le = license->mEntry.data.license();
        oldLicenseHash = sha256(xdr::xdr_to_opaque(le.adminCount, le.dueDate, le.ledgerHash, le.prevLicenseHash, le.signatures));
    }
    auto newStamp = StampFrame::createNew(ledgerHash, oldLicenseHash);

    stampHelper.storeAdd(newStamp->mEntry);
    return true;
}

bool
StampOpFrame::doCheckValid(Application& app)
{
    return true;
}

} // namespace stellar
