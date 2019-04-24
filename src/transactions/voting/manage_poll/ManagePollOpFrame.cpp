#include "ManagePollOpFrame.h"
#include "ClosePollOpFrame.h"
#include "UpdatePollEndTimeOpFrame.h"
#include "CancelPollOpFrame.h"

namespace stellar
{
ManagePollOpFrame::ManagePollOpFrame(
        const Operation& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManagePoll(mOperation.body.managePollOp())
{
}

std::shared_ptr<ManagePollOpFrame>
ManagePollOpFrame::makeHelper(Operation const& op, OperationResult& res,
                                           TransactionFrame& tx)
{
    switch (op.body.managePollOp().data.action())
    {
        case ManagePollAction::CLOSE:
            return std::make_shared<ClosePollOpFrame>(op, res, tx);
        case ManagePollAction::CANCEL:
            return std::make_shared<CancelPollOpFrame>(op, res, tx);
        case ManagePollAction::UPDATE_END_TIME:
            return std::make_shared<UpdatePollEndTimeOpFrame>(op, res, tx);
        default:
            throw std::runtime_error("Unexpected action in manage poll op");
    }
}
bool ManagePollOpFrame::doCheckValid(Application& app)
{
    if (mManagePoll.pollID == 0)
    {
        innerResult().code(ManagePollResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

bool
ManagePollOpFrame::isAuthorized(AccountID adminID, PollFrame::pointer poll)
{
    return poll->getEntry().ownerID == getSourceID() || getSourceID() == adminID;
}

} // namespace stellar
