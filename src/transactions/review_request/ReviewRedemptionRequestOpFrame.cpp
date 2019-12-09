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
    BalanceFrame::pointer srcBalanceFrame, dstBalanceFrame;
    if (!ledgerManager.shouldUse(LedgerVersion::MARK_ASSET_AS_DELETED)) {
        srcBalanceFrame = balanceHelper.mustLoadBalance(redemption.sourceBalanceID);
    } else {
        //it is safe to check for balance existence only, as balances are being removed on
        // asset removal
        srcBalanceFrame = balanceHelper.loadBalance(redemption.sourceBalanceID);
        if (!srcBalanceFrame) {
            innerResult().code(ReviewRequestResultCode::SRC_BALANCE_NOT_FOUND);
            return false;
        }
    }

    dstBalanceFrame = balanceHelper.loadBalance(redemption.destination, srcBalanceFrame->getAsset());
    if (!dstBalanceFrame) {
        innerResult().code(ReviewRequestResultCode::DESTINATION_BALANCE_NOT_FOUND);
        return false;
    }


    const BalanceFrame::Result chargeResult = srcBalanceFrame->tryChargeFromLocked(redemption.amount);
    if (chargeResult != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: failed to charge from locked specified amount in request: request"
                << xdr::xdr_to_string(redemption) << "; balance: " << xdr::xdr_to_string(srcBalanceFrame->getBalance());
        throw runtime_error("Unexpected state: failed to charge from unlock specified amount in aml request");
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

    handleTasks(requestHelper, request);
    requestHelper.storeDelete(request->getKey());
    innerResult().success().fulfilled = true;
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
    auto& db = app.getDatabase();
    // create reference to make sure that same alert will not be triggered again
    createReference(storageHelper, request->getRequestor(), request->getReference());
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

}