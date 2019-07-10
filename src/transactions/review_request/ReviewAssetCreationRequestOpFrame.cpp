#include "util/asio.h"
#include "ReviewAssetCreationRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "main/Application.h"
#include "transactions/managers/BalanceManager.h"

namespace stellar
{

using namespace std;
using xdr::operator==;

bool
ReviewAssetCreationRequestOpFrame::handleApprove(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager, ReviewableRequestFrame::pointer request)
{
    if (request->getRequestType() != ReviewableRequestType::CREATE_ASSET)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected request type. Expected ASSET_CREATE, but got "
                                               << xdr::xdr_traits<ReviewableRequestType>::enum_name(request->getRequestType());
        throw std::invalid_argument("Unexpected request type for review asset creation request");
    }

    auto assetCreationRequest = request->getRequestEntry().body.assetCreationRequest();

    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto isAssetExist = assetHelper.exists(assetCreationRequest.code);
    if (isAssetExist)
    {
        innerResult().code(ReviewRequestResultCode::ASSET_ALREADY_EXISTS);
        return false;
    }


    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    auto assetFrame = AssetFrame::create(assetCreationRequest, request->getRequestor());
    assetHelper.storeAdd(assetFrame->mEntry);

    BalanceManager balanceManager(app, storageHelper);

    if (assetFrame->isPolicySet(AssetPolicy::BASE_ASSET))
    {
        balanceManager.loadOrCreateBalanceForAdmin(assetFrame->getCode());
    }
    else
    {
        balanceManager.loadOrCreateBalance(assetFrame->getOwner(), assetFrame->getCode());
    }

    requestHelper.storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

ReviewAssetCreationRequestOpFrame::ReviewAssetCreationRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx)
    :
    ReviewRequestOpFrame(op, res, parentTx)
{
}

}
