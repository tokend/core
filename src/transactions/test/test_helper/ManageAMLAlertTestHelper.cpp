#include "ManageAMLAlertTestHelper.h"
#include "test/test_marshaler.h"
#include "CheckSaleStateTestHelper.h"
#include "ledger/BalanceHelperLegacy.h"

namespace stellar
{

namespace txtest
{

    ManageAMLAlertTestHelper::ManageAMLAlertTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
    {
    }

TransactionFramePtr ManageAMLAlertTestHelper::createAmlAlertTx(Account& source, const BalanceID balance, const uint64 amount,
    std::string creatorDetails, std::string reference, uint32_t* allTasks)
{
    Operation op;
    op.body.type(OperationType::CREATE_AML_ALERT);
    op.body.createAMLAlertRequestOp().reference = reference;
    if (allTasks){
        op.body.createAMLAlertRequestOp().allTasks.activate() = *allTasks;
    }
    auto& request = op.body.createAMLAlertRequestOp().amlAlertRequest;
    request.amount = amount;
    request.balanceID = balance;
    request.creatorDetails = creatorDetails;
    return txFromOperation(source, op);
}

CreateAMLAlertRequestResult ManageAMLAlertTestHelper::applyCreateAmlAlert(
    Account& source, const BalanceID balance, uint64 amount, const std::string reason, const std::string reference,
    uint32_t *allTasks,
    CreateAMLAlertRequestResultCode expectedResultCode,
    OperationResultCode expectedOpResultCode)
{
    auto tx = createAmlAlertTx(source, balance, amount, reason, reference, allTasks);
    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(tx, stateBeforeOps);
    auto txResult = tx->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpResultCode);
    if (opResult.code() != OperationResultCode::opINNER)
    {
        return CreateAMLAlertRequestResult();
    }
    const auto amlAlertResult = opResult.tr().createAMLAlertRequestResult();
    auto actualResultCode = amlAlertResult.code();
    REQUIRE(actualResultCode == expectedResultCode);


    if (actualResultCode != CreateAMLAlertRequestResultCode::SUCCESS)
    {
        return amlAlertResult;
    }

    REQUIRE(stateBeforeOps.size() == 1);
    const auto stateBeforeOp = stateBeforeOps[0];
    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);
    auto balanceBeforeTx = stateHelper.getBalance(balance);
    auto balanceAfterTx = BalanceHelperLegacy::Instance()->loadBalance(balance, mTestManager->getDB());
    REQUIRE(balanceBeforeTx->getAmount() == balanceAfterTx->getAmount() + amount);
    if (!amlAlertResult.success().fulfilled)
    {
        REQUIRE(balanceBeforeTx->getLocked() == balanceAfterTx->getLocked() - amount);
    }
    return amlAlertResult;
}
}

}
