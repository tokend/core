#include <transactions/manage_role_rule/ManageSignerRoleOpFrame.h>
#include "ManageSignerRoleTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
ManageSignerRoleTestHelper::ManageSignerRoleTestHelper(
        TestManager::pointer testManager) : TxHelper(testManager)
{
}

ManageSignerRoleOp
ManageSignerRoleTestHelper::buildCreateRoleOp(const std::string &details,
        std::vector<uint64_t> ruleIDs, bool isReadOnly)
{
    ManageSignerRoleOp op;
    op.data.action(ManageSignerRoleAction::CREATE);
    auto& data = op.data.createData();
    data.ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());
    data.isReadOnly = isReadOnly;
    data.details = details;

    return op;
}

ManageSignerRoleOp
ManageSignerRoleTestHelper::buildUpdateRoleOp(uint64_t roleID,
        const std::string &details, std::vector<uint64_t> ruleIDs)
{
    ManageSignerRoleOp op;
    op.data.action(ManageSignerRoleAction::UPDATE);
    auto& data = op.data.updateData();
    data.roleID = roleID;
    data.ruleIDs.assign(ruleIDs.begin(), ruleIDs.end());
    data.details = details;

    return op;
}

ManageSignerRoleOp
ManageSignerRoleTestHelper::buildRemoveRoleOp(uint64_t roleID)
{
    ManageSignerRoleOp op;
    op.data.action(ManageSignerRoleAction::REMOVE);
    auto& data = op.data.removeData();
    data.roleID = roleID;

    return op;
}

TransactionFramePtr
ManageSignerRoleTestHelper::createSignerRoleTx(Account &source,
                               const ManageSignerRoleOp &op, Account* signer)
{
    Operation baseOp;
    baseOp.body.type(OperationType::MANAGE_SIGNER_ROLE);
    baseOp.body.manageSignerRoleOp() = op;
    return txFromOperation(source, baseOp, signer);
}

ManageSignerRoleResult
ManageSignerRoleTestHelper::applyTx(Account &source, const ManageSignerRoleOp &op,
        ManageSignerRoleResultCode expectedResultCode,
        OperationResultCode operationResultCode,
        TransactionResultCode txResultCode, Account* signer)
{
    TransactionFramePtr txFrame = createSignerRoleTx(source, op, signer);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == txResultCode);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == operationResultCode);

    if (operationResultCode != OperationResultCode::opINNER)
    {
        return ManageSignerRoleResult{};
    }

    auto actualResultCode = ManageSignerRoleOpFrame::getInnerCode(opResult);

    REQUIRE(actualResultCode == expectedResultCode);

    auto txFee = mTestManager->getLedgerManager().getTxFee();
    REQUIRE(txResult.feeCharged == txFee);

    return opResult.tr().manageSignerRoleResult();
}

}
}