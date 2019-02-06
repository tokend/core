#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{

class ManageSignerRuleOpFrame : public OperationFrame
{
public:
    ManageSignerRuleOpFrame(Operation const& op, OperationResult& res,
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

    static ManageSignerRuleResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageSignerRuleResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageSignerRuleResultCode>::enum_name(innerResult().code());
    }

private:
    ManageSignerRuleOp const& mManageSignerRule;

    ManageSignerRuleResult&
    innerResult()
    {
        return mResult.tr().manageSignerRuleResult();
    }

    bool
    createRule(Application& app, StorageHelper& storageHelper);

    bool
    updateRule(Application &app, StorageHelper &storageHelper);

    bool
    deleteRule(Application &app, StorageHelper &storageHelper);

    bool
    isRuleUsed(StorageHelper &storageHelper, uint64_t ruleID);
};
}

