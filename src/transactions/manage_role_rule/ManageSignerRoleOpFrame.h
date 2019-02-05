#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class ManageSignerRoleOpFrame : public OperationFrame
{
public:
    ManageSignerRoleOpFrame(Operation const& op, OperationResult& res,
                            TransactionFrame& parentTx);

    bool
    doApply(Application& app, StorageHelper& storageHelper,
            LedgerManager& ledgerManager) override;

    bool
    doCheckValid(Application& app) override;

    static ManageSignerRoleResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageSignerRoleResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageSignerRoleResultCode>::enum_name(
                innerResult().code());
    }

private:
    ManageSignerRoleResult&
    innerResult()
    {
        return mResult.tr().manageSignerRoleResult();
    }

    ManageSignerRoleOp const& mManageSignerRole;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    bool
    createRole(Application& app, StorageHelper& storageHelper);

    bool
    updateRole(Application& app, StorageHelper& storageHelper);

    bool
    deleteRole(Application& app, StorageHelper& storageHelper);

    bool
    checkRulesExisting(StorageHelper& storageHelper, std::vector<uint64_t> ruleIDs);
};


}
