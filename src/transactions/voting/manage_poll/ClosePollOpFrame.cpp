#include "ClosePollOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "main/Application.h"

namespace stellar
{
ClosePollOpFrame::ClosePollOpFrame(const Operation& op, OperationResult& res,
                                   TransactionFrame& parentTx)
        : ManagePollOpFrame(op, res, parentTx)
        , mClosePollData(op.body.managePollOp().data.closePollData())
{
}

bool
ClosePollOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
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
    result.emplace_back(resource, AccountRuleAction::CLOSE, mSourceAccount);

    return true;
}

bool
ClosePollOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
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
    result.emplace_back(resource, SignerRuleAction::CLOSE);

    return true;
}

bool
ClosePollOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                           LedgerManager& ledgerManager)
{
    auto& pollHelper = storageHelper.getPollHelper();

    auto poll = pollHelper.mustLoadPoll(mManagePoll.pollID);

    if (!(poll->getResultProvider() == getSourceID()))
    {
        innerResult().code(ManagePollResultCode::NOT_AUTHORIZED_TO_CLOSE_POLL);
        return false;
    }

    if (ledgerManager.getCloseTime() <= poll->getEntry().endTime)
    {
        innerResult().code(ManagePollResultCode::POLL_NOT_READY);
        return false;
    }

    pollHelper.storeDelete(poll->getKey());

    innerResult().code(ManagePollResultCode::SUCCESS);
    return true;
}

bool ClosePollOpFrame::doCheckValid(Application& app)
{
    if (mManagePoll.pollID == 0)
    {
        innerResult().code(ManagePollResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

}
