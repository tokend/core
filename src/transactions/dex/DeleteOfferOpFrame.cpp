// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "DeleteOfferOpFrame.h"
#include "OfferManager.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/OfferHelper.h"
#include "main/Application.h"
#include "OfferManager.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

DeleteOfferOpFrame::DeleteOfferOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx)
    : ManageOfferOpFrame(op, res, parentTx)
{
}

bool
DeleteOfferOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                              std::vector<OperationCondition>& result) const
{
    // only offer owner can remove it
    return true;
}

bool
DeleteOfferOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                             std::vector<SignerRequirement>& result) const
{

    auto offerFrame = storageHelper.getOfferHelper().loadOffer(getSourceID(),
                                                         mManageOffer.offerID);
    if (!offerFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::OFFER_ENTRY;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto baseAsset = assetHelper.mustLoadAsset(offerFrame->getOffer().base);
    auto quoteAsset = assetHelper.mustLoadAsset(offerFrame->getOffer().quote);

    SignerRuleResource resource(LedgerEntryType::OFFER_ENTRY);
    resource.offer().baseAssetCode = baseAsset->getCode();
    resource.offer().quoteAssetCode = quoteAsset->getCode();
    resource.offer().baseAssetType = baseAsset->getType();
    resource.offer().quoteAssetType = quoteAsset->getType();

    result.emplace_back(resource, SignerRuleAction::REMOVE);

    return true;
}

bool
DeleteOfferOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                            LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    const auto offer = storageHelper.getOfferHelper().loadOffer(
        getSourceID(), mManageOffer.offerID, mManageOffer.orderBookID);
    if (!offer)
    {
        innerResult().code(ManageOfferResultCode::NOT_FOUND);
        return false;
    }

    OfferManager::deleteOffer(storageHelper, offer);
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto baseBalance = balanceHelper.mustLoadBalance(offer->getOffer().baseBalance);
    auto quoteBalance = balanceHelper.mustLoadBalance(offer->getOffer().quoteBalance);
    innerResult().code(ManageOfferResultCode::SUCCESS);
    auto& success = innerResult().success();
    success.offer.effect(ManageOfferEffect::DELETED);
    success.baseAsset = baseBalance->getAsset();
    success.quoteAsset = quoteBalance->getAsset();
    return true;
}

// makes sure the currencies are different
bool
DeleteOfferOpFrame::doCheckValid(Application& app)
{
    if (mManageOffer.amount != 0)
    {
        throw invalid_argument("DeleteOffer: expected amount to be 0");
    }

    if (mManageOffer.offerID == 0)
    {
        innerResult().code(ManageOfferResultCode::NOT_FOUND);
        return false;
    }

    return true;
}
} // namespace stellar
