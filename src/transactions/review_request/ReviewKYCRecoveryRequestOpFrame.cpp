#include <ledger/StorageHelperImpl.h>
#include "ReviewKYCRecoveryRequestOpFrame.h"
#include "ReviewRequestHelper.h"
#include "transactions/ManageSignerOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/SignerHelper.h"
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

    if (!handleSigners(app, storageHelper, request))
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

    if (mReviewRequest.reviewDetails.tasksToRemove != 0)
    {
        innerResult().code(ReviewRequestResultCode::NON_ZERO_TASKS_TO_REMOVE_NOT_ALLOWED);
        return false;
    }

    auto& requestEntry = request->getRequestEntry();
    requestEntry.tasks.allTasks |= mReviewRequest.reviewDetails.tasksToAdd;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.tasks.externalDetails.emplace_back(mReviewRequest.reviewDetails.externalDetails);

    request->setRejectReason(mReviewRequest.reason);

    const auto newHash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = newHash;
    ReviewableRequestHelper::Instance()->storeChange(delta, db, request->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

bool
ReviewKYCRecoveryRequestOpFrame::handleSigners(Application& app, StorageHelper& storageHelper, ReviewableRequestFrame::pointer request)
{
    auto kycRecoveryRequest = request->getRequestEntry().body.kycRecoveryRequest();

    auto accountFrame = storageHelper.getAccountHelper().mustLoadAccount(kycRecoveryRequest.targetAccount);

    removeRecoverySigner(app, storageHelper, kycRecoveryRequest, accountFrame);
    if (!createSigners(app, storageHelper, kycRecoveryRequest, accountFrame))
    {
        innerResult().code(ReviewRequestResultCode::INVALID_SIGNER_DATA);
        return false;
    }

    return true;
}

void
ReviewKYCRecoveryRequestOpFrame::removeRecoverySigner(Application& app, StorageHelper& storageHelper, KYCRecoveryRequest request, AccountFrame::pointer account)
{
    auto signers = storageHelper.getSignerHelper().loadSigners(request.targetAccount);
    if (signers.size() != 1)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: expected account during recovery "
                                                  "to have exactly 1 signer, have" <<
                                               signers.size();
        throw std::runtime_error("Unexpected state: expected account during recovery to have exactly 1 signer");
    }

    Operation op;
    op.sourceAccount.activate() = request.targetAccount;
    op.body.type(OperationType::MANAGE_SIGNER);
    ManageSignerOp& manageSignerOp = op.body.manageSignerOp();

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_SIGNER);

    RemoveSignerData removeData;

    removeData.publicKey = signers[0]->getEntry().pubKey;
    manageSignerOp.data.action(ManageSignerAction::REMOVE);
    manageSignerOp.data.removeData() = removeData;

    ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

    manageSignerOpFrame.setSourceAccountPtr(account);
    if (!manageSignerOpFrame.doCheckValid(app) ||
        !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to delete recovery signer";
        throw std::runtime_error("Unexpected state: failed to delete recovery signer");
    }
}
bool
ReviewKYCRecoveryRequestOpFrame::createSigners(Application& app, StorageHelper& storageHelper, KYCRecoveryRequest request, AccountFrame::pointer account)
{
    Operation op;
    op.sourceAccount.activate() = request.targetAccount;
    op.body.type(OperationType::MANAGE_SIGNER);
    ManageSignerOp& manageSignerOp = op.body.manageSignerOp();

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_SIGNER);

    for (auto const& createData : request.signersData)
    {
        manageSignerOp.data.action(ManageSignerAction::CREATE);
        manageSignerOp.data.createData() = createData;

        ManageSignerOpFrame manageSignerOpFrame(op, opRes, mParentTx);

        manageSignerOpFrame.setSourceAccountPtr(account);

        if (!manageSignerOpFrame.doCheckValid(app) ||
            !manageSignerOpFrame.doApply(app, storageHelper, app.getLedgerManager()))
        {
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
