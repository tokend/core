#pragma "once"

#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageAccountRoleOpFrame : public OperationFrame
{
  public:
    ManageAccountRoleOpFrame(Operation const& op, OperationResult& res,
                             TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static ManageAccountRoleResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageAccountRoleResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageAccountRoleResultCode>::enum_name(
            innerResult().code());
    }

  private:
    ManageAccountRoleResult&
    innerResult()
    {
        return mResult.tr().manageAccountRoleResult();
    }

    ManageAccountRoleOp const& mManageAccountRole;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool createAccountRole(Application& app, StorageHelper& storageHelper);
    bool updateAccountRole(Application& app, StorageHelper& storageHelper);
    bool deleteAccountRole(Application& app, StorageHelper& storageHelper);

    bool checkRulesExisting(StorageHelper& storageHelper, std::vector<uint64_t> ruleIDs);
};
} // namespace stellar