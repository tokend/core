// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <xdrpp/printer.h>
#include <transactions/review_request/ReviewIssuanceCreationRequestOpFrame.h>
#include <main/Application.h>
#include <transactions/review_request/ReviewRequestHelper.h>
#include "CreateAssetOpFrame.h"
#include "transactions/ManageKeyValueOpFrame.h"
#include "ledger/KeyValueHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

CreateAssetOpFrame::CreateAssetOpFrame(Operation const& op,
                                       OperationResult& res, TransactionFrame& parentTx)
    : ManageAssetOpFrame(op, res, parentTx), mAssetCreationRequest(mManageAsset.request.createAssetCreationRequest().createAsset)
{
}

bool
CreateAssetOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                              std::vector<OperationCondition>& result) const
{
    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = mAssetCreationRequest.type;
    resource.asset().assetCode = mAssetCreationRequest.code;
    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);

    if (mManageAsset.request.createAssetCreationRequest().allTasks)
    {
        result.emplace_back(resource, AccountRuleAction::CREATE_WITH_TASKS, mSourceAccount);
        return true;
    }

    result.emplace_back(resource, AccountRuleAction::CREATE, mSourceAccount);
    return true;
}

bool
CreateAssetOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                             std::vector<SignerRequirement>& result) const
{
    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = mAssetCreationRequest.type;
    resource.asset().assetCode = mAssetCreationRequest.code;
    result.emplace_back(resource, SignerRuleAction::CREATE);

    return true;
}

ReviewableRequestFrame::pointer
CreateAssetOpFrame::getUpdatedOrCreateReviewableRequest(Application& app, StorageHelper& storageHelper) const
{
    ReviewableRequestFrame::pointer request =
        getOrCreateReviewableRequest(app, storageHelper, ReviewableRequestType::CREATE_ASSET);
    if (!request)
    {
        return nullptr;
    }

    ReviewableRequestEntry& requestEntry = request->getRequestEntry();
    requestEntry.body.type(ReviewableRequestType::CREATE_ASSET);
    requestEntry.body.assetCreationRequest() = mAssetCreationRequest;
    if (mManageAsset.requestID == 0)
    {
        requestEntry.body.assetCreationRequest().sequenceNumber = 0;
        request->recalculateHashRejectReason();
    }
    const auto hash = ReviewableRequestFrame::calculateHash(requestEntry.body);
    requestEntry.hash = hash;
    return request;
}

bool CreateAssetOpFrame::doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager)
{

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    if (mManageAsset.requestID == 0 && requestHelper.exists(getSourceID(), mAssetCreationRequest.code))
    {
        innerResult().code(ManageAssetResultCode::REQUEST_ALREADY_EXISTS);
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();

    bool isAssetExist = assetHelper.exists(mAssetCreationRequest.code);
    if (isAssetExist)
    {
        innerResult().code(ManageAssetResultCode::ASSET_ALREADY_EXISTS);
        return false;
    }

    bool isStats = isSetFlag(mAssetCreationRequest.policies, AssetPolicy::STATS_QUOTE_ASSET);
    if (isStats && !!assetHelper.loadStatsAsset())
    {
        innerResult().code(ManageAssetResultCode::STATS_ASSET_ALREADY_EXISTS);
        return false;
    }

    auto request = getUpdatedOrCreateReviewableRequest(app, storageHelper);
    if (!request)
    {
        innerResult().code(ManageAssetResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    bool autoreview = true;
    if (mManageAsset.requestID == 0)
    {
        KeyValueHelper& keyValueHelper = storageHelper.getKeyValueHelper();
        uint32_t allTasks = 0;
        if (!keyValueHelper.loadTasks(allTasks, {ManageKeyValueOpFrame::makeAssetCreateTasksKey()},
                                      mManageAsset.request.createAssetCreationRequest().allTasks.get()))
        {
            innerResult().code(ManageAssetResultCode::ASSET_CREATE_TASKS_NOT_FOUND);
            return false;
        }
        request->setTasks(allTasks);
        requestHelper.storeAdd(request->mEntry);
        autoreview = allTasks == 0;
    }
    else
    {
        if (ledgerManager.shouldUse(LedgerVersion::FIX_AUTOREVIEW))
        {
            autoreview = false;
        }

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
            throw std::runtime_error("Failed to review create asset request");
        }
        fulfilled = result.success().fulfilled;
    }

    innerResult().code(ManageAssetResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    innerResult().success().fulfilled = fulfilled;
    return true;
}

bool CreateAssetOpFrame::doCheckValid(Application& app)
{
    if (!AssetFrame::isAssetCodeValid(mAssetCreationRequest.code))
    {
        innerResult().code(ManageAssetResultCode::INVALID_CODE);
        return false;
    }

    if (!isValidXDRFlag<AssetPolicy>(mAssetCreationRequest.policies))
    {
        innerResult().code(ManageAssetResultCode::INVALID_POLICIES);
        return false;
    }

    if (mAssetCreationRequest.maxIssuanceAmount < mAssetCreationRequest.initialPreissuedAmount)
    {
        innerResult().code(ManageAssetResultCode::INITIAL_PREISSUED_EXCEEDS_MAX_ISSUANCE);
        return false;
    }

    if (!isValidJson(mAssetCreationRequest.creatorDetails))
    {
        innerResult().code(ManageAssetResultCode::INVALID_CREATOR_DETAILS);
        return false;
    }

    if (mAssetCreationRequest.trailingDigitsCount > AssetFrame::kMaximumTrailingDigits)
    {
        innerResult().code(ManageAssetResultCode::INVALID_TRAILING_DIGITS_COUNT);
        return false;
    }

    const uint64 precision = AssetFrame::getMinimumAmountFromTrailingDigits(
        mAssetCreationRequest.trailingDigitsCount);
    if (mAssetCreationRequest.initialPreissuedAmount % precision != 0)
    {
        innerResult().code(ManageAssetResultCode::INVALID_PREISSUED_AMOUNT_PRECISION);
        return false;
    }
    if (mAssetCreationRequest.maxIssuanceAmount % precision != 0)
    {
        innerResult().code(ManageAssetResultCode::INVALID_MAX_ISSUANCE_AMOUNT_PRECISION);
        return false;
    }

    return true;
}

string CreateAssetOpFrame::getAssetCode() const
{
    return mAssetCreationRequest.code;
}

bool CreateAssetOpFrame::ensureUpdateRequestValid(ReviewableRequestFrame::pointer request)
{
    if (mManageAsset.request.createAssetCreationRequest().allTasks)
    {
        innerResult().code(ManageAssetResultCode::NOT_ALLOWED_TO_SET_TASKS_ON_UPDATE);
        return false;
    }
    return true;
}

void CreateAssetOpFrame::updateRequest(ReviewableRequestEntry& requestEntry)
{
    requestEntry.body.assetCreationRequest().code = mManageAsset.request.createAssetCreationRequest().createAsset.code;
    requestEntry.body.assetCreationRequest().creatorDetails = mManageAsset.request.createAssetCreationRequest().createAsset.creatorDetails;
    requestEntry.body.assetCreationRequest().policies = mManageAsset.request.createAssetCreationRequest().createAsset.policies;
    requestEntry.tasks.pendingTasks = requestEntry.tasks.allTasks;
    requestEntry.body.assetCreationRequest().sequenceNumber++;
}
}
