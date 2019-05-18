#include "KYCRecoveryTestHelper.h"
#include "test/test_marshaler.h"
#include "transactions/InitiateKYCRecoveryOpFrame.h"
#include "transactions/CreateKYCRecoveryRequestOpFrame.h"


namespace stellar
{

using xdr::operator==;

namespace txtest
{

InitiateKYCRecoveryTestHelper::InitiateKYCRecoveryTestHelper(TestManager::pointer testManager) : TxHelper(testManager) {
}


CreateKYCRecoveryRequestTestHelper::CreateKYCRecoveryRequestTestHelper(TestManager::pointer testManager) : TxHelper(testManager) {
}

Operation InitiateKYCRecoveryTestBuilder::buildOp() {
    Operation op;
    op.body.type(OperationType::INITIATE_KYC_RECOVERY);
    InitiateKYCRecoveryOp &initiateKYCRecovery= op.body.initiateKYCRecoveryOp();
    initiateKYCRecovery.account= targetAccount;
    initiateKYCRecovery.signer = signer;

    return op;
}

InitiateKYCRecoveryTestBuilder InitiateKYCRecoveryTestBuilder::setSigner(PublicKey recSigner)
{
    auto newTestHelper = copy();
    newTestHelper.signer = recSigner;
    return newTestHelper;
}

InitiateKYCRecoveryTestBuilder InitiateKYCRecoveryTestBuilder::setTargetAccount(AccountID target)
{
    auto newTestHelper = copy();
    newTestHelper.targetAccount = target;
    return newTestHelper;
}

InitiateKYCRecoveryTestBuilder InitiateKYCRecoveryTestBuilder::setResultCode(InitiateKYCRecoveryResultCode expectedResult) {
    auto newTestHelper = copy();
    newTestHelper.expectedResult = expectedResult;
    return newTestHelper;
}

InitiateKYCRecoveryTestBuilder InitiateKYCRecoveryTestBuilder::setTxResultCode(
    TransactionResultCode expectedResult)
{
    auto newTestHelper = copy();
    newTestHelper.expectedTxResult = expectedResult;
    return newTestHelper;
}

//start

InitiateKYCRecoveryResultCode InitiateKYCRecoveryTestHelper::applyTx(InitiateKYCRecoveryTestBuilder builder) {
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto firstResultOpCode = getFirstResult(*txFrame).code();

    if (firstResultOpCode != OperationResultCode::opINNER){
        REQUIRE(firstResultOpCode == builder.operationResultCode);
        return builder.expectedResult;
    }
    auto checker = InitiateKYCRecoveryChecker(mTestManager);
    checker.doCheck(builder, txFrame);
    return InitiateKYCRecoveryOpFrame::getInnerCode(opResult);
}

TransactionFramePtr
InitiateKYCRecoveryTestHelper::createInitiateKYCRecoveryTx(Account& source, AccountID& target, PublicKey signer,
    InitiateKYCRecoveryResultCode expectedResult)
{
    auto builder = InitiateKYCRecoveryTestBuilder()
        .setSource(source)
        .setSigner(signer)
        .setTargetAccount(target)
        .setResultCode(expectedResult);

    return builder.buildTx(mTestManager);
}

void
InitiateKYCRecoveryChecker::doCheck(InitiateKYCRecoveryTestBuilder builder, TransactionFramePtr txFrame) {

    auto txResult = txFrame->getResult();
    REQUIRE(txResult.result.code() == builder.expectedTxResult);
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = InitiateKYCRecoveryOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == builder.expectedResult);
    Database& db = mTestManager->getDB();


    if (builder.expectedResult != InitiateKYCRecoveryResultCode::SUCCESS)
    {
        return;
    }
    return;
}

InitiateKYCRecoveryChecker::InitiateKYCRecoveryChecker(TestManager::pointer testManager) : mTestManager(testManager) {
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::setTargetAccount(AccountID target)
{
    auto newTestHelper = copy();
    newTestHelper.target = target;
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::addSignerData(UpdateSignerData data)
{
    auto newTestHelper = copy();
    newTestHelper.signersData.emplace_back(data);
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::clearSignerData()
{
    auto newTestHelper = copy();
    newTestHelper.signersData.clear();
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::setResultCode(CreateKYCRecoveryRequestResultCode expectedResult)
{
    auto newTestHelper = copy();
    newTestHelper.expectedResult = expectedResult;
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::setRequestID(uint64_t requestID)
{
    auto newTestHelper = copy();
    newTestHelper.requestID = requestID;
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::setTxResultCode(TransactionResultCode expectedResult)
{
    auto newTestHelper = copy();
    newTestHelper.expectedTxResult = expectedResult;
    return newTestHelper;
}

CreateKYCRecoveryRequestTestBuilder CreateKYCRecoveryRequestTestBuilder::setTasks(uint32_t *tasks)
{
    auto newTestHelper = copy();
    newTestHelper.allTasks = tasks;
    return newTestHelper;
}

Operation CreateKYCRecoveryRequestTestBuilder::buildOp()
{
    Operation op;
    op.body.type(OperationType::CREATE_KYC_RECOVERY_REQUEST);
    CreateKYCRecoveryRequestOp &createKYCRecoveryRequest = op.body.createKYCRecoveryRequestOp();
    createKYCRecoveryRequest.targetAccount = target;
    createKYCRecoveryRequest.signersData = signersData;
    createKYCRecoveryRequest.requestID = requestID;
    createKYCRecoveryRequest.creatorDetails = "{}";
    if (allTasks)
        createKYCRecoveryRequest.allTasks.activate() = *allTasks;

    return op;
}


CreateKYCRecoveryRequestResult CreateKYCRecoveryRequestTestHelper::applyTx(CreateKYCRecoveryRequestTestBuilder builder) {
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto firstResultOpCode = getFirstResult(*txFrame).code();

    if (firstResultOpCode != OperationResultCode::opINNER){
        REQUIRE(firstResultOpCode == builder.operationResultCode);
        return opResult.tr().createKYCRecoveryRequestResult();
    }
    auto checker = CreateKYCRecoveryRequestChecker(mTestManager);
    checker.doCheck(builder, txFrame);
    return opResult.tr().createKYCRecoveryRequestResult();
}

TransactionFramePtr
CreateKYCRecoveryRequestTestHelper::createCreateKYCRecoveryRequestTx(Account& source, AccountID& target, UpdateSignerData data,
                                                           CreateKYCRecoveryRequestResultCode expectedResult)
{
    auto builder = CreateKYCRecoveryRequestTestBuilder()
        .setSource(source)
        .addSignerData(data)
        .setTargetAccount(target)
        .setResultCode(expectedResult);

    return builder.buildTx(mTestManager);
}

void
CreateKYCRecoveryRequestChecker::doCheck(CreateKYCRecoveryRequestTestBuilder builder, TransactionFramePtr txFrame) {

    auto txResult = txFrame->getResult();
    REQUIRE(txResult.result.code() == builder.expectedTxResult);
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = CreateKYCRecoveryRequestOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == builder.expectedResult);
    Database& db = mTestManager->getDB();


    if (builder.expectedResult != CreateKYCRecoveryRequestResultCode::SUCCESS)
    {
        return;
    }
    return;
}

CreateKYCRecoveryRequestChecker::CreateKYCRecoveryRequestChecker(TestManager::pointer testManager) : mTestManager(testManager) {

}

}
}
