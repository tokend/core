#include "ManageCreatePollRequestOpFrame.h"
#include "CreatePollRequestOpFrame.h"
#include "CancelPollRequestOpFrame.h"

namespace stellar
{
ManageCreatePollRequestOpFrame::ManageCreatePollRequestOpFrame(
        const Operation& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageCreatePollRequest(mOperation.body.manageCreatePollRequestOp())
{
}

std::shared_ptr<ManageCreatePollRequestOpFrame>
ManageCreatePollRequestOpFrame::makeHelper(Operation const& op, OperationResult& res,
                                           TransactionFrame& tx)
{
    switch (op.body.manageCreatePollRequestOp().data.action())
    {
        case ManageCreatePollRequestAction::CREATE:
            return std::make_shared<CreatePollRequestOpFrame>(op, res, tx);
        case ManageCreatePollRequestAction::CANCEL:
            return std::make_shared<CancelPollRequestOpFrame>(op, res, tx);
        default:
            throw std::runtime_error("Unexpected action in manage create poll request op");
    }
}

} // namespace stellar