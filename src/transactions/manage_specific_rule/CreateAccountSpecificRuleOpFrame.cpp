#include "CreateAccountSpecificRuleOpFrame.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AccountSpecificRuleFrame.h"
#include "ledger/AccountSpecificRuleHelper.h"
#include "ledger/AccountHelper.h"
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
CreateAccountSpecificRuleOpFrame::tryGetOperationConditions(StorageHelper& storageHelper, std::vector<OperationCondition>& result, LedgerManager& ledgerManager) const
{
    if(!ledgerManager.shouldUse(LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE))
    {
        return true;
    }

    AccountRuleResource resource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);
    auto ledgerKey = mCreateData.ledgerKey;
    resource.ext().v(LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE);
    resource.ext().accountSpecificRule().ledgerKey = ledgerKey;
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    return true;
}



bool
CreateAccountSpecificRuleOpFrame::tryGetSignerRequirements(
        StorageHelper &storageHelper, std::vector<SignerRequirement> &result, LedgerManager& lm) const
{
    if(!lm.shouldUse(LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE)){
        result.emplace_back(SignerRuleResource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE), SignerRuleAction::CREATE);
        return true;
    }

    SignerRuleResource resource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);
    auto ledgerKey = mCreateData.ledgerKey;
    resource.ext().v(LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE);
    resource.ext().accountSpecificRule().ledgerKey = ledgerKey;
    result.emplace_back(resource, SignerRuleAction::CREATE);
    return true;
}

bool
CreateAccountSpecificRuleOpFrame::doApply(Application &app,
        StorageHelper &storageHelper, LedgerManager &ledgerManager)
{
    auto existingRule = storageHelper.getAccountSpecificRuleHelper().loadRule(
            mCreateData.ledgerKey, mCreateData.accountID.get());

    if (existingRule)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::ALREADY_EXISTS);

        if (existingRule->forbids() != mCreateData.forbids)
        {
            innerResult().code(ManageAccountSpecificRuleResultCode::REVERSED_ALREADY_EXISTS);
        }

        return false;
    }

    if (mCreateData.accountID)
    {
        if (!storageHelper.getAccountHelper().exists(*mCreateData.accountID))
        {
            innerResult().code(ManageAccountSpecificRuleResultCode::ACCOUNT_NOT_FOUND);
            return false;
        }
    }

    switch (mCreateData.ledgerKey.type())
    {
        case LedgerEntryType::SALE:
            return createSaleRule(app, storageHelper, mCreateData.ledgerKey.sale().saleID);
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected entry type on "
                               << "creating account specific rule entry, type: "
                               << static_cast<int32_t>(mCreateData.ledgerKey.type());
            throw std::runtime_error("Unexpected entry type on creating account specific rule entry");
    }
}

bool
CreateAccountSpecificRuleOpFrame::checkSaleRule(Application &app,
        StorageHelper &sh, uint64_t saleID)
{
    if (!mSale)
    {
        auto saleHelper = SaleHelper::Instance();
        mSale = saleHelper->loadSale(saleID, sh.getDatabase(), sh.getLedgerDelta());
        if (!mSale)
        {
            innerResult().code(ManageAccountSpecificRuleResultCode::SALE_NOT_FOUND);
            return false;
        }
    }

    //  not sale owner and not admin
    if (!isAuthorized(mSale->getOwnerID(), app.getAdminID()))
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED);
        return false;
    }

    if (mSale->getSaleEntry().ext.v() != LedgerVersion::ADD_SALE_WHITELISTS)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::SPECIFIC_RULE_NOT_SUPPORTED);
        return false;
    }

    return true;
}

bool
CreateAccountSpecificRuleOpFrame::createSaleRule(Application &app,
        StorageHelper &sh, uint64_t saleID)
{
    if (!checkSaleRule(app, sh, saleID))
    {
        return false;
    }

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
