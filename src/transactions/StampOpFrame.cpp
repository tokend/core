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


bool
StampOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::STAMP);

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    return true;
}

bool
StampOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                               std::vector<SignerRequirement> &result) const
{
    SignerRuleResource resource(LedgerEntryType::STAMP);

    result.emplace_back(resource, SignerRuleAction::CREATE);
    return true;
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
    auto& stampHelper = storageHelper.getStampHelper();
    auto& licenseHelper = storageHelper.getLicenseHelper();

    auto ledgerHash = ledgerManager.getLastClosedLedgerHeader().hash;
    Hash oldLicenseHash;
    auto license = licenseHelper.loadCurrentLicense();
    if (license)
    {
        oldLicenseHash = license->getFullHash();
    }
    auto newStamp = StampFrame::createNew(ledgerHash, oldLicenseHash);
    auto key = stampHelper.getLedgerKey(newStamp->mEntry);
    if (!stampHelper.exists(key))
    {
        stampHelper.storeAdd(newStamp->mEntry);
    }

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
