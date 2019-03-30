#include "CreateVoteOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "main/Application.h"

namespace stellar
{
CreateVoteOpFrame::CreateVoteOpFrame(const Operation& op, OperationResult& res,
                                     TransactionFrame& parentTx)
        : ManageVoteOpFrame(op, res, parentTx)
{
}

bool
CreateVoteOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                         std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::VOTE);
    auto pollID = mManageVote.data.createData().pollID;
    resource.vote().pollID = pollID;

    auto poll = storageHelper.getPollHelper().loadPoll(pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }
    resource.vote().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateVoteOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                        std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::VOTE);

    auto pollID = mManageVote.data.createData().pollID;
    resource.vote().pollID = pollID;

    auto poll = storageHelper.getPollHelper().loadPoll(pollID);
    if (!poll)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::POLL;
        return false;
    }

    resource.vote().permissionType = poll->getEntry().permissionType;
    result.emplace_back(resource, SignerRuleAction::CREATE);

    if (poll->getEntry().voteConfirmationRequired)
    {
        auto resultProvider = std::make_shared<AccountID>(poll->getResultProvider());
        result.emplace_back(resource, SignerRuleAction::CREATE_FOR_OTHER, resultProvider);
    }

    return true;
}

bool
CreateVoteOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    auto createData = mManageVote.data.createData();
    auto& voteHelper = storageHelper.getVoteHelper();
    if (voteHelper.exists(createData.pollID, getSourceID()))
    {
        innerResult().code(ManageVoteResultCode::VOTE_EXISTS);
        return false;
    }

    auto poll = storageHelper.getPollHelper().mustLoadPoll(createData.pollID);
    if (poll->getEntry().data.type() != createData.data.pollType())
    {
        innerResult().code(ManageVoteResultCode::POLL_TYPE_MISMATCHED);
        return false;
    }

    if (!checkDates(poll, ledgerManager))
    {
        return false;
    }

    LedgerEntry le;
    le.data.type(LedgerEntryType::VOTE);
    auto& voteEntry = le.data.vote();
    voteEntry.pollID = createData.pollID;
    voteEntry.voterID = getSourceID();
    voteEntry.data = createData.data;

    voteHelper.storeAdd(le);

    innerResult().code(ManageVoteResultCode::SUCCESS);
    return true;
}

bool CreateVoteOpFrame::doCheckValid(Application& app)
{
    if (mManageVote.data.createData().pollID == 0)
    {
        innerResult().code(ManageVoteResultCode::POLL_NOT_FOUND);
        return false;
    }

    return true;
}

bool
CreateVoteOpFrame::checkDates(PollFrame::pointer poll, LedgerManager& lm)
{
    if (lm.getCloseTime() > poll->getEntry().endTime)
    {
        innerResult().code(ManageVoteResultCode::POLL_ENDED);
        return false;
    }

    if (lm.getCloseTime() < poll->getEntry().startTime)
    {
        innerResult().code(ManageVoteResultCode::POLL_NOT_STARTED);
        return false;
    }

    return true;
}

}
