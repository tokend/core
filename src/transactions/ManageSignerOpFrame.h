#pragma once

#include "OperationFrame.h"

namespace stellar
{
class ManageSignerOpFrame : public OperationFrame
{
public:
    ManageSignerOpFrame(Operation const& op, OperationResult& res,
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

    static ManageSignerResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageSignerResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageSignerResultCode>::enum_name(innerResult().code());
    }

private:
    ManageSignerOp const& mManageSigner;

    ManageSignerResult&
    innerResult()
    {
        return mResult.tr().manageSignerResult();
    }

    bool
    createSigner(Application& app, StorageHelper& storageHelper);

    bool
    updateSigner(Application &app, StorageHelper &storageHelper);

    bool
    deleteSigner(Application &app, StorageHelper &storageHelper);
};


}
