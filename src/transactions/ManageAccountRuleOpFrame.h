#pragma once

#include "transactions/OperationFrame.h"

#include <limits>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace stellar
{

class ManageAccountRuleOpFrame : public OperationFrame
{
  public:
    ManageAccountRuleOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    std::unordered_map<AccountID, CounterpartyDetails>
    getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;
    SourceDetails
    getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails>
                                counterpartiesDetails,
                            int32_t ledgerVersion) const override;

    static ManageAccountRuleResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageAccountRuleResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageAccountRuleResultCode>::enum_name(innerResult().code());
    }

  private:
    ManageAccountRuleOp const& mManageAccountRule;

    ManageAccountRuleResult&
    innerResult()
    {
        return mResult.tr().manageAccountRuleResult();
    }

    bool createOrUpdateRule(Application &app, StorageHelper &storageHelper);
    bool deleteAccountRule(Application &app, StorageHelper &storageHelper);
};

} // namespace stellar
