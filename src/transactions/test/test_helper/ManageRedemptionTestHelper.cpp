#include "ManageRedemptionTestHelper.h"
#include "test/test_marshaler.h"
#include "StateBeforeTxHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"

namespace stellar {

namespace txtest {

ManageRedemptionTestHelper::ManageRedemptionTestHelper(TestManager::pointer testManager) : TxHelper(
    testManager) {}

TransactionFramePtr ManageRedemptionTestHelper::createRedemptionTx(Account &opSource,
                                                                   BalanceID sourceBalanceID,
                                                                   AccountID destinationAccountID,
                                                                   uint64 amount,
                                                                   std::string creatorDetails,
                                                                   std::string reference, uint32_t *allTasks) {
    Operation op;
    op.body.type(OperationType::CREATE_REDEMPTION_REQUEST);
    op.body.createRedemptionRequestOp().reference = reference;
    if (allTasks) {
        op.body.createRedemptionRequestOp().allTasks.activate() = *allTasks;
    }
    auto &request = op.body.createRedemptionRequestOp().redemptionRequest;
    request.sourceBalanceID = sourceBalanceID;
    request.destination = destinationAccountID;
    request.amount = amount;
    request.creatorDetails = creatorDetails;
    return txFromOperation(opSource, op);
}

CreateRedemptionRequestResult ManageRedemptionTestHelper::applyCreateRedemption(
        Account &opSource,
        BalanceID sourceBalanceID, AccountID destinationAccountID, uint64 amount,
        std::string reason, std::string reference, uint32_t *allTasks,
        CreateRedemptionRequestResultCode expectedResultCode,
        OperationResultCode expectedOpResultCode) {

    auto tx = createRedemptionTx(opSource, sourceBalanceID, destinationAccountID, amount, reason, reference,
                                 allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(tx, stateBeforeOps);
    auto txResult = tx->getResult();
    auto opResult = txResult.result.results()[0];
    REQUIRE(opResult.code() == expectedOpResultCode);
    if (opResult.code() != OperationResultCode::opINNER) {
        return CreateRedemptionRequestResult();
    }

    const auto createRedemptionRequestResult = opResult.tr().createRedemptionRequestResult();
    auto actualResultCode = createRedemptionRequestResult.code();
    REQUIRE(actualResultCode == expectedResultCode);

    if (actualResultCode != CreateRedemptionRequestResultCode::SUCCESS) {
        return createRedemptionRequestResult;
    }

    REQUIRE(stateBeforeOps.size() == 1);
    const auto stateBeforeOp = stateBeforeOps[0];
    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);

    REQUIRE(!createRedemptionRequestResult.redemptionResponse().fulfilled);

    auto srcBalanceBeforeTx = stateHelper.getBalance(sourceBalanceID);

    auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();

    auto srcBalanceAfterTx = balanceHelper.loadBalance(sourceBalanceID);
    REQUIRE(srcBalanceBeforeTx->getLocked() == srcBalanceAfterTx->getLocked() - amount);

    auto dstBalance = balanceHelper.loadBalance(destinationAccountID, srcBalanceBeforeTx->getAsset());
    auto destinationBalanceID = dstBalance->getBalanceID();
    auto dstBalanceBeforeTx = stateHelper.getBalance(destinationBalanceID);
    auto dstBalanceAfterTx = balanceHelper.loadBalance(destinationBalanceID);

    REQUIRE(dstBalanceBeforeTx->getAmount() == dstBalanceAfterTx->getAmount());

    return createRedemptionRequestResult;
}

}
}