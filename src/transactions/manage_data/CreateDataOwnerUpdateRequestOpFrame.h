#pragma once

#include "ledger/ReviewableRequestFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class CreateDataOwnerUpdateRequestOpFrame : public OperationFrame
{

    CreateDataOwnerUpdateRequestOp const& mCreateDataOwnerUpdateRequestOp;

    CreateDataOwnerUpdateRequestResult& innerResult();
    void pickResultCode(CreateDataOwnerUpdateRequestResultCode code);

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

    std::vector<std::string> makeTasksKeyVector(StorageHelper& sh);

  public:
    CreateDataOwnerUpdateRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);
};
}
