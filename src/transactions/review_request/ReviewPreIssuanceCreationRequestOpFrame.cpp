// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/asio.h"
#include "ReviewPreIssuanceCreationRequestOpFrame.h"
#include "util/Logging.h"
#include "util/types.h"
#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ReferenceFrame.h"
#include "ledger/AssetHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewPreIssuanceCreationRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper,
                                                       LedgerManager& ledgerManager,
                                                       ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_PRE_ISSUANCE)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected CREATE_PRE_ISSUANCE, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw std::invalid_argument("Unexpected request type for review preIssuance creation request");
    }

    auto preIssuanceCreationRequest = request->getRequestEntry().body.preIssuanceRequest();

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    createReference(storageHelper, request->getRequestor(), request->getReference());

    auto& assetHelper = storageHelper.getAssetHelper();

    if (ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        if (!storageHelper.getAssetHelper().exists(preIssuanceCreationRequest.asset))
        {
            innerResult().code(ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS);
            return false;
        }
    }
    auto asset = assetHelper.loadAsset(preIssuanceCreationRequest.asset);
    if (!asset)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state. Expected asset to exist for pre issuance request. RequestID: "
            << request->getRequestID();
        throw std::runtime_error("Expected asset for pre issuance request to exist");
    }

    if (!asset->tryAddAvailableForIssuance(preIssuanceCreationRequest.amount))
    {
        innerResult().code(ReviewRequestResultCode::MAX_ISSUANCE_AMOUNT_EXCEEDED);
        return false;
    }

    assetHelper.storeChange(asset->mEntry);
    requestHelper.storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewPreIssuanceCreationRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

ReviewPreIssuanceCreationRequestOpFrame::ReviewPreIssuanceCreationRequestOpFrame(
    Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

}
