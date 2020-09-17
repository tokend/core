#pragma once

#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class CreateDataCreationRequestOpFrame : public OperationFrame
{

    CreateDataCreationRequestOp const& mCreateDataCreationRequestOp;

    CreateDataCreationRequestResult& innerResult();
    void pickResultCode(CreateDataCreationRequestResultCode code);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    void tryAutoApprove(Application& app, StorageHelper& storageHelper,
                        ReviewableRequestFrame::pointer request);

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        stellar::StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    bool createRequest(Application& app, StorageHelper& storageHelper,
                       LedgerManager& ledgerManager);

    bool updateRequest(Application& app, StorageHelper& storageHelper,
                       LedgerManager& ledgerManager);

    std::vector<std::string> makeTasksKeyVector();


  public:
    CreateDataCreationRequestOpFrame(Operation const& op, OperationResult& res,
                                     TransactionFrame& parentTx);
};
}
