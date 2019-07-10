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
#include "CreateAtomicSwapAskRequestOpFrame.h"

using namespace std;

namespace stellar
{

CreateAtomicSwapAskRequestOpFrame::CreateAtomicSwapAskRequestOpFrame(
        Operation const &op, OperationResult &opRes, TransactionFrame &parentTx)
        : OperationFrame(op, opRes, parentTx)
        , mCreateASwapAskCreationRequest(
                  mOperation.body.createAtomicSwapAskRequestOp())
{
}

bool
CreateAtomicSwapAskRequestOpFrame::tryGetOperationConditions(
                                StorageHelper &storageHelper,
                                std::vector<OperationCondition> &result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.loadBalance(mCreateASwapAskCreationRequest.request.baseBalance);
    if (!balance)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(balance->getAsset());

    AccountRuleResource resource(LedgerEntryType::ATOMIC_SWAP_ASK);
    resource.atomicSwapAsk().assetType = asset->getType();
    resource.atomicSwapAsk().assetCode = asset->getCode();

    if (mCreateASwapAskCreationRequest.allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    return true;
}

bool
CreateAtomicSwapAskRequestOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
        std::vector<SignerRequirement> &result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balance = balanceHelper.mustLoadBalance(
            mCreateASwapAskCreationRequest.request.baseBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto asset = assetHelper.mustLoadAsset(balance->getAsset());

    SignerRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
    resource.reviewableRequest().details.requestType(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    resource.reviewableRequest().details.createAtomicSwapAskExt().v(LedgerVersion::ATOMIC_SWAP_RETURNING);
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetCode = asset->getCode();
    resource.reviewableRequest().details.createAtomicSwapAskExt().createAtomicSwapAsk().assetType = asset->getType();
    resource.reviewableRequest().tasksToRemove = 0;
    resource.reviewableRequest().tasksToAdd = 0;
    resource.reviewableRequest().allTasks = 0;
    if (mCreateASwapAskCreationRequest.allTasks)
    {
        resource.reviewableRequest().allTasks = *mCreateASwapAskCreationRequest.allTasks;
    }

    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

CreateAtomicSwapAskRequestResultCode
CreateAtomicSwapAskRequestOpFrame::isBaseAssetValid(Database &db,
        uint64 baseAmount, AssetCode baseAssetCode)
{
    auto baseAsset = AssetHelperLegacy::Instance()->loadAsset(baseAssetCode, db);
    if (!baseAsset)
    {
        return CreateAtomicSwapAskRequestResultCode::BASE_ASSET_NOT_FOUND;
    }

    if (!baseAsset->isPolicySet(AssetPolicy::CAN_BE_BASE_IN_ATOMIC_SWAP))
    {
        return CreateAtomicSwapAskRequestResultCode::BASE_ASSET_CANNOT_BE_SWAPPED;
    }

    if (!baseAsset->isAmountAppropriate(baseAmount))
    {
        return CreateAtomicSwapAskRequestResultCode::INCORRECT_PRECISION;
    }

    return CreateAtomicSwapAskRequestResultCode::SUCCESS;
}

CreateAtomicSwapAskRequestResultCode
CreateAtomicSwapAskRequestOpFrame::isQuoteAssetValid(Database& db,
        AssetCode baseAssetCode, AtomicSwapAskQuoteAsset quoteAsset)
{
    if (baseAssetCode == quoteAsset.quoteAsset)
    {
        return CreateAtomicSwapAskRequestResultCode::ASSETS_ARE_EQUAL;
    }

    auto quoteAssetFrame = AssetHelperLegacy::Instance()->loadAsset(quoteAsset.quoteAsset, db);

    if (!quoteAssetFrame)
    {
        return CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_NOT_FOUND;
    }

    if (!quoteAssetFrame->isPolicySet(AssetPolicy::CAN_BE_QUOTE_IN_ATOMIC_SWAP))
    {
        return CreateAtomicSwapAskRequestResultCode::QUOTE_ASSET_CANNOT_BE_SWAPPED;
    }

    return CreateAtomicSwapAskRequestResultCode::SUCCESS;
}

CreateAtomicSwapAskRequestResultCode
CreateAtomicSwapAskRequestOpFrame::areQuoteAssetsValid(Database& db,
        AssetCode baseAssetCode, xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets)
{
    for (auto const& quoteAsset : quoteAssets)
    {
        auto quoteAssetValidationResultCode = isQuoteAssetValid(db,
                baseAssetCode, quoteAsset);
        if (quoteAssetValidationResultCode !=
            CreateAtomicSwapAskRequestResultCode::SUCCESS)
        {
            return quoteAssetValidationResultCode;
        }
    }

    return CreateAtomicSwapAskRequestResultCode::SUCCESS;
}

CreateAtomicSwapAskRequestResultCode
CreateAtomicSwapAskRequestOpFrame::areAllAssetsValid(Database &db,
        uint64_t baseAmount, AssetCode baseAssetCode,
        xdr::xvector<AtomicSwapAskQuoteAsset> quoteAssets)
{
    auto validationResultCode = isBaseAssetValid(db, baseAmount, baseAssetCode);
    if (validationResultCode != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    validationResultCode = areQuoteAssetsValid(db, baseAssetCode, quoteAssets);
    if (validationResultCode != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        return validationResultCode;
    }

    return CreateAtomicSwapAskRequestResultCode::SUCCESS;
}

void CreateAtomicSwapAskRequestOpFrame::tryAutoApprove(
        Database& db, LedgerDelta& delta, Application& app,
        ReviewableRequestFrame::pointer request)
{
    auto& ledgerManager = app.getLedgerManager();
    auto result = ReviewRequestHelper::tryApproveRequestWithResult(mParentTx,
            app, ledgerManager, delta, request);
    if (result.code() != ReviewRequestResultCode::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: "
                   "tryApproveRequest expected to be success, but was: "
                << xdr::xdr_to_string(result);
        throw std::runtime_error("Unexpected state: "
                                 "tryApproveRequest expected to be success");
    }

    innerResult().success().fulfilled = true;
    innerResult().success().askID = result.success().typeExt.atomicSwapAskExtended().askID;
}

bool
CreateAtomicSwapAskRequestOpFrame::doApply(Application &app, StorageHelper& storageHelper,
                                              LedgerManager &ledgerManager)
{
    Database& db = storageHelper.getDatabase();
    auto& requestBody = mCreateASwapAskCreationRequest.request;

    auto baseBalance = storageHelper.getBalanceHelper().loadBalance(
            requestBody.baseBalance, getSourceID());
    if (!baseBalance)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_NOT_FOUND);
        return false;
    }

    auto validationResultCode = areAllAssetsValid(db, requestBody.amount,
            baseBalance->getAsset(), requestBody.quoteAssets);
    if (validationResultCode != CreateAtomicSwapAskRequestResultCode::SUCCESS)
    {
        innerResult().code(validationResultCode);
        return false;
    }

    auto lockResult = baseBalance->tryLock(requestBody.amount);
    if (lockResult != BalanceFrame::Result::SUCCESS)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::BASE_BALANCE_UNDERFUNDED);
        return false;
    }

    storageHelper.getBalanceHelper().storeChange(baseBalance->mEntry);

    auto& keyValueHelper = storageHelper.getKeyValueHelper();
    uint32_t allTasks;
    if (!keyValueHelper.loadTasks(allTasks, makeTasksKeyVector(), mCreateASwapAskCreationRequest.allTasks.get()))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::ATOMIC_SWAP_ASK_TASKS_NOT_FOUND);
        return false;
    }

    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto requestFrame = ReviewableRequestFrame::createNew(delta, getSourceID(),
            app.getAdminID(), nullptr, ledgerManager.getCloseTime());
    fillRequest(requestFrame->getRequestEntry(), requestBody, allTasks);
    requestFrame->recalculateHashRejectReason();

    ReviewableRequestHelperLegacy::Instance()->storeAdd(delta, db, requestFrame->mEntry);

    innerResult().code(CreateAtomicSwapAskRequestResultCode::SUCCESS);
    innerResult().success().requestID = requestFrame->getRequestID();
    innerResult().success().fulfilled = false;

    if (requestFrame->canBeFulfilled(ledgerManager))
    {
        tryAutoApprove(db, delta, app, requestFrame);
    }

    return true;
}

bool CreateAtomicSwapAskRequestOpFrame::doCheckValid(Application &app)
{
    auto& aSwapCreationRequest = mCreateASwapAskCreationRequest.request;

    if (aSwapCreationRequest.amount == 0)
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::INVALID_AMOUNT);
        return false;
    }

    if (!isValidJson(aSwapCreationRequest.creatorDetails))
    {
        innerResult().code(CreateAtomicSwapAskRequestResultCode::INVALID_DETAILS);
        return false;
    }

    set<AssetCode> quoteAssets;
    for (auto const& quoteAsset : aSwapCreationRequest.quoteAssets)
    {
        if (!AssetFrame::isAssetCodeValid(quoteAsset.quoteAsset))
        {
            innerResult().code(
                    CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        if (quoteAssets.find(quoteAsset.quoteAsset) != quoteAssets.end())
        {
            innerResult().code(
                    CreateAtomicSwapAskRequestResultCode::INVALID_QUOTE_ASSET);
            return false;
        }

        quoteAssets.insert(quoteAsset.quoteAsset);

        if (quoteAsset.price == 0)
        {
            innerResult().code(CreateAtomicSwapAskRequestResultCode::INVALID_PRICE);
            return false;
        }
    }

    return true;
}

void
CreateAtomicSwapAskRequestOpFrame::fillRequest(ReviewableRequestEntry &requestEntry,
                                                  CreateAtomicSwapAskRequest body, uint32_t allTasks)
{
    requestEntry.body.type(ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK);
    requestEntry.body.createAtomicSwapAskRequest() = body;

    requestEntry.tasks.allTasks = allTasks;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
}

std::vector<std::string>
CreateAtomicSwapAskRequestOpFrame::makeTasksKeyVector()
{
    return {ManageKeyValueOpFrame::makeAtomicSwapAskTasksKey()};
}

}
