#include "UpdatePollEndTimeOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "main/Application.h"

namespace stellar
{
UpdatePollEndTimeOpFrame::UpdatePollEndTimeOpFrame(const Operation& op, OperationResult& res,
                                   TransactionFrame& parentTx)
        : ManagePollOpFrame(op, res, parentTx)
        , mUpdatePollEndTimeData(op.body.managePollOp().data.updateTimeData())
{
}

bool
UpdatePollEndTimeOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
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
    result.emplace_back(resource, AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
UpdatePollEndTimeOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
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
    result.emplace_back(resource, SignerRuleAction::MANAGE);

    return true;
}

bool
UpdatePollEndTimeOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    auto& pollHelper = storageHelper.getPollHelper();

    auto poll = pollHelper.mustLoadPoll(mManagePoll.pollID);
    poll->getEntry().endTime = mUpdatePollEndTimeData.newEndTime;
    pollHelper.storeChange(poll->mEntry);

    innerResult().code(ManagePollResultCode::SUCCESS);
    return true;
}

bool UpdatePollEndTimeOpFrame::doCheckValid(Application& app)
{
    if (mManagePoll.pollID == 0)
    {
        innerResult().code(ManagePollResultCode::NOT_FOUND);
        return false;
    }

    if (mUpdatePollEndTimeData.newEndTime <= app.getLedgerManager().getCloseTime())
    {
        innerResult().code(ManagePollResultCode::INVALID_END_TIME);
        return false;
    }

    return true;
}

}
