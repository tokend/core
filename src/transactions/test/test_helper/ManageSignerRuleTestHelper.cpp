#include "transactions/manage_role_rule/ManageSignerRuleOpFrame.h"
#include "ManageSignerRuleTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
ManageSignerRuleTestHelper::ManageSignerRuleTestHelper(
        TestManager::pointer testManager)
        : TxHelper(testManager)
{
}

ManageSignerRuleOp
ManageSignerRuleTestHelper::buildCreateRuleOp(SignerRuleResource resource,
                                              std::string action, bool isForbid,
                                              bool isDefault, bool isReadOnly)
{
    ManageSignerRuleOp result;
    result.data.action(ManageSignerRuleAction::CREATE);
    auto& data = result.data.createData();
    data.resource = resource;
    data.action = action;
    data.isForbid = isForbid;
    data.isDefault = isDefault;
    data.isReadOnly = isReadOnly;
    data.details = R"({"from" : "tests"})";

    return result;
}

ManageSignerRuleOp
ManageSignerRuleTestHelper::buildUpdateRuleOp(uint64_t id,
                                              SignerRuleResource resource,
                                              std::string action, bool isForbid,
                                              bool isDefault)
{
    ManageSignerRuleOp result;
    result.data.action(ManageSignerRuleAction::UPDATE);
    auto& data = result.data.updateData();
    data.ruleID = id;
    data.resource = resource;
    data.action = action;
    data.isForbid = isForbid;
    data.isDefault = isDefault;
    data.details = R"({"from" : "tests"})";

    return result;
}

ManageSignerRuleOp
ManageSignerRuleTestHelper::buildRemoveRuleOp(uint64_t ruleID)
{
    ManageSignerRuleOp result;
    result.data.action(ManageSignerRuleAction::REMOVE);
    auto& data = result.data.removeData();
    data.ruleID = ruleID;

    return result;
}

TransactionFramePtr
ManageSignerRuleTestHelper::createTx(Account &source, ManageSignerRuleOp op,
                                     Account* signer)
{
    Operation opBase;
    opBase.body.type(OperationType::MANAGE_SIGNER_RULE);
    opBase.body.manageSignerRuleOp() = op;

    return txFromOperation(source, opBase, signer);
}

ManageSignerRuleResult ManageSignerRuleTestHelper::applyTx(Account &source,
        ManageSignerRuleOp &op,
        ManageSignerRuleResultCode expectedResult,
        OperationResultCode operationResultCode,
        TransactionResultCode expectedTxResult, Account* signer)
{
    auto txFrame = createTx(source, op, signer);

    mTestManager->applyCheck(txFrame);
    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.code() == expectedTxResult);

    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == operationResultCode);

    if (operationResultCode != OperationResultCode::opINNER)
    {
        return ManageSignerRuleResult{};
    }

    auto actualResultCode = ManageSignerRuleOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == expectedResult);

    if (expectedResult != ManageSignerRuleResultCode::SUCCESS)
    {
        return ManageSignerRuleResult{};
    }

    return opResult.tr().manageSignerRuleResult();
}

}
}