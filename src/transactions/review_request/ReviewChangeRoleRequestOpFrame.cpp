#include <ledger/StorageHelperImpl.h>
#include "ReviewChangeRoleRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/AccountKYCHelper.h"

namespace stellar
{

ReviewChangeRoleRequestOpFrame::ReviewChangeRoleRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewChangeRoleRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                              LedgerManager& ledgerManager,
                                              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CHANGE_ROLE);

    if (ledgerManager.shouldUse(LedgerVersion::FIX_CHANGE_TO_NON_EXISTING_ROLE))
    {
        auto roleID = request->getRequestEntry().body.changeRoleRequest().accountRoleToSet;
        auto accountRole = storageHelper.getAccountRoleHelper().loadAccountRole(roleID);
        if (!accountRole)
        {
            innerResult().code(ReviewRequestResultCode::ACCOUNT_ROLE_TO_SET_DOES_NOT_EXIST);
            return false;
        }

    }

    auto& requestEntry = request->getRequestEntry();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    requestHelper.storeDelete(request->getKey());

    auto& changeRoleRequest = requestEntry.body.changeRoleRequest();
    auto destinationAccount = changeRoleRequest.destinationAccount;

    auto& accountHelper = storageHelper.getAccountHelper();

    auto destinationAccountFrame = accountHelper.mustLoadAccount(destinationAccount);

    // set KYC Data
    auto& kycHelper = storageHelper.getAccountKYCHelper();
    auto updatedKYC = kycHelper.loadAccountKYC(destinationAccount);
    if (!updatedKYC)
    {
        auto updatedKYCAccountFrame = AccountKYCFrame::createNew(destinationAccount, changeRoleRequest.creatorDetails);
        kycHelper.storeAdd(updatedKYCAccountFrame->mEntry);
    }
    else
    {
        updatedKYC->setKYCData(changeRoleRequest.creatorDetails);
        kycHelper.storeChange(updatedKYC->mEntry);
    }

    destinationAccountFrame->setAccountRole(changeRoleRequest.accountRoleToSet);
    accountHelper.storeChange(destinationAccountFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewChangeRoleRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager,
                                             ReviewableRequestFrame::pointer request)
{
    if (mReviewRequest.reviewDetails.tasksToRemove != 0)
    {
        innerResult().code(ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED);
        return false;
    }

    request->checkRequestType(ReviewableRequestType::CHANGE_ROLE);

    auto& requestEntry = request->getRequestEntry();
    requestEntry.tasks.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    if (!ledgerManager.shouldUse(LedgerVersion::FIX_CHANGE_ROLE_REJECT_TASKS))
    {
        requestEntry.tasks.pendingTasks = mReviewRequest.reviewDetails.tasksToAdd;
    }
    requestEntry.tasks.externalDetails.emplace_back(mReviewRequest.reviewDetails.externalDetails);

    request->setRejectReason(mReviewRequest.reason);

    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;

    storageHelper.getReviewableRequestHelper().storeChange(request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

bool ReviewChangeRoleRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}
}
