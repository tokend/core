// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CreateSaleParticipationOpFrame.h"
#include "OfferManager.h"
#include "database/Database.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountSpecificRuleHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetHelperLegacy.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelperImpl.h"
#include "main/Application.h"
#include "transactions/issuance/CreateIssuanceRequestOpFrame.h"
#include "transactions/sale/CheckSaleStateOpFrame.h"
#include "xdrpp/printer.h"
#include "xdrpp/marshal.h"

namespace stellar
{
using namespace std;
using xdr::operator==;
using xdr::operator<;

bool
CreateSaleParticipationOpFrame::tryGetOperationConditions(StorageHelper &storageHelper,
                                            std::vector<OperationCondition> &result) const
{
    auto sale = SaleHelper::Instance()->loadSale(mManageOffer.orderBookID,
            storageHelper.getDatabase());
    if (!sale)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SALE;
        return false;
    }

    AccountRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();

    result.emplace_back(resource, AccountRuleAction::PARTICIPATE, mSourceAccount);

    return CreateOfferOpFrame::tryGetOperationConditions(storageHelper, result);
}

bool
CreateSaleParticipationOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                         std::vector<SignerRequirement>& result) const
{
    auto sale = SaleHelper::Instance()->loadSale(mManageOffer.orderBookID,
            storageHelper.getDatabase());
    if (!sale)
    {
        throw std::runtime_error("Expected sale to exists");
    }

    SignerRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();

    result.emplace_back(resource, SignerRuleAction::PARTICIPATE);

    return CreateOfferOpFrame::tryGetSignerRequirements(storageHelper, result);
}

SaleFrame::pointer CreateSaleParticipationOpFrame::loadSaleForOffer(
    Database& db, LedgerDelta& delta)
{
    auto baseBalance = loadBalanceValidForTrading(mManageOffer.baseBalance, db,
                                                  delta);
    if (!baseBalance)
    {
        return nullptr;
    }

    auto quoteBalance = loadBalanceValidForTrading(mManageOffer.quoteBalance,
                                                   db, delta);
    if (!quoteBalance)
    {
        return nullptr;
    }

    auto sale = SaleHelper::Instance()->loadSale(mManageOffer.orderBookID,
                                                 baseBalance->getAsset(),
                                                 quoteBalance->getAsset(), db,
                                                 &delta);
    if (!sale)
    {
        innerResult().code(ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS);
        return nullptr;
    }

    if (!isPriceValid(sale, quoteBalance, db))
    {
        return nullptr;
    }

    return sale;
}

bool CreateSaleParticipationOpFrame::isPriceValid(SaleFrame::pointer sale, BalanceFrame::pointer quoteBalance, Database& db) const
{
    if (sale->getPrice(quoteBalance->getAsset()) != mManageOffer.price)
    {
        innerResult().code(ManageOfferResultCode::PRICE_DOES_NOT_MATCH);
        return false;
    }

    //ensure that on soft cap we are able to receive some tokens
    if (sale->getSaleType() != SaleType::CROWD_FUNDING)
    {
        return true;
    }

    const int64_t priceForSoftCap = CheckSaleStateOpFrame::getSalePriceForCap(sale->getSoftCap(), sale);
    const int64_t priceInQuoteAsset = CheckSaleStateOpFrame::getPriceInQuoteAsset(priceForSoftCap, sale, quoteBalance->getAsset(), db);
    const uint64_t baseStep = AssetHelperLegacy::Instance()->mustLoadAsset(sale->getBaseAsset(), db)->getMinimumAmount();
    int64_t baseAmount = 0;
    if (!bigDivide(baseAmount, mManageOffer.amount, ONE, priceInQuoteAsset, ROUND_DOWN, baseStep))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate base amount for sale participation on soft cap " << xdr::xdr_to_string(mManageOffer);
        throw runtime_error("Failed to calculate base amount for sale participation on soft cap");
    }

    if (baseAmount == 0)
    {
        innerResult().code(ManageOfferResultCode::INVALID_AMOUNT);
        return false;
    }

    return true;
}

CreateSaleParticipationOpFrame::CreateSaleParticipationOpFrame(
    Operation const& op, OperationResult& res,
    TransactionFrame& parentTx) : CreateOfferOpFrame(op, res, parentTx, FeeType::INVEST_FEE)
{
}

bool CreateSaleParticipationOpFrame::doCheckValid(Application& app)
{
    if (!mManageOffer.isBuy)
    {
        innerResult().code(ManageOfferResultCode::MALFORMED);
        return false;
    }

    return CreateOfferOpFrame::doCheckValid(app);
}

bool CreateSaleParticipationOpFrame::isSaleActive(Database& db, LedgerManager& ledgerManager, const SaleFrame::pointer sale)
{
    const auto saleState = getSaleState(sale, db, ledgerManager.getCloseTime());
    switch (saleState)
    {
    case SaleFrame::State::ACTIVE:
        return true;
        // just fall through
    case SaleFrame::State::NOT_STARTED_YET:
    {
        innerResult().code(ManageOfferResultCode::SALE_IS_NOT_STARTED_YET);
        return false;
    }
    case SaleFrame::State::ENDED:
    {
        innerResult().code(ManageOfferResultCode::SALE_ALREADY_ENDED);
        return false;
    }
    default:
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
            "Unexpected state of the sale: " << static_cast<int32_t>(saleState);
        throw runtime_error("Unexpected state of the sale");
    }
    }
}

bool
CreateSaleParticipationOpFrame::checkSaleRules(StorageHelper& storageHelper, SaleFrame::pointer const& sale)
{
    switch (sale->getSaleEntry().ext.v())
    {
        case LedgerVersion::EMPTY_VERSION:
            return true;
        case LedgerVersion::ADD_SALE_WHITELISTS:
            break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected sale request version"
                                 << static_cast<int32_t>(sale->getSaleEntry().ext.v());
            throw std::runtime_error("Unexpected sale request version");
    }

    auto& accountSpecificRule = storageHelper.getAccountSpecificRuleHelper();

    auto rule = accountSpecificRule.loadRule(sale->getKey(), getSourceID());
    if (!rule)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Expected specific rule to exists, sale id: "
                                               << sale->getID() << ", account id: "
                                               << PubKeyUtils::toStrKey(getSourceID());
        throw std::runtime_error("Expected specific rule to exists");
    }

    if (rule->forbids())
    {
        innerResult().code(ManageOfferResultCode::SPECIFIC_RULE_FORBIDS);
        return false;
    }

    return true;
}

bool CreateSaleParticipationOpFrame::doApply(Application& app,
                                             LedgerDelta& delta,
                                             LedgerManager& ledgerManager)
{
    auto& db = app.getDatabase();
    StorageHelperImpl storageHelper(db, &delta);

    auto sale = loadSaleForOffer(db, delta);
    if (!sale)
    {
        return false;
    }

    if (sale->getSaleEntry().ownerID == getSourceID())
    {
        innerResult().code(ManageOfferResultCode::CANT_PARTICIPATE_OWN_SALE);
        return false;
    }

    if (!isSaleActive(db, ledgerManager, sale))
    {
        return false;
    }

    if (!checkSaleRules(storageHelper, sale))
    {
        return false;
    }

    if (!sale->tryLockBaseAsset(mManageOffer.amount))
    {
        innerResult().code(ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP);
        return false;
    }

    auto quoteBalance = BalanceHelperLegacy::Instance()->mustLoadBalance(mManageOffer.quoteBalance, db);
    const auto quoteAmount = OfferManager::calculateQuoteAmount(mManageOffer.amount, mManageOffer.price,
            quoteBalance->getMinimumAmount());
    if (quoteAmount == 0)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: quote amount overflows";
        throw runtime_error("Unexpected state: quote amount overflows");
    }

    if (!tryAddSaleCap(db, quoteAmount, quoteBalance->getAsset(), sale))
    {
        innerResult().code(ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP);
        return false;
    }
    switch (sale->getSaleType())
    {
    case SaleType::BASIC_SALE:
    case SaleType::CROWD_FUNDING:
    case SaleType::FIXED_PRICE:
        break;
    case SaleType::IMMEDIATE:
    {
        createImmediateSaleCounterOffer(app, storageHelper, ledgerManager, sale,
                                        quoteAmount);
    }
    }

    const auto isApplied = CreateOfferOpFrame::doApply(app, delta, ledgerManager);
    if (!isApplied)
    {
        return false;
    }

    if (innerResult().code() != ManageOfferResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) <<
            "Unexpected state: expected success for manage offer on create sale participation, but got: "
            << getInnerResultCodeAsStr();
        throw
            runtime_error("Unexpected state: expected success for manage offer on create sale participation");
    }

    switch (sale->getSaleType())
    {
    case SaleType::BASIC_SALE:
    case SaleType::CROWD_FUNDING:
    case SaleType::FIXED_PRICE:
    {
        if (!innerResult().success().offersClaimed.empty())
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) <<
                                                   "Unexpected state. Order match on sale participation: " <<
                                                   mManageOffer.orderBookID;
            throw runtime_error("Order match on sale participation");
        }
        break;
    }
    case SaleType::IMMEDIATE:
        break;
    }

    SaleHelper::Instance()->storeChange(delta, db, sale->mEntry);

    return true;
}

bool CreateSaleParticipationOpFrame::getSaleCurrentCap(const SaleFrame::pointer sale,
    Database& db, uint64_t& totalCurrentCapInDefaultQuote)
{
    totalCurrentCapInDefaultQuote = 0;
    auto const& saleEntry = sale->getSaleEntry();
    for (auto const& quoteAsset : saleEntry.quoteAssets)
    {
        if (quoteAsset.currentCap == 0)
            continue;

        if (quoteAsset.quoteAsset == saleEntry.defaultQuoteAsset)
        {
            if (!safeSum(totalCurrentCapInDefaultQuote, quoteAsset.currentCap, totalCurrentCapInDefaultQuote))
                return false;

            continue;
        }

        const auto assetPair = AssetPairHelper::Instance()->tryLoadAssetPairForAssets(quoteAsset.quoteAsset, saleEntry.defaultQuoteAsset, db);
        if (!assetPair)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to load asset pair for sale: " << saleEntry.saleID
                << " assets: " << quoteAsset.quoteAsset << " & " << saleEntry.defaultQuoteAsset;
            throw runtime_error("Failed to load asset pair for sale");
        }

        auto defaultQuoteAssetFrame = AssetHelperLegacy::Instance()->mustLoadAsset(saleEntry.defaultQuoteAsset, db);
        uint64_t currentCapInDefaultQuote = 0;
        if (!AssetPairHelper::Instance()->convertAmount(assetPair, saleEntry.defaultQuoteAsset, quoteAsset.currentCap,
                                                        ROUND_UP, db, currentCapInDefaultQuote))
        {
            return false;
        }

        if (!safeSum(totalCurrentCapInDefaultQuote, currentCapInDefaultQuote, totalCurrentCapInDefaultQuote))
            return false;
    }

    return true;
}

SaleFrame::State CreateSaleParticipationOpFrame::getSaleState(const SaleFrame::pointer sale, Database& db, const uint64_t currentTime)
{
    uint64_t currentCap = 0;
    if (!getSaleCurrentCap(sale, db, currentCap))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate current cap for sale: " << sale->getID();
        throw runtime_error("Failed to calculate current cap for sale");
    }

    if (currentCap >= sale->getHardCap() || sale->getEndTime() <= currentTime)
    {
        return SaleFrame::State::ENDED;
    }

    if (sale->getStartTime() > currentTime)
    {
        return SaleFrame::State::NOT_STARTED_YET;
    }

    return SaleFrame::State::ACTIVE;
}

bool CreateSaleParticipationOpFrame::tryAddSaleCap(Database& db, uint64_t const& amount,
    AssetCode const& asset, SaleFrame::pointer sale)
{
    auto& saleQuoteAsset = sale->getSaleQuoteAsset(asset);
    if (!safeSum(amount, saleQuoteAsset.currentCap, saleQuoteAsset.currentCap))
    {
        return false;
    }

    uint64_t currentCap = 0;
    if (!getSaleCurrentCap(sale, db, currentCap))
    {
        return false;
    }

    if (sale->getHardCap() < currentCap)
    {
        const auto isViolationTolerable = currentCap - sale->getHardCap() < ONE;
        if (!isViolationTolerable)
            return false;
    }

    return true;

}

void
CreateSaleParticipationOpFrame::createImmediateSaleCounterOffer(
    Application& app, StorageHelper& storageHelper, LedgerManager& lm,
    SaleFrame::pointer sale, uint64_t quoteAmount)
{
    auto& assetHelper = storageHelper.getAssetHelper();
    auto baseAsset = assetHelper.mustLoadAsset(sale->getBaseAsset());
    baseAsset->mustUnlockIssuedAmount(mManageOffer.amount);
    assetHelper.storeChange(baseAsset->mEntry);

    auto saleOwner =
        storageHelper.getAccountHelper().loadAccount(sale->getOwnerID());

    auto reference = binToHex(sha256(xdr::xdr_to_opaque(
        mSourceAccount->getID(), sale->getBaseBalanceID(), baseAsset->getCode(),
        mManageOffer.amount, lm.getCloseTime())));

    const auto issuanceRequestOp = CreateIssuanceRequestOpFrame::build(
        baseAsset->getCode(), mManageOffer.amount, sale->getBaseBalanceID(), lm,
        0, &reference);

    Operation op;
    op.sourceAccount.activate() = sale->getOwnerID();
    op.body.type(OperationType::CREATE_ISSUANCE_REQUEST);
    op.body.createIssuanceRequestOp() = issuanceRequestOp;

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::CREATE_ISSUANCE_REQUEST);
    CreateIssuanceRequestOpFrame createIssuanceRequestOpFrame(op, opRes, mParentTx);
    createIssuanceRequestOpFrame.doNotRequireFee();
    createIssuanceRequestOpFrame.setSourceAccountPtr(saleOwner);

    if (!createIssuanceRequestOpFrame.doCheckValid(app) || !createIssuanceRequestOpFrame.doApply(app, storageHelper, lm))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state: failed to apply create issuance request ";
        throw runtime_error("Unexpected state: failed to create issuance request");
    }

    auto quoteBalance =
        storageHelper.getBalanceHelper().loadBalance(mManageOffer.quoteBalance);
    auto& saleQuoteAsset = sale->getSaleQuoteAsset(quoteBalance->getAsset());

    auto& db = storageHelper.getDatabase();
    auto const feeResult = FeeManager::calculateFeeForAccount(
        saleOwner, FeeType::CAPITAL_DEPLOYMENT_FEE, saleQuoteAsset.quoteAsset,
        FeeFrame::SUBTYPE_ANY, quoteAmount, db);

    CheckSaleStateOpFrame::createCounterOffer(
        app, storageHelper.mustGetLedgerDelta(), lm, mParentTx, sale, saleOwner,
        saleQuoteAsset, mManageOffer.amount, mManageOffer.price, feeResult);
}
}
