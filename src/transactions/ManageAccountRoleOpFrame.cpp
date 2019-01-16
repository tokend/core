#include "ManageAccountRoleOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelperImpl.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"

namespace stellar
{
using namespace std;

ManageAccountRoleOpFrame::ManageAccountRoleOpFrame(Operation const& op,
                                                   OperationResult& res,
                                                   TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mManageAccountRole(mOperation.body.manageAccountRoleOp())
{
}

bool
ManageAccountRoleOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                    std::vector<OperationCondition> &result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ACCOUNT_ROLE), "manage", mSourceAccount);

    return true;
}

bool
ManageAccountRoleOpFrame::createAccountRole(Application& app,
                                            StorageHelper& storageHelper)
{
    auto& headerFrame = storageHelper.mustGetLedgerDelta().getHeaderFrame();

    auto newAccountRoleID = headerFrame.generateID(LedgerEntryType::ACCOUNT_ROLE);
    auto frame = AccountRoleFrame::createNew(newAccountRoleID,
                                             mManageAccountRole.data.createData());

    storageHelper.getAccountRoleHelper().storeAdd(frame->mEntry);

    innerResult().code(ManageAccountRoleResultCode::SUCCESS);
    innerResult().success().roleID = newAccountRoleID;

    return true;
}

bool
ManageAccountRoleOpFrame::updateAccountRole(Application& app,
                                            StorageHelper& storageHelper)
{
    auto& helper = storageHelper.getAccountRoleHelper();
    auto updateData = mManageAccountRole.data.updateData();

    auto accountRole = helper.loadAccountRole(updateData.roleID);
    if (!accountRole)
    {
        innerResult().code(ManageAccountRoleResultCode::NOT_FOUND);
        return false;
    }

    auto& roleEntry = accountRole->getAccountRole();
    roleEntry.ruleIDs = updateData.accountRuleIDs;
    roleEntry.details = updateData.details;

    helper.storeChange(accountRole->mEntry);

    innerResult().code(ManageAccountRoleResultCode::SUCCESS);
    innerResult().success().roleID = updateData.roleID;

    return true;
}

bool
ManageAccountRoleOpFrame::deleteAccountRole(Application& app,
                                            StorageHelper& storageHelper)
{
    auto& data = mManageAccountRole.data.removeData();

    if (AccountHelper::Instance()->isRoleIDUsed(data.accountRoleID, storageHelper.getDatabase()))
    {
        innerResult().code(ManageAccountRoleResultCode::ROLE_IS_USED);
        return false;
    }

    LedgerKey ledgerKey;
    ledgerKey.type(LedgerEntryType::ACCOUNT_ROLE);
    ledgerKey.accountRole().id = data.accountRoleID;

    auto& accountRoleHelper = storageHelper.getAccountRoleHelper();

    if (!accountRoleHelper.exists(ledgerKey))
    {
        innerResult().code(ManageAccountRoleResultCode::NOT_FOUND);
        return false;
    }

    accountRoleHelper.storeDelete(ledgerKey);


    innerResult().code(ManageAccountRoleResultCode::SUCCESS);
    innerResult().success().roleID = data.accountRoleID;

    return true;
}

bool
ManageAccountRoleOpFrame::doApply(Application& app,
                                  StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    switch (mManageAccountRole.data.action())
    {
    case ManageAccountRoleAction::CREATE:
        return createAccountRole(app, storageHelper);
    case ManageAccountRoleAction::UPDATE:
        return updateAccountRole(app, storageHelper);
    case ManageAccountRoleAction::REMOVE:
        return deleteAccountRole(app, storageHelper);
    default:
        throw std::runtime_error("Unknown action in manage account role");
    }
}

bool
ManageAccountRoleOpFrame::doCheckValid(Application& app)
{
    switch (mManageAccountRole.data.action())
    {
        case ManageAccountRoleAction::CREATE:
            return isValidJson(mManageAccountRole.data.createData().details);
        case ManageAccountRoleAction::UPDATE:
            return isValidJson(mManageAccountRole.data.updateData().details);
        case ManageAccountRoleAction::REMOVE:
            return true;
        default:
            throw std::runtime_error("Unexpected action in manage account role");
    }
}
} // namespace stellar