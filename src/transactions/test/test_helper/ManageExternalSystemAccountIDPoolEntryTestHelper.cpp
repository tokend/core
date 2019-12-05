#include <ledger/ExternalSystemAccountIDHelper.h>
#include "ManageExternalSystemAccountIDPoolEntryTestHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "transactions/external_system_pool/ManageExternalSystemAccountIDPoolEntryOpFrame.h"
#include "test/test_marshaler.h"
#include "ledger/StorageHelper.h"

namespace stellar
{

namespace txtest
{
    ManageExternalSystemAccountIDPoolEntryTestHelper::ManageExternalSystemAccountIDPoolEntryTestHelper(
            TestManager::pointer testManager) : TxHelper(testManager)
    {
    }

    TransactionFramePtr
    ManageExternalSystemAccountIDPoolEntryTestHelper::createManageExternalSystemAccountIDPoolEntryTx(Account &source,
                                                ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t actionInput,
                                                Account *signer)
    {
        Operation op;
        op.body.type(OperationType::MANAGE_EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY);
        auto& manageExSysAccIdPoolEntry = op.body.manageExternalSystemAccountIdPoolEntryOp();
        manageExSysAccIdPoolEntry.actionInput = actionInput;

        return TxHelper::txFromOperation(source, op, signer);
    }

    ManageExternalSystemAccountIdPoolEntryResult
    ManageExternalSystemAccountIDPoolEntryTestHelper::applyCreateExternalSystemAccountIDPoolEntryTx(Account &source,
                                                ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t actionInput,
                                                ManageExternalSystemAccountIdPoolEntryResultCode expectedResultCode,
                                                Account *signer)
    {
        TransactionFramePtr txFrame;

        auto& poolEntryHelper = mTestManager->getStorageHelper().getExternalSystemAccountIDPoolEntryHelper();

        std::vector<ExternalSystemAccountIDPoolEntryFrame::pointer> pool;
        pool = poolEntryHelper.loadPool();

        txFrame = createManageExternalSystemAccountIDPoolEntryTx(source, actionInput, signer);

        mTestManager->applyCheck(txFrame);

        auto txResult = txFrame->getResult();
        auto actualResultCode =
                ManageExternalSystemAccountIdPoolEntryOpFrame::getInnerCode(txResult.result.results()[0]);

        REQUIRE(actualResultCode == expectedResultCode);

        std::vector<ExternalSystemAccountIDPoolEntryFrame::pointer> poolAfter;
        poolAfter = poolEntryHelper.loadPool();

        auto opResult = txResult.result.results()[0].tr().manageExternalSystemAccountIdPoolEntryResult();

        if (actualResultCode != ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS)
        {
            return opResult;
        }

        REQUIRE(pool.size() == poolAfter.size() - 1);

        auto poolEntryFrame = poolEntryHelper.load(opResult.success().poolEntryID);
        REQUIRE(poolEntryFrame);

        auto poolEntry = poolEntryFrame->getExternalSystemAccountIDPoolEntry();
        REQUIRE(poolEntry.externalSystemType ==
                        actionInput.createExternalSystemAccountIdPoolEntryActionInput().externalSystemType);
        REQUIRE(poolEntry.data ==
                        actionInput.createExternalSystemAccountIdPoolEntryActionInput().data);
        REQUIRE(!poolEntry.accountID);
        REQUIRE(poolEntry.expiresAt == 0);
        REQUIRE(poolEntry.bindedAt == 0);
        REQUIRE(!poolEntry.isDeleted);

        return opResult;
    }

    ManageExternalSystemAccountIdPoolEntryResult
    ManageExternalSystemAccountIDPoolEntryTestHelper::applyDeleteExternalSystemAccountIDPoolEntryTx(Account &source,
                                                ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t actionInput,
                                                ManageExternalSystemAccountIdPoolEntryResultCode expectedResultCode,
                                                Account *signer)
    {
        TransactionFramePtr txFrame;

        auto& poolEntryHelper = mTestManager->getStorageHelper().getExternalSystemAccountIDPoolEntryHelper();

        std::vector<ExternalSystemAccountIDPoolEntryFrame::pointer> pool;
        pool = poolEntryHelper.loadPool();

        txFrame = createManageExternalSystemAccountIDPoolEntryTx(source, actionInput, signer);

        mTestManager->applyCheck(txFrame);

        auto txResult = txFrame->getResult();
        auto actualResultCode =
                ManageExternalSystemAccountIdPoolEntryOpFrame::getInnerCode(txResult.result.results()[0]);

        REQUIRE(actualResultCode == expectedResultCode);

        std::vector<ExternalSystemAccountIDPoolEntryFrame::pointer> poolAfter;
        poolAfter = poolEntryHelper.loadPool();

        auto opResult = txResult.result.results()[0].tr().manageExternalSystemAccountIdPoolEntryResult();

        if (actualResultCode != ManageExternalSystemAccountIdPoolEntryResultCode::SUCCESS)
        {
            return opResult;
        }

        auto poolEntryFrame = poolEntryHelper.load(opResult.success().poolEntryID);

        if (!poolEntryFrame) {
            REQUIRE(pool.size() == poolAfter.size() + 1);
            return opResult;
        }

        REQUIRE(pool.size() == poolAfter.size());

        REQUIRE(poolEntryFrame->getExternalSystemAccountIDPoolEntry().isDeleted);

        auto poolEntry = poolEntryFrame->getExternalSystemAccountIDPoolEntry();
        auto& externalSystemAccountIDHelper = mTestManager->getStorageHelper().getExternalSystemAccountIDHelper();
        auto externalSystemAccountIDFrame = externalSystemAccountIDHelper.load(
                *poolEntry.accountID, poolEntry.externalSystemType);

        REQUIRE(!!externalSystemAccountIDFrame);

        return opResult;
    }

    ManageExternalSystemAccountIdPoolEntryResult
    ManageExternalSystemAccountIDPoolEntryTestHelper::createExternalSystemAccountIdPoolEntry(Account &source,
                                                 int32 type, std::string data,
                                                 ManageExternalSystemAccountIdPoolEntryResultCode expectedResultCode,
                                                 Account *signer)
    {
        ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t actionInput;
        actionInput.action(ManageExternalSystemAccountIdPoolEntryAction::CREATE);
        CreateExternalSystemAccountIdPoolEntryActionInput& input =
                actionInput.createExternalSystemAccountIdPoolEntryActionInput();
        input.externalSystemType = type;
        input.data = data;
        return applyCreateExternalSystemAccountIDPoolEntryTx(source, actionInput, expectedResultCode, signer);
    }

    ManageExternalSystemAccountIdPoolEntryResult
    ManageExternalSystemAccountIDPoolEntryTestHelper::deleteExternalSystemAccountIdPoolEntry(Account &source,
                                           ManageExternalSystemAccountIdPoolEntryResultCode expectedResultCode,
                                           uint64 poolEntryID,
                                           Account *signer)
    {
        ManageExternalSystemAccountIdPoolEntryOp::_actionInput_t actionInput;
        actionInput.action(ManageExternalSystemAccountIdPoolEntryAction::REMOVE);
        DeleteExternalSystemAccountIdPoolEntryActionInput& input =
                actionInput.deleteExternalSystemAccountIdPoolEntryActionInput();
        input.poolEntryID = poolEntryID;
        return applyDeleteExternalSystemAccountIDPoolEntryTx(source, actionInput, expectedResultCode, signer);
    }


}
}
