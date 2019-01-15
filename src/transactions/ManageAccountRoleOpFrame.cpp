#include "ManageAccountRoleOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelperImpl.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include <xdr/Stellar-operation-manage-account-role.h>

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
    if (!storageHelper.getLedgerDelta())
    {
        throw std::runtime_error(
            "Unable to create account role without ledger");
    }
    LedgerDelta& delta = *storageHelper.getLedgerDelta();

    auto newAccountRoleID =
        delta.getHeaderFrame().generateID(LedgerEntryType::ACCOUNT_ROLE);
    auto frame = AccountRoleFrame::createNew(newAccountRoleID,
                                             mManageAccountRole.data.createData());

    storageHelper.getAccountRoleHelper().storeAdd(frame->mEntry);

    innerResult().code(ManageAccountRoleResultCode::SUCCESS);
    innerResult().success().roleID = newAccountRoleID;
    return true;
}

bool
ManageAccountRoleOpFrame::deleteAccountRole(Application& app,
                                            StorageHelper& storageHelper)
{
    auto& data = mManageAccountRole.data.removeData();

    LedgerKey ledgerKey;
    ledgerKey.type(LedgerEntryType::ACCOUNT_ROLE);
    ledgerKey.accountRole().id = data.accountRoleID;

    auto& accountRoleHelper = storageHelper.getAccountRoleHelper();
    auto result = accountRoleHelper.storeLoad(ledgerKey);

    if (result)
    {
        accountRoleHelper.storeDelete(ledgerKey);

        innerResult().code(ManageAccountRoleResultCode::SUCCESS);
        innerResult().success().roleID = data.accountRoleID;
        return true;
    }
    else
    {
        innerResult().code(ManageAccountRoleResultCode::NOT_FOUND);
        return false;
    }
}

bool
ManageAccountRoleOpFrame::doApply(Application& app,
                                  StorageHelper& storageHelper,
                                  LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();

    switch (mManageAccountRole.data.action())
    {
    case ManageAccountRoleAction::CREATE:
        return createAccountRole(app, storageHelper);
    case ManageAccountRoleAction::REMOVE:
        return deleteAccountRole(app, storageHelper);
    default:
        throw std::runtime_error("Unknown action.");
    }
}

bool
ManageAccountRoleOpFrame::doCheckValid(Application& app)
{
    return true;
}
} // namespace stellar