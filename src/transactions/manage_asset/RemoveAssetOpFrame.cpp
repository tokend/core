#include "RemoveAssetOpFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/OfferHelper.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
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
    AccountRuleAction action;

    if (asset->getOwner() == mSourceAccount->getID())
    {
        action = AccountRuleAction::REMOVE;
    }
    else
    {
        action = AccountRuleAction::REMOVE_FOR_OTHER;
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

    result.emplace_back(resource, SignerRuleAction::REMOVE);

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
    auto asset = assetHelper.loadAsset(mRemoveAsset.code);

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

    deleteBalances(storageHelper);

    assetHelper.storeDelete(asset->getKey());

    innerResult().code(RemoveAssetResultCode::SUCCESS);
    return true;
}

bool
RemoveAssetOpFrame::doCheckValid(stellar::Application& app)
{
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