#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class RemoveAssetPairOpFrame : public OperationFrame
{
    RemoveAssetPairResult&
    innerResult()
    {
        return mResult.tr().removeAssetPairResult();
    }
    RemoveAssetPairOp const& mRemoveAssetPair;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result,
                              LedgerManager& ledgerManager) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    RemoveAssetPairOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static RemoveAssetPairResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().removeAssetPairResult().code();
    }
};

}