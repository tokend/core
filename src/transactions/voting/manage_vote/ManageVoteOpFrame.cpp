#include "ManageVoteOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/VoteHelper.h"
#include "ledger/PollHelper.h"
#include "ledger/VoteFrame.h"
#include "CreateVoteOpFrame.h"
#include "DeleteVoteOpFrame.h"
#include "main/Application.h"

namespace stellar
{
ManageVoteOpFrame::ManageVoteOpFrame(const Operation &op,
        OperationResult &res, TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx)
        , mManageVote(op.body.manageVoteOp())
{
}

ManageVoteOpFrame* ManageVoteOpFrame::make(Operation const& op,
                                             OperationResult& res,
                                             TransactionFrame& parentTx)
{
    const auto manageVote = op.body.manageVoteOp();
    switch (manageVote.data.action())
    {
        case ManageVoteAction::CREATE:
            return new CreateVoteOpFrame(op, res, parentTx);
        case ManageVoteAction::REMOVE:
            return new DeleteVoteOpFrame(op, res, parentTx);
        default:
            throw std::runtime_error("Unexpected manage vote action");

    }
}

}
