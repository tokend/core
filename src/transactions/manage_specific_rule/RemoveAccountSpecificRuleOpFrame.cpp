#include "RemoveAccountSpecificRuleOpFrame.h"
#include "transactions/dex/OfferManager.h"
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
    return true;
}

bool
RemoveAccountSpecificRuleOpFrame::tryGetSignerRequirements(
        StorageHelper &storageHelper, std::vector<SignerRequirement> &result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ACCOUNT_SPECIFIC_RULE), SignerRuleAction::REMOVE);
    return true;
}

bool
RemoveAccountSpecificRuleOpFrame::doApply(Application &app,
        StorageHelper &storageHelper, LedgerManager &ledgerManager)
{
    auto frame = storageHelper.getAccountSpecificRuleHelper().loadRule(mRemoveData.ruleID);
    if (!frame)
    {
        innerResult().code(ManageAccountSpecificRuleResultCode::NOT_FOUND);
        return false;
    }

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

    saleHelper->storeDelete(delta, db, ruleFrame->getKey());

    if (!ruleFrame->forbids())
    {
        auto offerHelper = OfferHelper::Instance();
        auto offersToDelete = offerHelper->loadOffers(sale->getOwnerID(), sale->getID(), db);
        OfferManager::deleteOffers(offersToDelete, db, delta);
    }

    innerResult().code(ManageAccountSpecificRuleResultCode::SUCCESS);
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