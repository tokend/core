#include "CreateKYCRecoveryRequestOpFrame.h"
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/AccountHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/SignerHelper.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/KeyValueHelper.h"
#include <xdrpp/marshal.h>
#include <crypto/SHA.h>
#include "xdrpp/printer.h"
#include "ledger/LedgerDelta.h"
#include "ledger/SignerRuleFrame.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "InitiateKYCRecoveryOpFrame.h"
#include "ManageKeyValueOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CreateKYCRecoveryRequestOpFrame::CreateKYCRecoveryRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCreateKYCRecoveryRequestOp(mOperation.body.createKYCRecoveryRequestOp())
{
}

bool
CreateKYCRecoveryRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                           std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::KYC_RECOVERY);

    auto action = AccountRuleAction::CREATE;

    if (!(getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount))
    {
        action = AccountRuleAction::CREATE_FOR_OTHER;
        if (mCreateKYCRecoveryRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }
    if (getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount)
    {
        action = AccountRuleAction::CREATE;
        if (mCreateKYCRecoveryRequestOp.allTasks)
        {
            action = AccountRuleAction::CREATE_WITH_TASKS;
        }
    }
    result.emplace_back(resource, action, mSourceAccount);
    return true;
}

bool
CreateKYCRecoveryRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                          std::vector<SignerRequirement>& result,
                                                          LedgerManager& ledgerManager) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::KYC_RECOVERY);
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    SignerRuleAction action;
    if (mCreateKYCRecoveryRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateKYCRecoveryRequestOp.allTasks;
        action = SignerRuleAction::CREATE_WITH_TASKS;
        if (!(getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount))
            action = SignerRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
    }
    else {
        action = SignerRuleAction::CREATE;
        if (!(getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount))
            action = SignerRuleAction::CREATE_FOR_OTHER;

        if (!ledgerManager.shouldUse(LedgerVersion::FIX_CREATE_KYC_RECOVERY_PERMISSIONS))
        {
            action = SignerRuleAction::CREATE_WITH_TASKS;
            if (!(getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount))
                action = SignerRuleAction::CREATE_FOR_OTHER_WITH_TASKS;
        }
    }

    result.emplace_back(resource, action);

    return true;
}

bool
CreateKYCRecoveryRequestOpFrame::doCheckValid(Application& app)
{
    if (mCreateKYCRecoveryRequestOp.requestID != 0 && mCreateKYCRecoveryRequestOp.allTasks)
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }

    if (!isValidJson(mCreateKYCRecoveryRequestOp.creatorDetails))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mCreateKYCRecoveryRequestOp.signersData.size() == 0)
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::NO_SIGNER_DATA);
        return false;
    }

    set<PublicKey> usedKeys;
    for (auto& data : mCreateKYCRecoveryRequestOp.signersData)
    {
        if (usedKeys.find(data.publicKey) != usedKeys.end())
        {
            innerResult().code(CreateKYCRecoveryRequestResultCode::SIGNER_DUPLICATION);
            return false;
        }

        usedKeys.insert(data.publicKey);

        if (data.weight > SignerRuleFrame::threshold)
        {
            innerResult().code(CreateKYCRecoveryRequestResultCode::INVALID_WEIGHT);
            return false;
        }

        if (!isValidJson(data.details))
        {
            innerResult().code(CreateKYCRecoveryRequestResultCode::INVALID_DETAILS);
            return false;
        }
    }

    return true;
}

bool
CreateKYCRecoveryRequestOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();

    auto targetAccountID = mCreateKYCRecoveryRequestOp.targetAccount;
    auto& accountHelper = storageHelper.getAccountHelper();

    if (!InitiateKYCRecoveryOpFrame::isRecoveryAllowed(storageHelper))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::RECOVERY_NOT_ALLOWED);
        return false;
    }

    auto targetAccount = accountHelper.loadAccount(targetAccountID);
    if (!targetAccount)
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::TARGET_ACCOUNT_NOT_FOUND);
        return false;
    }

    if (mCreateKYCRecoveryRequestOp.requestID != 0)
        return updateRecoveryRequest(storageHelper, app);

    auto reference = getReference();
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));
    auto requestFrame = ReviewableRequestFrame::createNew(delta,
                                                          targetAccountID, app.getAdminID(),
                                                          referencePtr, ledgerManager.getCloseTime());

    auto requestHelper = ReviewableRequestHelper::Instance();
    if (requestHelper->isReferenceExist(db, targetAccountID, reference, requestFrame->getRequestID()))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::REQUEST_ALREADY_EXISTS);
        return false;
    }

    uint32 allTasks = 0;
    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    if (!keyValueHelper.loadTasks(allTasks,
        {ManageKeyValueOpFrame::makeCreateKYCRecoveryTasksKey()},
        mCreateKYCRecoveryRequestOp.allTasks.get()))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::KYC_RECOVERY_TASKS_NOT_FOUND);
        return false;
    }

    auto& requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::KYC_RECOVERY);

    createRequest(requestEntry, allTasks);

    requestFrame->recalculateHashRejectReason();

    requestHelper->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateKYCRecoveryRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;

    if (requestFrame->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(db, delta, app, requestFrame);
    }

    return true;
}

void
CreateKYCRecoveryRequestOpFrame::createRequest(ReviewableRequestEntry& requestEntry, uint32 defaultMask)
{
    auto& kycRecoveryRequest = requestEntry.body.kycRecoveryRequest();

    kycRecoveryRequest.signersData = mCreateKYCRecoveryRequestOp.signersData;
    kycRecoveryRequest.creatorDetails = mCreateKYCRecoveryRequestOp.creatorDetails;
    kycRecoveryRequest.targetAccount = mCreateKYCRecoveryRequestOp.targetAccount;
    kycRecoveryRequest.sequenceNumber = 0;

    requestEntry.tasks.allTasks = defaultMask;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
}

std::string
CreateKYCRecoveryRequestOpFrame::getReference()
{
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::KYC_RECOVERY));
    return binToHex(hash);
}

void
CreateKYCRecoveryRequestOpFrame::tryAutoApprove(Database& db, LedgerDelta& delta, Application& app,
                                                ReviewableRequestFrame::pointer requestFrame)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequest(mParentTx, app, ledgerManager, delta, requestFrame);
    if (result != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: tryApproveRequest expected to be success, but was: "
            << xdr::xdr_to_string(result);
        throw std::runtime_error("Unexpected state: tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled = true;
}

bool
CreateKYCRecoveryRequestOpFrame::updateRecoveryRequest(StorageHelper& storageHelper,
                                                       Application& app)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();

    // ensure that request is being updated legitimately
    if (!(getSourceID() == mCreateKYCRecoveryRequestOp.targetAccount))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST);
        return false;
    }

    auto request = ReviewableRequestHelper::Instance()->loadRequest(
        mCreateKYCRecoveryRequestOp.requestID, db, &delta);
    if (!request)
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& requestEntry = request->getRequestEntry();
    if (!ensureTargetNotChanged(requestEntry))
    {
        return false;
    }

    //update request
    updateRequest(requestEntry);

    request->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    innerResult().code(CreateKYCRecoveryRequestResultCode::SUCCESS);
    innerResult().success().requestID = mCreateKYCRecoveryRequestOp.requestID;
    return true;
}

bool
CreateKYCRecoveryRequestOpFrame::ensureTargetNotChanged(ReviewableRequestEntry& requestEntry)
{
    auto& kycRecoveryRequest = requestEntry.body.kycRecoveryRequest();

    if (!(kycRecoveryRequest.targetAccount == mCreateKYCRecoveryRequestOp.targetAccount))
    {
        innerResult().code(CreateKYCRecoveryRequestResultCode::INVALID_UPDATE_DATA);
        return false;
    }

    return true;
}

void
CreateKYCRecoveryRequestOpFrame::updateRequest(ReviewableRequestEntry& requestEntry)
{
    requestEntry.body.kycRecoveryRequest().creatorDetails = mCreateKYCRecoveryRequestOp.creatorDetails;
    requestEntry.body.kycRecoveryRequest().signersData = mCreateKYCRecoveryRequestOp.signersData;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.body.kycRecoveryRequest().sequenceNumber++;
}

}
