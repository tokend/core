#include "RemoveAssetOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/AtomicSwapAskHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/SwapHelper.h"
#include "main/Application.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"

namespace stellar
{

using namespace std;

RemoveAssetOpFrame::RemoveAssetOpFrame(const stellar::Operation& op,
                                       stellar::OperationResult& res,
                                       stellar::TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mRemoveAsset(mOperation.body.removeAssetOp())
{
}

bool
RemoveAssetOpFrame::tryGetOperationConditions(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::OperationCondition>& result,
    stellar::LedgerManager& ledgerManager) const
{
    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.loadAsset(mRemoveAsset.code);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }
    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetCode = asset->getCode();
    resource.asset().assetType = asset->getType();
    AccountRuleAction action = AccountRuleAction::REMOVE_FOR_OTHER;

    if (getSourceID() == asset->getOwner())
    {
        action = AccountRuleAction::REMOVE;
    }

    result.emplace_back(resource, action, mSourceAccount);

    return true;
}

bool
RemoveAssetOpFrame::tryGetSignerRequirements(
    stellar::StorageHelper& storageHelper,
    std::vector<stellar::SignerRequirement>& result) const
{
    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.loadAsset(mRemoveAsset.code);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }
    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetCode = asset->getCode();
    resource.asset().assetType = asset->getType();
    SignerRuleAction action = SignerRuleAction::REMOVE_FOR_OTHER;
    if (getSourceID() == asset->getOwner())
    {
        action = SignerRuleAction::REMOVE;
    }

    result.emplace_back(resource, action);

    return true;
}

bool
RemoveAssetOpFrame::doApply(stellar::Application& app,
                            stellar::StorageHelper& storageHelper,
                            stellar::LedgerManager& ledgerManager)
{
    Database& db = ledgerManager.getDatabase();

    auto& assetHelper = storageHelper.getAssetHelper();

    // Asset existence was checked previously
    auto asset = assetHelper.mustLoadAsset(mRemoveAsset.code);

    auto saleHelper = SaleHelper::Instance();
    if (saleHelper->exists(db, mRemoveAsset.code))
    {
        innerResult().code(RemoveAssetResultCode::HAS_ACTIVE_SALES);
        return false;
    }

    if (OfferHelper::Instance()->exists(db, mRemoveAsset.code, nullptr))
    {
        innerResult().code(RemoveAssetResultCode::HAS_ACTIVE_OFFERS);
        return false;
    }

    auto assetPairHelper = AssetPairHelper::Instance();
    if (assetPairHelper->existsForAsset(db, mRemoveAsset.code))
    {
        innerResult().code(RemoveAssetResultCode::HAS_PAIR);
        return false;
    }
    if (ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        if (AtomicSwapAskHelper::Instance()->existForAsset(db,
                                                           mRemoveAsset.code))
        {
            innerResult().code(RemoveAssetResultCode::HAS_ACTIVE_ATOMIC_SWAPS);
            return false;
        }

        if (storageHelper.getSwapHelper().existForAsset(mRemoveAsset.code))
        {
            innerResult().code(RemoveAssetResultCode::HAS_ACTIVE_SWAPS);
            return false;
        }

        if (asset->isPolicySet(AssetPolicy::STATS_QUOTE_ASSET))
        {
            innerResult().code(RemoveAssetResultCode::CANNOT_REMOVE_STATS_QUOTE_ASSET);
            return false;
        }

        assetHelper.markDeleted(mRemoveAsset.code);
    }
    else
    {
        deleteBalances(storageHelper);

        assetHelper.storeDelete(asset->getKey());
    }

    innerResult().code(RemoveAssetResultCode::SUCCESS);
    return true;
}

bool
RemoveAssetOpFrame::doCheckValid(stellar::Application& app)
{
    if (!AssetFrame::isAssetCodeValid(mRemoveAsset.code))
    {
        innerResult().code(RemoveAssetResultCode::INVALID_ASSET_CODE);
        return false;
    }

    return true;
}

void
RemoveAssetOpFrame::deleteBalances(StorageHelper& storageHelper)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto holders = balanceHelper.loadBalancesForAsset(mRemoveAsset.code);

    for (auto& holder : holders)
    {
        balanceHelper.storeDelete(holder->getKey());
    }
}

}