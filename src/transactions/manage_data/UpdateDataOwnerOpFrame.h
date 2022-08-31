#pragma once

#include "ledger/DataFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class UpdateDataOwnerOpFrame : public OperationFrame
{
    UpdateDataOwnerOp const& mUpdateDataOwner;

    UpdateDataOwnerResult&
    innerResult()
    {
        return mResult.tr().updateDataOwnerResult();
    }

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    std::string getInnerResultCodeAsStr() override;

  public:
    UpdateDataOwnerOpFrame(Operation const& op, OperationResult& res,
                      TransactionFrame& parentTx);
    bool doCheckValid(Application& app) override;

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
};
}