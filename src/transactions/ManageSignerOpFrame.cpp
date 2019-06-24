#include <ledger/SignerRuleFrame.h>
#include "ManageSignerOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/SignerHelper.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/LedgerDelta.h"
#include "main/Application.h"

namespace stellar
{
ManageSignerOpFrame::ManageSignerOpFrame(const Operation &op,
        OperationResult &res, TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageSigner(op.body.manageSignerOp())
{
}

bool
ManageSignerOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                               std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::SIGNER),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageSignerOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                              std::vector<SignerRequirement> &result) const
{
    uint64_t roleID = 0;

    switch (mManageSigner.data.action()) {
        case ManageSignerAction::CREATE:
            roleID = mManageSigner.data.createData().roleID;
            break;
        case ManageSignerAction::UPDATE:
        {
            roleID = mManageSigner.data.updateData().roleID;
            // checking for rules which allows to change signer with such role
            auto signer = storageHelper.getSignerHelper().loadSigner(
                    mManageSigner.data.updateData().publicKey, getSourceID());
            if (!signer)
            {
                mResult.code(OperationResultCode::opNO_ENTRY);
                mResult.entryType() = LedgerEntryType::SIGNER;
                return false;
            }
            SignerRuleResource resource(LedgerEntryType::SIGNER);
            resource.signer().roleID = signer->getRoleID();
            result.emplace_back(resource, SignerRuleAction::MANAGE);
            break;
        }
        case ManageSignerAction::REMOVE:
        {
            auto signer = storageHelper.getSignerHelper().loadSigner(
                    mManageSigner.data.removeData().publicKey, getSourceID());
            if (!signer) {
                mResult.code(OperationResultCode::opNO_ENTRY);
                mResult.entryType() = LedgerEntryType::SIGNER;
                return false;
            }
            roleID = signer->getRoleID();
            break;
        }
        default:
            throw std::runtime_error("Unexpected manage signer action");
    }

    SignerRuleResource resource(LedgerEntryType::SIGNER);
    resource.signer().roleID = roleID;

    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

bool
ManageSignerOpFrame::doApply(Application &app, StorageHelper &storageHelper,
                             LedgerManager &ledgerManager)
{
    switch (mManageSigner.data.action())
    {
        case ManageSignerAction::CREATE:
            return createSigner(app, storageHelper);
        case ManageSignerAction::UPDATE:
            return updateSigner(app, storageHelper);
        case ManageSignerAction::REMOVE:
            return deleteSigner(app, storageHelper);
        default:
            throw std::runtime_error("Unexpected manage signer action");
    }
}

bool ManageSignerOpFrame::doCheckValid(Application &app)
{
    std::string details;
    uint32_t weight;

    switch (mManageSigner.data.action())
    {
        case ManageSignerAction::CREATE:
            details = mManageSigner.data.createData().details;
            weight = mManageSigner.data.createData().weight;
            break;
        case ManageSignerAction::UPDATE:
            details = mManageSigner.data.updateData().details;
            weight = mManageSigner.data.updateData().weight;
            break;
        case ManageSignerAction::REMOVE:
            return true;
        default:
            throw std::runtime_error("Unexpected manage signer action");
    }

    if (!isValidJson(details))
    {
        innerResult().code(ManageSignerResultCode::INVALID_DETAILS);
        return false;
    }

    if (weight > SignerRuleFrame::threshold)
    {
        innerResult().code(ManageSignerResultCode::INVALID_WEIGHT);
        return false;
    }

    return true;
}

bool
ManageSignerOpFrame::createSigner(Application &app, StorageHelper &storageHelper)
{
    auto data = mManageSigner.data.createData();

    auto& signerHelper = storageHelper.getSignerHelper();
    if (signerHelper.exists(data.publicKey, getSourceID()))
    {
        innerResult().code(ManageSignerResultCode::ALREADY_EXISTS);
        return false;
    }

    auto& signerRoleHelper = storageHelper.getSignerRoleHelper();
    if (!signerRoleHelper.exists(data.roleID))
    {
        innerResult().code(ManageSignerResultCode::NO_SUCH_ROLE);
        return false;
    }

    LedgerEntry le;
    le.data.type(LedgerEntryType::SIGNER);
    auto& signerEntry = le.data.signer();
    signerEntry.accountID = getSourceID();
    signerEntry.pubKey = data.publicKey;
    signerEntry.roleID = data.roleID;
    signerEntry.weight = data.weight;
    signerEntry.identity = data.identity;
    signerEntry.details = data.details;

    signerHelper.storeAdd(le);

    if (getSourceID() == app.getAdminID())
    {
        if (!checkAdminCount(app, storageHelper))
        {
            innerResult().code(
                ManageSignerResultCode::NUMBER_OF_ADMINS_EXCEEDS_LICENSE);
            return false;
        }
    }

    innerResult().code(ManageSignerResultCode::SUCCESS);

    return true;
}

bool
ManageSignerOpFrame::updateSigner(Application &app, StorageHelper &storageHelper)
{
    auto data = mManageSigner.data.updateData();

    auto& signerHelper = storageHelper.getSignerHelper();

    auto signerFrame = signerHelper.loadSigner(data.publicKey, getSourceID());
    if (!signerFrame)
    {
        innerResult().code(ManageSignerResultCode::NOT_FOUND);
        return false;
    }

    auto& signerRoleHelper = storageHelper.getSignerRoleHelper();
    if (!signerRoleHelper.exists(data.roleID))
    {
        innerResult().code(ManageSignerResultCode::NO_SUCH_ROLE);
        return false;
    }

    auto& signerEntry = signerFrame->getEntry();
    signerEntry.roleID = data.roleID;
    signerEntry.weight = data.weight;
    signerEntry.identity = data.identity;
    signerEntry.details = data.details;

    signerHelper.storeChange(signerFrame->mEntry);

    innerResult().code(ManageSignerResultCode::SUCCESS);

    return true;
}

bool
ManageSignerOpFrame::deleteSigner(Application &app, StorageHelper &storageHelper)
{
    LedgerKey key(LedgerEntryType::SIGNER);
    key.signer().pubKey = mManageSigner.data.removeData().publicKey;
    key.signer().accountID = getSourceID();

    auto& signerHelper = storageHelper.getSignerHelper();
    if (!signerHelper.exists(key))
    {
        innerResult().code(ManageSignerResultCode::NOT_FOUND);
        return false;
    }

    signerHelper.storeDelete(key);
    if (app.getLedgerManager().shouldUse(LedgerVersion::FIX_SIGNER_CHANGES_REMOVE))
    {
        storageHelper.mustGetLedgerDelta().deleteEntry(key);
    }

    innerResult().code(ManageSignerResultCode::SUCCESS);

    return true;
}
}
