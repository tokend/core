#include "ReviewCreatePollRequestOpFrame.h"
#include "database/Database.h"
#include "main/Application.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/LedgerDelta.h"
#include <ledger/PollFrame.h>
#include <ledger/PollHelper.h>
#include "ledger/StorageHelperImpl.h"
#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewCreatePollRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                           std::vector<SignerRequirement>& result) const
{
    auto request = ReviewableRequestHelper::Instance()->loadRequest(
            mReviewRequest.requestID, storageHelper.getDatabase());
    if (!request || (request->getType() != ReviewableRequestType::CREATE_POLL))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_POLL);
    resource.reviewableRequest().details.createPoll().permissionType =
            request->getRequestEntry().body.createPollRequest().permissionType;
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

bool
ReviewCreatePollRequestOpFrame::handleApprove(Application& app, LedgerDelta& delta,
        LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    request->checkRequestType(ReviewableRequestType::CREATE_POLL);

    Database& db = app.getDatabase();

    handleTasks(db, delta, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    ReviewableRequestHelper::Instance()->storeDelete(delta, db, request->getKey());

    auto newPollID = delta.getHeaderFrame().generateID(LedgerEntryType::POLL);

    auto pollFrame = PollFrame::createNew(newPollID,
            request->getRequestEntry().body.createPollRequest(), request->getRequestor());

    StorageHelperImpl storageHelperImpl(db, &delta);
    StorageHelper& storageHelper = storageHelperImpl;
    storageHelper.getPollHelper().storeAdd(pollFrame->mEntry);

    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_POLL);
    innerResult().success().typeExt.createPoll().pollID = newPollID;
    return true;
}

bool
ReviewCreatePollRequestOpFrame::handleReject(Application &app, LedgerDelta &delta,
        LedgerManager &ledgerManager, ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewCreatePollRequestOpFrame::ReviewCreatePollRequestOpFrame(Operation const& op,
        OperationResult& res, TransactionFrame& parentTx)
        : ReviewRequestOpFrame(op, res, parentTx)
{
}
}
