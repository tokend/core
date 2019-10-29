#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class RemoveAssetOpFrame : public OperationFrame
{
    RemoveAssetResult&
    innerResult()
    {
        return mResult.tr().removeAssetResult();
    }
    RemoveAssetOp const& mRemoveAsset;

    void deleteBalances(StorageHelper& storageHelper);
    bool deleteBalancesWithCheck(StorageHelper& storageHelper);

    bool tryGetOperationConditions(StorageHelper& storageHelper,
                                   std::vector<OperationCondition>& result,
                                   LedgerManager& ledgerManager) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

  public:
    RemoveAssetOpFrame(Operation const& op, OperationResult& res,
                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static RemoveAssetResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().removeAssetResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<RemoveAssetResultCode>::enum_name(
            innerResult().code());
    }
};

}