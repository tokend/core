#include "ReviewRedemptionRequestOpFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/ReviewableRequestHelper.h"
#include "ledger/BalanceHelper.h"
#include "xdrpp/printer.h"
#include "database/Database.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

ReviewRedemptionRequestOpFrame::ReviewRedemptionRequestOpFrame(const Operation &op,
                                                               OperationResult &res, TransactionFrame &parentTx)
   : ReviewRequestOpFrame(op, res, parentTx) {}


bool ReviewRedemptionRequestOpFrame::handleApprove(Application &app, StorageHelper &storageHelper,
                                                   LedgerManager &ledgerManager,
                                                   ReviewableRequestFrame::pointer request)
{
    const auto redemption = getRedemption(request);

    auto& requestHelper = storageHelper.getReviewableRequestHelper();

    auto& balanceHelper = storageHelper.getBalanceHelper();
    createReference(storageHelper, request->getRequestor(), request->getReference());

    auto srcBalanceFrame = balanceHelper.loadBalance(redemption.sourceBalanceID);
    if (!srcBalanceFrame) {
        innerResult().code(ReviewRequestResultCode::SRC_BALANCE_NOT_FOUND);
        return false;
    }

    auto dstBalanceFrame = balanceHelper.loadBalance(redemption.destination, srcBalanceFrame->getAsset());
    if (!dstBalanceFrame) {
        innerResult().code(ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND);
        return false;
    }

    handleTasks(requestHelper, request);
    if (!request->canBeFulfilled(ledgerManager)) {
        CLOG(WARNING, Logging::OPERATION_LOGGER)
                << "Unexpected state: pending tasks are not zero: request: "
                << xdr::xdr_to_string(redemption) <<  "; tasks: " << request->getPendingTasks();

        return true;
    }

    const BalanceFrame::Result chargeResult = srcBalanceFrame->tryChargeFromLocked(redemption.amount);
    if (chargeResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge from locked specified amount in request: request"
                << xdr::xdr_to_string(redemption) << "; balance: " << xdr::xdr_to_string(srcBalanceFrame->getBalance());
        throw runtime_error("Unexpected state: failed to charge from unlock specified amount in redemption request");
    }
    balanceHelper.storeChange(srcBalanceFrame->mEntry);

    const BalanceFrame::Result fundResult = dstBalanceFrame->tryFundAccount(redemption.amount);
    if (fundResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to fund balance by specified amount in request: request"
                << xdr::xdr_to_string(redemption) << "; balance: " << xdr::xdr_to_string(srcBalanceFrame->getBalance());
        throw runtime_error("Unexpected state: failed to charge from unlock specified amount in redemption request");
    }
    balanceHelper.storeChange(dstBalanceFrame->mEntry);

    requestHelper.storeDelete(request->getKey());
    innerResult().success().fulfilled = true;
    innerResult().success().typeExt.requestType(ReviewableRequestType::PERFORM_REDEMPTION);
    innerResult().success().typeExt.createRedemptionResult().redemptionResponse().requestID = request->getRequestID();
    innerResult().success().typeExt.createRedemptionResult().redemptionResponse().asset = srcBalanceFrame->getAsset();
    innerResult().success().typeExt.createRedemptionResult().redemptionResponse().destinationBalanceID = dstBalanceFrame->getBalanceID();

    return true;
}

bool ReviewRedemptionRequestOpFrame::handleReject(stellar::Application &app, stellar::StorageHelper &storageHelper,
                                                  stellar::LedgerManager &ledgerManager,
                                                  stellar::ReviewableRequestFrame::pointer request)
{
    innerResult().code(ReviewRequestResultCode::REJECT_NOT_ALLOWED);
    return false;
}

bool ReviewRedemptionRequestOpFrame::handlePermanentReject(stellar::Application &app,
                                                           stellar::StorageHelper &storageHelper,
                                                           stellar::LedgerManager &ledgerManager,
                                                           stellar::ReviewableRequestFrame::pointer request)
{
    const auto redemption = getRedemption(request);

    auto& balanceHelper = storageHelper.getBalanceHelper();

    auto balanceFrame = balanceHelper.mustLoadBalance(redemption.sourceBalanceID);

    const BalanceFrame::Result unlockResult = balanceFrame->unlock(redemption.amount);
    if (unlockResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to unlock specified amount in request: request "
                << xdr::xdr_to_string(redemption) << "; balance: " << xdr::xdr_to_string(balanceFrame->getBalance())
                << "; result " << unlockResult;
        throw runtime_error("Unexpected state: failed to unlock specified amount in redemption request");
    }

    balanceHelper.storeChange(balanceFrame->mEntry);
    storageHelper.getReviewableRequestHelper().storeDelete(request->getKey());
    innerResult().code(ReviewRequestResultCode::SUCCESS);
    return true;
}

RedemptionRequest
ReviewRedemptionRequestOpFrame::getRedemption(stellar::ReviewableRequestFrame::pointer request)
{
    auto requestEntry = request->getRequestEntry();
    if (requestEntry.body.type() != ReviewableRequestType::PERFORM_REDEMPTION)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Review redemption: expected redemption but got "
                                               << xdr::xdr_to_string(requestEntry.body.type());
        throw runtime_error("Expected request to be redemption");
    }
    return requestEntry.body.redemptionRequest();
}

}