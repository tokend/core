#include <transactions/CreateChangeRoleRequestOpFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include "ledger/StorageHelper.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "CreateChangeRoleRequestTestHelper.h"
#include "ReviewChangeRoleRequestHelper.h"
#include "test/test_marshaler.h"
#include "bucket/BucketApplicator.h"


namespace stellar
{

using xdr::operator==;

namespace txtest
{
CreateChangeRoleTestHelper::CreateChangeRoleTestHelper(const TestManager::pointer testManager)
    : TxHelper(testManager)
{
}

ReviewableRequestFrame::pointer
CreateChangeRoleTestHelper::createReviewableChangeKYCRequest(ChangeRoleRequest request, uint64 requestID)
{
    auto referencePtr = getReference(request);
    auto frame = ReviewableRequestFrame::createNew(requestID, request.destinationAccount,
                                                   mTestManager->getApp().getAdminID(),
                                                   referencePtr,
                                                   mTestManager->getLedgerManager().getCloseTime());
    frame->mEntry.data.reviewableRequest().body.changeRoleRequest() = request;
    frame->recalculateHashRejectReason();
    return frame;
}

CreateChangeRoleRequestResult
CreateChangeRoleTestHelper::applyCreateChangeRoleRequest(Account& source,
                                                         uint64_t requestID,
                                                         AccountID accountToUpdateKYC,
                                                         uint64_t roleIDToSet,
                                                         longstring kycData,
                                                         uint32 *allTasks,
                                                         CreateChangeRoleRequestResultCode expectedResultCode)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& accountHelper = storageHelper.getAccountHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto& keyValueHelper = storageHelper.getKeyValueHelper();

    Database& db = mTestManager->getDB();
    auto accountBefore = accountHelper.loadAccount(accountToUpdateKYC);
    auto sourceAccount = accountHelper.loadAccount(source.key.getPublicKey());

    ReviewableRequestFrame::pointer requestBeforeTx;

    if (requestID != 0)
    {
        requestBeforeTx = requestHelper.loadRequest(requestID);
    }

    auto txFrame = createUpdateKYCRequestTx(source, requestID,
                                            accountToUpdateKYC, roleIDToSet, kycData, allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(txFrame, stateBeforeOps);

    auto txResult = txFrame->getResult();
    auto actualResultCode = CreateChangeRoleRequestOpFrame::getInnerCode(txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto accountAfter = accountHelper.loadAccount(accountToUpdateKYC);

    auto opResult = txResult.result.results()[0].tr().createChangeRoleRequestResult();

    if (actualResultCode != CreateChangeRoleRequestResultCode::SUCCESS)
    {

        if (requestBeforeTx)
        {
            auto requestAfterTx = requestHelper.loadRequest(requestID);
            auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
            auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();

            REQUIRE(requestAfterTxEntry.body.changeRoleRequest().destinationAccount ==
                    requestBeforeTxEntry.body.changeRoleRequest().destinationAccount);
            REQUIRE(requestAfterTxEntry.body.changeRoleRequest().accountRoleToSet ==
                    requestBeforeTxEntry.body.changeRoleRequest().accountRoleToSet);
            REQUIRE(requestAfterTxEntry.body.changeRoleRequest().creatorDetails ==
                    requestBeforeTxEntry.body.changeRoleRequest().creatorDetails);
            REQUIRE(requestAfterTxEntry.tasks.allTasks ==
                    requestBeforeTxEntry.tasks.allTasks);
            REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
                    requestBeforeTxEntry.tasks.pendingTasks);
            REQUIRE(requestAfterTxEntry.body.changeRoleRequest().sequenceNumber ==
                    requestBeforeTxEntry.body.changeRoleRequest().sequenceNumber);
        }

        return opResult;
    }

    requestID = opResult.success().requestID;

    if (allTasks != nullptr && *allTasks == 0)
    {
        return checkApprovedCreation(opResult, accountToUpdateKYC, stateBeforeOps[0]);
    }

    REQUIRE_FALSE(opResult.success().fulfilled);

    auto requestAfterTx = requestHelper.loadRequest(requestID);
    REQUIRE(requestAfterTx);

    auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
    auto referencePtr = getReference(requestAfterTxEntry.body.changeRoleRequest());

    REQUIRE(requestAfterTx->getReference() == referencePtr);
    REQUIRE(requestAfterTx->getRequestID() == requestID);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().destinationAccount == accountToUpdateKYC);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().accountRoleToSet == roleIDToSet);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().creatorDetails == kycData);

    if (!!allTasks)
    {
        REQUIRE(requestAfterTxEntry.tasks.allTasks == *allTasks);
    }
    else
    {
        auto key = ManageKeyValueOpFrame::makeChangeRoleKey(
            std::to_string(accountBefore->getAccountRole()), std::to_string(roleIDToSet));
        auto kvEntry = keyValueHelper.loadKeyValue(key);
        REQUIRE(kvEntry);

        REQUIRE (kvEntry.get()->getKeyValue().value.type() == KeyValueEntryType::UINT32);
        auto tasks = kvEntry.get()->getKeyValue().value.ui32Value();

        REQUIRE(requestAfterTxEntry.tasks.allTasks == tasks);
    }

    REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
            requestAfterTxEntry.tasks.allTasks);

    if (requestBeforeTx)
    {
        auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();
        REQUIRE(requestAfterTxEntry.body.changeRoleRequest().sequenceNumber ==
                requestBeforeTxEntry.body.changeRoleRequest().sequenceNumber + 1);
    }
    else
    {
        REQUIRE(requestAfterTxEntry.body.changeRoleRequest().sequenceNumber == 0);
    }

    return opResult;
}

TransactionFramePtr
CreateChangeRoleTestHelper::createUpdateKYCRequestTx(Account& source, uint64_t requestID,
                                                     AccountID accountToUpdateKYC, uint64_t roleIDToSet,
                                                     longstring kycData, uint32 *allTasks)
{
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_CHANGE_ROLE_REQUEST);
    auto& op = baseOp.body.createChangeRoleRequestOp();
    op.requestID = requestID;
    op.destinationAccount = accountToUpdateKYC;
    op.accountRoleToSet = roleIDToSet;
    op.creatorDetails = kycData;
    if (allTasks != nullptr)
    {
        op.allTasks.activate() = *allTasks;
    }

    return txFromOperation(source, baseOp, nullptr);
}

CreateChangeRoleRequestResult
CreateChangeRoleTestHelper::checkApprovedCreation(CreateChangeRoleRequestResult opResult,
                                                  AccountID accountToUpdateKYC,
                                                  LedgerDelta::KeyEntryMap stateBeforeOp)
{
    auto& storageHelper = mTestManager->getStorageHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    REQUIRE(opResult.success().fulfilled);

    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);
    auto requestFrame = stateHelper.getReviewableRequest(opResult.success().requestID);

    ReviewChangeRoleRequestChecker kycRequestChecker(mTestManager);
    kycRequestChecker.checkApprove(requestFrame);

    auto request = requestHelper.loadRequest(opResult.success().requestID,
                                             accountToUpdateKYC,
                                             ReviewableRequestType::CHANGE_ROLE);
    REQUIRE_FALSE(request);

    return opResult;
}

xdr::pointer<string64> CreateChangeRoleTestHelper::getReference(const ChangeRoleRequest& request)
{

    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::CHANGE_ROLE, request.destinationAccount));
    auto reference = binToHex(hash);
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));
    return referencePtr;
}
}
}
