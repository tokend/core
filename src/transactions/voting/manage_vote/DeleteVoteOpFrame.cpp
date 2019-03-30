#include "DeleteVoteOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "main/Application.h"

namespace stellar
{
DeleteVoteOpFrame::DeleteVoteOpFrame(const Operation& op,
                                     OperationResult& res, TransactionFrame& parentTx)
    : ManageVoteOpFrame(op, res, parentTx)
{
}

bool
DeleteVoteOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                             std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::VOTE);
    uint64_t pollID = mManageVote.data.removeData().pollID;

    resource.vote().pollID = pollID;
    auto poll = storageHelper.getPollHelper().loadPoll(pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }

    resource.vote().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, AccountRuleAction::REMOVE, mSourceAccount);

    return true;
}

bool
DeleteVoteOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                            std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::VOTE);
    uint64_t pollID = mManageVote.data.removeData().pollID;

    resource.vote().pollID = pollID;
    auto poll = storageHelper.getPollHelper().loadPoll(pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }

    resource.vote().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, SignerRuleAction::REMOVE);

    return true;
}

bool
DeleteVoteOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    LedgerKey key(LedgerEntryType::VOTE);
    key.vote().pollID = mManageVote.data.removeData().pollID;
    key.vote().voterID = getSourceID();

    auto& voteHelper = storageHelper.getVoteHelper();

    if (!voteHelper.exists(key))
    {
        innerResult().code(ManageVoteResultCode::VOTE_NOT_FOUND);
        return false;
    }

    voteHelper.storeDelete(key);

    innerResult().code(ManageVoteResultCode::SUCCESS);

    return true;
}

bool DeleteVoteOpFrame::doCheckValid(stellar::Application& app)
{
    if (mManageVote.data.removeData().pollID == 0)
    {
        innerResult().code(ManageVoteResultCode::POLL_NOT_FOUND);
        return false;
    }

    return true;
}
}
