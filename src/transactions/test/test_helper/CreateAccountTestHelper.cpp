#include <ledger/AccountHelperLegacy.h>
#include <transactions/CreateAccountOpFrame.h>
#include <ledger/StatisticsHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include "CreateAccountTestHelper.h"
#include "test/test_marshaler.h"

namespace stellar {
    namespace txtest {

        CreateAccountTestHelper::CreateAccountTestHelper(TestManager::pointer testManager) : TxHelper(testManager) {
        }

        Operation CreateAccountTestBuilder::buildOp() {
            Operation op;
            op.body.type(OperationType::CREATE_ACCOUNT);
            CreateAccountOp &createAccountOp = op.body.createAccountOp();
            createAccountOp.destination = to;
            createAccountOp.roleID = roleID;

            return op;
        }

        CreateAccountTestBuilder CreateAccountTestBuilder::setToPublicKey(PublicKey to) {
            auto newTestHelper = copy();
            newTestHelper.to = to;
            return newTestHelper;
        }

        CreateAccountTestBuilder CreateAccountTestBuilder::setType(AccountType accountType) {
            auto newTestHelper = copy();
            newTestHelper.accountType = accountType;
            return newTestHelper;
        }

        CreateAccountTestBuilder CreateAccountTestBuilder::setType(int32_t accountType) {
            return setType(static_cast<AccountType>(accountType));
        }

        CreateAccountTestBuilder CreateAccountTestBuilder::setReferrer(AccountID *referrer) {
            auto newTestHelper = copy();
            newTestHelper.referrer = referrer;
            return newTestHelper;
        }

        CreateAccountTestBuilder CreateAccountTestBuilder::setPolicies(int32 policies) {
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

        CreateAccountTestBuilder CreateAccountTestBuilder::setResultCode(CreateAccountResultCode expectedResult) {
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

        CreateAccountTestBuilder CreateAccountTestBuilder::setRecovery(const PublicKey& recovery) {
            auto newTestHelper = copy();
            newTestHelper.recovery = recovery;
            return newTestHelper;
        }

        CreateAccountResultCode
        CreateAccountTestHelper::applyCreateAccountTx(Account &from, PublicKey to, AccountType accountType,
                                                      Account *signer, AccountID *referrer, int32 policies,
                                                      CreateAccountResultCode expectedResult) {
            auto builder = CreateAccountTestBuilder()
                    .setSource(from)
                    .setToPublicKey(to)
                    .setType(accountType)
                    .setSigner(signer)
                    .setReferrer(referrer)
                    .setPolicies(policies)
                    .setResultCode(expectedResult)
                    .setRecovery(SecretKey::random().getPublicKey());
            return applyTx(builder);
        }

        CreateAccountResultCode CreateAccountTestHelper::applyTx(CreateAccountTestBuilder builder) {
            auto txFrame = builder.buildTx(mTestManager);
            mTestManager->applyCheck(txFrame);

            auto txResult = txFrame->getResult();
            auto opResult = txResult.result.results()[0];
            auto firstResultOpCode = getFirstResult(*txFrame).code();

            if (firstResultOpCode != OperationResultCode::opINNER){
                REQUIRE(firstResultOpCode == builder.operationResultCode);
                return builder.expectedResult;
            }
            auto checker = CreateAccountChecker(mTestManager);
            checker.doCheck(builder, txFrame);
            return CreateAccountOpFrame::getInnerCode(opResult);
        }

        TransactionFramePtr
        CreateAccountTestHelper::createCreateAccountTx(Account &source, PublicKey to, AccountType accountType,
                                                       uint32_t policies)
        {
            auto builder = CreateAccountTestBuilder()
                    .setSource(source)
                    .setToPublicKey(to)
                    .setType(accountType)
                    .setPolicies(policies);

            return builder.buildTx(mTestManager);
        }

        void
        CreateAccountChecker::doCheck(CreateAccountTestBuilder builder, TransactionFramePtr txFrame) {

            auto txResult = txFrame->getResult();
            REQUIRE(txResult.result.code() == builder.expectedTxResult);
            auto opResult = txResult.result.results()[0];
            auto actualResultCode = CreateAccountOpFrame::getInnerCode(opResult);
            REQUIRE(actualResultCode == builder.expectedResult);
            REQUIRE(txResult.feeCharged == mTestManager->getApp().getLedgerManager().getTxFee());
            Database& db = mTestManager->getDB();

            auto accountHelper = AccountHelperLegacy::Instance();
            AccountFrame::pointer fromAccount = accountHelper->loadAccount(builder.source.key.getPublicKey(), db);
            AccountFrame::pointer toAccount = accountHelper->loadAccount(builder.to, db);

            AccountFrame::pointer toAccountAfter = accountHelper->loadAccount(builder.to, db);

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
                auto balanceHelper = BalanceHelperLegacy::Instance();
                std::vector<BalanceFrame::pointer> balances;
                balanceHelper->loadBalances(toAccountAfter->getAccount().accountID, balances, db);
                for (const auto& balance : balances)
                {
                    REQUIRE(balance->getBalance().amount == 0);
                    REQUIRE(balance->getAccountID() == toAccountAfter->getAccount().accountID);
                }
            }
        }

        CreateAccountChecker::CreateAccountChecker(TestManager::pointer testManager) : mTestManager(testManager) {
        }
    }
}


