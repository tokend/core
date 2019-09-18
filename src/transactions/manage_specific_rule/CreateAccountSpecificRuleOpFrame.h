#pragma once

#include "ManageAccountSpecificRuleOpFrame.h"
#include "ledger/SaleFrame.h"

namespace stellar
{

class CreateAccountSpecificRuleOpFrame : public ManageAccountSpecificRuleOpFrame
{
    CreateAccountSpecificRuleData const& mCreateData;
    SaleFrame::pointer mSale = nullptr;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result, LedgerManager& lm) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result, LedgerManager& lm) const override;

    bool doCheckValid(Application& app) override;

    bool
    checkSaleRule(Application &app, StorageHelper &sh, uint64_t saleID);

    bool
    createSaleRule(Application &app, StorageHelper &sh, uint64_t saleID);

public:
    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    CreateAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);

    void
    setSale(SaleFrame::pointer const& sale)
    {
        mSale = sale;
    }
};
}
