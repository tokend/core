#include "CreateAccountSpecificRuleOpFrame.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{

CreateAccountSpecificRuleOpFrame::CreateAccountSpecificRuleOpFrame(
        const Operation &op, OperationResult &res, TransactionFrame &parentTx)
        : ManageAccountSpecificRuleOpFrame(op, res, parentTx)
        , mCreateData(mManageAccountSpecificRule.data.createData())
{
}

bool
CreateAccountSpecificRuleOpFrame::tryGetOperationConditions(
        StorageHelper &storageHelper,std::vector<OperationCondition> &result) const
{
    // only admin or entry owner can perform such operation
    return true;
}

bool
CreateAccountSpecificRuleOpFrame::tryGetSignerRequirements(
        StorageHelper &storageHelper, std::vector<SignerRequirement> &result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE), SignerRuleAction::CREATE);
    return true;
}

bool
CreateAccountSpecificRuleOpFrame::doApply(Application &app,
        StorageHelper &storageHelper, LedgerManager &ledgerManager)
{
    switch (mCreateData.ledgerKey.type())
    {
        case LedgerEntryType::SALE:
            createSaleRule(app, storageHelper, mCreateData.ledgerKey.sale().saleID);
        default:
            innerResult().code(ManageAccountSpecificRuleResultCode::ENTRY_TYPE_NOT_SUPPORTED);
    }
}

bool
CreateAccountSpecificRuleOpFrame::createSaleRule(Application& app,
        StorageHelper& sh, uint64_t id)
{
    auto saleHelper = SaleHelper::Instance();
    auto sale = saleHelper->loadSale(id, sh.getDatabase(), sh.getLedgerDelta());
    if (!sale)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND);
        return false;
    }

    //  not sale owner and not admin
    if (!(sale->getOwnerID() == getSourceID()) && !(app.getAdminID() == getSourceID()))
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_AUTORIZED);
        return false;
    }


}
}