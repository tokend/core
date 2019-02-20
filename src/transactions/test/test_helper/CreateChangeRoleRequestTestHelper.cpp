#include <transactions/CreateChangeRoleRequestOpFrame.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include <ledger/KeyValueHelperLegacy.h>
#include <ledger/ReviewableRequestHelper.h>
#include "CreateChangeRoleRequestTestHelper.h"
#include "ReviewChangeRoleRequestHelper.h"
#include "test/test_marshaler.h"
#include "ledger/AccountHelperLegacy.h"
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
CreateChangeRoleTestHelper::createReviewableChangeKYCRequest(ChangeRoleRequest request, uint64 requestID) {
    auto referencePtr = getReference();
    auto frame = ReviewableRequestFrame::createNew(requestID, request.destinationAccount,
                                                   mTestManager->getApp().getAdminID(),
                                                   referencePtr,
                                                   mTestManager->getLedgerManager().getCloseTime());
    frame->mEntry.data.reviewableRequest().body.changeRoleRequest() = request;
    frame->recalculateHashRejectReason();
    return frame;
}

CreateChangeRoleRequestResult
CreateChangeRoleTestHelper::applyCreateChangeRoleRequest(Account &source,
                                                         uint64_t requestID,
                                                         AccountID accountToUpdateKYC,
                                                         uint64_t roleIDToSet,
                                                         longstring kycData,
                                                         uint32 *allTasks,
                                                         CreateChangeRoleRequestResultCode expectedResultCode) {
    auto accountHelper = AccountHelperLegacy::Instance();
    auto requestHelper = ReviewableRequestHelper::Instance();

    Database &db = mTestManager->getDB();
    auto accountBefore = accountHelper->loadAccount(accountToUpdateKYC, db);
    auto sourceAccount = accountHelper->loadAccount(source.key.getPublicKey(), db);

    ReviewableRequestFrame::pointer requestBeforeTx;

    if (requestID != 0) {
        requestBeforeTx = requestHelper->loadRequest(requestID, db);
    }

    auto txFrame = createUpdateKYCRequestTx(source, requestID,
            accountToUpdateKYC, roleIDToSet, kycData, allTasks);

    std::vector<LedgerDelta::KeyEntryMap> stateBeforeOps;
    mTestManager->applyCheck(txFrame, stateBeforeOps);

    auto txResult = txFrame->getResult();
    auto actualResultCode = CreateChangeRoleRequestOpFrame::getInnerCode(txResult.result.results()[0]);

    REQUIRE(actualResultCode == expectedResultCode);

    auto txFee = mTestManager->getApp().getLedgerManager().getTxFee();
    REQUIRE(txResult.feeCharged == txFee);

    auto accountAfter = accountHelper->loadAccount(accountToUpdateKYC, db);

    auto opResult = txResult.result.results()[0].tr().createChangeRoleRequestResult();

    if (actualResultCode != CreateChangeRoleRequestResultCode::SUCCESS) {

        if (requestBeforeTx) {
            auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
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

    if (allTasks != nullptr && *allTasks == 0) {
        return checkApprovedCreation(opResult, accountToUpdateKYC, stateBeforeOps[0]);
    }

    REQUIRE_FALSE(opResult.success().fulfilled);

    auto requestAfterTx = ReviewableRequestHelper::Instance()->loadRequest(requestID, db);
    REQUIRE(requestAfterTx);

    auto requestAfterTxEntry = requestAfterTx->getRequestEntry();
    auto referencePtr = getReference();

    REQUIRE(requestAfterTx->getReference() == referencePtr);
    REQUIRE(requestAfterTx->getRequestID() == requestID);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().destinationAccount == accountToUpdateKYC);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().accountRoleToSet == roleIDToSet);
    REQUIRE(requestAfterTxEntry.body.changeRoleRequest().creatorDetails == kycData);

    if (!!allTasks) {
        REQUIRE(requestAfterTxEntry.tasks.allTasks == *allTasks);
    } else {
        auto key = ManageKeyValueOpFrame::makeChangeRoleKey(
                accountBefore->getAccountRole(), roleIDToSet);
        auto kvEntry = KeyValueHelperLegacy::Instance()->loadKeyValue(key,db);
        REQUIRE(kvEntry);

        REQUIRE (kvEntry.get()->getKeyValue().value.type() == KeyValueEntryType::UINT32);
        auto tasks = kvEntry.get()->getKeyValue().value.ui32Value();

        REQUIRE(requestAfterTxEntry.tasks.allTasks == tasks);
    }

    REQUIRE(requestAfterTxEntry.tasks.pendingTasks ==
            requestAfterTxEntry.tasks.allTasks);

    if (requestBeforeTx) {
        auto requestBeforeTxEntry = requestBeforeTx->getRequestEntry();
        REQUIRE(requestAfterTxEntry.body.changeRoleRequest().sequenceNumber ==
                requestBeforeTxEntry.body.changeRoleRequest().sequenceNumber + 1);
    } else {
        REQUIRE(requestAfterTxEntry.body.changeRoleRequest().sequenceNumber == 0);
    }

    return opResult;
}

TransactionFramePtr
CreateChangeRoleTestHelper::createUpdateKYCRequestTx(Account &source, uint64_t requestID,
                                                     AccountID accountToUpdateKYC, uint64_t roleIDToSet,
                                                     longstring kycData, uint32 *allTasks) {
    Operation baseOp;
    baseOp.body.type(OperationType::CREATE_CHANGE_ROLE_REQUEST);
    auto &op = baseOp.body.createChangeRoleRequestOp();
    op.requestID = requestID;
    op.destinationAccount = accountToUpdateKYC;
    op.accountRoleToSet = roleIDToSet;
    op.creatorDetails = kycData;
    if (allTasks != nullptr) {
        op.allTasks.activate() = *allTasks;
    }

    return txFromOperation(source, baseOp, nullptr);
}

CreateChangeRoleRequestResult
CreateChangeRoleTestHelper::checkApprovedCreation(CreateChangeRoleRequestResult opResult,
                                                  AccountID accountToUpdateKYC,
                                                  LedgerDelta::KeyEntryMap stateBeforeOp) {
    REQUIRE(opResult.success().fulfilled);

    auto stateHelper = StateBeforeTxHelper(stateBeforeOp);
    auto requestFrame = stateHelper.getReviewableRequest(opResult.success().requestID);

    ReviewChangeRoleRequestChecker kycRequestChecker(mTestManager);
    kycRequestChecker.checkApprove(requestFrame);

    auto request = ReviewableRequestHelper::Instance()->loadRequest(opResult.success().requestID,
                                                                    accountToUpdateKYC,
                                                                    ReviewableRequestType::CHANGE_ROLE,
                                                                    mTestManager->getDB());
    REQUIRE_FALSE(request);

    return opResult;
}

xdr::pointer<string64> CreateChangeRoleTestHelper::getReference() {
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::CHANGE_ROLE));
    auto reference = binToHex(hash);
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));
    return referencePtr;
}
}
}
