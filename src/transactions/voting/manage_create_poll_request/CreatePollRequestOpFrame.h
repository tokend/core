#pragma once

#include "ManageCreatePollRequestOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{

class CreatePollRequestOpFrame : public ManageCreatePollRequestOpFrame
{
    CreatePollRequestData const& mCreatePollRequestData;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    tryPopulateRequest(StorageHelper &storageHelper,
                       ReviewableRequestEntry &requestEntry);

    void
    tryAutoApprove(Application& app, StorageHelper& storageHelper,
                   ReviewableRequestFrame::pointer request);

    bool
    checkDates(LedgerManager& lm);

    std::vector<std::string>
    makeTasksKeys() const;

public:
    CreatePollRequestOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};


}
