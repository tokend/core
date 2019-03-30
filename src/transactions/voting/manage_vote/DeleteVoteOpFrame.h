#pragma once

#include "transactions/voting/manage_vote/ManageVoteOpFrame.h"

namespace stellar
{
class DeleteVoteOpFrame : public ManageVoteOpFrame
{
public:
    DeleteVoteOpFrame(Operation const& op, OperationResult& res,
                        TransactionFrame& parentTx);

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

};


}
