#include "CancelPollOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "main/Application.h"

namespace stellar
{
CancelPollOpFrame::CancelPollOpFrame(const Operation& op, OperationResult& res,
                                   TransactionFrame& parentTx)
        : ManagePollOpFrame(op, res, parentTx)
{
}

bool
CancelPollOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                             std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::POLL);

    resource.poll().pollID = mManagePoll.pollID;
    auto poll = storageHelper.getPollHelper().loadPoll(mManagePoll.pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }

    resource.poll().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, AccountRuleAction::CANCEL, mSourceAccount);

    return true;
}

bool
CancelPollOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                            std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::POLL);

    resource.poll().pollID = mManagePoll.pollID;
    auto poll = storageHelper.getPollHelper().loadPoll(mManagePoll.pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }

    resource.poll().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelPollOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    auto& pollHelper = storageHelper.getPollHelper();

    // Poll existence is being check on rules checking stage
    auto poll = pollHelper.mustLoadPoll(mManagePoll.pollID);
    if (!isAuthorized(app.getAdminID(), poll))
    {
        innerResult().code(ManagePollResultCode::NOT_AUTHORIZED);
        return false;
    }
    auto& voteHelper = storageHelper.getVoteHelper();
    voteHelper.deleteForPoll(poll->getEntry().id);
    pollHelper.storeDelete(poll->getKey());


    innerResult().code(ManagePollResultCode::SUCCESS);
    return true;
}

}
