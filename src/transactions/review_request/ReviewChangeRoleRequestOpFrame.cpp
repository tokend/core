#include "ReviewChangeRoleRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelperLegacy.h"
#include "ledger/AccountKYCHelper.h"

namespace stellar
{

ReviewChangeRoleRequestOpFrame::ReviewChangeRoleRequestOpFrame(
        Operation const &op, OperationResult &res, TransactionFrame &parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewChangeRoleRequestOpFrame::handleApprove(Application &app, LedgerDelta &delta,
                                              LedgerManager &ledgerManager,
                                              ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CHANGE_ROLE);

    Database &db = ledgerManager.getDatabase();

    auto& requestEntry = request->getRequestEntry();
    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    auto& changeRoleRequest = requestEntry.body.changeRoleRequest();
    auto destinationAccount = changeRoleRequest.destinationAccount;
    auto destinationAccountFrame = AccountHelperLegacy::Instance()->loadAccount(destinationAccount, db);
    if (!destinationAccountFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. Requestor account not found.";
        throw std::runtime_error("Unexpected state. Updated account not found.");
    }

    // set KYC Data
    auto kycHelper = AccountKYCHelper::Instance();
    auto updatedKYC = kycHelper->loadAccountKYC(destinationAccount, db, &delta);
    if (!updatedKYC)
    {
        auto updatedKYCAccountFrame = AccountKYCFrame::createNew(destinationAccount, changeRoleRequest.kycData);
        kycHelper->storeAdd(delta, db, updatedKYCAccountFrame->mEntry);
    }
    else
    {
        updatedKYC->setKYCData(changeRoleRequest.kycData);
        kycHelper->storeChange(delta, db, updatedKYC->mEntry);
    }

    destinationAccountFrame->setAccountRole(changeRoleRequest.accountRoleToSet);
    EntryHelperProvider::storeChangeEntry(delta, db, destinationAccountFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewChangeRoleRequestOpFrame::handleReject(Application &app, LedgerDelta &delta,
                                             LedgerManager &ledgerManager,
                                             ReviewableRequestFrame::pointer request)
{
    if (mReviewRequest.reviewDetails.tasksToRemove != 0)
    {
        innerResult().code(ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED);
        return false;
    }

    request->checkRequestType(ReviewableRequestType::CHANGE_ROLE);

    Database &db = ledgerManager.getDatabase();

    auto& requestEntry = request->getRequestEntry();
    requestEntry.tasks.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.pendingTasks = mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.externalDetails.emplace_back(mReviewRequest.reviewDetails.externalDetails);

    request->setRejectReason(mReviewRequest.reason);

    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;
    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

bool ReviewChangeRoleRequestOpFrame::doCheckValid(Application &app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}
}