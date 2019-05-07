#include "CreateChangeRoleRequestOpFrame.h"
#include <ledger/ReviewableRequestHelper.h>
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AccountRoleHelper.h"
#include <lib/xdrpp/xdrpp/marshal.h>
#include <crypto/SHA.h>
#include "xdrpp/printer.h"
#include "ledger/LedgerDelta.h"
#include "transactions/review_request/ReviewRequestHelper.h"
#include "ledger/KeyValueHelperLegacy.h"
#include "ManageKeyValueOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CreateChangeRoleRequestOpFrame::CreateChangeRoleRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx)
        , mCreateChangeRoleRequestOp(mOperation.body.createChangeRoleRequestOp())
{
}

bool
CreateChangeRoleRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                        std::vector<OperationCondition>& result) const
{
    auto destAccountID = mCreateChangeRoleRequestOp.destinationAccount;

    AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CHANGE_ROLE);

    if (!(getSourceID() == destAccountID) || (mCreateChangeRoleRequestOp.allTasks))
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    return true;
}

bool
CreateChangeRoleRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                        std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CHANGE_ROLE);
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateChangeRoleRequestOp.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateChangeRoleRequestOp.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

bool
CreateChangeRoleRequestOpFrame::ensureDestinationNotChanged(ReviewableRequestEntry &requestEntry)
{
    auto &changeRoleRequest = requestEntry.body.changeRoleRequest();

    if (!(changeRoleRequest.destinationAccount == mCreateChangeRoleRequestOp.destinationAccount))
    {
        return false;
    }
    if (changeRoleRequest.accountRoleToSet != mCreateChangeRoleRequestOp.accountRoleToSet)
    {
        return false;
    }
    return !mCreateChangeRoleRequestOp.allTasks;
}

bool
CreateChangeRoleRequestOpFrame::updateChangeRoleRequest(Database &db, LedgerDelta &delta,
                                                        Application &app)
{
    // ensure that logic is true
    if (!(getSourceID() == mCreateChangeRoleRequestOp.destinationAccount))
    {
        innerResult().code(CreateChangeRoleRequestResultCode::NOT_ALLOWED_TO_UPDATE_REQUEST);
        return false;
    }

    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            mCreateChangeRoleRequestOp.requestID, db, &delta);
    if (!request)
    {
        innerResult().code(CreateChangeRoleRequestResultCode::REQUEST_DOES_NOT_EXIST);
        return false;
    }

    auto &requestEntry = request->getRequestEntry();
    if (!ensureDestinationNotChanged(requestEntry))
    {
        innerResult().code(CreateChangeRoleRequestResultCode::INVALID_CHANGE_ROLE_REQUEST_DATA);
        return false;
    }

    updateRequest(requestEntry);

    request->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    innerResult().code(CreateChangeRoleRequestResultCode::SUCCESS);
    innerResult().success().requestID = mCreateChangeRoleRequestOp.requestID;
    return true;
}

bool
CreateChangeRoleRequestOpFrame::doApply(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager)
{
    Database& db = ledgerManager.getDatabase();
    StorageHelperImpl storageHelperImpl(db, &delta);
    StorageHelper& storageHelper = storageHelperImpl;

    if (ledgerManager.shouldUse(LedgerVersion::FIX_CHANGE_TO_NON_EXISTING_ROLE))
    {
        auto roleID = mCreateChangeRoleRequestOp.accountRoleToSet;
        auto accountRole = storageHelper.getAccountRoleHelper().loadAccountRole(roleID);
        if(!accountRole)
        {
            innerResult().code(CreateChangeRoleRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST);
            return false;
        }
    }

    if (mCreateChangeRoleRequestOp.requestID != 0)
    {
        return updateChangeRoleRequest(db, delta, app);
    }

    auto accountHelper = AccountHelperLegacy::Instance();
    auto accountFrame = accountHelper->loadAccount(delta,
            mCreateChangeRoleRequestOp.destinationAccount, db);
    if (!accountFrame)
    {
        innerResult().code(CreateChangeRoleRequestResultCode::ACC_TO_UPDATE_DOES_NOT_EXIST);
        return false;
    }

    auto reference = getReference();
    const auto referencePtr = xdr::pointer<string64>(new string64(reference));
    auto requestFrame = ReviewableRequestFrame::createNew(delta,
            mCreateChangeRoleRequestOp.destinationAccount, app.getAdminID(),
            referencePtr, ledgerManager.getCloseTime());

    auto requestHelper = ReviewableRequestHelper::Instance();
    if (requestHelper->isReferenceExist(db, mCreateChangeRoleRequestOp.destinationAccount,
                                        reference, requestFrame->getRequestID()))
    {
        innerResult().code(CreateChangeRoleRequestResultCode::REQUEST_ALREADY_EXISTS);
        return false;
    }

    uint32 defaultMask;
    if(!loadTasks(storageHelper, defaultMask, mCreateChangeRoleRequestOp.allTasks))
    {
        innerResult().code(CreateChangeRoleRequestResultCode::CHANGE_ROLE_TASKS_NOT_FOUND);
        return false;
    }

    auto &requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CHANGE_ROLE);

    createRequest(requestEntry, defaultMask);

    requestFrame->recalculateHashRejectReason();

    requestHelper->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateChangeRoleRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;

    if (requestFrame->canBeFulfilled(ledgerManager))
        tryAutoApprove(db, delta, app, requestFrame);

    return true;
}

void
CreateChangeRoleRequestOpFrame::tryAutoApprove(Database &db, LedgerDelta &delta, Application &app,
                                               ReviewableRequestFrame::pointer requestFrame)
{
    auto &ledgerManager = app.getLedgerManager();
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
CreateChangeRoleRequestOpFrame::doCheckValid(Application &app)
{
    if (!isValidJson(mCreateChangeRoleRequestOp.creatorDetails))
    {
        innerResult().code(CreateChangeRoleRequestResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

std::string
CreateChangeRoleRequestOpFrame::getReference() const
{
    const auto hash = sha256(xdr::xdr_to_opaque(ReviewableRequestType::CHANGE_ROLE));
    return binToHex(hash);
}

void
CreateChangeRoleRequestOpFrame::createRequest(ReviewableRequestEntry &requestEntry, uint32 defaultMask)
{
    auto& changeRoleRequest = requestEntry.body.changeRoleRequest();

    changeRoleRequest.destinationAccount = mCreateChangeRoleRequestOp.destinationAccount;
    changeRoleRequest.accountRoleToSet = mCreateChangeRoleRequestOp.accountRoleToSet;
    changeRoleRequest.creatorDetails = mCreateChangeRoleRequestOp.creatorDetails;
    changeRoleRequest.sequenceNumber = 0;

    requestEntry.tasks.allTasks = defaultMask;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
}

std::vector<longstring>
CreateChangeRoleRequestOpFrame::makeTasksKeyVector(StorageHelper &storageHelper)
{
    auto account = storageHelper.getAccountHelper().mustLoadAccount(
            mCreateChangeRoleRequestOp.destinationAccount);

    return std::vector<longstring>
    {
        ManageKeyValueOpFrame::makeChangeRoleKey(to_string(account->getAccountRole()),
                                                 to_string(mCreateChangeRoleRequestOp.accountRoleToSet)),
        ManageKeyValueOpFrame::makeChangeRoleKey("*",
                                                 to_string(mCreateChangeRoleRequestOp.accountRoleToSet)),
        ManageKeyValueOpFrame::makeChangeRoleKey(to_string(account->getAccountRole()),
                                                 "*"),
        ManageKeyValueOpFrame::makeChangeRoleKey("*", "*"),
    };
};

void
CreateChangeRoleRequestOpFrame::updateRequest(ReviewableRequestEntry &requestEntry)
{
    requestEntry.body.changeRoleRequest().creatorDetails = mCreateChangeRoleRequestOp.creatorDetails;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.body.changeRoleRequest().sequenceNumber++;
}
}
