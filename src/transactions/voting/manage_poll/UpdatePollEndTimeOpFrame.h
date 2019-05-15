#pragma once

#include "ManagePollOpFrame.h"
#include "ledger/PollFrame.h"

namespace stellar
{
class UpdatePollEndTimeOpFrame : public ManagePollOpFrame
{
public:
    UpdatePollEndTimeOpFrame(Operation const& op, OperationResult& res,
                        TransactionFrame& parentTx);

    bool
    doApply(Application& app, StorageHelper& storageHelper,
            LedgerManager& ledgerManager);

    bool
    doCheckValid(Application& app);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const;

private:
    UpdatePollEndTimeData const& mUpdatePollEndTimeData;

};


}
