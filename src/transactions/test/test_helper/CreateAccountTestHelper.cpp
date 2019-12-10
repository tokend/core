#include <transactions/CreateAccountOpFrame.h>
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AccountHelper.h"
#include <ledger/SignerRuleFrame.h>
#include <lib/util/basen.h>
#include "CreateAccountTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar
{
namespace txtest
{

CreateAccountTestHelper::CreateAccountTestHelper(TestManager::pointer testManager) : TxHelper(testManager)
{
}

Operation CreateAccountTestBuilder::buildOp()
{
    Operation op;
    op.body.type(OperationType::CREATE_ACCOUNT);
    CreateAccountOp& createAccountOp = op.body.createAccountOp();
    createAccountOp.destination = to;
    createAccountOp.roleID = roleID;
    if (referrer != nullptr)
    {
        createAccountOp.referrer.activate() = *referrer;
    }
    createAccountOp.signersData = signersData;

    return op;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setToPublicKey(PublicKey to)
{
    auto newTestHelper = copy();
    newTestHelper.to = to;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setReferrer(AccountID *referrer)
{
    auto newTestHelper = copy();
    newTestHelper.referrer = referrer;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setPolicies(int32 policies)
{
    auto newTestHelper = copy();
    newTestHelper.policies = policies;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setRoleID(uint64_t roleID)
{
    auto newTestHelper = copy();
    newTestHelper.roleID = roleID;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setResultCode(CreateAccountResultCode expectedResult)
{
    auto newTestHelper = copy();
    newTestHelper.expectedResult = expectedResult;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::setTxResultCode(
    TransactionResultCode expectedResult)
{
    auto newTestHelper = copy();
    newTestHelper.expectedTxResult = expectedResult;
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::addSignerData(
    UpdateSignerData data)
{
    auto newTestHelper = copy();
    newTestHelper.signersData.emplace_back(data);
    return newTestHelper;
}

CreateAccountTestBuilder CreateAccountTestBuilder::addBasicSigner(
    uint64_t roleID)
{
    auto newTestHelper = copy();
    UpdateSignerData data;
    data.publicKey = to;
    data.roleID = roleID;
    data.weight = SignerRuleFrame::threshold;
    data.identity = 1;
    data.details = "{}";
    newTestHelper.signersData.emplace_back(data);
    return newTestHelper;
}

CreateAccountResultCode
CreateAccountTestHelper::applyCreateAccountTx(Account& from, PublicKey to, uint64_t roleID,
                                              Account *signer, AccountID *referrer, int32 policies,
                                              CreateAccountResultCode expectedResult)
{
    auto builder = CreateAccountTestBuilder()
        .setSource(from)
        .setToPublicKey(to)
        .setSigner(signer)
        .setReferrer(referrer)
        .setPolicies(policies)
        .setResultCode(expectedResult)
        .addBasicSigner()
        .setRoleID(roleID);
    return applyTx(builder);
}

CreateAccountResultCode CreateAccountTestHelper::applyTx(CreateAccountTestBuilder builder)
{
    auto txFrame = builder.buildTx(mTestManager);
    mTestManager->applyCheck(txFrame);

    auto txResult = txFrame->getResult();
    auto opResult = txResult.result.results()[0];
    auto firstResultOpCode = getFirstResult(*txFrame).code();

    if (firstResultOpCode != OperationResultCode::opINNER)
    {
        REQUIRE(firstResultOpCode == builder.operationResultCode);
        return builder.expectedResult;
    }
    auto checker = CreateAccountChecker(mTestManager);
    checker.doCheck(builder, txFrame);
    return CreateAccountOpFrame::getInnerCode(opResult);
}

TransactionFramePtr
CreateAccountTestHelper::createCreateAccountTx(Account& source, PublicKey to,
                                               uint32_t policies)
{
    auto builder = CreateAccountTestBuilder()
        .setSource(source)
        .setToPublicKey(to)
        .setPolicies(policies);

    return builder.buildTx(mTestManager);
}

void
CreateAccountChecker::doCheck(CreateAccountTestBuilder builder, TransactionFramePtr txFrame)
{

    auto txResult = txFrame->getResult();
    REQUIRE(txResult.result.code() == builder.expectedTxResult);
    auto opResult = txResult.result.results()[0];
    auto actualResultCode = CreateAccountOpFrame::getInnerCode(opResult);
    REQUIRE(actualResultCode == builder.expectedResult);
    Database& db = mTestManager->getDB();

    auto& accountHelper = mTestManager->getStorageHelper().getAccountHelper();
    AccountFrame::pointer fromAccount = accountHelper.loadAccount(builder.source.key.getPublicKey());
    AccountFrame::pointer toAccount = accountHelper.loadAccount(builder.to);

    AccountFrame::pointer toAccountAfter = accountHelper.loadAccount(builder.to);

    if (builder.expectedResult != CreateAccountResultCode::SUCCESS)
    {
        // check that the target account didn't change
        REQUIRE(!!toAccount == !!toAccountAfter);
        if (toAccount && toAccountAfter)
        {
            REQUIRE(toAccount->getAccount() == toAccountAfter->getAccount());
        }

        return;

    }
    REQUIRE(toAccountAfter);

    if (!toAccount)
    {
        auto& balanceHelper = mTestManager->getStorageHelper().getBalanceHelper();
        std::vector<BalanceFrame::pointer> balances;
        balanceHelper.loadBalances(toAccountAfter->getAccount().accountID, balances);
        for (const auto& balance : balances)
        {
            REQUIRE(balance->getBalance().amount == 0);
            REQUIRE(balance->getAccountID() == toAccountAfter->getAccount().accountID);
        }
    }
}

CreateAccountChecker::CreateAccountChecker(TestManager::pointer testManager) : mTestManager(testManager)
{
}
}
}


