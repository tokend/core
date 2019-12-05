// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "CancelAssetRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestHelper.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

CancelAssetRequestOpFrame::CancelAssetRequestOpFrame(Operation const& op,
                                                     OperationResult& res,
                                                     TransactionFrame& parentTx)
    : ManageAssetOpFrame(op, res, parentTx)
{
}

bool
CancelAssetRequestOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                                     std::vector<OperationCondition>& result) const
{
    // only request creator can cancel it
    return true;
}

bool
CancelAssetRequestOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                                    std::vector<stellar::SignerRequirement>& result) const
{
    auto request = storageHelper.getReviewableRequestHelper().loadRequest(mManageAsset.requestID);
    if (!request || ((request->getType() != ReviewableRequestType::CREATE_ASSET) &&
                     (request->getType() != ReviewableRequestType::UPDATE_ASSET)))
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::REVIEWABLE_REQUEST;
        return false;
    }

    SignerRuleResource resource(LedgerEntryType::ASSET);

    switch (request->getType())
    {
        case ReviewableRequestType::CREATE_ASSET:
        {
            auto createData = request->getRequestEntry().body.assetCreationRequest();
            resource.asset().assetType = createData.type;
            resource.asset().assetCode = createData.code;
            break;
        }
        case ReviewableRequestType::UPDATE_ASSET:
        {
            auto updateData = request->getRequestEntry().body.assetUpdateRequest();
            resource.asset().assetCode = updateData.code;
            auto asset = storageHelper.getAssetHelper().mustLoadAsset(updateData.code);
            resource.asset().assetType = asset->getType();
            break;
        }
        default:
            throw std::runtime_error("Unexpected request type");
    }

    result.emplace_back(resource, SignerRuleAction::CANCEL);

    return true;
}

bool
CancelAssetRequestOpFrame::doApply(Application& app,
                                   StorageHelper& storageHelper, LedgerManager& ledgerManager)
{
    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    auto request = requestHelper.loadRequest(mManageAsset.requestID, getSourceID());
    if (!request)
    {
        innerResult().code(ManageAssetResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    auto requestType = request->getRequestEntry().body.type();
    if (requestType != ReviewableRequestType::CREATE_ASSET && requestType != ReviewableRequestType::UPDATE_ASSET)
    {
        innerResult().code(ManageAssetResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    requestHelper.storeDelete(request->getKey());

    innerResult().code(ManageAssetResultCode::SUCCESS);
    innerResult().success().requestID = request->getRequestID();
    return true;
}

bool CancelAssetRequestOpFrame::doCheckValid(Application& app)
{
    if (mManageAsset.requestID == 0)
    {
        innerResult().code(ManageAssetResultCode::REQUEST_NOT_FOUND);
        return false;
    }

    return true;
}

string CancelAssetRequestOpFrame::getAssetCode() const
{
    throw runtime_error("Unexpected method call. No asset code is required for asset request cancelation.");
}
}
