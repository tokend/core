// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "OfferManager.h"
#include "ledger/BalanceHelper.h"
#include "ledger/LedgerDelta.h"
#include "xdrpp/printer.h"
#include "ledger/FeeHelper.h"
#include "ledger/StorageHelperImpl.h"

namespace stellar
{
void OfferManager::deleteOffer(OfferFrame::pointer offerFrame, Database& db,
    LedgerDelta& delta)
{
    StorageHelperImpl storageHelperImpl(db,&delta);
    StorageHelper& storageHelper = storageHelperImpl;
    const auto balanceID = offerFrame->getLockedBalance();
    auto balanceFrame = storageHelper.getBalanceHelper().loadBalance(balanceID);
    if (!balanceFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Invalid database state: failed to load balance to cancel order: " << xdr::xdr_to_string(offerFrame->getOffer());
        throw std::runtime_error("Invalid database state: failed to load balance to cancel order");
    }

    const auto amountToUnlock = offerFrame->getLockedAmount();
    const BalanceFrame::Result unlockResult = balanceFrame->unlock(amountToUnlock);
    if (unlockResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Invalid database state: failed to unlocked locked amount for offer: " << xdr::xdr_to_string(offerFrame->getOffer());
        throw std::runtime_error("Invalid database state: failed to unlocked locked amount for offer");
    }

    storageHelper.getHelper(offerFrame->getKey().type())->storeDelete(offerFrame->getKey());
    storageHelper.getHelper(balanceFrame->mEntry.data.type())->storeChange(balanceFrame->mEntry);
}

void OfferManager::deleteOffers(std::vector<OfferFrame::pointer> offers,
    Database& db, LedgerDelta& delta)
{
    for (auto& offer : offers)
    {
        delta.recordEntry(*offer);
        deleteOffer(offer, db, delta);
    }
}

OfferFrame::pointer OfferManager::buildOffer(AccountID const& sourceID, ManageOfferOp const& op,
    AssetCode const& base, AssetCode const& quote, uint64_t quotePrecisionStep)
{
    OfferEntry o;
    o.orderBookID = op.orderBookID;
    o.base = base;
    o.baseAmount = op.amount;
    o.baseBalance = op.baseBalance;
    o.quoteBalance = op.quoteBalance;
    o.isBuy = op.isBuy;
    o.offerID = op.offerID;
    o.ownerID = sourceID;
    o.price = op.price;
    o.quote = quote;
    o.quoteAmount = calculateQuoteAmount(op.amount, op.price, quotePrecisionStep);
    if (o.quoteAmount == 0)
        return nullptr;

    LedgerEntry le;
    le.data.type(LedgerEntryType::OFFER_ENTRY);
    le.data.offer() = o;
    return std::make_shared<OfferFrame>(le);
}

ManageOfferOp OfferManager::buildManageOfferOp(BalanceID const& baseBalance,
    BalanceID const& quoteBalance, bool const isBuy, int64_t const amount,
    int64_t const price, int64_t const fee, uint64_t const offerID,
    uint64_t const orderBookID)
{
    ManageOfferOp op;
    op.baseBalance = baseBalance;
    op.quoteBalance = quoteBalance;
    op.isBuy = isBuy;
    op.amount = amount;
    op.price = price;
    op.fee = fee;
    op.offerID = offerID;
    op.orderBookID = orderBookID;
    return op;
}

// TODO: use uint64
int64_t OfferManager::calculateQuoteAmount(int64_t const baseAmount,
                                           int64_t const price,
                                           uint64_t quotePrecisionStep)
{
    int64_t result;
    if (!bigDivide(result, baseAmount, price, ONE, ROUND_UP, quotePrecisionStep))
        return 0;
    return result;
}
}
