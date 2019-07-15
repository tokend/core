// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/sale/ManageSaleOpFrame.h>
#include "CheckSaleStateOpFrame.h"
#include "ledger/SaleHelper.h"
#include "transactions/dex/ManageOfferOpFrame.h"
#include "ledger/OfferHelper.h"
#include "transactions/dex/OfferManager.h"
#include "ledger/AccountHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "xdrpp/printer.h"
#include "transactions/issuance/CreateIssuanceRequestOpFrame.h"
#include "transactions/dex/CreateSaleParticipationOpFrame.h"
#include "ledger/AssetPairHelper.h"
#include "transactions/dex/DeleteSaleParticipationOpFrame.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CheckSaleStateOpFrame::SaleState CheckSaleStateOpFrame::getSaleState(
    const SaleFrame::pointer sale, StorageHelper& storageHelper, LedgerManager& lm)
{
    uint64_t currentCap = 0;
    if (!CreateSaleParticipationOpFrame::getSaleCurrentCap(storageHelper, sale, currentCap))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate current cap for sale: " << sale->getID();
        throw runtime_error("Failed to calculate current cap for sale");
    }
    const auto reachedHardCap = currentCap >= sale->getHardCap();
    if (reachedHardCap)
    {
        return CLOSE;
    }
    const auto currentTime = lm.getCloseTime();
    const auto expired = sale->getEndTime() <= currentTime;
    if (expired)
    {
        const auto reachedSoftCap = currentCap >= sale->getSoftCap();
        if (reachedSoftCap)
        {
            return CLOSE;
        }
        return CANCEL;
    }
    return NOT_READY;
}

bool
CheckSaleStateOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                 std::vector<OperationCondition>& result) const
{
    auto sale = SaleHelper::Instance()->loadSale(mCheckSaleState.saleID, storageHelper.getDatabase());
    if (!sale)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SALE;
        return false;
    }
    AccountRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();
    result.emplace_back(resource, AccountRuleAction::CHECK, mSourceAccount);
    return true;
}

bool
CheckSaleStateOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                std::vector<SignerRequirement>& result) const
{
    auto sale = SaleHelper::Instance()->loadSale(mCheckSaleState.saleID, storageHelper.getDatabase());
    if (!sale)
    {
        throw std::runtime_error("Expected sale to exists");
    }
    SignerRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();
    result.emplace_back(resource, SignerRuleAction::CHECK);
    return true;
}

void
CheckSaleStateOpFrame::issueBaseTokens(const SaleFrame::pointer sale, const AccountFrame::pointer saleOwnerAccount, Application& app,
                                       StorageHelper& storageHelper, LedgerManager& lm) const
{
    ManageSaleOpFrame::unlockPendingIssuance(storageHelper, sale->getBaseAsset(), sale->getMaxAmountToBeSold());
    auto result = applyCreateIssuanceRequest(sale, saleOwnerAccount, app, storageHelper, lm);
    if (result.code() != CreateIssuanceRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. Create issuance request returned unepected result!"
                                               << xdr::xdr_traits<CreateIssuanceRequestResultCode>::enum_name(result.code())
                                               << "; saleID: " << sale->getID();
        throw runtime_error("Unexpected state. Create issuance request returned unepected result!");
    }
    if (!result.success().fulfilled)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state; issuance request was not fulfilled on check sale state" << "saleID: "
            << sale->getID();
        throw runtime_error("Unexpected state; issuance request was not fulfilled on check sale state");
    }
}

bool CheckSaleStateOpFrame::handleCancel(SaleFrame::pointer sale, StorageHelper& storageHelper, LedgerManager& lm)
{
    ManageSaleOpFrame::cancelSale(sale, storageHelper, lm);
    innerResult().code(CheckSaleStateResultCode::SUCCESS);
    auto& success = innerResult().success();
    success.saleID = sale->getID();
    success.effect.effect(CheckSaleStateEffect::CANCELED);
    return true;
}

void
CheckSaleStateOpFrame::cleanupIssuerBalance(SaleFrame::pointer sale, StorageHelper& storageHelper, LedgerManager& lm, BalanceFrame::pointer balanceBefore)
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceAfter = balanceHelper.loadBalance(sale->getBaseBalanceID());
    auto balanceDelta = safeDelta(balanceBefore->getAmount(), balanceAfter->getAmount());
    if (balanceDelta > ONE)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: after sale close issuer endup with balance different from before sale"
            << sale->getID();
        throw runtime_error(
            "Unexpected state: after sale close issuer endup with balance different from before sale");
    }

    // return delta back to the asset
    const BalanceFrame::Result balanceAfterChargeResult = balanceAfter->tryCharge(balanceDelta);
    if (balanceAfterChargeResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to clean up sale manager balance after sale been performed: " << sale->getID();
        throw std::runtime_error("Unexpected state: failed to clean up sale manager balance after sale been performed");
    }
    balanceHelper.storeChange(balanceAfter->mEntry);

    // return base asset
    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(balanceAfter->getAsset());
    if (!asset->tryUnIssue(balanceDelta))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to unissue redundant amount after sale been performed: "
            << sale->getID();
        throw std::runtime_error("Unexpected state: failed to unissue redundant amount after sale been performed");
    }
    assetHelper.storeChange(asset->mEntry);
}

bool CheckSaleStateOpFrame::handleClose(SaleFrame::pointer sale, Application& app,
                                        StorageHelper& storageHelper, LedgerManager& lm)
{
    updateOfferPrices(sale, storageHelper);
    const auto saleOwnerAccount = storageHelper.getAccountHelper().loadAccount(sale->getOwnerID());

    if (!saleOwnerAccount)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected db state: expected sale owner to exist: "
                                               << PubKeyUtils::toStrKey(sale->getOwnerID());
        throw runtime_error("Unexpected db state: expected sale owner to exist");
    }

    auto balanceBefore = storageHelper.getBalanceHelper().loadBalance(sale->getBaseBalanceID());

    issueBaseTokens(sale, saleOwnerAccount, app, storageHelper, lm);

    innerResult().code(CheckSaleStateResultCode::SUCCESS);
    auto& success = innerResult().success();
    success.saleID = sale->getID();
    success.effect.effect(CheckSaleStateEffect::CLOSED);
    success.effect.saleClosed().saleOwner = saleOwnerAccount->getID();
    for (auto const& quoteAsset : sale->getSaleEntry().quoteAssets)
    {
        if (quoteAsset.currentCap == 0)
            continue;
        const auto saleOfferResult = applySaleOffer(saleOwnerAccount, sale, quoteAsset, app, lm, storageHelper);
        CheckSubSaleClosedResult result;
        result.saleDetails = saleOfferResult;
        result.saleBaseBalance = sale->getBaseBalanceID();
        result.saleQuoteBalance = quoteAsset.quoteBalance;
        success.effect.saleClosed().results.push_back(result);
        ManageSaleOpFrame::cancelAllOffersForQuoteAsset(sale, quoteAsset, storageHelper);
    }
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();

    SaleHelper::Instance()->storeDelete(delta, db, sale->getKey());

    ManageSaleOpFrame::removeSaleRules(storageHelper, sale->getKey());
    cleanupIssuerBalance(sale, storageHelper, lm, balanceBefore);
    return true;
}

CreateIssuanceRequestResult CheckSaleStateOpFrame::applyCreateIssuanceRequest(
    SaleFrame::pointer sale, const AccountFrame::pointer saleOwnerAccount,
    Application& app, StorageHelper& storageHelper, LedgerManager& lm) const
{
    const auto asset = storageHelper.getAssetHelper().loadAsset(sale->getBaseAsset());
    //TODO Must be refactored
    uint64_t amountToIssue = std::min(sale->getBaseAmountForCurrentCap(asset->getMinimumAmount()), asset->getMaxIssuanceAmount());
    const auto issuanceRequestOp = CreateIssuanceRequestOpFrame::build(sale->getBaseAsset(), amountToIssue,
                                                                       sale->getBaseBalanceID(), lm, 0);
    Operation op;
    op.sourceAccount.activate() = sale->getOwnerID();
    op.body.type(OperationType::CREATE_ISSUANCE_REQUEST);
    op.body.createIssuanceRequestOp() = issuanceRequestOp;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::CREATE_ISSUANCE_REQUEST);
    CreateIssuanceRequestOpFrame createIssuanceRequestOpFrame(op, opRes, mParentTx);
    createIssuanceRequestOpFrame.doNotRequireFee();
    createIssuanceRequestOpFrame.setSourceAccountPtr(saleOwnerAccount);

    if (!createIssuanceRequestOpFrame.doCheckValid(app)
        || !createIssuanceRequestOpFrame.doApply(app, storageHelper, lm))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to apply create issuance request on check sale: " << sale->getID();
        throw runtime_error("Unexpected state: failed to create issuance request on check sale");
    }
    return createIssuanceRequestOpFrame.getResult().tr().createIssuanceRequestResult();
}

FeeManager::FeeResult
CheckSaleStateOpFrame::obtainCalculatedFeeForAccount(const AccountFrame::pointer saleOwnerAccount,
                                                     AssetCode const& asset, int64_t amount,
                                                     LedgerManager& lm, Database& db) const
{
    return FeeManager::calculateFeeForAccount(saleOwnerAccount, FeeType::CAPITAL_DEPLOYMENT_FEE, asset,
                                              FeeFrame::SUBTYPE_ANY, amount, db);
}

ManageOfferSuccessResult CheckSaleStateOpFrame::applySaleOffer(
    const AccountFrame::pointer saleOwnerAccount, SaleFrame::pointer sale, SaleQuoteAsset const& saleQuoteAsset, Application& app,
    LedgerManager& lm, StorageHelper& storageHelper) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto baseBalance = balanceHelper.mustLoadBalance(sale->getBaseBalanceID());
    auto quoteBalance = balanceHelper.mustLoadBalance(saleQuoteAsset.quoteBalance);

    const uint64_t baseAmountByCap = sale->getBaseAmountForCurrentCap(saleQuoteAsset.quoteAsset, baseBalance->getMinimumAmount());
    uint64_t baseAmount = min(baseAmountByCap, static_cast<uint64_t>(baseBalance->getAmount()));
    int64_t quoteAmount = OfferManager::calculateQuoteAmount(baseAmount, saleQuoteAsset.price, quoteBalance->getMinimumAmount());

    auto baseAsset = sale->getBaseAsset();
    auto price = saleQuoteAsset.price;

    auto& db = storageHelper.getDatabase();
    auto const feeResult = obtainCalculatedFeeForAccount(saleOwnerAccount, saleQuoteAsset.quoteAsset, quoteAmount, lm, db);

    if (feeResult.isOverflow)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: overflow on sale fees calculation: "
                                               << xdr::xdr_to_string(sale->getSaleEntry());
        throw runtime_error("Unexpected state: overflow on sale fees calculation");
    }


    ManageOfferOp manageOfferOp;
    manageOfferOp = OfferManager::buildManageOfferOp(sale->getBaseBalanceID(), saleQuoteAsset.quoteBalance,
                                                     false, baseAmount, price, feeResult.calculatedPercentFee, 0, sale->getID());

    Operation op;
    op.sourceAccount.activate() = sale->getOwnerID();
    op.body.type(OperationType::MANAGE_OFFER);
    op.body.manageOfferOp() = manageOfferOp;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_OFFER);
    // need to directly create CreateOfferOpFrame to bypass validation of CreateSaleParticipationOpFrame
    CreateOfferOpFrame manageOfferOpFrame(op, opRes, mParentTx, FeeType::CAPITAL_DEPLOYMENT_FEE);
    manageOfferOpFrame.setSourceAccountPtr(saleOwnerAccount);

    if (!manageOfferOpFrame.doCheckValid(app) || !manageOfferOpFrame.doApply(app, storageHelper, lm))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to apply manage offer on check sale: "
                                               << sale->getID() << manageOfferOpFrame.getInnerResultCodeAsStr();
        throw runtime_error("Unexpected state: failed to apply manage offer on check sale");
    }

    const auto manageOfferResultCode = ManageOfferOpFrame::getInnerCode(opRes);
    if (manageOfferResultCode != ManageOfferResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from manage offer on check sale state"
                                               << xdr::xdr_traits<ManageOfferResultCode>::enum_name(manageOfferResultCode);
        throw runtime_error("Unexpected result code from manage offer on check sale state");
    }
    auto result = opRes.tr().manageOfferResult().success();
    if (result.offersClaimed.empty())
    {
        throw runtime_error("Unexpected state: sale was closed, but no order matches");
    }
    return result;
}

bool
CheckSaleStateOpFrame::
cleanSale(SaleFrame::pointer sale, Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) const
{
    if (sale->getSaleType() != SaleType::CROWD_FUNDING)
    {
        return false;
    }

    const auto saleState = getSaleState(sale, storageHelper, ledgerManager);
    if (saleState != CLOSE)
    {
        return false;
    }

    bool wasUpdated = false;
    const int64_t priceInDefaultQuoteAsset = getSaleCurrentPriceInDefaultQuote(sale, storageHelper);
    auto& db = storageHelper.getDatabase();
    for (auto const& quoteAsset : sale->getSaleEntry().quoteAssets)
    {
        const int64_t priceInQuoteAsset = getPriceInQuoteAsset(priceInDefaultQuoteAsset, sale, quoteAsset.quoteAsset, db);
        const uint64 minimumBaseAmount = getMinimumAssetAmount(sale->getSaleEntry().baseAsset, storageHelper);
        int64_t minAllowedQuoteAmount = 0;
        if (!bigDivide(minAllowedQuoteAmount, priceInQuoteAsset, minimumBaseAmount, ONE, ROUND_UP))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate min allowed quote amount: " << sale->getID();
            throw runtime_error("Failed to calculate min quote amount");
        }
        const uint64 minimumQuoteAmount = getMinimumAssetAmount(quoteAsset.quoteAsset, storageHelper);
        minAllowedQuoteAmount = std::max<uint64>(minAllowedQuoteAmount, minimumQuoteAmount);

        // optimization: it's not possible to create offer with quote amount < 1, so we don't have to cancel here
        if (minAllowedQuoteAmount == 1)
        {
            continue;
        }

        // cancel all offers which are less than minAllowedQuoteAmount
        auto offersToCancel =
            OfferHelper::
            Instance()
                ->loadOffers(sale->getBaseAsset(), quoteAsset.quoteAsset, sale->getID(), minAllowedQuoteAmount, db);
        for (const auto offerToCancel : offersToCancel)
        {
            DeleteSaleParticipationOpFrame::
            deleteSaleParticipation(app, storageHelper, ledgerManager, offerToCancel, mParentTx);
            wasUpdated = true;
        }

    }
    return wasUpdated;
}

void CheckSaleStateOpFrame::updateOfferPrices(SaleFrame::pointer sale, StorageHelper& storageHelper) const
{
    auto saleType = sale->getSaleType();
    if (saleType != SaleType::CROWD_FUNDING && saleType != SaleType::FIXED_PRICE)
    {
        return;
    }
    auto& saleEntry = sale->getSaleEntry();
    uint64_t priceInDefaultQuoteAsset = getSaleCurrentPriceInDefaultQuote(sale, storageHelper);
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    for (auto& quoteAsset : saleEntry.quoteAssets)
    {
        quoteAsset.price = getPriceInQuoteAsset(priceInDefaultQuoteAsset, sale, quoteAsset.quoteAsset, db);
        const auto offersToUpdate = OfferHelper::
        Instance()->
            loadOffersWithFilters(sale->getBaseAsset(), quoteAsset.quoteAsset, &saleEntry.saleID, nullptr, db);
        for (auto& offerToUpdate : offersToUpdate)
        {
            auto& offerEntry = offerToUpdate->getOffer();
            offerEntry.price = quoteAsset.price;
            if (!bigDivide(offerEntry.baseAmount, offerEntry.quoteAmount, ONE, offerEntry.price, ROUND_DOWN))
            {
                CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to update price for offer: offerID: "
                                                       << offerEntry.offerID;
                throw runtime_error("Failed to update price for offer on check state");
            }
            offerEntry.baseAmount -= offerEntry.baseAmount % getMinimumAssetAmount(saleEntry.baseAsset, storageHelper);
            OfferHelper::Instance()->storeChange(delta, db, offerToUpdate->mEntry);
        }
    }
    SaleHelper::Instance()->storeChange(delta, db, sale->mEntry);
}

int64_t CheckSaleStateOpFrame::getSaleCurrentPriceInDefaultQuote(
    const SaleFrame::pointer sale, StorageHelper& storageHelper)
{
    if (sale->getSaleType() == SaleType::FIXED_PRICE)
    {
        uint64_t priceInDefaultQuoteAsset = 0;
        if (!bigDivide(priceInDefaultQuoteAsset, sale->getHardCap(), ONE, sale->getMaxAmountToBeSold(), ROUND_UP))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to update prices! saleID: " << sale->getID();
            throw runtime_error("Failed to update prices");
        }
        return priceInDefaultQuoteAsset;
    }
    uint64_t currentCap = 0;
    if (!CreateSaleParticipationOpFrame::getSaleCurrentCap(storageHelper, sale, currentCap) || currentCap > INT64_MAX)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to get sale current cap! saleID: " << sale->getID();
        throw runtime_error("Failed to get current sale cap");
    }
    return getSalePriceForCap(currentCap, sale);
}

int64_t CheckSaleStateOpFrame::getPriceInQuoteAsset(
    int64_t const salePriceInDefaultQuote, const SaleFrame::pointer sale,
    AssetCode const quoteAsset, Database& db)
{
    if (sale->getDefaultQuoteAsset() == quoteAsset)
    {
        return salePriceInDefaultQuote;
    }
    auto assetPair = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(sale->getDefaultQuoteAsset(), quoteAsset, db);
    if (!assetPair)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to load asset pair for quote asset and default quote asset. SaleID: "
            << sale->getID() << " quoteAsset" << quoteAsset;
        throw runtime_error("failed to load default quote asset for sale");
    }
    int64_t priceInQuoteAsset = 0;
    auto ok = false;
    if (assetPair->getBaseAsset() == sale->getDefaultQuoteAsset())
    {
        ok = bigDivide(priceInQuoteAsset, salePriceInDefaultQuote, assetPair->getCurrentPrice(), ONE, ROUND_UP);
    }
    else
    {
        ok = bigDivide(priceInQuoteAsset, salePriceInDefaultQuote, ONE, assetPair->getCurrentPrice(), ROUND_UP);
    }
    if (!ok)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate price in quote asset. SaleID: "
                                               << sale->getID() << " quoteAsset" << quoteAsset;
        throw runtime_error("Failed to calculate price in quote asset");
    }
    return priceInQuoteAsset;
}

CheckSaleStateOpFrame::CheckSaleStateOpFrame(Operation const& op,
                                             OperationResult& res, TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mCheckSaleState(mOperation.body.checkSaleStateOp())
{
}

bool CheckSaleStateOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                                    LedgerManager& ledgerManager)
{
    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    const auto sale = SaleHelper::Instance()->loadSale(mCheckSaleState.saleID, db, &delta);
    if (!sale)
    {
        innerResult().code(CheckSaleStateResultCode::NOT_FOUND);
        return false;
    }
    const auto wasCleaned = cleanSale(sale, app, storageHelper, ledgerManager);
    if (wasCleaned)
    {
        innerResult().code(CheckSaleStateResultCode::SUCCESS);
        innerResult().success().saleID = sale->getID();
        innerResult().success().effect.effect(CheckSaleStateEffect::UPDATED);
        return true;
    }
    auto const saleState = getSaleState(sale, storageHelper, ledgerManager);
    switch (saleState)
    {
        case CLOSE:
            return handleClose(sale, app, storageHelper, ledgerManager);
        case CANCEL:
            return handleCancel(sale, storageHelper, ledgerManager);
        case NOT_READY:
            innerResult().code(CheckSaleStateResultCode::NOT_READY);
            return false;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected sale state: " << saleState;
            throw runtime_error("Unexpected sale state");
    }
}

bool CheckSaleStateOpFrame::doCheckValid(Application& app)
{
    return true;
}

int64_t CheckSaleStateOpFrame::getSalePriceForCap(int64_t const cap,
                                                  const SaleFrame::pointer sale)
{
    int64_t currentSalePrice = 0;
    if (!bigDivide(currentSalePrice, cap, ONE, sale->getMaxAmountToBeSold(), ROUND_UP))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate current sale price in default quote. SaleID: "
                                               << sale->getID();
        throw runtime_error("Failed to calculate current sale price in default quote");
    }
    return currentSalePrice;
}

std::string CheckSaleStateOpFrame::getInnerResultCodeAsStr()
{
    const auto code = getInnerCode(mResult);
    return xdr::xdr_traits<CheckSaleStateResultCode>::enum_name(code);
}

uint64 CheckSaleStateOpFrame::getMinimumAssetAmount(const AssetCode& balance, StorageHelper& storageHelper)
{
    AssetFrame::pointer assetFrame = storageHelper.getAssetHelper().mustLoadAsset(balance);
    return assetFrame->getMinimumAmount();
}
}
