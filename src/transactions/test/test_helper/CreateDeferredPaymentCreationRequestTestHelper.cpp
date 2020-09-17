#include "CreateDeferredPaymentCreationRequestTestHelper.h"
#include "bucket/BucketApplicator.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "test/test_marshaler.h"
#include <transactions/CreateDeferredPaymentCreationRequestOpFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>

namespace stellar
{

using xdr::operator==;

namespace txtest
{
CreateDeferredPaymentCreationTestHelper::
    CreateDeferredPaymentCreationTestHelper(
        const TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ReviewableRequestFrame::pointer
CreateDeferredPaymentCreationTestHelper::createDeferredPaymentCreationRequest(
    Account& source, CreateDeferredPaymentRequest request, uint64 requestID)
{
    auto referencePtr = getReference();
    auto frame = ReviewableRequestFrame::createNew(
        requestID, source.key.getPublicKey(),
        mTestManager->getApp().getAdminID(), referencePtr,
        mTestManager->getLedgerManager().getCloseTime());
    frame->mEntry.data.reviewableRequest().body.createDeferredPaymentRequest() =
        request;
    frame->recalculateHashRejectReason();
    return frame;
}

CreateDeferredPaymentCreationRequestResult
CreateDeferredPaymentCreationTestHelper::
    applyCreateDeferredPaymentCreationRequest(
        Account& source, CreateDeferredPaymentRequest request,
        uint64_t requestID, uint32* allTasks,
        OperationResultCode operationResultCode,
        CreateDeferredPaymentCreationRequestResultCode expectedResultCode)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& keyValueHelper = storageHelper.getKeyValueHelper();

    auto sourceBalance = balanceHelper.loadBalance(request.sourceBalance);

    Database& db = mTestManager->getDB();
    ReviewableRequestFrame::pointer requestBeforeTx;

    if (requestID != 0)
    {
        requestBeforeTx = requestHelper.loadRequest(requestID);
    }

    auto txFrame = createDeferredPaymentCreationRequestTx(source, request,
                                                          requestID, allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(txFrame, stateBeforeOps);

    auto txResult = txFrame->getResult();

    REQUIRE(txResult.result.results()[0].code() == operationResultCode);

    if (operationResultCode != OperationResultCode::opINNER)
    {
        return CreateDeferredPaymentCreationRequestResult{};
    }

    auto actualResultCode =
        CreateDeferredPaymentCreationRequestOpFrame::getInnerCode(
            txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto opResult = txResult.result.results()[0]
                        .tr()
                        .createDeferredPaymentCreationRequestResult();

    if (actualResultCode !=
        CreateDeferredPaymentCreationRequestResultCode::SUCCESS)
    {

        if (requestBeforeTx)
        {
            auto requestAfterTx = requestHelper.loadRequest(requestID);
            auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
            auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();

            REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                        .sourceBalance ==
                    requestBeforeTxEntry.body.createDeferredPaymentRequest()
                        .sourceBalance);
            REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                        .amount ==
                    requestBeforeTxEntry.body.createDeferredPaymentRequest()
                        .amount);
            REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                        .creatorDetails ==
                    requestBeforeTxEntry.body.createDeferredPaymentRequest()
                        .creatorDetails);

            REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                        .destination ==
                    requestBeforeTxEntry.body.createDeferredPaymentRequest()
                        .destination);
            REQUIRE(requestAfterTxEntry.tasks.allTasks ==
                    requestBeforeTxEntry.tasks.allTasks);
            REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
                    requestBeforeTxEntry.tasks.pendingTasks);
            REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                        .sequenceNumber ==
                    requestBeforeTxEntry.body.createDeferredPaymentRequest()
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
    REQUIRE(
        requestAfterTxEntry.body.createDeferredPaymentRequest().destination ==
        request.destination);
    REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest().amount ==
            request.amount);
    REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                .creatorDetails == request.creatorDetails);

    if (!!allTasks)
    {
        REQUIRE(requestAfterTxEntry.tasks.allTasks == *allTasks);
    }
    else
    {

        auto key =
            ManageKeyValueOpFrame::makeCreateDeferredPaymentCreationTasksKey(
                sourceBalance->getAsset());
        auto kvEntry = keyValueHelper.loadKeyValue(key);
        REQUIRE(kvEntry);

        REQUIRE(kvEntry.get()->getKeyValue().value.type() ==
                KeyValueEntryType::UINT32);
        auto tasks = kvEntry.get()->getKeyValue().value.ui32Value();

        REQUIRE(requestAfterTxEntry.tasks.allTasks == tasks);
    }

    REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
            requestAfterTxEntry.tasks.allTasks);

    if (requestBeforeTx)
    {
        auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();
        REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                    .sequenceNumber ==
                requestBeforeTxEntry.body.createDeferredPaymentRequest()
                        .sequenceNumber +
                    1);
    }
    else
    {
        REQUIRE(requestAfterTxEntry.body.createDeferredPaymentRequest()
                    .sequenceNumber == 0);
    }

    return opResult;
}

TransactionFramePtr
CreateDeferredPaymentCreationTestHelper::createDeferredPaymentCreationRequestTx(
    Account& source, CreateDeferredPaymentRequest request, uint64_t requestID,
    uint32* allTask)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_DEFERRED_PAYMENT_CREATION_REQUEST);
    auto& op = baseOp.body.createDeferredPaymentCreationRequestOp();
    op.requestID = requestID;
    op.request = request;
    if (allTask)
    {
        op.allTasks.activate() = *allTask;
    }

    return txFromOperation(source, baseOp, nullptr);
}
CreateDeferredPaymentCreationRequestResult
CreateDeferredPaymentCreationTestHelper::checkApprovedCreation(
    CreateDeferredPaymentCreationRequestResult opResult, AccountID source,
    LedgerDelta::KeyEntryMap stateBeforeOp)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    REQUIRE(opResult.success().fulfilled);

    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);
    auto requestFrame =
        stateHelper.getReviewableRequest(opResult.success().requestID);

    ReviewCreateDeferredPaymentRequestChecker
        createDeferredPaymentRequestChecker(mTestManager);
    createDeferredPaymentRequestChecker.checkApprove(requestFrame);

    auto request = requestHelper.loadRequest(
        opResult.success().requestID, source,
        ReviewableRequestType::CREATE_DEFERRED_PAYMENT);
    REQUIRE_FALSE(request);

    return opResult;
}

xdr::pointer<string64>
CreateDeferredPaymentCreationTestHelper::getReference()
{
    const auto hash = sha256(
        xdr::xdr_to_opaque(ReviewableRequestType::CREATE_DEFERRED_PAYMENT));
    auto reference = binToHex(hash);
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));
    return referencePtr;
}
}
}
