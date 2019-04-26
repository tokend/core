#include "CreateAccountSpecificRuleOpFrame.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AccountSpecificRuleFrame.h"
#include "ledger/AccountSpecificRuleHelper.h"
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
            return createSaleRuleWithChecks(app, storageHelper,
                                            mCreateData.ledgerKey.sale().saleID);
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected entry type on "
                               << "creating account specific rule entry, type: "
                               << static_cast<int32_t>(mCreateData.ledgerKey.type());
            throw std::runtime_error("Unexpected entry type on creating account specific rule entry");
    }
}

bool
CreateAccountSpecificRuleOpFrame::createSaleRuleWithChecks(Application &app,
        StorageHelper &sh, uint64_t saleID)
{
    auto saleHelper = SaleHelper::Instance();
    auto sale = saleHelper->loadSale(saleID, sh.getDatabase(), sh.getLedgerDelta());
    if (!sale)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND);
        return false;
    }

    //  not sale owner and not admin
    if (!isAuthorized(sale->getOwnerID(), app.getAdminID()))
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED);
        return false;
    }

    auto existingRule = sh.getAccountSpecificRuleHelper().loadRule(
            mCreateData.ledgerKey, mCreateData.accountID.get(), true);

    if (!existingRule)
    {
        return createSaleRule(sh);
    }

    if (existingRule->forbids() == mCreateData.forbids)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::ALREADY_EXISTS);
        return false;
    }

    innerResult().code(ManageAccountSpecificRuleResultCode::REVERSED_ALREADY_EXISTS);
    return false;
}

bool
CreateAccountSpecificRuleOpFrame::createSaleRule(StorageHelper& sh)
{
    auto ruleID = sh.mustGetLedgerDelta().getHeaderFrame()
            .generateID(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);
    auto frame = std::make_shared<AccountSpecificRuleFrame>(ruleID, mCreateData);

    sh.getAccountSpecificRuleHelper().storeAdd(frame->mEntry);

    innerResult().code(ManageAccountSpecificRuleResultCode::SUCCESS);
    innerResult().success().ruleID = ruleID;
    return true;
}

bool
CreateAccountSpecificRuleOpFrame::doCheckValid(Application &app)
{
    switch (mCreateData.ledgerKey.type())
    {
        case LedgerEntryType::SALE:
            if (mCreateData.ledgerKey.sale().saleID == 0)
            {
                innerResult().code(ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND);
                return false;
            }
            break;
        default:
            innerResult().code(ManageAccountSpecificRuleResultCode::ENTRY_TYPE_NOT_SUPPORTED);
            return false;
    }

    return true;
}
}