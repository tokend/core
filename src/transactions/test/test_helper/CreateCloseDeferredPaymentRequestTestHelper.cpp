#include "CreateCloseDeferredPaymentRequestTestHelper.h"
#include "bucket/BucketApplicator.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include <transactions/CreateCloseDeferredPaymentRequestOpFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>

namespace stellar
{

using xdr::operator==;

namespace txtest
{
CreateCloseDeferredPaymentTestHelper::CreateCloseDeferredPaymentTestHelper(
    const TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ReviewableRequestFrame::pointer
CreateCloseDeferredPaymentTestHelper::createCloseDeferredPaymentRequest(
    Account& source, CloseDeferredPaymentRequest request, uint64 requestID)
{
    auto referencePtr = getReference();
    auto frame = ReviewableRequestFrame::createNew(
        requestID, source.key.getPublicKey(),
        mTestManager->getApp().getAdminID(), referencePtr,
        mTestManager->getLedgerManager().getCloseTime());
    frame->mEntry.data.reviewableRequest().body.closeDeferredPaymentRequest() =
        request;
    frame->recalculateHashRejectReason();
    return frame;
}

CreateCloseDeferredPaymentRequestResult
CreateCloseDeferredPaymentTestHelper::applyCreateCloseDeferredPaymentRequest(
    Account& source, CloseDeferredPaymentRequest request, uint64_t requestID,
    uint32* allTasks,
    OperationResultCode operationResultCode,
    CreateCloseDeferredPaymentRequestResultCode expectedResultCode)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& keyValueHelper = storageHelper.getKeyValueHelper();

//    auto destinationBalance = balanceHelper.loadBalance(request.destinationBalance);

    Database& db = mTestManager->getDB();
    ReviewableRequestFrame::pointer requestBeforeTx;

    if (requestID != 0)
    {
        requestBeforeTx = requestHelper.loadRequest(requestID);
    }

    auto txFrame = createCloseDeferredPaymentRequestTx(source, request,
                                                       requestID, allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(txFrame, stateBeforeOps);

    auto txResult = txFrame->getResult();
    auto actualResultCode =
        CreateCloseDeferredPaymentRequestOpFrame::getInnerCode(
            txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto opResult = txResult.result.results()[0]
                        .tr()
                        .createCloseDeferredPaymentRequestResult();

    if (actualResultCode !=
        CreateCloseDeferredPaymentRequestResultCode::SUCCESS)
    {

        if (requestBeforeTx)
        {
            auto requestAfterTx = requestHelper.loadRequest(requestID);
            auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
            auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();

//            REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
//                        .destinationBalance ==
//                    requestBeforeTxEntry.body.closeDeferredPaymentRequest()
//                        .destinationBalance);

            REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
                        .deferredPaymentID ==
                    requestBeforeTxEntry.body.closeDeferredPaymentRequest()
                        .deferredPaymentID);
            REQUIRE(
                requestAfterTxEntry.body.closeDeferredPaymentRequest().amount ==
                requestBeforeTxEntry.body.closeDeferredPaymentRequest().amount);
            REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
                        .creatorDetails ==
                    requestBeforeTxEntry.body.closeDeferredPaymentRequest()
                        .creatorDetails);

            REQUIRE(requestAfterTxEntry.tasks.allTasks ==
                    requestBeforeTxEntry.tasks.allTasks);
            REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
                    requestBeforeTxEntry.tasks.pendingTasks);
            REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
                        .sequenceNumber ==
                    requestBeforeTxEntry.body.closeDeferredPaymentRequest()
                        .sequenceNumber);
        }

        return opResult;
    }

    requestID = opResult.success().requestID;

    if (allTasks != nullptr && *allTasks == 0)
    {
        return checkApprovedCreation(opResult, source.key.getPublicKey(),
                                     stateBeforeOps[0]);
    }

    REQUIRE_FALSE(opResult.success().fulfilled);

    auto requestAfterTx = requestHelper.loadRequest(requestID);
    REQUIRE(requestAfterTx);

    auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
    auto referencePtr = getReference();

    REQUIRE(requestAfterTx->getReference() == referencePtr);
    REQUIRE(requestAfterTx->getRequestID() == requestID);
    REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest().amount ==
            request.amount);
    REQUIRE(
        requestAfterTxEntry.body.closeDeferredPaymentRequest().creatorDetails ==
        request.creatorDetails);

    if (!!allTasks)
    {
        REQUIRE(requestAfterTxEntry.tasks.allTasks == *allTasks);
    }
    else
    {

//        auto key =
//            ManageKeyValueOpFrame::makeCreateDeferredPaymentCloseTasksKey(
//                destinationBalance->getAsset());
//        auto kvEntry = keyValueHelper.loadKeyValue(key);
//        REQUIRE(kvEntry);
//
//        REQUIRE(kvEntry.get()->getKeyValue().value.type() ==
//                KeyValueEntryType::UINT32);
//        auto tasks = kvEntry.get()->getKeyValue().value.ui32Value();
//
//        REQUIRE(requestAfterTxEntry.tasks.allTasks == tasks);
    }

    REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
            requestAfterTxEntry.tasks.allTasks);

    if (requestBeforeTx)
    {
        auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();
        REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
                    .sequenceNumber ==
                requestBeforeTxEntry.body.closeDeferredPaymentRequest()
                        .sequenceNumber +
                    1);
    }
    else
    {
        REQUIRE(requestAfterTxEntry.body.closeDeferredPaymentRequest()
                    .sequenceNumber == 0);
    }

    return opResult;
}

TransactionFramePtr
CreateCloseDeferredPaymentTestHelper::createCloseDeferredPaymentRequestTx(
    Account& source, CloseDeferredPaymentRequest request, uint64_t requestID,
    uint32* allTask)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_CLOSE_DEFERRED_PAYMENT_REQUEST);
    auto& op = baseOp.body.createCloseDeferredPaymentRequestOp();
    op.requestID = requestID;
    op.request = request;
    if (allTask)
    {
        op.allTasks.activate() = *allTask;
    }

    return txFromOperation(source, baseOp, nullptr);
}
CreateCloseDeferredPaymentRequestResult
CreateCloseDeferredPaymentTestHelper::checkApprovedCreation(
    CreateCloseDeferredPaymentRequestResult opResult, AccountID source,
    LedgerDelta::KeyEntryMap stateBeforeOp)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    REQUIRE(opResult.success().fulfilled);

    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);
    auto requestFrame =
        stateHelper.getReviewableRequest(opResult.success().requestID);

    ReviewCloseDeferredPaymentRequestChecker closeDeferredPaymentRequestChecker(
        mTestManager, opResult.success().requestID);
    closeDeferredPaymentRequestChecker.checkApprove(requestFrame);

    auto request = requestHelper.loadRequest(
        opResult.success().requestID, source,
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    REQUIRE_FALSE(request);

    return opResult;
}

xdr::pointer<string64>
CreateCloseDeferredPaymentTestHelper::getReference()
{
    return nullptr;
}
}
}
