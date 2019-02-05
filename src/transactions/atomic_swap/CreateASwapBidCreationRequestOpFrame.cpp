#include "main/Application.h"
#include "database/Database.h"
#include <transactions/dex/OfferManager.h>
#include <ledger/LedgerDelta.h>
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include <ledger/BalanceHelperLegacy.h>
#include <ledger/AssetHelperLegacy.h>
#include <ledger/ReviewableRequestFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include "CreateASwapBidCreationRequestOpFrame.h"

using namespace std;

namespace stellar
{

CreateASwapBidCreationRequestOpFrame::CreateASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx),
          mCreateASwapBidCreationRequest(
                  mOperation.body.createASwapBidCreationRequestOp())
{
}

bool
CreateASwapBidCreationRequestOpFrame::tryGetOperationConditions(
                                StorageHelper &storageHelper,
                                std::vector<OperationCondition> &result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.loadBalance(mCreateASwapBidCreationRequest.request.baseBalance);
    if (!balance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(balance->getAsset());

    AccountRuleResource resource(LedgerEntryType::ATOMIC_SWAP_BID);
    resource.atomicSwapBid().assetType = asset->getType();
    resource.atomicSwapBid().assetCode = asset->getCode();

    result.emplace_back(resource, "create", mSourceAccount);

    return true;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isBaseAssetValid(Database &db,
                                                       AssetCode baseAssetCode)
{
    AssetFrame::pointer baseAssetFrame =
            AssetHelperLegacy::Instance()->loadAsset(baseAssetCode, db);
    if (baseAssetFrame == nullptr)
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND;
    }

    if (!baseAssetFrame->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isQuoteAssetValid(Database& db,
                                                        AssetCode baseAssetCode,
                                                        AssetCode quoteAssetCode)
{
    if (baseAssetCode == quoteAssetCode)
    {
        return CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL;
    }

    auto quoteAssetFrame = AssetHelperLegacy::Instance()->loadAsset(quoteAssetCode, db);

    if (quoteAssetFrame == nullptr)
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND;
    }

    if (!quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areQuoteAssetsValid(
        Database& db, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        auto quoteAssetValidationResultCode = isQuoteAssetValid(db, baseAssetCode,
                                                                quoteAsset.quoteAsset);
        if (quoteAssetValidationResultCode !=
            CreateASwapBidCreationRequestResultCode::SUCCESS)
        {
            return quoteAssetValidationResultCode;
        }
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(
        Database &db, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    CreateASwapBidCreationRequestResultCode validationResultCode = isBaseAssetValid(
            db, baseAssetCode);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    validationResultCode = areQuoteAssetsValid(db, baseAssetCode, quoteAssets);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

void CreateASwapBidCreationRequestOpFrame::tryAutoApprove(
        Database& db, LedgerDelta& delta, Application& app,
        ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequest(mParentTx, app, ledgerManager,
                                                         delta, request);
    if (result != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: "
                   "tryApproveRequest expected to be success, but was: "
                << xdr::xdr_to_string(result);
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled = true;
}

bool CreateASwapBidCreationRequestOpFrame::doApply(Application &app, LedgerDelta &delta,
                                                LedgerManager &ledgerManager)
{
    Database& db = app.getDatabase();

    auto& aSwapBidCreationRequest = mCreateASwapBidCreationRequest.request;

    BalanceFrame::pointer baseBalanceFrame = BalanceHelperLegacy::Instance()->loadBalance(
                    getSourceID(), aSwapBidCreationRequest.baseBalance, db);
    if (baseBalanceFrame == nullptr)
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::BASE_BALANCE_NOT_FOUND);
        return false;
    }

    auto allAssetsValidationResultCode = areAllAssetsValid(
            db, baseBalanceFrame->getAsset(), aSwapBidCreationRequest.quoteAssets);
    if (allAssetsValidationResultCode !=
        CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        innerResult().code(allAssetsValidationResultCode);
        return false;
    }

    // TODO: move asset requirements check to separate method
    auto baseAssetFrame = AssetHelperLegacy::Instance()->loadAsset(baseBalanceFrame->getAsset(),
                                                             db);
    if (baseAssetFrame == nullptr)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND);
        return false;
    }

    auto lockResult = baseBalanceFrame->tryLock(aSwapBidCreationRequest.amount);
    if (lockResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(
                CreateASwapBidCreationRequestResultCode::BASE_BALANCE_UNDERFUNDED);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
                                                          app.getAdminID(), nullptr,
                                                          ledgerManager.getCloseTime());
    auto& requestEntry = requestFrame->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    requestEntry.body.aSwapBidCreationRequest() = aSwapBidCreationRequest;

    requestFrame->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    EntryHelperProvider::storeChangeEntry(delta, db, baseBalanceFrame->mEntry);

    innerResult().code(CreateASwapBidCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;

    // FIXME: remove constant autoapprove
    tryAutoApprove(db, delta, app, requestFrame);

    return true;
}

bool CreateASwapBidCreationRequestOpFrame::doCheckValid(Application &app)
{
    auto& aSwapCreationRequest = mCreateASwapBidCreationRequest.request;

    if (aSwapCreationRequest.amount == 0)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (!isValidJson(aSwapCreationRequest.creatorDetails))
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_DETAILS);
        return false;
    }

    set<AssetCode> quoteAssets;
    for (auto const& quoteAsset : aSwapCreationRequest.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset))
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        if (quoteAssets.find(quoteAsset.quoteAsset) != quoteAssets.end())
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        quoteAssets.insert(quoteAsset.quoteAsset);

        if (quoteAsset.price == 0)
        {
            innerResult().code(CreateASwapBidCreationRequestResultCode::INVALID_PRICE);
            return false;
        }

        // FIXME: use minimal amount of current quote asset
        const bool isQuoteAmountFits = OfferManager::calculateQuoteAmount(
                aSwapCreationRequest.amount, quoteAsset.price, 1) > 0;
        if (!isQuoteAmountFits)
        {
            innerResult().code(
                    CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW);
            return false;
        }
    }

    return true;
}

}