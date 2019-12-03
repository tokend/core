// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CreateSaleParticipationOpFrame.h"
#include "OfferManager.h"
#include "database/Database.h"
#include "ledger/AccountHelper.h"
#include "ledger/AccountSpecificRuleHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/SaleHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include "transactions/issuance/CreateIssuanceRequestOpFrame.h"
#include "transactions/sale/CheckSaleStateOpFrame.h"
#include "xdrpp/marshal.h"
#include "xdrpp/printer.h"
#include "ledger/StorageHelperImpl.h"

namespace stellar
{
using namespace std;
using xdr::operator==;
using xdr::operator<;

bool
CreateSaleParticipationOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto sale = storageHelper.getSaleHelper().loadSale(mManageOffer.orderBookID);
    if (!sale)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SALE;
        return false;
    }

    AccountRuleResource resource(LedgerEntryType::SALE);
    resource.sale().saleID = sale->getID();
    resource.sale().saleType = sale->getType();

    result.emplace_back(resource, AccountRuleAction::PARTICIPATE,
                        mSourceAccount);

    return CreateOfferOpFrame::tryGetOperationConditions(storageHelper, result);
}

bool
CreateSaleParticipationOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto sale = storageHelper.getSaleHelper().loadSale(mManageOffer.orderBookID);
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

SaleFrame::pointer
CreateSaleParticipationOpFrame::loadSaleForOffer(StorageHelper& storageHelper)
{
    auto baseBalance =
        loadBalanceValidForTrading(storageHelper, mManageOffer.baseBalance);
    if (!baseBalance)
    {
        return nullptr;
    }

    auto quoteBalance =
        loadBalanceValidForTrading(storageHelper, mManageOffer.quoteBalance);
    if (!quoteBalance)
    {
        return nullptr;
    }

    auto& db = storageHelper.getDatabase();
    auto& delta = storageHelper.mustGetLedgerDelta();
    auto sale = storageHelper.getSaleHelper().loadSale(
        mManageOffer.orderBookID, baseBalance->getAsset(),
        quoteBalance->getAsset());
    if (!sale)
    {
        innerResult().code(ManageOfferResultCode::ORDER_BOOK_DOES_NOT_EXISTS);
        return nullptr;
    }

    if (!isPriceValid(storageHelper, sale, quoteBalance))
    {
        return nullptr;
    }

    return sale;
}

bool
CreateSaleParticipationOpFrame::isPriceValid(
    StorageHelper& storageHelper, SaleFrame::pointer sale,
    BalanceFrame::pointer quoteBalance) const
{
    if (sale->getPrice(quoteBalance->getAsset()) != mManageOffer.price)
    {
        innerResult().code(ManageOfferResultCode::PRICE_DOES_NOT_MATCH);
        return false;
    }

    // ensure that on soft cap we are able to receive some tokens
    if (sale->getSaleType() != SaleType::CROWD_FUNDING)
    {
        return true;
    }

    const int64_t priceForSoftCap =
        CheckSaleStateOpFrame::getSalePriceForCap(sale->getSoftCap(), sale);
    auto& db = storageHelper.getDatabase();
    const int64_t priceInQuoteAsset =
        CheckSaleStateOpFrame::getPriceInQuoteAsset(storageHelper, priceForSoftCap, sale, quoteBalance->getAsset());
    const uint64_t baseStep = storageHelper.getAssetHelper()
                                  .mustLoadAsset(sale->getBaseAsset())
                                  ->getMinimumAmount();
    int64_t baseAmount = 0;
    if (!bigDivide(baseAmount, mManageOffer.amount, ONE, priceInQuoteAsset,
                   ROUND_DOWN, baseStep))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate base amount for sale participation on soft "
               "cap "
            << xdr::xdr_to_string(mManageOffer);
        throw runtime_error("Failed to calculate base amount for sale "
                            "participation on soft cap");
    }

    if (baseAmount == 0)
    {
        innerResult().code(ManageOfferResultCode::INVALID_AMOUNT);
        return false;
    }

    return true;
}

CreateSaleParticipationOpFrame::CreateSaleParticipationOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : CreateOfferOpFrame(op, res, parentTx, FeeType::INVEST_FEE)
{
}

bool
CreateSaleParticipationOpFrame::doCheckValid(Application& app)
{
    if (!mManageOffer.isBuy)
    {
        innerResult().code(ManageOfferResultCode::MALFORMED);
        return false;
    }

    return CreateOfferOpFrame::doCheckValid(app);
}

bool
CreateSaleParticipationOpFrame::isSaleActive(StorageHelper& storageHelper,
                                             LedgerManager& ledgerManager,
                                             const SaleFrame::pointer sale)
{
    const auto saleState =
        getSaleState(storageHelper, sale, ledgerManager.getCloseTime());
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
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state of the sale: "
            << static_cast<int32_t>(saleState);
        throw runtime_error("Unexpected state of the sale");
    }
    }
}

bool
CreateSaleParticipationOpFrame::checkSaleRules(StorageHelper& storageHelper,
                                               SaleFrame::pointer const& sale)
{
    switch (sale->getSaleEntry().ext.v())
    {
    case LedgerVersion::EMPTY_VERSION:
        return true;
    case LedgerVersion::ADD_SALE_WHITELISTS:
        break;
    default:
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected sale request version"
            << static_cast<int32_t>(sale->getSaleEntry().ext.v());
        throw std::runtime_error("Unexpected sale request version");
    }

    auto& accountSpecificRule = storageHelper.getAccountSpecificRuleHelper();

    auto rule = accountSpecificRule.loadRule(sale->getKey(), getSourceID());
    if (!rule)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Expected specific rule to exists, sale id: " << sale->getID()
            << ", account id: " << PubKeyUtils::toStrKey(getSourceID());
        throw std::runtime_error("Expected specific rule to exists");
    }

    if (rule->forbids())
    {
        innerResult().code(ManageOfferResultCode::SPECIFIC_RULE_FORBIDS);
        return false;
    }

    return true;
}

bool
CreateSaleParticipationOpFrame::doApply(Application& app,
                                        StorageHelper& storageHelper,
                                        LedgerManager& ledgerManager)
{
    auto sale = loadSaleForOffer(storageHelper);
    if (!sale)
    {
        return false;
    }

    if (sale->getSaleEntry().ownerID == getSourceID())
    {
        innerResult().code(ManageOfferResultCode::CANT_PARTICIPATE_OWN_SALE);
        return false;
    }

    if (!isSaleActive(storageHelper, ledgerManager, sale))
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

    auto quoteBalance = storageHelper.getBalanceHelper().mustLoadBalance(
        mManageOffer.quoteBalance);
    const auto quoteAmount = OfferManager::calculateQuoteAmount(
        mManageOffer.amount, mManageOffer.price,
        quoteBalance->getMinimumAmount());
    if (quoteAmount == 0)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: quote amount overflows";
        throw runtime_error("Unexpected state: quote amount overflows");
    }

    if (!tryAddSaleCap(storageHelper, quoteAmount, quoteBalance->getAsset(),
                       sale))
    {
        innerResult().code(ManageOfferResultCode::ORDER_VIOLATES_HARD_CAP);
        return false;
    }

    // Only for `IMMEDIATE` sale we create counter offer immediately
    if (sale->getSaleType() == SaleType::IMMEDIATE)
    {
        createImmediateSaleCounterOffer(app, storageHelper, ledgerManager, sale,
                                        quoteAmount);
    }

    const auto isApplied =
        CreateOfferOpFrame::doApply(app, storageHelper, ledgerManager);
    if (!isApplied)
    {
        return false;
    }

    if (innerResult().code() != ManageOfferResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: expected success for manage offer on create "
               "sale participation, but got: "
            << getInnerResultCodeAsStr();
        throw runtime_error("Unexpected state: expected success for manage "
                            "offer on create sale participation");
    }

    // For all sale types except `IMMEDIATE` offer claim is erroneous
    if (sale->getSaleType() != SaleType::IMMEDIATE)
    {
        if (!innerResult().success().offersClaimed.empty())
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state. Order match on sale participation: "
                << mManageOffer.orderBookID;
            throw runtime_error("Order match on sale participation");
        }
    }
    storageHelper.getSaleHelper().storeChange(sale->mEntry);
    return true;
}

bool
CreateSaleParticipationOpFrame::getSaleCurrentCap(
    StorageHelper& storageHelper, const SaleFrame::pointer sale,
    uint64_t& totalCurrentCapInDefaultQuote)
{
    totalCurrentCapInDefaultQuote = 0;
    auto const& saleEntry = sale->getSaleEntry();

    auto& assetHelper = storageHelper.getAssetHelper();
    auto& db = storageHelper.getDatabase();

    for (auto const& quoteAsset : saleEntry.quoteAssets)
    {
        if (quoteAsset.currentCap == 0)
            continue;

        if (quoteAsset.quoteAsset == saleEntry.defaultQuoteAsset)
        {
            if (!safeSum(totalCurrentCapInDefaultQuote, quoteAsset.currentCap,
                         totalCurrentCapInDefaultQuote))
                return false;

            continue;
        }

        const auto assetPair = storageHelper.getAssetPairHelper().tryLoadAssetPairForAssets(
                quoteAsset.quoteAsset, saleEntry.defaultQuoteAsset);
        if (!assetPair)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to load asset pair for sale: "
                << saleEntry.saleID << " assets: " << quoteAsset.quoteAsset
                << " & " << saleEntry.defaultQuoteAsset;
            throw runtime_error("Failed to load asset pair for sale");
        }

        auto defaultQuoteAssetFrame =
            assetHelper.mustLoadAsset(saleEntry.defaultQuoteAsset);
        uint64_t currentCapInDefaultQuote = 0;
        if (!storageHelper.getAssetPairHelper().convertAmount(
                assetPair, saleEntry.defaultQuoteAsset, quoteAsset.currentCap,
                ROUND_UP, currentCapInDefaultQuote))
        {
            return false;
        }

        if (!safeSum(totalCurrentCapInDefaultQuote, currentCapInDefaultQuote,
                     totalCurrentCapInDefaultQuote))
            return false;
    }

    return true;
}

SaleFrame::State
CreateSaleParticipationOpFrame::getSaleState(StorageHelper& storageHelper,
                                             const SaleFrame::pointer sale,
                                             const uint64_t currentTime)
{
    uint64_t currentCap = 0;
    if (!getSaleCurrentCap(storageHelper, sale, currentCap))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate current cap for sale: " << sale->getID();
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

bool
CreateSaleParticipationOpFrame::tryAddSaleCap(StorageHelper& storageHelper,
                                              uint64_t const& amount,
                                              AssetCode const& asset,
                                              SaleFrame::pointer sale)
{
    auto& saleQuoteAsset = sale->getSaleQuoteAsset(asset);
    if (!safeSum(amount, saleQuoteAsset.currentCap, saleQuoteAsset.currentCap))
    {
        return false;
    }

    uint64_t currentCap = 0;
    if (!getSaleCurrentCap(storageHelper, sale, currentCap))
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
    CreateIssuanceRequestOpFrame createIssuanceRequestOpFrame(op, opRes,
                                                              mParentTx);
    createIssuanceRequestOpFrame.doNotRequireFee();
    createIssuanceRequestOpFrame.setSourceAccountPtr(saleOwner);

    if (!createIssuanceRequestOpFrame.doCheckValid(app) ||
        !createIssuanceRequestOpFrame.doApply(app, storageHelper, lm))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to apply create issuance request ";
        throw runtime_error(
            "Unexpected state: failed to create issuance request");
    }

    auto quoteBalance =
        storageHelper.getBalanceHelper().loadBalance(mManageOffer.quoteBalance);
    auto& saleQuoteAsset = sale->getSaleQuoteAsset(quoteBalance->getAsset());

    auto& db = storageHelper.getDatabase();
    auto const feeResult = FeeManager::calculateFeeForAccount(storageHelper,
                                                                 saleOwner, FeeType::CAPITAL_DEPLOYMENT_FEE, saleQuoteAsset.quoteAsset,
                                                                 FeeFrame::SUBTYPE_ANY, quoteAmount);

    CheckSaleStateOpFrame::createCounterOffer(
        app, storageHelper, lm, mParentTx, sale, saleOwner, saleQuoteAsset,
        mManageOffer.amount, mManageOffer.price, feeResult);
}
}
