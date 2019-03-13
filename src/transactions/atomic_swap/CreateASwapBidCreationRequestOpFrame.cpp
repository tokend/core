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
#include <ledger/StorageHelperImpl.h>
#include <transactions/ManageKeyValueOpFrame.h>
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

    if (mCreateASwapBidCreationRequest.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateASwapBidCreationRequestOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
        std::vector<SignerRequirement> &result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.mustLoadBalance(
            mCreateASwapBidCreationRequest.request.baseBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(balance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    resource.reviewableRequest().details.createAtomicSwapBid().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapBid().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateASwapBidCreationRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateASwapBidCreationRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isBaseAssetValid(Database &db,
                                                       AssetCode baseAssetCode)
{
    auto baseAsset = AssetHelperLegacy::Instance()->loadAsset(baseAssetCode, db);
    if (!baseAsset)
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_NOT_FOUND;
    }

    if (!baseAsset->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::isQuoteAssetValid(Database& db,
         uint64_t baseAmount, AssetCode baseAssetCode, ASwapBidQuoteAsset quoteAsset)
{
    if (baseAssetCode == quoteAsset.quoteAsset)
    {
        return CreateASwapBidCreationRequestResultCode::ASSETS_ARE_EQUAL;
    }

    auto quoteAssetFrame = AssetHelperLegacy::Instance()->loadAsset(quoteAsset.quoteAsset, db);

    if (!quoteAssetFrame)
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_NOT_FOUND;
    }

    if (!quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
    {
        return CreateASwapBidCreationRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED;
    }

    const bool isQuoteAmountFits = OfferManager::calculateQuoteAmount(
            baseAmount, quoteAsset.price, quoteAssetFrame->getMinimumAmount()) > 0;
    if (!isQuoteAmountFits)
    {
        return CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_OVERFLOW;
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areQuoteAssetsValid(Database& db,
        uint64_t baseAmount, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        auto quoteAssetValidationResultCode = isQuoteAssetValid(db, baseAmount,
                baseAssetCode, quoteAsset);
        if (quoteAssetValidationResultCode !=
            CreateASwapBidCreationRequestResultCode::SUCCESS)
        {
            return quoteAssetValidationResultCode;
        }
    }

    return CreateASwapBidCreationRequestResultCode::SUCCESS;
}

CreateASwapBidCreationRequestResultCode
CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(Database &db,
        uint64_t baseAmount, AssetCode baseAssetCode,
        xdr::xvector<ASwapBidQuoteAsset> quoteAssets)
{
    auto validationResultCode = isBaseAssetValid(db, baseAssetCode);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    validationResultCode = areQuoteAssetsValid(db, baseAmount, baseAssetCode, quoteAssets);
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

bool
CreateASwapBidCreationRequestOpFrame::doApply(Application &app, LedgerDelta &delta,
                                              LedgerManager &ledgerManager)
{
    Database& db = app.getDatabase();

    auto& requestBody = mCreateASwapBidCreationRequest.request;

    auto balanceHelper = BalanceHelperLegacy::Instance();
    auto baseBalance = balanceHelper->loadBalance(
            getSourceID(), requestBody.baseBalance, db);
    if (!baseBalance)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::BASE_BALANCE_NOT_FOUND);
        return false;
    }

    auto validationResultCode = areAllAssetsValid(db, requestBody.amount,
            baseBalance->getAsset(), requestBody.quoteAssets);
    if (validationResultCode != CreateASwapBidCreationRequestResultCode::SUCCESS)
    {
        innerResult().code(validationResultCode);
        return false;
    }

    auto lockResult = baseBalance->tryLock(requestBody.amount);
    if (lockResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::BASE_BALANCE_UNDERFUNDED);
        return false;
    }

    balanceHelper->storeChange(delta, db, baseBalance->mEntry);

    StorageHelperImpl storageHelper(db, &delta);
    uint32_t allTasks;
    if (!loadTasks(storageHelper, allTasks, mCreateASwapBidCreationRequest.allTasks))
    {
        innerResult().code(CreateASwapBidCreationRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND);
        return false;
    }

    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());
    fillRequest(requestFrame->getRequestEntry(), requestBody, allTasks);
    requestFrame->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateASwapBidCreationRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;

    if (requestFrame->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(db, delta, app, requestFrame);
    }

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
    }

    return true;
}

void
CreateASwapBidCreationRequestOpFrame::fillRequest(ReviewableRequestEntry &requestEntry,
                                                  ASwapBidCreationRequest body, uint32_t allTasks)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    requestEntry.body.aSwapBidCreationRequest() = body;

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
}

std::vector<longstring>
CreateASwapBidCreationRequestOpFrame::makeTasksKeyVector(StorageHelper& storageHelper)
{
    return {ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey()};
}

}