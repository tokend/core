// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "DeleteOfferOpFrame.h"
#include "OfferManager.h"
#include "database/Database.h"
#include "ledger/BalanceHelperLegacy.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/OfferHelper.h"
#include "main/Application.h"

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
DeleteOfferOpFrame::doApply(Application& app, LedgerDelta& delta,
                            LedgerManager& ledgerManager)
{
    auto& db = app.getDatabase();
    const auto offer = OfferHelper::Instance()->loadOffer(
        getSourceID(), mManageOffer.offerID, mManageOffer.orderBookID, db,
        &delta);
    if (!offer)
    {
        innerResult().code(ManageOfferResultCode::NOT_FOUND);
        return false;
    }

    OfferManager::deleteOffer(offer, db, delta);
    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto baseBalance =
        balanceHelper->mustLoadBalance(offer->getOffer().baseBalance, db, &delta);
    auto quoteBalance = balanceHelper->mustLoadBalance(
        offer->getOffer().quoteBalance, db, &delta);
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
