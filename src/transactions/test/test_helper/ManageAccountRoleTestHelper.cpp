#include "ManageAccountRoleTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/manage_role_rule/ManageAccountRoleOpFrame.h"
#include "ManageAccountRuleTestHelper.h"

namespace stellar
{
namespace txtest
{

ManageAccountRoleTestHelper::ManageAccountRoleTestHelper(
    TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ManageAccountRoleOp
ManageAccountRoleTestHelper::buildCreateRoleOp(const std::string &name,
                                               std::vector<uint64_t> ruleIDs)
{
    ManageAccountRoleOp opData;
    opData.data.action(ManageAccountRoleAction::CREATE);
    opData.data.createData().details = name;
    opData.data.createData().ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());
    return opData;
}

ManageAccountRoleOp
ManageAccountRoleTestHelper::buildUpdateRoleOp(uint64_t accountRoleID,
                                               const std::string &name,
                                               std::vector<uint64_t> ruleIDs)
{
    ManageAccountRoleOp opData;
    opData.data.action(ManageAccountRoleAction::UPDATE);
    opData.data.updateData().details = name;
    opData.data.updateData().roleID = accountRoleID;
    opData.data.updateData().ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());
    return opData;
}

ManageAccountRoleOp
ManageAccountRoleTestHelper::buildRemoveRoleOp(uint64_t accountRoleID)
{
    ManageAccountRoleOp opData;
    opData.data.action(ManageAccountRoleAction::REMOVE);
    opData.data.removeData().roleID = accountRoleID;
    return opData;
}

TransactionFramePtr
ManageAccountRoleTestHelper::createAccountRoleTx(Account& source,
                                                 const ManageAccountRoleOp& op)
{
    Operation baseOp;
    baseOp.body.type(OperationType::MANAGE_ACCOUNT_ROLE);
    baseOp.body.manageAccountRoleOp() = op;
    return txFromOperation(source, baseOp, nullptr);
}

ManageAccountRoleResult
ManageAccountRoleTestHelper::applyTx(
        Account &source, const ManageAccountRoleOp &op,
        ManageAccountRoleResultCode expectedResultCode)
{
    auto& db = mTestManager->getDB();

    TransactionFramePtr txFrame;
    txFrame = createAccountRoleTx(source, op);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto actualResultCode =
        ManageAccountRoleOpFrame::getInnerCode(txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto txFee = mTestManager->getApp().getLedgerManager().getTxFee();
    REQUIRE(txResult.feeCharged == txFee);

    auto opResult = txResult.result.results()[0].tr().manageAccountRoleResult();

    return opResult;
}

uint64_t
ManageAccountRoleTestHelper::createTxSenderRole(Account &root)
{
    ManageAccountRuleTestHelper manageAccountRuleTestHelper(mTestManager);

    auto ruleEntry = manageAccountRuleTestHelper.createAccountRuleEntry(0,
            AccountRuleResource(LedgerEntryType::TRANSACTION), AccountRuleAction::SEND, false);

    auto ruleID = manageAccountRuleTestHelper.applyTx(root, ruleEntry,
            ManageAccountRuleAction::CREATE).success().ruleID;

    auto op = buildCreateRoleOp(R"({"name":"tx_sender"})", {ruleID});

    return applyTx(root, op).success().roleID;
}
} // namespace txtest
} // namespace stellar