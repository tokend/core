#pragma once

#include "ledger/DataFrame.h"
#include "transactions/OperationFrame.h"

namespace stellar
{
class UpdateDataOpFrame : public OperationFrame
{
    UpdateDataOp const& mUpdateData;

    bool isAuthorized(DataFrame::pointer dataFrame, AccountID admin);

    bool doCheckValid(Application& app) override;

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    UpdateDataResult&
    innerResult()
    {
        return mResult.tr().updateDataResult();
    }

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    std::string getInnerResultCodeAsStr() override;

  public:
    UpdateDataOpFrame(Operation const& op, OperationResult& res,
                      TransactionFrame& parentTx);
};
}