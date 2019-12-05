// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "DeleteSaleParticipationOpFrame.h"
#include "ledger/SaleHelper.h"
#include "main/Application.h"
#include "ledger/OfferHelper.h"
#include "CreateSaleParticipationOpFrame.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AccountHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

DeleteSaleParticipationOpFrame::DeleteSaleParticipationOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx) : DeleteOfferOpFrame(op, res, parentTx)
{
    mCheckSaleState = true;
}

bool DeleteSaleParticipationOpFrame::doCheckValid(Application& app)
{
    if (mManageOffer.orderBookID == SECONDARY_MARKET_ORDER_BOOK_ID)
    {
        throw invalid_argument("Delete sale participation: unexpected order book id SECONDARY_MARKET_ORDER_BOOK_ID");
    }

    if (!mManageOffer.isBuy)
    {
        innerResult().code(ManageOfferResultCode::MALFORMED);
        return false;
    }

    return DeleteOfferOpFrame::doCheckValid(app);
}

bool DeleteSaleParticipationOpFrame::doApply(Application& app,
                                             StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto offer = storageHelper.getOfferHelper().loadOffer(getSourceID(), mManageOffer.offerID, mManageOffer.orderBookID);
    if (!offer)
    {
        innerResult().code(ManageOfferResultCode::NOT_FOUND);
        return false;
    }

    auto sale = storageHelper.getSaleHelper().loadSale(mManageOffer.orderBookID);
    if (!sale)
    {
        innerResult().code(ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS);
        return false;
    }

    if (mCheckSaleState
        && CreateSaleParticipationOpFrame::getSaleState(storageHelper, sale, ledgerManager.getCloseTime())
           != SaleFrame::State::ACTIVE)
    {
        innerResult().code(ManageOfferResultCode::SALE_IS_NOT_ACTIVE);
        return false;
    }

    auto quoteBalanceID = getQuoteBalanceID(offer, ledgerManager);
    auto balance = storageHelper.getBalanceHelper().mustLoadBalance(quoteBalanceID);
    sale->subCurrentCap(balance->getAsset(), offer->getOffer().quoteAmount);
    sale->unlockBaseAsset(offer->getOffer().baseAmount);
    storageHelper.getSaleHelper().storeChange(sale->mEntry);
    return DeleteOfferOpFrame::doApply(app, storageHelper, ledgerManager);
}

void DeleteSaleParticipationOpFrame::deleteSaleParticipation(
    Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
    OfferFrame::pointer offer, TransactionFrame& parentTx)
{
    Operation op;
    auto& offerEntry = offer->getOffer();
    op.sourceAccount.activate() = offerEntry.ownerID;
    op.body.type(OperationType::MANAGE_OFFER);
    auto& manageOfferOp = op.body.manageOfferOp();
    manageOfferOp.quoteBalance = offerEntry.quoteBalance;
    manageOfferOp.amount = 0;
    manageOfferOp.baseBalance = offerEntry.baseBalance;
    manageOfferOp.fee = offerEntry.fee;
    manageOfferOp.isBuy = offerEntry.isBuy;
    manageOfferOp.offerID = offerEntry.offerID;
    manageOfferOp.orderBookID = offerEntry.orderBookID;
    manageOfferOp.price = offerEntry.price;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_OFFER);
    DeleteSaleParticipationOpFrame opFrame(op, opRes, parentTx);
    opFrame.doNotCheckSaleState();
    const auto offerOwner = storageHelper.getAccountHelper().mustLoadAccount(offerEntry.ownerID);
    opFrame.setSourceAccountPtr(offerOwner);
    if (!opFrame.doCheckValid(app) || !opFrame.doApply(app, storageHelper, ledgerManager))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to apply delete sale participation: offerID"
                                               << offer->getOfferID();
        throw runtime_error("Unexpected state: failed to apply delete sale participation");
    }
}

void DeleteSaleParticipationOpFrame::doNotCheckSaleState()
{
    mCheckSaleState = false;
}
BalanceID DeleteSaleParticipationOpFrame::getQuoteBalanceID(OfferFrame::pointer offer, LedgerManager& lm)
{
    return offer->getOffer().quoteBalance;
}
}
