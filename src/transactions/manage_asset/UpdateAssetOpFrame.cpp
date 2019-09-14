// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <transactions/review_request/ReviewRequestHelper.h>
#include "UpdateAssetOpFrame.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/KeyValueHelper.h"
#include "transactions/ManageKeyValueOpFrame.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
UpdateAssetOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                              std::vector<OperationCondition>& result,
                                              LedgerManager& ledgerManager) const
{
    if (ledgerManager.shouldUse(LedgerVersion::FIX_NOT_CHECKING_SET_TASKS_PERMISSIONS))
    {
        AccountRuleResource resource(LedgerEntryType::REVIEWABLE_REQUEST);
        resource.reviewableRequest().details.requestType(ReviewableRequestType::UPDATE_ASSET);

        if (mManageAsset.request.createAssetUpdateRequest().allTasks)
        {
            result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        }
        else
        {
            result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
        }
    }

    // only asset owner can update asset
    return true;
}

bool
UpdateAssetOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                             std::vector<SignerRequirement>& result) const
{
    auto asset = storageHelper.getAssetHelper().loadAsset(mAssetUpdateRequest.code);
    if (!asset)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ASSET;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetCode = asset->getCode();
    resource.asset().assetType = asset->getType();

    result.emplace_back(resource, SignerRuleAction::UPDATE);

    return true;
}

ReviewableRequestFrame::pointer
UpdateAssetOpFrame::getUpdatedOrCreateReviewableRequest(Application& app, StorageHelper& storageHelper)
{
    ReviewableRequestFrame::pointer request =
        getOrCreateReviewableRequest(app, storageHelper, ReviewableRequestType::UPDATE_ASSET);
    if (!request)
    {
        return nullptr;
    }

    ReviewableRequestEntry& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::UPDATE_ASSET);
    requestEntry.body.assetUpdateRequest() = mAssetUpdateRequest;
    if (mManageAsset.requestID == 0)
    {
        requestEntry.body.assetUpdateRequest().sequenceNumber = 0;
        request->recalculateHashRejectReason();
    }
    const auto hash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = hash;
    return request;
}

UpdateAssetOpFrame::UpdateAssetOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx) :
    ManageAssetOpFrame(op, res, parentTx), mAssetUpdateRequest(mManageAsset.request.createAssetUpdateRequest().updateAsset)
{
}

bool UpdateAssetOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    bool isRequestReferenceCheckNeeded = mManageAsset.requestID == 0;
    if (isRequestReferenceCheckNeeded && requestHelper.exists(getSourceID(), mAssetUpdateRequest.code))
    {
        innerResult().code(ManageAssetResultCode::REQUEST_ALREADY_EXISTS);
        return false;
    }

    auto request = getUpdatedOrCreateReviewableRequest(app, storageHelper);
    if (!request)
    {
        innerResult().code(ManageAssetResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.loadAsset(mAssetUpdateRequest.code, getSourceID());
    if (!assetFrame)
    {
        innerResult().code(ManageAssetResultCode::ASSET_NOT_FOUND);
        return false;
    }

    bool isStats = isSetFlag(mAssetUpdateRequest.policies, AssetPolicy::STATS_QUOTE_ASSET);
    if (isStats)
    {
        auto statsAssetFrame = assetHelper.loadStatsAsset();
        if (statsAssetFrame && mAssetUpdateRequest.code != statsAssetFrame->getCode())
        {
            innerResult().code(ManageAssetResultCode::STATS_ASSET_ALREADY_EXISTS);
            return false;
        }
    }
    bool autoreview = true;
    if (mManageAsset.requestID == 0)
    {
        KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
        uint32_t allTasks = 0;
        if (!keyValueHelper.loadTasks(allTasks, {ManageKeyValueOpFrame::makeAssetUpdateTasksKey()},
                                      mManageAsset.request.createAssetUpdateRequest().allTasks.get()))
        {
            innerResult().code(ManageAssetResultCode::ASSET_UPDATE_TASKS_NOT_FOUND);
            return false;
        }

        request->setTasks(allTasks);
        requestHelper.storeAdd(request->mEntry);
        autoreview = allTasks == 0;
    }
    else
    {

        if (!ensureUpdateRequestValid(request))
        {
            return false;
        }
        updateRequest(request->getRequestEntry());
        request->recalculateHashRejectReason();
        requestHelper.storeChange(request->mEntry);
    }

    bool fulfilled = false;

    if (autoreview)
    {
        auto result =
            ReviewRequestHelper::tryApproveRequestWithResult(mParentTx, app, ledgerManager, storageHelper, request);
        if (result.code() != ReviewRequestResultCode::SUCCESS)
        {
            throw std::runtime_error("Failed to review update asset request");
        }
        fulfilled = result.success().fulfilled;
    }

    innerResult().code(ManageAssetResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = fulfilled;
    return true;
}

bool UpdateAssetOpFrame::doCheckValid(Application& app)
{
    if (!AssetFrame::isAssetCodeValid(mAssetUpdateRequest.code))
    {
        innerResult().code(ManageAssetResultCode::INVALID_CODE);
        return false;
    }

    if (!isValidXDRFlag<AssetPolicy>(mAssetUpdateRequest.policies))
    {
        innerResult().code(ManageAssetResultCode::INVALID_POLICIES);
        return false;
    }

    if (!isValidJson(mAssetUpdateRequest.creatorDetails))
    {
        innerResult().code(ManageAssetResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    return true;
}

string UpdateAssetOpFrame::getAssetCode() const
{
    return mAssetUpdateRequest.code;
}


bool UpdateAssetOpFrame::ensureUpdateRequestValid(ReviewableRequestFrame::pointer request)
{
    if (mManageAsset.request.createAssetUpdateRequest().allTasks)
    {
        innerResult().code(ManageAssetResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }
    return true;
}

void UpdateAssetOpFrame::updateRequest(ReviewableRequestEntry& requestEntry)
{
    requestEntry.body.assetUpdateRequest().code = mManageAsset.request.createAssetUpdateRequest().updateAsset.code;
    requestEntry.body.assetUpdateRequest().creatorDetails = mManageAsset.request.createAssetUpdateRequest().updateAsset.creatorDetails;
    requestEntry.body.assetUpdateRequest().policies = mManageAsset.request.createAssetUpdateRequest().updateAsset.policies;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.body.assetUpdateRequest().sequenceNumber++;
}

}
