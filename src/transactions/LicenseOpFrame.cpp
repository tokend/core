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

bool
LicenseOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::LICENSE);

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    return true;
}

bool
LicenseOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                               std::vector<SignerRequirement> &result) const
{
    SignerRuleResource resource(LedgerEntryType::LICENSE);

    result.emplace_back(resource, SignerRuleAction::CREATE);
    return true;
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
    auto& stampHelper = storageHelper.getStampHelper();
    auto& licenseHelper = storageHelper.getLicenseHelper();
    if (!stampHelper.exists(mLicense.ledgerHash, mLicense.prevLicenseHash))
    {
        innerResult().code(LicenseResultCode::INVALID_STAMP);
        return false;
    }

    auto newLicense = LicenseFrame::createNew(mLicense.ledgerHash,
                                              mLicense.prevLicenseHash, mLicense.adminCount, mLicense.dueDate, mLicense.signatures);

    if(!newLicense->isSignatureValid(app))
    {
        innerResult().code(LicenseResultCode::INVALID_SIGNATURE);
        return false;
    }

    licenseHelper.storeAdd(newLicense->mEntry);
    innerResult().code(LicenseResultCode::SUCCESS);
    return true;
}


bool
LicenseOpFrame::doCheckValid(Application& app)
{
    if (app.getLedgerManager().getCloseTime() >= mLicense.dueDate)
    {
        innerResult().code(LicenseResultCode::INVALID_DUE_DATE);
        return false;
    }

    return true;
}

} // namespace stellar
