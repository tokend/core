#pragma once

#include "transactions/voting/manage_vote/ManageVoteOpFrame.h"
#include "ledger/PollFrame.h"

namespace stellar
{
class CreateVoteOpFrame : public ManageVoteOpFrame
{
    bool
    doApply(Application& app, StorageHelper& storageHelper,
            LedgerManager& ledgerManager) override;

    bool
    doCheckValid(Application& app) override;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    checkDates(PollFrame::pointer poll, LedgerManager& lm);

public:
    CreateVoteOpFrame(Operation const& op, OperationResult& res,
                      TransactionFrame& parentTx);

};


}
