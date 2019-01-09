#include "ManageAccountRolePermissionOpFrame.h"
#include "database/Database.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

ManageAccountRolePermissionOpFrame::ManageAccountRolePermissionOpFrame(
    const Operation& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageAccountRolePermission(mOperation.body.manageAccountRolePermissionOp())
{
}

bool
ManageAccountRolePermissionOpFrame::doApply(Application& app,
                                            StorageHelper& storageHelper,
                                            LedgerManager& ledgerManager)
{
    switch (mManageAccountRolePermission.data.action())
    {
    case ManageAccountRolePermissionOpAction::CREATE:
    case ManageAccountRolePermissionOpAction::UPDATE:
        return createOrUpdatePolicy(app, storageHelper);
    case ManageAccountRolePermissionOpAction::REMOVE:
        return deleteAccountPolicy(app, storageHelper);
    default:
        throw std::runtime_error("Unknown action.");
    }
}

bool
ManageAccountRolePermissionOpFrame::doCheckValid(Application& app)
{
    return isValidEnumValue(mManageAccountRolePermission.data.action());
}

SourceDetails
ManageAccountRolePermissionOpFrame::getSourceAccountDetails(
    std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
    int32_t ledgerVersion) const
{
    // allow for any user
    return SourceDetails(
        getAllAccountTypes(), mSourceAccount->getMediumThreshold(),
        static_cast<int32_t>(SignerType::ACCOUNT_ROLE_PERMISSION_MANAGER));
}

std::unordered_map<AccountID, CounterpartyDetails>
ManageAccountRolePermissionOpFrame::getCounterpartyDetails(
    Database& db, LedgerDelta* delta) const
{
    return {};
}

bool
ManageAccountRolePermissionOpFrame::createOrUpdatePolicy(
    Application& app, StorageHelper& storageHelper)
{
    if (!storageHelper.getLedgerDelta())
    {
        throw std::runtime_error("Unable to process policy without ledger.");
    }
    LedgerHeaderFrame& headerFrame =
        storageHelper.getLedgerDelta()->getHeaderFrame();
    auto& helper = storageHelper.getAccountRuleHelper();

    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);

    auto& lePermission = le.data.accountRolePermission();
    switch (mManageAccountRolePermission.data.action())
    {
    case ManageAccountRolePermissionOpAction::CREATE:
        lePermission.id = headerFrame.generateID(LedgerEntryType::ACCOUNT_RULE);
        lePermission.resource =
            mManageAccountRolePermission.data.createData().resource;
        lePermission.action =
            mManageAccountRolePermission.data.createData().action;
        lePermission.isForbid = mManageAccountRolePermission.data.createData().isForbid;
        lePermission.details = mManageAccountRolePermission.data.createData().details;
        break;
    case ManageAccountRolePermissionOpAction::UPDATE:
        lePermission.id =
            mManageAccountRolePermission.data.updateData().accountRuleID;
        lePermission.resource =
                mManageAccountRolePermission.data.updateData().resource;
        lePermission.action =
                mManageAccountRolePermission.data.updateData().action;
        lePermission.isForbid = mManageAccountRolePermission.data.updateData().isForbid;
        lePermission.details = mManageAccountRolePermission.data.updateData().details;
        break;
    default:
        throw std::runtime_error("Unexpected action type.");
    }

    innerResult().code(ManageAccountRolePermissionResultCode::SUCCESS);
    innerResult().success().permissionID = le.data.accountRolePermission().id;

    if (helper.exists(helper.getLedgerKey(le)))
    {
        helper.storeChange(le);
    }
    else
    {
        helper.storeAdd(le);
    }

    return true;
}

bool
ManageAccountRolePermissionOpFrame::deleteAccountPolicy(
    Application& app, StorageHelper& storageHelper)
{
    LedgerKey key;
    key.type(LedgerEntryType::ACCOUNT_RULE);
    key.accountRolePermission().id = mManageAccountRolePermission.data.removeData().accountRuleID;

    auto frame = storageHelper.getAccountRuleHelper().storeLoad(key);
    if (!frame)
    {
        innerResult().code(ManageAccountRolePermissionResultCode::NOT_FOUND);
        return false;
    }

    storageHelper.getAccountRuleHelper().storeDelete(frame->getKey());
    innerResult().code(ManageAccountRolePermissionResultCode::SUCCESS);
    innerResult().success().permissionID = key.accountRolePermission().id;
    return true;
}

} // namespace stellar