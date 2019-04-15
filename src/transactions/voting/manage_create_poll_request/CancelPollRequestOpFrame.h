#pragma once

#include "ManageCreatePollRequestOpFrame.h"

namespace stellar
{

class CancelPollRequestOpFrame : public ManageCreatePollRequestOpFrame
{
    CancelPollRequestData const& mCancelPollRequestData;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:
    CancelPollRequestOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};


}

