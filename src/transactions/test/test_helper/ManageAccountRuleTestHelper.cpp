#include "ManageAccountRuleTestHelper.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/StorageHelperImpl.h"
#include "transactions/manage_role_rule/ManageAccountRuleOpFrame.h"
#include <lib/catch.hpp>

namespace stellar
{
namespace txtest
{

using xdr::operator==;

ManageAccountRuleTestHelper::ManageAccountRuleTestHelper(
    TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

TransactionFramePtr
ManageAccountRuleTestHelper::createManageAccountRuleTx(
        Account &source, AccountRuleEntry permissionEntry,
        ManageAccountRuleAction action)
{
    Operation op;
    op.body.type(OperationType::MANAGE_ACCOUNT_RULE);
    ManageAccountRuleOp& manageAccountRolePermissionOp =
        op.body.manageAccountRuleOp();
    manageAccountRolePermissionOp.data.action(action);

    switch (action)
    {
    case ManageAccountRuleAction::CREATE:
        manageAccountRolePermissionOp.data.createData().resource = permissionEntry.resource;
        manageAccountRolePermissionOp.data.createData().action = permissionEntry.action;
        manageAccountRolePermissionOp.data.createData().isForbid = permissionEntry.isForbid;
        manageAccountRolePermissionOp.data.createData().details = permissionEntry.details;
        break;
    case ManageAccountRuleAction::UPDATE:
        manageAccountRolePermissionOp.data.updateData().accountRuleID = permissionEntry.id;
        manageAccountRolePermissionOp.data.updateData().resource = permissionEntry.resource;
        manageAccountRolePermissionOp.data.updateData().action = permissionEntry.action;
        manageAccountRolePermissionOp.data.updateData().isForbid = permissionEntry.isForbid;
        manageAccountRolePermissionOp.data.updateData().details = permissionEntry.details;
        break;
    case ManageAccountRuleAction::REMOVE:
        manageAccountRolePermissionOp.data.removeData().accountRuleID = permissionEntry.id;
        break;
    default:
        throw std::runtime_error("Unknown action");
    }
    manageAccountRolePermissionOp.ext.v(LedgerVersion::EMPTY_VERSION);

    return TxHelper::txFromOperation(source, op, nullptr);
}

ManageAccountRuleResult
ManageAccountRuleTestHelper::applyTx(
        Account &source, AccountRuleEntry &permissionEntry,
        ManageAccountRuleAction action,
        ManageAccountRuleResultCode expectedResult,
        TransactionResultCode expectedTxResult)
{
    TransactionFramePtr txFrame =
            createManageAccountRuleTx(source, permissionEntry, action);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == expectedTxResult);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == OperationResultCode::opINNER);

    auto actualResult = ManageAccountRuleOpFrame::getInnerCode(opResult);

    REQUIRE(actualResult == expectedResult);

    ManageAccountRuleResult result = opResult.tr().manageAccountRuleResult();

    if (actualResult != ManageAccountRuleResultCode::SUCCESS)
    {
        return result;
    }

    StorageHelperImpl storageHelperImpl(mTestManager->getDB(), nullptr);
    static_cast<StorageHelper&>(storageHelperImpl).begin();
    AccountRuleHelperImpl rolePermissionHelper(storageHelperImpl);
    LedgerKey affectedPermissionKey;
    affectedPermissionKey.type(LedgerEntryType::ACCOUNT_RULE);
    affectedPermissionKey.accountRule().id = result.success().ruleID;

    EntryFrame::pointer affectedPermission =
        static_cast<AccountRuleHelper&>(rolePermissionHelper)
            .storeLoad(affectedPermissionKey);
    if (action == ManageAccountRuleAction::REMOVE)
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
ManageAccountRuleTestHelper::createAccountRuleEntry(
        uint64_t id, AccountRuleResource resource, std::string action,
        bool isForbid)
{
    LedgerEntry le;
    le.data.type(LedgerEntryType::ACCOUNT_RULE);
    auto ruleEntry = le.data.accountRule();

    ruleEntry.id = id;
    ruleEntry.resource = resource;
    ruleEntry.action = action;
    ruleEntry.isForbid = isForbid;
    ruleEntry.details = "{\"data\": \"some_details\"}";

    return ruleEntry;
}

} // namespace txtest
} // namespace stellar
