#include <ledger/StorageHelperImpl.h>
#include "ReviewKYCRecoveryRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "transactions/ManageSignerOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountRoleHelper.h"
#include "ledger/AccountKYCHelper.h"

namespace stellar
{

ReviewKYCRecoveryRequestOpFrame::ReviewKYCRecoveryRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool
ReviewKYCRecoveryRequestOpFrame::handleApprove(Application& app, LedgerDelta& delta,
                                               LedgerManager& ledgerManager,
                                               ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::KYC_RECOVERY);

    Database& db = ledgerManager.getDatabase();
    StorageHelperImpl storageHelperImpl(db, &delta);
    StorageHelper& storageHelper = storageHelperImpl;

    auto& requestEntry = request->getRequestEntry();

    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    if (!createSigners(app, storageHelper, request))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_SIGNER_DATA);
        return false;
    }

    EntryHelperProvider::storeDeleteEntry(delta, db, request->getKey());

    auto& kycRecoveryRequest = requestEntry.body.kycRecoveryRequest();

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewKYCRecoveryRequestOpFrame::handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::KYC_RECOVERY);

    Database& db = ledgerManager.getDatabase();

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

bool
ReviewKYCRecoveryRequestOpFrame::createSigners(Application& app, StorageHelper& storageHelper, ReviewableRequestFrame::pointer request)
{
    auto kycRecoveryRequest = request->getRequestEntry().body.kycRecoveryRequest();

    auto accountFrame = storageHelper.getAccountHelper().mustLoadAccount(
        kycRecoveryRequest.targetAccount);

    Operation op;
    op.sourceAccount.activate() = accountFrame->getID();
    op.body.type(OperationType::MANAGE_SIGNER);
    ManageSignerOp& manageSignerOp = op.body.manageSignerOp();
    manageSignerOp.data.action(ManageSignerAction::CREATE);

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_SIGNER);

    for (auto const& createData : kycRecoveryRequest.signersData)
    {
        manageSignerOp.data.createData() = createData;

        ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

        manageSignerOpFrame.setSourceAccountPtr(accountFrame);

        if (!manageSignerOpFrame.doCheckValid(app) ||
            !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
        {
            innerResult().code(ReviewRequestResultCode::INVALID_SIGNER_DATA);
            return false;
        }
    }

    return true;
}

bool ReviewKYCRecoveryRequestOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mReviewRequest.reviewDetails.externalDetails))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_EXTERNAL_DETAILS);
        return false;
    }

    return true;
}
}
