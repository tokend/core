#include "ManagePollTestHelper.h"
#include "transactions/voting/manage_poll/ManagePollOpFrame.h"
#include "transactions/voting/manage_create_poll_request/ManageCreatePollRequestOpFrame.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{
ManagePollTestHelper::ManagePollTestHelper(
    TestManager::pointer testManager) : TxHelper(testManager)
{
}

Operation ManageCreatePollRequestTestBuilder::buildOp() {
    Operation op;
    op.body.type(OperationType::MANAGE_CREATE_POLL_REQUEST);
    ManageCreatePollRequestOp &manageCreatePollRequest = op.body.manageCreatePollRequestOp();
    manageCreatePollRequest.data.action(action);
    switch (action) {
        case ManageCreatePollRequestAction::CREATE:
            manageCreatePollRequest.data.createData() = create;
            break;
        case ManageCreatePollRequestAction::CANCEL:
            manageCreatePollRequest.data.cancelData() = cancel;
            break;
    }

    return op;
}


ManageCreatePollRequestTestBuilder ManageCreatePollRequestTestBuilder::setAction(ManageCreatePollRequestAction action)
{
    auto newBuilder = copy();
    newBuilder.action = action;
    return newBuilder;
}

ManageCreatePollRequestTestBuilder ManageCreatePollRequestTestBuilder::setCreateRequestData(CreatePollRequestData data)
{
    auto newBuilder = copy();
    newBuilder.create = data;
    return newBuilder;
}

ManageCreatePollRequestTestBuilder ManageCreatePollRequestTestBuilder::setCancelPollRequestData(CancelPollRequestData data)
{
    auto newBuilder = copy();
    newBuilder.cancel = data;
    return newBuilder;
}

ManageCreatePollRequestTestBuilder ManageCreatePollRequestTestBuilder::setResultCode(ManageCreatePollRequestResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedResult = expectedResult;
    return newBuilder;
}
ManageCreatePollRequestTestBuilder ManageCreatePollRequestTestBuilder::setTxResultCode(TransactionResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedTxResult = expectedResult;
    return newBuilder;
}

Operation ManagePollTestBuilder::buildOp() {
    Operation op;
    op.body.type(OperationType::MANAGE_POLL);
    ManagePollOp &managePoll = op.body.managePollOp();
    managePoll.pollID = pollID;
    managePoll.data.action(action);
    switch (action) {
        case ManagePollAction::CLOSE:
            managePoll.data.closePollData() = close;
            break;
        case ManagePollAction::UPDATE_END_TIME:
            managePoll.data.updateTimeData() = updateEndTime;
            break;
    }

    return op;
}


ManagePollTestBuilder ManagePollTestBuilder::setAction(ManagePollAction action)
{
    auto newBuilder = copy();
    newBuilder.action = action;
    return newBuilder;
}

ManagePollTestBuilder ManagePollTestBuilder::setPollID(uint64_t pollID)
{
    auto newBuilder = copy();
    newBuilder.pollID = pollID;
    return newBuilder;
}

ManagePollTestBuilder ManagePollTestBuilder::setClosePollData(ClosePollData data)
{
    auto newBuilder = copy();
    newBuilder.close = data;
    return newBuilder;
}

ManagePollTestBuilder ManagePollTestBuilder::setUpdateEndTimeData(UpdatePollEndTimeData data)
{
    auto newBuilder = copy();
    newBuilder.updateEndTime = data;
    return newBuilder;
}

ManagePollTestBuilder ManagePollTestBuilder::setResultCode(ManagePollResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedResult = expectedResult;
    return newBuilder;
}
ManagePollTestBuilder ManagePollTestBuilder::setTxResultCode(TransactionResultCode expectedResult)
{
    auto newBuilder = copy();
    newBuilder.expectedTxResult = expectedResult;
    return newBuilder;
}

ManagePollResult
ManagePollTestHelper::applyTx(ManagePollTestBuilder builder)
{
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == builder.operationResultCode);

    if (opResult.code() != OperationResultCode::opINNER)
    {
        return ManagePollResult{};
    }

    REQUIRE(ManagePollOpFrame::getInnerCode(opResult) == builder.expectedResult);

    return opResult.tr().managePollResult();
}

ManageCreatePollRequestResult
ManagePollTestHelper::applyTx(ManageCreatePollRequestTestBuilder builder)
{
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];

    REQUIRE(opResult.code() == builder.operationResultCode);

    if (opResult.code() != OperationResultCode::opINNER)
    {
        return ManageCreatePollRequestResult{};
    }

    REQUIRE(ManageCreatePollRequestOpFrame::getInnerCode(opResult) == builder.expectedResult);

    return opResult.tr().manageCreatePollRequestResult();
}

}
}
