// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ReviewSaleCreationRequestOpFrame.h"
#include "database/Database.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/SaleHelper.h"
#include "main/Application.h"
#include "transactions/sale/CreateSaleCreationRequestOpFrame.h"
#include "xdrpp/printer.h"
#include <ledger/AccountHelperLegacy.h>
#include <transactions/manage_asset_pair/ManageAssetPairOpFrame.h>
#include <transactions/manage_specific_rule/CreateAccountSpecificRuleOpFrame.h>
#include <ledger/StorageHelperImpl.h>
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

bool
ReviewSaleCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                           std::vector<SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(mReviewRequest.requestID);
    if (!request || (request->getType() != ReviewableRequestType::CREATE_SALE))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_SALE);
    resource.reviewableRequest().details.createSale().type =
        request->getRequestEntry().body.saleCreationRequest().saleType;
    resource.reviewableRequest().tasksToAdd = mReviewRequest.reviewDetails.tasksToAdd;
    resource.reviewableRequest().tasksToRemove = mReviewRequest.reviewDetails.tasksToRemove;
    resource.reviewableRequest().allTasks = 0;

    result.emplace_back(resource, SignerRuleAction::REVIEW);

    return true;
}

SaleCreationRequest&
ReviewSaleCreationRequestOpFrame::getSaleCreationRequestFromBody(
    ReviewableRequestFrame::pointer request)
{
    auto requestType = request->getType();
    switch (requestType)
    {
        case ReviewableRequestType::CREATE_SALE:
        {
            return request->getRequestEntry().body.saleCreationRequest();
        }
        default:
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected reviewable request type while retrieving sale "
                   "creation request from body: "
                << request->getRequestID();
            throw runtime_error("Unexpected reviewable request type while "
                                "retrieving sale creation request from body");
        }
    }
}

ReviewRequestResultCode
ReviewSaleCreationRequestOpFrame::tryCreateSale(
    Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request,
    uint64_t saleID)
{
    auto saleCreationRequest = getSaleCreationRequestFromBody(request);

    auto& db = storageHelper.getDatabase();
    if (!CreateSaleCreationRequestOpFrame::areQuoteAssetsValid(
        db, saleCreationRequest.quoteAssets,
        saleCreationRequest.defaultQuoteAsset))
    {
        if (ledgerManager.shouldUse(LedgerVersion::FIX_INVEST_FEE))
        {
            return ReviewRequestResultCode::ASSET_PAIR_NOT_FOUND;
        }

        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state, quote asset does not exist: "
            << request->getRequestID();
        throw runtime_error("Quote asset does not exist");
    }
    auto& assetHelper = storageHelper.getAssetHelper();

    auto baseAsset = assetHelper.loadAsset(saleCreationRequest.baseAsset, request->getRequestor());
    if (!baseAsset)
    {
        return ReviewRequestResultCode::BASE_ASSET_DOES_NOT_EXISTS;
    }

    const uint64_t requiredBaseAssetForHardCap =
        getRequiredBaseAssetForHardCap(saleCreationRequest);

    if (!baseAsset->lockIssuedAmount(requiredBaseAssetForHardCap))
    {
        return ReviewRequestResultCode::INSUFFICIENT_PREISSUED_FOR_HARD_CAP;
    }

    assetHelper.storeChange(baseAsset->mEntry);

    auto& delta = storageHelper.mustGetLedgerDelta();
    AccountManager accountManager(app, db, delta, ledgerManager);
    const auto balances =
        loadBalances(accountManager, request, saleCreationRequest);
    const auto saleFrame =
        SaleFrame::createNew(saleID, baseAsset->getOwner(), saleCreationRequest,
                             balances, requiredBaseAssetForHardCap);
    SaleHelper::Instance()->storeAdd(delta, db, saleFrame->mEntry);
    createAssetPair(saleFrame, app, ledgerManager, delta);

    createSaleRules(app, storageHelper, ledgerManager, saleCreationRequest, saleFrame);

    return ReviewRequestResultCode::SUCCESS;
}

void
ReviewSaleCreationRequestOpFrame::createSaleRules(Application& app,
                                                  StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                  SaleCreationRequest const& request, SaleFrame::pointer const& sale)
{
    switch (request.ext.v())
    {
        case LedgerVersion::EMPTY_VERSION:
            return;
        case LedgerVersion::ADD_SALE_WHITELISTS:
            break;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected sale request version"
                                                   << static_cast<int32_t>(request.ext.v());
            throw std::runtime_error("Unexpected sale request version");
    }

    auto createRulesData = request.ext.saleRules();

    Operation op;
    op.sourceAccount.activate() = getSourceID();
    op.body.type(OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE);
    ManageAccountSpecificRuleOp& manageRuleOp = op.body.manageAccountSpecificRuleOp();
    manageRuleOp.data.action(ManageAccountSpecificRuleAction::CREATE);

    OperationResult opRes;
    opRes.code(OperationResultCode::opINNER);
    opRes.tr().type(OperationType::MANAGE_ACCOUNT_SPECIFIC_RULE);

    CreateAccountSpecificRuleData createData;
    createData.ledgerKey = sale->getKey();

    for (auto const& createRuleData : createRulesData)
    {
        createData.accountID = createRuleData.accountID;
        createData.forbids = createRuleData.forbids;
        manageRuleOp.data.createData() = createData;

        CreateAccountSpecificRuleOpFrame opFrame(op, opRes, mParentTx);
        opFrame.setSale(sale);
        opFrame.setSourceAccountPtr(mSourceAccount);

        if (!opFrame.doApply(app, storageHelper, ledgerManager))
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to create sale rule "
                                                   << xdr::xdr_to_string(createData, "createData")
                                                   << opFrame.getInnerResultCodeAsStr();
            throw std::runtime_error("Failed to create sale rule");
        }
    }
}

bool
ReviewSaleCreationRequestOpFrame::handleApprove(
    Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
    ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_SALE)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected request type. Expected SALE, but got "
            << xdr::xdr_traits<ReviewableRequestType>::enum_name(
                request->getRequestType());
        throw invalid_argument(
            "Unexpected request type for review sale creation request");
    }

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    requestHelper.storeDelete(request->getKey());

    auto& delta = storageHelper.mustGetLedgerDelta();
    auto newSaleID = delta.getHeaderFrame().generateID(LedgerEntryType::SALE);

    ReviewRequestResultCode saleCreationResult =
        tryCreateSale(app, storageHelper, ledgerManager, request, newSaleID);

    innerResult().code(saleCreationResult);

    if (saleCreationResult != ReviewRequestResultCode::SUCCESS)
    {
        return false;
    }

    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::CREATE_SALE);
    innerResult().success().typeExt.saleExtended().saleID = newSaleID;
    return true;
}

uint64
ReviewSaleCreationRequestOpFrame::getRequiredBaseAssetForHardCap(
    SaleCreationRequest const& saleCreationRequest)
{
    return saleCreationRequest.requiredBaseAssetForHardCap;
}

void
ReviewSaleCreationRequestOpFrame::createAssetPair(SaleFrame::pointer sale,
                                                  Application& app,
                                                  LedgerManager& ledgerManager,
                                                  LedgerDelta& delta) const
{
    for (const auto quoteAsset : sale->getSaleEntry().quoteAssets)
    {
        const auto assetPair = ledgerManager.shouldUse(LedgerVersion::FIX_REVERSE_SALE_PAIR)
                               ? AssetPairHelper::Instance()->loadAssetPair(sale->getBaseAsset(), quoteAsset.quoteAsset,
                                                                            ledgerManager.getDatabase())
                               : AssetPairHelper::Instance()->tryLoadAssetPairForAssets(sale->getBaseAsset(), quoteAsset.quoteAsset,
                                                                                        ledgerManager.getDatabase());
        if (!!assetPair)
        {
            continue;
        }

        // create new asset pair
        Operation op;
        op.body.type(OperationType::MANAGE_ASSET_PAIR);
        auto& manageAssetPair = op.body.manageAssetPairOp();
        manageAssetPair.action = ManageAssetPairAction::CREATE;
        manageAssetPair.base = sale->getBaseAsset();
        manageAssetPair.quote = quoteAsset.quoteAsset;
        manageAssetPair.physicalPrice = quoteAsset.price;

        OperationResult opRes;
        opRes.code(OperationResultCode::opINNER);
        opRes.tr().type(OperationType::MANAGE_ASSET_PAIR);
        ManageAssetPairOpFrame assetPairOpFrame(op, opRes, mParentTx);
        assetPairOpFrame.setSourceAccountPtr(mSourceAccount);
        const auto applied =
            assetPairOpFrame.doCheckValid(app) &&
            assetPairOpFrame.doApply(app, delta, ledgerManager);
        if (!applied)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unable to create asset pair for sale creation request: "
                << sale->getID();
            throw runtime_error(
                "Unexpected state. Unable to create asset pair");
        }
    }
}

std::map<AssetCode, BalanceID>
ReviewSaleCreationRequestOpFrame::loadBalances(
    AccountManager& accountManager,
    const ReviewableRequestFrame::pointer request,
    SaleCreationRequest const& saleCreationRequest)
{
    map<AssetCode, BalanceID> result;
    const auto baseBalanceID = accountManager.loadOrCreateBalanceForAsset(
        request->getRequestor(), saleCreationRequest.baseAsset);
    result.insert(make_pair(saleCreationRequest.baseAsset, baseBalanceID));
    for (auto quoteAsset : saleCreationRequest.quoteAssets)
    {
        const auto quoteBalanceID = accountManager.loadOrCreateBalanceForAsset(
            request->getRequestor(), quoteAsset.quoteAsset);
        result.insert(make_pair(quoteAsset.quoteAsset, quoteBalanceID));
    }
    return result;
}

ReviewSaleCreationRequestOpFrame::ReviewSaleCreationRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}
}
