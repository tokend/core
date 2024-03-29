#include "ReviewAMLAlertRequestOpFrame.h"
#include "util/asio.h"

#include "database/Database.h"
#include "ledger/LedgerDelta.h"
#include "ledger/AssetHelper.h"
#include "ledger/StorageHelper.h"
#include "ledger/BalanceHelper.h"
#include "main/Application.h"
#include "ledger/ReviewableRequestHelper.h"
#include "xdrpp/printer.h"

namespace stellar
{

using namespace std;
using xdr::operator==;


ReviewAMLAlertRequestOpFrame::ReviewAMLAlertRequestOpFrame(Operation const& op,
                                                           OperationResult& res, TransactionFrame& parentTx)
    : ReviewRequestOpFrame(op, res, parentTx)
{
}

bool ReviewAMLAlertRequestOpFrame::handleApprove(Application& app,
                                                 StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                                 const ReviewableRequestFrame::pointer request)
{
    const auto amlAlert = getAmlAlert(request);
    auto& db = app.getDatabase();

    auto& assetHelper = storageHelper.getAssetHelper();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    handleTasks(requestHelper, request);

    if (!request->canBeFulfilled(ledgerManager))
    {
        innerResult().code(ReviewRequestResultCode::SUCCESS);
        innerResult().success().fulfilled = false;
        return true;
    }

    createReference(storageHelper, request->getRequestor(), request->getReference());
    BalanceFrame::pointer balanceFrame;
    if (!ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED))
    {
        balanceFrame = balanceHelper.mustLoadBalance(amlAlert.balanceID);
    }
    else {
        //it is safe to check for balance existense only, as balances are being removed on
        // asset removal
       balanceFrame = balanceHelper.loadBalance(amlAlert.balanceID);
       if (!balanceFrame)
       {
            innerResult().code(ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND);
            return false;
       }
    }
    const BalanceFrame::Result chargeResult = balanceFrame->tryChargeFromLocked(amlAlert.amount);
    if (chargeResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to charge from unlock specified amount in request: request"
            << xdr::xdr_to_string(amlAlert) << "; balance: " << xdr::xdr_to_string(balanceFrame->getBalance());
        throw runtime_error("Unexpected state: failed to charge from unlock specified amount in aml request");
    }

    balanceHelper.storeChange(balanceFrame->mEntry);

    auto assetFrame = assetHelper.mustLoadAsset(balanceFrame->getAsset());
    if (!assetFrame->tryWithdraw(amlAlert.amount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to withdraw from asset for aml alert request: " << request->getRequestID();
        throw runtime_error("Failed to withdraw from asset for aml alert");
    }

    assetHelper.storeChange(assetFrame->mEntry);
    requestHelper.storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    innerResult().success().fulfilled = true;
    return true;
}

bool
ReviewAMLAlertRequestOpFrame::handleReject(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager,
                                           ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

AMLAlertRequest ReviewAMLAlertRequestOpFrame::getAmlAlert(
    ReviewableRequestFrame::pointer request)
{
    auto requestEntry = request->getRequestEntry();
    if (requestEntry.body.type() != ReviewableRequestType::CREATE_AML_ALERT)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Review aml alert: expected aml alert but got "
                                               << xdr::xdr_to_string(requestEntry.body.type());
        throw runtime_error("Expected request to be AML alert");
    }
    return requestEntry.body.amlAlertRequest();
}

bool ReviewAMLAlertRequestOpFrame::handlePermanentReject(Application& app, StorageHelper& storageHelper,
                                                         LedgerManager& ledgerManager,
                                                         const ReviewableRequestFrame::pointer request)
{
    auto& db = app.getDatabase();
    // create reference to make sure that same alert will not be triggered again
    createReference(storageHelper, request->getRequestor(), request->getReference());
    const auto amlAlert = getAmlAlert(request);

    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto balanceFrame = balanceHelper.mustLoadBalance(amlAlert.balanceID);

    const BalanceFrame::Result unlockResult = balanceFrame->unlock(amlAlert.amount);
    if (unlockResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to unlock specified amount in request: request "
            << xdr::xdr_to_string(amlAlert) << "; balance: " << xdr::xdr_to_string(balanceFrame->getBalance())
            << "; result " << unlockResult;
        throw runtime_error("Unexpected state: failed to unlock specified amount in aml request");
    }

    balanceHelper.storeChange(balanceFrame->mEntry);
    storageHelper.getReviewableRequestHelper().storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

}
