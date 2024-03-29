// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ManageAssetPairOpFrame.h"
#include "transactions/dex/ManageOfferOpFrame.h"
#include "transactions/managers/BalanceManager.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/StorageHelper.h"

#include "database/Database.h"

#include "main/Application.h"
#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "ledger/OfferHelper.h"
#include "transactions/dex/OfferManager.h"
#include "ledger/BalanceHelper.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

ManageAssetPairOpFrame::ManageAssetPairOpFrame(Operation const& op,
                                               OperationResult& res,
                                               TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mManageAssetPair(mOperation.body.manageAssetPairOp())
{
}

bool
ManageAssetPairOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                  std::vector<OperationCondition>& result) const
{
    result.emplace_back(AccountRuleResource(LedgerEntryType::ASSET_PAIR),
                        AccountRuleAction::MANAGE, mSourceAccount);

    return true;
}

bool
ManageAssetPairOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                 std::vector<SignerRequirement>& result) const
{
    result.emplace_back(SignerRuleResource(LedgerEntryType::ASSET_PAIR),
                        SignerRuleAction::MANAGE);

    return true;
}

bool
ManageAssetPairOpFrame::createNewAssetPair(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, AssetPairFrame::pointer assetPair)
{
    // already exists or reverced already exists
    auto& assetPairHelper = storageHelper.getAssetPairHelper();
    if (assetPair || assetPairHelper.exists(mManageAssetPair.quote, mManageAssetPair.base))
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid", "already-exists"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::ALREADY_EXISTS);
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    bool assetsExist = assetHelper.existActive(mManageAssetPair.base);
    assetsExist = assetsExist && assetHelper.existActive(mManageAssetPair.quote);
    if (!assetsExist)
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid", "asset-not-exists"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::ASSET_NOT_FOUND);
        return false;
    }

    assetPair = AssetPairFrame::create(mManageAssetPair.base, mManageAssetPair.quote, mManageAssetPair.physicalPrice,
                                       mManageAssetPair.physicalPrice, mManageAssetPair.physicalPriceCorrection,
                                       mManageAssetPair.maxPriceStep, mManageAssetPair.policies);
    storageHelper.getHelper(assetPair->mEntry.data.type())->storeAdd(assetPair->mEntry);
    BalanceManager balanceManager(app, storageHelper);
    balanceManager.loadOrCreateBalanceForAdmin(assetPair->getQuoteAsset());

    app.getMetrics().NewMeter({"op-manage-asset-pair", "success", "apply"},
                              "operation").Mark();
    innerResult().code(ManageAssetPairResultCode::SUCCESS);
    innerResult().success().currentPrice = assetPair->getCurrentPrice();
    return true;
}

bool
ManageAssetPairOpFrame::doApply(Application& app,
                                StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto& assetPairHelper = storageHelper.getAssetPairHelper();
    AssetPairFrame::pointer assetPair = assetPairHelper.loadAssetPair(mManageAssetPair.base, mManageAssetPair.quote);
    if (mManageAssetPair.action == ManageAssetPairAction::CREATE)
    {
        return createNewAssetPair(app, storageHelper, ledgerManager, assetPair);
    }

    if (!assetPair)
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "not-found"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::NOT_FOUND);
        return false;
    }

    auto& assetPairEntry = assetPair->getAssetPair();
    if (mManageAssetPair.action == ManageAssetPairAction::UPDATE_POLICIES)
    {
        assetPairEntry.maxPriceStep = mManageAssetPair.maxPriceStep;
        assetPairEntry.physicalPriceCorrection = mManageAssetPair.physicalPriceCorrection;
        assetPairEntry.policies = mManageAssetPair.policies;
        // if pair not tradable remove all offers
        if (!assetPair->checkPolicy(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET))
        {
            auto orderBookID = ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID;
            const auto offersToRemove = storageHelper.getOfferHelper().loadOffersWithFilters(assetPair->getBaseAsset(), assetPair->getQuoteAsset(), &orderBookID, nullptr);
            OfferManager::deleteOffers(storageHelper, offersToRemove);
        }
    }
    else
    {
        int64_t premium = assetPairEntry.currentPrice - assetPairEntry.physicalPrice;
        if (premium < 0)
        {
            premium = 0;
        }
        assetPairEntry.physicalPrice = mManageAssetPair.physicalPrice;
        assetPairEntry.currentPrice = mManageAssetPair.physicalPrice + premium;
        auto orderBookID = ManageOfferOpFrame::SECONDARY_MARKET_ORDER_BOOK_ID;
        uint64_t minAllowedPrice = assetPair->getMinAllowedPrice();
        const auto offersToRemove = storageHelper.getOfferHelper().loadOffersWithFilters(assetPair->getBaseAsset(), assetPair->getQuoteAsset(), &orderBookID, &minAllowedPrice);
        OfferManager::deleteOffers(storageHelper, offersToRemove);
    }

    storageHelper.getHelper(assetPair->mEntry.data.type())->storeChange(assetPair->mEntry);

    app.getMetrics().NewMeter({"op-manage-asset-pair", "success", "apply"},
                              "operation").Mark();
    innerResult().code(ManageAssetPairResultCode::SUCCESS);
    innerResult().success().currentPrice = assetPair->getCurrentPrice();
    return true;
}


bool
ManageAssetPairOpFrame::doCheckValid(Application& app)
{
    if (!AssetFrame::isAssetCodeValid(mManageAssetPair.base) || !AssetFrame::isAssetCodeValid(mManageAssetPair.quote))
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "malformed-invalid-asset-pair"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::INVALID_ASSET);
        return false;
    }
    if (!isValidManageAssetPairAction(mManageAssetPair.action))
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "malformed-invalid-action"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::INVALID_ACTION);
        return false;
    }
    if (app.getLedgerManager().shouldUse(LedgerVersion::FIX_SAME_ASSET_PAIR) &&
        mManageAssetPair.action == ManageAssetPairAction::CREATE &&
        mManageAssetPair.base == mManageAssetPair.quote)
    {
        innerResult().code(ManageAssetPairResultCode::SAME_ASSET);
        return false;
    }


    if (mManageAssetPair.physicalPrice < 0 ||
        (mManageAssetPair.action == ManageAssetPairAction::UPDATE_PRICE && mManageAssetPair.physicalPrice == 0))
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "malformed-invalid-physical-price"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::MALFORMED);
        return false;
    }

    if (mManageAssetPair.policies < 0)
    {
        app.getMetrics().NewMeter({"op-manage-assetPair", "invalid",
                                   "malformed-invalid-policies"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::INVALID_POLICIES);
        return false;
    }


    if (mManageAssetPair.physicalPriceCorrection < 0)
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "malformed-invalid-phusical-price-correction"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::MALFORMED);
        return false;
    }

    if (mManageAssetPair.maxPriceStep < 0 || mManageAssetPair.maxPriceStep > 100 * ONE)
    {
        app.getMetrics().NewMeter({"op-manage-asset-pair", "invalid",
                                   "malformed-invalid-max-price-step"},
                                  "operation").Mark();
        innerResult().code(ManageAssetPairResultCode::MALFORMED);
        return false;
    }


    return true;
}
}
