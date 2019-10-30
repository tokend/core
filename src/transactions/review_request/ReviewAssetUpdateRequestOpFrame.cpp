#include "ReviewAssetUpdateRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/AssetFrame.h"
#include "main/Application.h"
#include "lib/util/format.h"
#include "transactions/managers/BalanceManager.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewAssetUpdateRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::UPDATE_ASSET)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected ASSET_UPDATE, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw std::invalid_argument("Unexpected request type for review asset update request");
    }

    auto assetUpdateRequest = request->getRequestEntry().body.assetUpdateRequest();

    auto& assetHelper = storageHelper.getAssetHelper();

    auto assetFrame = assetHelper.loadActiveAsset(assetUpdateRequest.code);
    if (!assetFrame)
    {
        innerResult().code(ReviewRequestResultCode::ASSET_DOES_NOT_EXISTS);
        return false;
    }

    if (!(assetFrame->getOwner() == request->getRequestor()))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Received approval for update request not initiated by owner of asset." <<
            "request id: " << request->getRequestID();
        throw std::runtime_error("Received approval for update request not initiated by owner of asset.");
    }

    auto& requestHelper = storageHelper.getReviewableRequestHelper();
    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    bool wasBase = assetFrame->isPolicySet(AssetPolicy::BASE_ASSET);

    AssetEntry& assetEntry = assetFrame->getAsset();
    assetEntry.details = assetUpdateRequest.creatorDetails;
    assetEntry.policies = assetUpdateRequest.policies;

    assetHelper.storeChange(assetFrame->mEntry);
    bool isBase = assetFrame->isPolicySet(AssetPolicy::BASE_ASSET);

    BalanceManager balanceManager(app, storageHelper);
    if (!wasBase && isBase)
    {
        balanceManager.loadOrCreateBalanceForAdmin(assetFrame->getCode());

    }

    requestHelper.storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

ReviewAssetUpdateRequestOpFrame::ReviewAssetUpdateRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    :
    ReviewRequestOpFrame(op, res, parentTx)
{
}

}
