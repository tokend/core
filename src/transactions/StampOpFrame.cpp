#include "transactions/StampOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "ledger/StampHelper.h"
#include "ledger/StampFrame.h"
#include "ledger/LicenseHelper.h"
#include "ledger/LicenseFrame.h"
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
    return SourceDetails({AccountType::MASTER}, mSourceAccount->getHighThreshold(),
                         static_cast<int32_t>(SignerType::TX_SENDER));}

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
    auto& stampHelper = storageHelper.getStampHelper();
    auto& licenseHelper = storageHelper.getLicenseHelper();

    auto ledgerHash = ledgerManager.getLastClosedLedgerHeader().hash;
    Hash oldLicenseHash;
    auto license = licenseHelper.loadCurrentLicense();
    if (license)
    {
        auto licenseFrame = make_shared<LicenseFrame>(license->mEntry);
        oldLicenseHash = licenseFrame->getFullHash();
    }
    auto newStamp = StampFrame::createNew(ledgerHash, oldLicenseHash);

    stampHelper.storeAdd(newStamp->mEntry);

    innerResult().code(StampResultCode::SUCCESS);
    innerResult().success().licenseHash = oldLicenseHash;
    innerResult().success().ledgerHash = ledgerHash;
    return true;
}

bool
StampOpFrame::doCheckValid(Application& app)
{
    return true;
}

} // namespace stellar
