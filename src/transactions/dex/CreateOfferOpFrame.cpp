// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CreateOfferOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "main/Application.h"
#include "OfferManager.h"
#include "transactions/managers/BalanceManager.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

// TODO requires refactoring
CreateOfferOpFrame::CreateOfferOpFrame(Operation const& op,
                                       OperationResult& res,
                                       TransactionFrame& parentTx,
                                       FeeType type)
    : ManageOfferOpFrame(op, res, parentTx)
{
    feeType = type;
}

bool
CreateOfferOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                              std::vector<OperationCondition>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.loadBalance(mManageOffer.baseBalance);
    if (!baseBalance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto quoteBalance = balanceHelper.loadBalance(mManageOffer.quoteBalance);
    if (!quoteBalance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto baseAsset = assetHelper.mustLoadAsset(baseBalance->getAsset());
    auto quoteAsset = assetHelper.mustLoadAsset(quoteBalance->getAsset());

    AccountRuleResource resource(LedgerEntryType::OFFER_ENTRY);
    resource.offer().baseAssetCode = baseAsset->getCode();
    resource.offer().quoteAssetCode = quoteAsset->getCode();
    resource.offer().baseAssetType = baseAsset->getType();
    resource.offer().quoteAssetType = quoteAsset->getType();
    resource.offer().isBuy = mManageOffer.isBuy;

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateOfferOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                             std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseBalance = balanceHelper.mustLoadBalance(mManageOffer.baseBalance);
    auto quoteBalance = balanceHelper.mustLoadBalance(mManageOffer.quoteBalance);

    auto baseAsset = assetHelper.mustLoadAsset(baseBalance->getAsset());
    auto quoteAsset = assetHelper.mustLoadAsset(quoteBalance->getAsset());

    SignerRuleResource resource(LedgerEntryType::OFFER_ENTRY);
    resource.offer().baseAssetCode = baseAsset->getCode();
    resource.offer().quoteAssetCode = quoteAsset->getCode();
    resource.offer().baseAssetType = baseAsset->getType();
    resource.offer().quoteAssetType = quoteAsset->getType();
    resource.offer().isBuy = mManageOffer.isBuy;

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
};

BalanceFrame::pointer
CreateOfferOpFrame::loadBalanceValidForTrading(StorageHelper& storageHelper, BalanceID const& balanceID)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.loadBalance(balanceID);
    if (!balance || !(balance->getAccountID() == getSourceID()))
    {
        innerResult().code(ManageOfferResultCode::BALANCE_NOT_FOUND);
        return nullptr;
    }

    return balance;
}

AssetPairFrame::pointer CreateOfferOpFrame::loadTradableAssetPair(StorageHelper& storageHelper)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    auto& assetPairHelper = storageHelper.getAssetPairHelper();
    AssetPairFrame::pointer assetPair = assetPairHelper.
        loadAssetPair(mBaseBalance->getAsset(), mQuoteBalance->getAsset());
    if (!assetPair)
        return nullptr;

    if (mManageOffer.orderBookID != SECONDARY_MARKET_ORDER_BOOK_ID)
        return assetPair;

    if (assetPair->checkPolicy(AssetPairPolicy::TRADEABLE_SECONDARY_MARKET))
    {
        return assetPair;
    }

    return nullptr;
}

bool CreateOfferOpFrame::checkOfferValid(LedgerManager& lm, StorageHelper& storageHelper)
{
    assert(mManageOffer.amount != 0);

    mBaseBalance =
        loadBalanceValidForTrading(storageHelper, mManageOffer.baseBalance);
    if (!mBaseBalance)
        return false;

    mQuoteBalance =
        loadBalanceValidForTrading(storageHelper, mManageOffer.quoteBalance);
    if (!mQuoteBalance)
        return false;

    if (mBaseBalance->getAsset() == mQuoteBalance->getAsset())
    {
        innerResult().code(ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE);
        return false;
    }

    if (mManageOffer.amount % mBaseBalance->getMinimumAmount() != 0)
    {
        innerResult().code(ManageOfferResultCode::INCORRECT_AMOUNT_PRECISION);
        return false;
    }

    BalanceID receivingBalance;
    if (mManageOffer.isBuy)
        receivingBalance = mManageOffer.baseBalance;
    else
        receivingBalance = mManageOffer.quoteBalance;

    auto balanceFrame = storageHelper.getBalanceHelper().loadBalance(receivingBalance);
    if (!balanceFrame)
    {
        innerResult().code(ManageOfferResultCode::BALANCE_NOT_FOUND);
        return false;
    }

    mAssetPair = loadTradableAssetPair(storageHelper);
    if (!mAssetPair)
    {
        innerResult().code(ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE);
        return false;
    }

    if (!currentPriceRestrictionsMet(lm))
    {
        innerResult().code(ManageOfferResultCode::CURRENT_PRICE_RESTRICTION);
        return false;
    }
    if (!physicalPriceRestrictionsMet(lm))
    {
        innerResult().code(ManageOfferResultCode::PHYSICAL_PRICE_RESTRICTION);
        return false;
    }

    return true;
}

OfferExchange::OfferFilterResult CreateOfferOpFrame::filterOffer(const uint64_t price,
                                                                 OfferFrame const& o)
{
    const auto isPriceBetter = o.getOffer().isBuy
                               ? o.getPrice() >= price
                               : o.getPrice() <= price;
    if (!isPriceBetter)
    {
        return OfferExchange::eStop;
    }

    if (o.getOffer().ownerID == getSourceID())
    {
        // we are crossing our own offer
        innerResult().code(ManageOfferResultCode::CROSS_SELF);
        return OfferExchange::eStop;
    }

    return OfferExchange::eKeep;
}

bool CreateOfferOpFrame::lockSellingAmount(OfferEntry const& offer)
{
    BalanceFrame::pointer sellingBalance;
    int64_t sellingAmount;
    if (offer.isBuy)
    {
        sellingBalance = mQuoteBalance;
        sellingAmount = offer.quoteAmount + offer.fee;
    }
    else
    {
        sellingBalance = mBaseBalance;
        sellingAmount = offer.baseAmount;
    }

    if (sellingAmount <= 0)
        return false;
    return sellingBalance->tryLock(sellingAmount) == BalanceFrame::Result::
    SUCCESS;
}

FeeManager::FeeResult
CreateOfferOpFrame::obtainCalculatedFeeForAccount(int64_t amount, LedgerManager& lm, Database& db) const
{
    if (!lm.shouldUse(LedgerVersion::ADD_INVEST_FEE) && feeType == FeeType::INVEST_FEE)
    {
        return FeeManager::calculateFeeForAccount(mSourceAccount, FeeType::OFFER_FEE, mQuoteBalance->getAsset(),
                                                  FeeFrame::SUBTYPE_ANY, amount, db);
    }

    return FeeManager::calculateFeeForAccount(mSourceAccount, feeType, mQuoteBalance->getAsset(),
                                              FeeFrame::SUBTYPE_ANY, amount, db);
}

bool
CreateOfferOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                            LedgerManager& ledgerManager)
{
    if (!checkOfferValid(ledgerManager, storageHelper))
    {
        return false;
    }

    auto offerFrame = OfferManager::buildOffer(getSourceID(), mManageOffer, mBaseBalance->getAsset(),
                                               mQuoteBalance->getAsset(), mQuoteBalance->getMinimumAmount());
    if (!offerFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: quote amount overflows";
        throw std::runtime_error("Unexpected state: quote amount overflows");
    }

    auto& db = storageHelper.getDatabase();
    auto& offer = offerFrame->getOffer();
    offer.createdAt = ledgerManager.getCloseTime();
    auto const feeResult = obtainCalculatedFeeForAccount(offer.quoteAmount, ledgerManager, db);

    if (feeResult.isOverflow)
    {
        innerResult().code(ManageOfferResultCode::OFFER_OVERFLOW);
        return false;
    }

    offer.percentFee = feeResult.percentFee;
    offer.fee = feeResult.calculatedPercentFee;

    const bool isFeeCorrect = offer.fee <= mManageOffer.fee;
    if (!isFeeCorrect)
    {
        innerResult().code(ManageOfferResultCode::MALFORMED);
        return false;
    }

    offer.fee = mManageOffer.fee;

    if (offer.quoteAmount <= offer.fee)
    {
        innerResult().code(ManageOfferResultCode::MALFORMED);
        return false;
    }

    if (!lockSellingAmount(offer))
    {
        innerResult().code(ManageOfferResultCode::UNDERFUNDED);
        return false;
    }

    innerResult().code(ManageOfferResultCode::SUCCESS);

    BalanceManager balanceManager(app, storageHelper);
    const auto commissionBalance = balanceManager.loadOrCreateBalanceForAdmin(
        mAssetPair->getQuoteAsset());

    auto& delta = storageHelper.mustGetLedgerDelta();

    OfferExchange oe(delta, ledgerManager, mAssetPair, commissionBalance,
                     mManageOffer.orderBookID);

    int64_t price = offer.price;
    const OfferExchange::ConvertResult r = oe.convertWithOffers(offer,
                                                                mBaseBalance,
                                                                mQuoteBalance,
                                                                [this, &price](
                                                                    OfferFrame const
                                                                    & o)
                                                                {
                                                                    return
                                                                        filterOffer(price,
                                                                                    o);
                                                                });

    switch (r)
    {
        case OfferExchange::eOK:
        case OfferExchange::ePartial:
            break;
        case OfferExchange::eFilterStop:
            if (innerResult().code() != ManageOfferResultCode::SUCCESS)
            {
                return false;
            }
            break;
        default:
            throw std::runtime_error("Unexpected offer exchange result");
    }

    // updates the result with the offers that got taken on the way
    auto takenOffers = oe.getOfferTrail();

    for (auto const& oatom : takenOffers)
    {
        innerResult().success().offersClaimed.push_back(oatom);
    }

    if (!takenOffers.empty())
    {
        const int64_t currentPrice = takenOffers[takenOffers.size() - 1].currentPrice;
        mAssetPair->setCurrentPrice(currentPrice);
        storageHelper.getHelper(mAssetPair->mEntry.data.type())->storeChange(mAssetPair->mEntry);
        storageHelper.getHelper(commissionBalance->mEntry.data.type())->storeChange(commissionBalance->mEntry);
    }

    if (oe.offerNeedsMore(offer, mQuoteBalance->getMinimumAmount()))
    {
        offerFrame->mEntry.data.offer().offerID = delta.getHeaderFrame().
            generateID(LedgerEntryType
                       ::
                       OFFER_ENTRY);
        innerResult().success().offer.effect(ManageOfferEffect::CREATED);
        storageHelper.getHelper(offerFrame->mEntry.data.type())->storeAdd(offerFrame->mEntry);
        innerResult().success().offer.offer() = offer;
    }
    else
    {
        OfferExchange::unlockBalancesForTakenOffer(*offerFrame, mBaseBalance,
                                                   mQuoteBalance);
        innerResult().success().offer.effect(ManageOfferEffect::DELETED);
    }

    auto& balanceHelper = storageHelper.getBalanceHelper();

    innerResult().success().baseAsset = mAssetPair->getBaseAsset();
    innerResult().success().quoteAsset = mAssetPair->getQuoteAsset();
    balanceHelper.storeChange(mBaseBalance->mEntry);
    balanceHelper.storeChange(mQuoteBalance->mEntry);
    return true;
}

// makes sure the currencies are different
bool CreateOfferOpFrame::doCheckValid(Application& app)
{
    if (mManageOffer.amount <= 0)
    {
        innerResult().code(ManageOfferResultCode::INVALID_AMOUNT);
        return false;
    }

    if (mManageOffer.price <= 0)
    {
        innerResult().code(ManageOfferResultCode::PRICE_IS_INVALID);
        return false;
    }

    // merely check for overflow - we don't need precision here, so set it to 1
    const bool isQuoteAmountFits = OfferManager::calculateQuoteAmount(mManageOffer.amount, mManageOffer.price, 1) > 0;
    if (!isQuoteAmountFits)
    {
        innerResult().code(ManageOfferResultCode::OFFER_OVERFLOW);
        return false;
    }
    if (mManageOffer.fee < 0)
    {
        innerResult().code(ManageOfferResultCode::INVALID_PERCENT_FEE);
        return false;
    }

    if (mManageOffer.baseBalance == mManageOffer.quoteBalance)
    {
        innerResult().code(ManageOfferResultCode::ASSET_PAIR_NOT_TRADABLE);
        return false;
    }

    return true;
}

bool
CreateOfferOpFrame::currentPriceRestrictionsMet(LedgerManager& lm)
{
    if (!lm.shouldUse(LedgerVersion::ASSET_PAIR_RESTRICTIONS))
    {
        return true;
    }

    if (!mAssetPair->checkPolicy(AssetPairPolicy::CURRENT_PRICE_RESTRICTION))
    {
        return true;
    }

    if (mManageOffer.price < mAssetPair->getMinPriceInTermsOfCurrent())
    {
        return false;
    }

    if (mManageOffer.price > mAssetPair->getMaxPriceInTermsOfCurrent())
    {
        return false;
    }

    return true;
}

bool
CreateOfferOpFrame::physicalPriceRestrictionsMet(LedgerManager& lm)
{
    if (!lm.shouldUse(LedgerVersion::ASSET_PAIR_RESTRICTIONS))
    {
        return true;
    }

    if (!mAssetPair->checkPolicy(AssetPairPolicy::PHYSICAL_PRICE_RESTRICTION))
    {
        return true;
    }

    if (mManageOffer.price < mAssetPair->getMinAllowedPrice())
    {
        return false;
    }

    return true;
}
}
