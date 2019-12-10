#include "ledger/AssetPairHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/SaleHelper.h"
#include "RemoveAssetPairOpFrame.h"
#include "main/Application.h"
#include "ledger/StorageHelper.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "transactions/dex/ManageOfferOpFrame.h"

namespace stellar
{

using namespace std;

RemoveAssetPairOpFrame::RemoveAssetPairOpFrame(const stellar::Operation& op, stellar::OperationResult& res,
                                               stellar::TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mRemoveAssetPair(mOperation.body.removeAssetPairOp())
{}

bool RemoveAssetPairOpFrame::tryGetOperationConditions(stellar::StorageHelper& storageHelper,
                                                       std::vector<stellar::OperationCondition>& result,
                                                       stellar::LedgerManager& ledgerManager) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ASSET_PAIR),
                        AccountRuleAction::REMOVE, mSourceAccount);

    return true;
}

bool RemoveAssetPairOpFrame::tryGetSignerRequirements(stellar::StorageHelper& storageHelper,
                                                      std::vector<stellar::SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ASSET_PAIR),
                        SignerRuleAction::REMOVE);

    return true;
}

bool RemoveAssetPairOpFrame::doApply(stellar::Application& app, stellar::StorageHelper& storageHelper,
                                     stellar::LedgerManager& ledgerManager)
{
    auto& assetPairHelper = storageHelper.getAssetPairHelper();
    auto assetPair = assetPairHelper.loadAssetPair(mRemoveAssetPair.base, mRemoveAssetPair.quote);
    if (assetPair == nullptr)
    {
        innerResult().code(RemoveAssetPairResultCode::NOT_FOUND);
        return false;
    }

    auto& offerHelper = storageHelper.getOfferHelper();
    auto orderBookID = ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID;
    if (offerHelper.exists(mRemoveAssetPair.base, mRemoveAssetPair.quote, &orderBookID))
    {
        innerResult().code(RemoveAssetPairResultCode::HAS_ACTIVE_OFFERS);
        return false;
    }

    auto& saleHelper = storageHelper.getSaleHelper();
    if (saleHelper.exists(mRemoveAssetPair.base, mRemoveAssetPair.quote))
    {
        innerResult().code(RemoveAssetPairResultCode::HAS_ACTIVE_SALES);
        return false;
    }

    assetPairHelper.storeDelete(assetPair->getKey());

    innerResult().code(RemoveAssetPairResultCode::SUCCESS);
    return true;
}

bool RemoveAssetPairOpFrame::doCheckValid(stellar::Application& app)
{
    if (!AssetFrame::isAssetCodeValid(mRemoveAssetPair.base) || !AssetFrame::isAssetCodeValid(mRemoveAssetPair.quote))
    {
        innerResult().code(RemoveAssetPairResultCode::INVALID_ASSET_CODE);
        return false;
    }

    return true;
}

}