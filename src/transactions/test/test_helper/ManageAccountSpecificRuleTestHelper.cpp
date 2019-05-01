#include "ManageAccountSpecificRuleTestHelper.h"
#include "ledger/AccountRuleHelperImpl.h"
#include "ledger/StorageHelperImpl.h"
#include "transactions/manage_specific_rule/ManageAccountSpecificRuleOpFrame.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{

using xdr::operator==;

ManageAccountSpecificRuleTestHelper::ManageAccountSpecificRuleTestHelper(
        TestManager::pointer const& testManager)
        : TxHelper(testManager)
{
}

TransactionFramePtr
ManageAccountSpecificRuleTestHelper::createManageRuleTx(Account &source,
        ManageAccountSpecificRuleOp const& opBody)
{
    Operation op(nullptr, OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE);
    op.body.manageAccountSpecificRuleOp() = opBody;

    return TxHelper::txFromOperation(source, op, nullptr);
}

ManageAccountSpecificRuleResult
ManageAccountSpecificRuleTestHelper::applyTx(Account &source,
        ManageAccountSpecificRuleOp const& op,
        ManageAccountSpecificRuleResultCode expectedResult,
        TransactionResultCode expectedTxResult)
{
    TransactionFramePtr txFrame = createManageRuleTx(source, op);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == expectedTxResult);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == OperationResultCode::opINNER);

    auto actualResult = ManageAccountSpecificRuleOpFrame::getInnerCode(opResult);

    REQUIRE(actualResult == expectedResult);

    auto result = opResult.tr().manageAccountSpecificRuleResult();

    if (actualResult != ManageAccountSpecificRuleResultCode::SUCCESS)
    {
        return result;
    }

    /*StorageHelperImpl storageHelperImpl(mTestManager->getDB(), nullptr);
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
    }*/

    return result;
}

ManageAccountSpecificRuleResult
ManageAccountSpecificRuleTestHelper::applyTx(Account &source, uint64_t ruleID,
        ManageAccountSpecificRuleResultCode expectedResult,
        TransactionResultCode expectedTxResult)
{
    ManageAccountSpecificRuleOp op(ManageAccountSpecificRuleAction::REMOVE, LedgerVersion::EMPTY_VERSION);
    op.data.removeData().ruleID = ruleID;

    return applyTx(source, op, expectedResult, expectedTxResult);
}

ManageAccountSpecificRuleResult
ManageAccountSpecificRuleTestHelper::applyTx(Account &source,
        LedgerKey const& ledgerKey, bool forbids, AccountID *accountID,
        ManageAccountSpecificRuleResultCode expectedResult,
        TransactionResultCode expectedTxResult)
{
    ManageAccountSpecificRuleOp op(ManageAccountSpecificRuleAction::CREATE, LedgerVersion::EMPTY_VERSION);
    auto& data = op.data.createData();

    data.ledgerKey = ledgerKey;
    data.forbids = forbids;
    if (accountID != nullptr)
    {
        data.accountID.activate() = *accountID;
    }

    return applyTx(source, op, expectedResult, expectedTxResult);
}

} // namespace txtest
} // namespace stellar
