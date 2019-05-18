#include "main/Application.h"
#include "database/Database.h"
#include <transactions/dex/OfferManager.h>
#include <ledger/LedgerDelta.h>
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/KeyValueHelper.h"
#include <ledger/AssetHelperLegacy.h>
#include <ledger/ReviewableRequestFrame.h>
#include <ledger/ReviewableRequestHelper.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include <transactions/ManageKeyValueOpFrame.h>
#include "CreateASwapBidCreationRequestOpFrame.h"

using namespace std;

namespace stellar
{

CreateASwapBidCreationRequestOpFrame::CreateASwapBidCreationRequestOpFrame(
        Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx)
        , mCreateASwapBidCreationRequest(
                  mOperation.body.createAtomicSwapBidRequestOp())
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
    resource.reviewableRequest().details.createAtomicSwapBidExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapBidExt().createAtomicSwapBid().assetType = asset->getType();
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

CreateAtomicSwapBidRequestResultCode
CreateASwapBidCreationRequestOpFrame::isBaseAssetValid(Database &db,
        uint64 baseAmount, AssetCode baseAssetCode)
{
    auto baseAsset = AssetHelperLegacy::Instance()->loadAsset(baseAssetCode, db);
    if (!baseAsset)
    {
        return CreateAtomicSwapBidRequestResultCode::BASE_ASSET_NOT_FOUND;
    }

    if (!baseAsset->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
    {
        return CreateAtomicSwapBidRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED;
    }

    if (!baseAsset->isAmountAppropriate(baseAmount))
    {
        return CreateAtomicSwapBidRequestResultCode::INCORRECT_PRECISION;
    }

    return CreateAtomicSwapBidRequestResultCode::SUCCESS;
}

CreateAtomicSwapBidRequestResultCode
CreateASwapBidCreationRequestOpFrame::isQuoteAssetValid(Database& db,
        AssetCode baseAssetCode, AtomicSwapBidQuoteAsset quoteAsset)
{
    if (baseAssetCode == quoteAsset.quoteAsset)
    {
        return CreateAtomicSwapBidRequestResultCode::ASSETS_ARE_EQUAL;
    }

    auto quoteAssetFrame = AssetHelperLegacy::Instance()->loadAsset(quoteAsset.quoteAsset, db);

    if (!quoteAssetFrame)
    {
        return CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_NOT_FOUND;
    }

    if (!quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
    {
        return CreateAtomicSwapBidRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateAtomicSwapBidRequestResultCode::SUCCESS;
}

CreateAtomicSwapBidRequestResultCode
CreateASwapBidCreationRequestOpFrame::areQuoteAssetsValid(Database& db,
        AssetCode baseAssetCode, xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        auto quoteAssetValidationResultCode = isQuoteAssetValid(db,
                baseAssetCode, quoteAsset);
        if (quoteAssetValidationResultCode !=
            CreateAtomicSwapBidRequestResultCode::SUCCESS)
        {
            return quoteAssetValidationResultCode;
        }
    }

    return CreateAtomicSwapBidRequestResultCode::SUCCESS;
}

CreateAtomicSwapBidRequestResultCode
CreateASwapBidCreationRequestOpFrame::areAllAssetsValid(Database &db,
        uint64_t baseAmount, AssetCode baseAssetCode,
        xdr::xvector<AtomicSwapBidQuoteAsset> quoteAssets)
{
    auto validationResultCode = isBaseAssetValid(db, baseAmount, baseAssetCode);
    if (validationResultCode != CreateAtomicSwapBidRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    validationResultCode = areQuoteAssetsValid(db, baseAssetCode, quoteAssets);
    if (validationResultCode != CreateAtomicSwapBidRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    return CreateAtomicSwapBidRequestResultCode::SUCCESS;
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
CreateASwapBidCreationRequestOpFrame::doApply(Application &app, StorageHelper& storageHelper,
                                              LedgerManager &ledgerManager)
{
    Database& db = storageHelper.getDatabase();
    auto& requestBody = mCreateASwapBidCreationRequest.request;

    auto baseBalance = storageHelper.getBalanceHelper().loadBalance(
            requestBody.baseBalance, getSourceID());
    if (!baseBalance)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::BASE_BALANCE_NOT_FOUND);
        return false;
    }

    auto validationResultCode = areAllAssetsValid(db, requestBody.amount,
            baseBalance->getAsset(), requestBody.quoteAssets);
    if (validationResultCode != CreateAtomicSwapBidRequestResultCode::SUCCESS)
    {
        innerResult().code(validationResultCode);
        return false;
    }

    auto lockResult = baseBalance->tryLock(requestBody.amount);
    if (lockResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::BASE_BALANCE_UNDERFUNDED);
        return false;
    }

    storageHelper.getBalanceHelper().storeChange(baseBalance->mEntry);

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(), mCreateASwapBidCreationRequest.allTasks.get()))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::ATOMIC_SWAP_BID_TASKS_NOT_FOUND);
        return false;
    }

    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());
    fillRequest(requestFrame->getRequestEntry(), requestBody, allTasks);
    requestFrame->recalculateHashRejectReason();

    ReviewableRequestHelper::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateAtomicSwapBidRequestResultCode::SUCCESS);
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
        innerResult().code(CreateAtomicSwapBidRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (!isValidJson(aSwapCreationRequest.creatorDetails))
    {
        innerResult().code(CreateAtomicSwapBidRequestResultCode::INVALID_DETAILS);
        return false;
    }

    set<AssetCode> quoteAssets;
    for (auto const& quoteAsset : aSwapCreationRequest.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset))
        {
            innerResult().code(
                    CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        if (quoteAssets.find(quoteAsset.quoteAsset) != quoteAssets.end())
        {
            innerResult().code(
                    CreateAtomicSwapBidRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        quoteAssets.insert(quoteAsset.quoteAsset);

        if (quoteAsset.price == 0)
        {
            innerResult().code(CreateAtomicSwapBidRequestResultCode::INVALID_PRICE);
            return false;
        }
    }

    return true;
}

void
CreateASwapBidCreationRequestOpFrame::fillRequest(ReviewableRequestEntry &requestEntry,
                                                  CreateAtomicSwapBidRequest body, uint32_t allTasks)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_BID);
    requestEntry.body.createAtomicSwapBidRequest() = body;

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
}

std::vector<std::string>
CreateASwapBidCreationRequestOpFrame::makeTasksKeyVector()
{
    return {ManageKeyValueOpFrame::makeAtomicSwapBidTasksKey()};
}

}