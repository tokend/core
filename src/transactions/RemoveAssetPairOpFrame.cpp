#include "ledger/AssetPairHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/SaleHelper.h"
#include "RemoveAssetPairOpFrame.h"
#include "main/Application.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "dex/ManageOfferOpFrame.h"

namespace stellar
{

using namespace std;

RemoveAssetPairOpFrame::RemoveAssetPairOpFrame(const stellar::Operation &op, stellar::OperationResult &res,
                                               stellar::TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx), mRemoveAssetPair(mOperation.body.removeAssetPairOp()) {}

bool RemoveAssetPairOpFrame::tryGetOperationConditions(stellar::StorageHelper &storageHelper,
                                                       std::vector<stellar::OperationCondition> &result,
                                                       stellar::LedgerManager &ledgerManager) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ASSET_PAIR),
                        AccountRuleAction::REMOVE, mSourceAccount);

    return true;
}

bool RemoveAssetPairOpFrame::tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                                      std::vector<stellar::SignerRequirement> &result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ASSET_PAIR),
                        SignerRuleAction::REMOVE);

    return true;
}

bool RemoveAssetPairOpFrame::doApply(stellar::Application &app, stellar::LedgerDelta &delta,
                                     stellar::LedgerManager &ledgerManager)
{
    Database& db = ledgerManager.getDatabase();

    auto assetPairHelper = AssetPairHelper::Instance();
    auto assetPair = assetPairHelper->loadAssetPair(mRemoveAssetPair.base, mRemoveAssetPair.quote, db, &delta);
    if (assetPair == nullptr)
    {
        app.getMetrics().NewMeter({"op-remove-asset-pair", "invalid", "not-found" },
                "operation").Mark();
        innerResult().code(RemoveAssetPairResultCode::NOT_FOUND);
        return false;
    }

    auto offerHelper = OfferHelper::Instance();
    auto orderBookID = ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID;
    if (offerHelper->exists(db, mRemoveAssetPair.base, mRemoveAssetPair.quote, &orderBookID))
    {
        app.getMetrics().NewMeter({"op-remove-asset-pair", "invalid", "has-active-offers" },
                                  "operation").Mark();
        innerResult().code(RemoveAssetPairResultCode::HAS_ACTIVE_OFFERS);
        return false;
    }

    auto saleHelper = SaleHelper::Instance();
    if (saleHelper->exists(db, mRemoveAssetPair.base, mRemoveAssetPair.quote))
    {
        app.getMetrics().NewMeter({"op-remove-asset-pair", "invalid", "has-active-sales" },
                                  "operation").Mark();
        innerResult().code(RemoveAssetPairResultCode::HAS_ACTIVE_SALES);
        return false;
    }

    assetPairHelper->storeDelete(delta, db, assetPair->getKey());

    innerResult().code(RemoveAssetPairResultCode::SUCCESS);
    return true;
}

bool RemoveAssetPairOpFrame::doCheckValid(stellar::Application &app)
{
    if (!AssetFrame::isAssetCodeValid(mRemoveAssetPair.base) || !AssetFrame::isAssetCodeValid(mRemoveAssetPair.quote))
    {
        app.getMetrics().NewMeter({"op-remove-asset-pair", "invalid", "malformed-invalid-asset-pair"},
                "operation").Mark();
        innerResult().code(RemoveAssetPairResultCode::INVALID_ASSET_CODE);
        return false;
    }

    return true;
}

}