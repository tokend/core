#include "ManageAccountRolePermissionTestHelper.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/StorageHelperImpl.h"
#include "transactions/ManageAccountRolePermissionOpFrame.h"
#include <lib/catch.hpp>

namespace stellar
{
namespace txtest
{

using xdr::operator==;

ManageAccountRolePermissionTestHelper::ManageAccountRolePermissionTestHelper(
    TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

TransactionFramePtr
ManageAccountRolePermissionTestHelper::createSetAccountRolePermissionTx(
    Account& source, AccountRuleEntry permissionEntry,
    ManageAccountRolePermissionOpAction action)
{
    Operation op;
    op.body.type(OperationType::MANAGE_ACCOUNT_RULE);
    ManageAccountRuleOp& manageAccountRolePermissionOp =
        op.body.manageAccountRolePermissionOp();
    manageAccountRolePermissionOp.data.action(action);

    switch (action)
    {
    case ManageAccountRolePermissionOpAction::CREATE:
        manageAccountRolePermissionOp.data.createData().resource = permissionEntry.resource;
        manageAccountRolePermissionOp.data.createData().action = permissionEntry.action;
        manageAccountRolePermissionOp.data.createData().isForbid = permissionEntry.isForbid;
        manageAccountRolePermissionOp.data.createData().details = permissionEntry.details;
        break;
    case ManageAccountRolePermissionOpAction::UPDATE:
        manageAccountRolePermissionOp.data.updateData().accountRuleID = permissionEntry.id;
        manageAccountRolePermissionOp.data.updateData().resource = permissionEntry.resource;
        manageAccountRolePermissionOp.data.updateData().action = permissionEntry.action;
        manageAccountRolePermissionOp.data.updateData().isForbid = permissionEntry.isForbid;
        manageAccountRolePermissionOp.data.updateData().details = permissionEntry.details;
        break;
    case ManageAccountRolePermissionOpAction::REMOVE:
        manageAccountRolePermissionOp.data.removeData().accountRuleID = permissionEntry.id;
        break;
    default:
        throw std::runtime_error("Unknown action");
    }
    manageAccountRolePermissionOp.ext.v(LedgerVersion::EMPTY_VERSION);

    return TxHelper::txFromOperation(source, op, nullptr);
}

ManageAccountRolePermissionResult
ManageAccountRolePermissionTestHelper::applySetIdentityPermissionTx(
    Account& source, AccountRuleEntry& permissionEntry,
    ManageAccountRolePermissionOpAction action,
    ManageAccountRolePermissionResultCode expectedResult)
{
    TransactionFramePtr txFrame =
        createSetAccountRolePermissionTx(source, permissionEntry, action);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == TransactionResultCode::txSUCCESS);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == OperationResultCode::opINNER);

    auto actualResult = ManageAccountRolePermissionOpFrame::getInnerCode(opResult);

    REQUIRE(actualResult == expectedResult);

    if (actualResult != ManageAccountRolePermissionResultCode::SUCCESS)
    {
        return ManageAccountRolePermissionResult();
    }

    ManageAccountRolePermissionResult result =
        txResult.result.results()[0].tr().manageAccountRolePermissionResult();

    StorageHelperImpl storageHelperImpl(mTestManager->getDB(), nullptr);
    static_cast<StorageHelper&>(storageHelperImpl).begin();
    AccountRuleHelperImpl rolePermissionHelper(storageHelperImpl);
    LedgerKey affectedPermissionKey;
    affectedPermissionKey.type(LedgerEntryType::ACCOUNT_RULE);
    affectedPermissionKey.accountRolePermission().id = result.success().permissionID;

    EntryFrame::pointer affectedPermission =
        static_cast<AccountRuleHelper&>(rolePermissionHelper)
            .storeLoad(affectedPermissionKey);
    if (action == ManageAccountRolePermissionOpAction::REMOVE)
    {
        REQUIRE(!affectedPermission);
    }
    else
    {
        auto affectedAccountRolePermission =
            std::dynamic_pointer_cast<AccountRuleFrame>(
                affectedPermission);
        REQUIRE(affectedAccountRolePermission);
        // update auto generated id of identity permission
        permissionEntry.id = affectedAccountRolePermission->getID();

        REQUIRE(affectedAccountRolePermission->getRuleEntry() ==
                permissionEntry);
    }

    return result;
}

AccountRuleEntry
ManageAccountRolePermissionTestHelper::createAccountRolePermissionEntry(
    uint64_t id, AccountRuleResource resource, std::string action, bool isForbid)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);
    auto permissionEntry = le.data.accountRolePermission();

    permissionEntry.id = id;
    permissionEntry.resource = resource;
    permissionEntry.action = action;
    permissionEntry.isForbid = isForbid;
    permissionEntry.details = "some_details";

    return permissionEntry;
}

} // namespace txtest
} // namespace stellar
