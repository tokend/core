#pragma once

#include "TxHelper.h"
#include "transactions/test/TxTests.h"

namespace stellar
{
namespace txtest
{
class InitiateKYCRecoveryTestBuilder : public OperationBuilder<InitiateKYCRecoveryTestBuilder> {
public:
    InitiateKYCRecoveryTestBuilder copy() override
    {
        return *this;
    }

    Operation buildOp() override;

    InitiateKYCRecoveryTestBuilder setSigner(PublicKey signer);

    InitiateKYCRecoveryTestBuilder setTargetAccount(AccountID target);

    InitiateKYCRecoveryTestBuilder setResultCode(InitiateKYCRecoveryResultCode expectedResult);

    InitiateKYCRecoveryTestBuilder setTxResultCode(
        TransactionResultCode expectedResult);

    PublicKey signer;
    AccountID targetAccount;

    TransactionResultCode expectedTxResult = TransactionResultCode::txSUCCESS;
    InitiateKYCRecoveryResultCode expectedResult = InitiateKYCRecoveryResultCode::SUCCESS;
};

class InitiateKYCRecoveryChecker {
public:
    TestManager::pointer mTestManager;

    explicit InitiateKYCRecoveryChecker(TestManager::pointer testManager);

    void doCheck(InitiateKYCRecoveryTestBuilder builder, TransactionFramePtr txFrame);
};

class InitiateKYCRecoveryTestHelper : public TxHelper {
public:
    explicit InitiateKYCRecoveryTestHelper(TestManager::pointer testManager);

    friend InitiateKYCRecoveryChecker;


    TransactionFramePtr createInitiateKYCRecoveryTx(Account& source, AccountID& target,
                                                    PublicKey signer, InitiateKYCRecoveryResultCode expectedResult = InitiateKYCRecoveryResultCode::SUCCESS);

    InitiateKYCRecoveryResultCode applyTx(InitiateKYCRecoveryTestBuilder builder);
};

class CreateKYCRecoveryRequestTestBuilder : public OperationBuilder<CreateKYCRecoveryRequestTestBuilder> {
public:
    CreateKYCRecoveryRequestTestBuilder copy() override
    {
        return *this;
    }

    Operation buildOp() override;

    CreateKYCRecoveryRequestTestBuilder addSignerData(UpdateSignerData data);

    CreateKYCRecoveryRequestTestBuilder clearSignerData();

    CreateKYCRecoveryRequestTestBuilder setTargetAccount(AccountID target);

    CreateKYCRecoveryRequestTestBuilder setTasks(uint32_t *tasks);

    CreateKYCRecoveryRequestTestBuilder setRequestID(uint64_t requestID);

    CreateKYCRecoveryRequestTestBuilder setResultCode(CreateKYCRecoveryRequestResultCode expectedResult);

    CreateKYCRecoveryRequestTestBuilder setTxResultCode(
        TransactionResultCode expectedResult);

    uint32_t *allTasks = nullptr;
    xdr::xvector<UpdateSignerData> signersData = {};
    AccountID target;
    uint64_t requestID = 0;
    TransactionResultCode expectedTxResult = TransactionResultCode::txSUCCESS;
    CreateKYCRecoveryRequestResultCode expectedResult = CreateKYCRecoveryRequestResultCode::SUCCESS;
};


class CreateKYCRecoveryRequestChecker {
public:
    TestManager::pointer mTestManager;

    explicit CreateKYCRecoveryRequestChecker(TestManager::pointer testManager);

    void doCheck(CreateKYCRecoveryRequestTestBuilder builder, TransactionFramePtr txFrame);
};

class CreateKYCRecoveryRequestTestHelper : public TxHelper {
public:
    explicit CreateKYCRecoveryRequestTestHelper(TestManager::pointer testManager);

    friend CreateKYCRecoveryRequestChecker;

    TransactionFramePtr createCreateKYCRecoveryRequestTx(Account& source, AccountID& target,
                                                         UpdateSignerData data, CreateKYCRecoveryRequestResultCode expectedResult = CreateKYCRecoveryRequestResultCode::SUCCESS);

    CreateKYCRecoveryRequestResult applyTx(CreateKYCRecoveryRequestTestBuilder builder);
};

}
}
