#include "RemoveAccountSpecificRuleOpFrame.h"
#include "transactions/dex/OfferManager.h"
#include "transactions/dex/DeleteSaleParticipationOpFrame.h"
#include "ledger/OfferHelper.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/AccountSpecificRuleHelper.h"
#include "main/Application.h"

namespace stellar
{
RemoveAccountSpecificRuleOpFrame::RemoveAccountSpecificRuleOpFrame(
        const Operation &op, OperationResult &res, TransactionFrame &parentTx)
        : ManageAccountSpecificRuleOpFrame(op, res, parentTx)
        , mRemoveData(mManageAccountSpecificRule.data.removeData())
{
}

bool
RemoveAccountSpecificRuleOpFrame::tryGetOperationConditions(
        StorageHelper &storageHelper, std::vector<OperationCondition> &result) const
{
    AccountRuleResource resource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);

    auto rule = storageHelper.getAccountSpecificRuleHelper().loadRule(mRemoveData.ruleID);
    if (!rule)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ACCOUNT_SPECIFIC_RULE;
        return false;
    }
    resource.accountSpecificRule().ledgerKey = rule->getEntry().ledgerKey;

    result.emplace_back(resource, AccountRuleAction::REMOVE, mSourceAccount);
    return true;
}

bool
RemoveAccountSpecificRuleOpFrame::tryGetSignerRequirements(
        StorageHelper &storageHelper, std::vector<SignerRequirement> &result) const
{
    SignerRuleResource resource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE);

    auto rule = storageHelper.getAccountSpecificRuleHelper().loadRule(mRemoveData.ruleID);
    if (!rule)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ACCOUNT_SPECIFIC_RULE;
        return false;
    }
    resource.accountSpecificRule().ledgerKey = rule->getEntry().ledgerKey;

    result.emplace_back(resource, SignerRuleAction::REMOVE);
    return true;
}

bool
RemoveAccountSpecificRuleOpFrame::doApply(Application &app,
        StorageHelper &storageHelper, LedgerManager &ledgerManager)
{
    auto frame = storageHelper.getAccountSpecificRuleHelper().mustLoadRule(mRemoveData.ruleID);

    switch (frame->getEntry().ledgerKey.type())
    {
        case LedgerEntryType::SALE:
            return tryRemoveSaleRule(app, storageHelper, frame);
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected entry type on "
                                << "creating account specific rule entry, type: "
                                << static_cast<int32_t>(frame->getEntry().ledgerKey.type());
            throw std::runtime_error("Unexpected entry type on creating account specific rule entry");
    }
}

bool
RemoveAccountSpecificRuleOpFrame::tryRemoveSaleRule(Application& app,
        StorageHelper& storageHelper, AccountSpecificRuleFrame::pointer const& ruleFrame)
{
    if (!ruleFrame->getEntry().accountID)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::REMOVING_GLOBAL_RULE_FORBIDDEN);
        return false;
    }

    Database& db = storageHelper.getDatabase();
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto saleHelper = SaleHelper::Instance();

    auto sale = saleHelper->loadSale(ruleFrame->getEntry().ledgerKey.sale().saleID, db, &delta);
    if (!sale)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Expected sale to exists on "
                                   << "remove account specific rule, saleID: "
                                   << ruleFrame->getEntry().ledgerKey.sale().saleID;
        throw std::runtime_error("Expected sale to exists");
    }

    if (!isAuthorized(sale->getOwnerID(), app.getAdminID()))
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_AUTHORIZED);
        return false;
    }

    storageHelper.getAccountSpecificRuleHelper().storeDelete(ruleFrame->getKey());

    if (!ruleFrame->forbids()) // accountID existing was checked above
    {
        auto offerHelper = OfferHelper::Instance();
        auto offersToDelete = offerHelper->loadOffers(*ruleFrame->getEntry().accountID, sale->getID(), db);
        for (auto const& offerToCancel : offersToDelete)
        {
            DeleteSaleParticipationOpFrame::deleteSaleParticipation(app, delta,
                    app.getLedgerManager(), offerToCancel, mParentTx);
        }
    }

    innerResult().code(ManageAccountSpecificRuleResultCode::SUCCESS);
    innerResult().success().ruleID = ruleFrame->getID();
    return true;
}

bool
RemoveAccountSpecificRuleOpFrame::doCheckValid(Application &app)
{
    if (mRemoveData.ruleID == 0)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_FOUND);
        return false;
    }

    return true;
}

}
