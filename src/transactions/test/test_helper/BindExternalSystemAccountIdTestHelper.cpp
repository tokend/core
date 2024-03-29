#include "BindExternalSystemAccountIdTestHelper.h"
#include "ledger/ExternalSystemAccountIDHelper.h"
#include "ledger/ExternalSystemAccountIDPoolEntryHelper.h"
#include "test/test_marshaler.h"
#include "transactions/test/test_helper/ManageKeyValueTestHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{

namespace txtest
{
    BindExternalSystemAccountIdTestHelper::BindExternalSystemAccountIdTestHelper(TestManager::pointer testManager)
            : TxHelper(testManager)
    {
    }

    TransactionFramePtr
    BindExternalSystemAccountIdTestHelper::createBindExternalSystemAccountIdTx(Account &source,
                                                                               int32 externalSystemType,
                                                                               Account *signer)
    {
        Operation op;
        op.body.type(OperationType::BIND_EXTERNAL_SYSTEM_ACCOUNT_ID);
        auto& bindExternalSystemAccountId = op.body.bindExternalSystemAccountIdOp();
        bindExternalSystemAccountId.externalSystemType = externalSystemType;

        return TxHelper::txFromOperation(source, op, signer);
    }

    BindExternalSystemAccountIdResult
    BindExternalSystemAccountIdTestHelper::applyBindExternalSystemAccountIdTx(Account &source,
                                                                              int32 externalSystemType,
                                                                              BindExternalSystemAccountIdResultCode expectedResultCode,
                                                                              Account *signer)
    {
        TransactionFramePtr txFrame;

        auto& externalSystemAccountIDHelper = mTestManager->getStorageHelper().getExternalSystemAccountIDHelper();
        auto& externalSystemAccountIDPoolEntryHelper = mTestManager->getStorageHelper().getExternalSystemAccountIDPoolEntryHelper();

        std::vector<ExternalSystemAccountIDFrame::pointer> externalSystemAccountIDs;
        externalSystemAccountIDs = externalSystemAccountIDHelper.loadAll();
        auto poolEntryToBindFrame = externalSystemAccountIDPoolEntryHelper.loadAvailablePoolEntry(mTestManager->getLedgerManager(),
                                                                                                   externalSystemType);
        bool rebinding = false;
        ExternalSystemAccountIDFrame::pointer externalSystemAccountIDBeforeTx;
        bool prolongation = externalSystemAccountIDHelper.exists(source.key.getPublicKey(), externalSystemType);
        if (!prolongation)
        {
            if (!!poolEntryToBindFrame && !!poolEntryToBindFrame->getExternalSystemAccountIDPoolEntry().accountID)
            {
                auto poolEntryToBind = poolEntryToBindFrame->getExternalSystemAccountIDPoolEntry();
                externalSystemAccountIDBeforeTx = externalSystemAccountIDHelper.load(*poolEntryToBind.accountID,
                                                                                      externalSystemType);
                if (!!externalSystemAccountIDBeforeTx)
                    rebinding = true;
            }
        }

        txFrame = createBindExternalSystemAccountIdTx(source, externalSystemType, signer);

        mTestManager->applyCheck(txFrame);

        auto txResult = txFrame->getResult();
        auto opResult = txResult.result.results()[0];
        REQUIRE(opResult.code() == OperationResultCode::opINNER);

        auto actualResultCode = BindExternalSystemAccountIdOpFrame::getInnerCode(opResult);

        REQUIRE(actualResultCode == expectedResultCode);

        std::vector<ExternalSystemAccountIDFrame::pointer> externalSystemAccountIDsAfter;
        externalSystemAccountIDsAfter = externalSystemAccountIDHelper.loadAll();

        auto innerResult = opResult.tr().bindExternalSystemAccountIdResult();

        if (actualResultCode != BindExternalSystemAccountIdResultCode::SUCCESS)
        {
            REQUIRE(externalSystemAccountIDs.size() == externalSystemAccountIDsAfter.size());
        }
        else
        {
            if (prolongation || rebinding)
                REQUIRE(externalSystemAccountIDs.size() == externalSystemAccountIDsAfter.size());
            else
                REQUIRE(externalSystemAccountIDs.size() == externalSystemAccountIDsAfter.size() - 1);

            auto boundPoolEntryData = innerResult.success().data;
            auto boundPoolEntryFrame = externalSystemAccountIDPoolEntryHelper.load(externalSystemType,
                                                                                    boundPoolEntryData);
            REQUIRE(!!boundPoolEntryFrame);

            auto boundPoolEntry = boundPoolEntryFrame->getExternalSystemAccountIDPoolEntry();
            REQUIRE(boundPoolEntry.externalSystemType == externalSystemType);
            REQUIRE(boundPoolEntry.data == boundPoolEntryData);
            REQUIRE(!!boundPoolEntry.accountID);
            REQUIRE(*boundPoolEntry.accountID == source.key.getPublicKey());
            REQUIRE(boundPoolEntry.expiresAt == mTestManager->getLedgerManager().getCloseTime() + getExpireAt(externalSystemType));

            if (rebinding)
                REQUIRE(!externalSystemAccountIDHelper.exists(externalSystemAccountIDBeforeTx->getExternalSystemAccountID().accountID,
                                                               externalSystemType));

            auto externalSystemAccountIDFrame = externalSystemAccountIDHelper.load(source.key.getPublicKey(),
                                                                               externalSystemType);
            REQUIRE(!!externalSystemAccountIDFrame);

            auto externalSystemAccountID = externalSystemAccountIDFrame->getExternalSystemAccountID();
            REQUIRE(externalSystemAccountID.accountID == source.key.getPublicKey());
            REQUIRE(externalSystemAccountID.externalSystemType == externalSystemType);
            REQUIRE(externalSystemAccountID.data == boundPoolEntryData);
        }

        return innerResult;
    }

    int BindExternalSystemAccountIdTestHelper::getExpireAt(int32 externalSystemType)
    {
        auto key = ManageKeyValueOpFrame::makeExternalSystemExpirationPeriodKey(
                externalSystemType);

        KeyValueHelper& kvHelper = mTestManager->getStorageHelper().getKeyValueHelper();
        auto kvEntry = kvHelper.loadKeyValue(key);

        if (!kvEntry)
        {
            return BindExternalSystemAccountIdOpFrame::dayInSeconds;
        }

        return kvEntry.get()->getKeyValue().value.ui32Value();
    }
}

}
