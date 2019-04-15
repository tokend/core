#include "ManagePollOpFrame.h"
#include "ClosePollOpFrame.h"

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
        default:
            throw std::runtime_error("Unexpected action in manage poll op");
    }
}

} // namespace stellar
