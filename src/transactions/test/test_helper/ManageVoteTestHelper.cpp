#include "ManageVoteTestHelper.h"
#include "transactions/voting/manage_vote/ManageVoteOpFrame.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
ManageVoteTestHelper::ManageVoteTestHelper(
    TestManager::pointer testManager) : TxHelper(testManager)
{
}

Operation ManageVoteTestBuilder::buildOp() {
    Operation op;
    op.body.type(OperationType::MANAGE_VOTE);
    ManageVoteOp &manageVote = op.body.manageVoteOp();
    manageVote.data.action(action);
    switch (action) {
        case ManageVoteAction::CREATE:
            manageVote.data.createData() = create;
            break;
        case ManageVoteAction::REMOVE:
            manageVote.data.removeData() = remove;
            break;
    }

    return op;
}


ManageVoteTestBuilder ManageVoteTestBuilder::setAction(ManageVoteAction action)
{
    auto newBuilder = copy();
    newBuilder.action = action;
    return newBuilder;
}

ManageVoteTestBuilder ManageVoteTestBuilder::setCreateVoteData(CreateVoteData data)
{
    auto newBuilder = copy();
    newBuilder.create = data;
    return newBuilder;
}

ManageVoteTestBuilder ManageVoteTestBuilder::setRemoveVoteData(RemoveVoteData data)
{
    auto newBuilder = copy();
    newBuilder.remove= data;
    return newBuilder;
}

ManageVoteTestBuilder ManageVoteTestBuilder::setResultCode(ManageVoteResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedResult = expectedResult;
    return newBuilder;
}
ManageVoteTestBuilder ManageVoteTestBuilder::setTxResultCode(TransactionResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedTxResult = expectedResult;
    return newBuilder;
}

ManageVoteResult
ManageVoteTestHelper::applyTx(ManageVoteTestBuilder builder)
{
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == builder.operationResultCode);

    if (opResult.code() != OperationResultCode::opINNER)
    {
        return ManageVoteResult{};
    }

    REQUIRE(opResult.tr().manageVoteResult().code() == builder.expectedResult);

    return opResult.tr().manageVoteResult();
}

}
}
