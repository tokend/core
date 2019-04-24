#include "ManageAccountSpecificRuleOpFrame.h"
#include "CreatePollRequestOpFrame.h"
#include "CancelPollRequestOpFrame.h"

namespace stellar
{
ManageAccountSpecificRuleOpFrame::ManageAccountSpecificRuleOpFrame(
        const Operation& op, OperationResult& res, TransactionFrame& parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageAccountSpecificRule(mOperation.body.manageAccountSpecificRuleOp())
{
}

std::shared_ptr<ManageAccountSpecificRuleOpFrame>
ManageAccountSpecificRuleOpFrame::makeHelper(Operation const& op,
        OperationResult& res, TransactionFrame& tx)
{
    switch (op.body.manageAccountSpecificRuleOp().data.action())
    {
        case ManageAccountSpecificRuleAction::CREATE:
            return std::make_shared<CreateAccountSpecificRuleOpFrame>(op, res, tx);
        case ManageAccountSpecificRuleAction::REMOVE:
            return std::make_shared<RemoveAccountSpecificRuleOpFrame>(op, res, tx);
        default:
            throw std::runtime_error("Unexpected action in manage account specific rule op");
    }
}

} // namespace stellar
