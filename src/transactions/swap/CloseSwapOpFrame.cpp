#include "CloseSwapOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/FeeHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/StorageHelper.h"
#include "ledger/SwapHelper.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

CloseSwapOpFrame::CloseSwapOpFrame(const stellar::Operation& op,
                                   OperationResult& res,
                                   TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx)
    , mCloseSwap(mOperation.body.closeSwapOp())
{
}

bool
CloseSwapOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto swap = storageHelper.getSwapHelper().loadSwap(mCloseSwap.swapID);
    if (!swap)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SWAP;
        return false;
    }
    auto swapEntry = swap->getSwapEntry();

    auto destinationBalance = storageHelper.getBalanceHelper().mustLoadBalance(
        swapEntry.destinationBalance);
    auto sourceBalance = storageHelper.getBalanceHelper().mustLoadBalance(
        swapEntry.sourceBalance);

    auto destination = storageHelper.getAccountHelper().mustLoadAccount(
        destinationBalance->getAccountID());
    auto source = storageHelper.getAccountHelper().mustLoadAccount(
        sourceBalance->getAccountID());

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(
        destinationBalance->getAsset());

    AccountRuleResource resource(LedgerEntryType::SWAP);
    resource.swap().assetCode = asset->getCode();
    resource.swap().assetType = asset->getType();
    result.emplace_back(resource, AccountRuleAction::EXCHANGE, source);
    result.emplace_back(resource, AccountRuleAction::EXCHANGE, destination);

    return true;
}

bool
CloseSwapOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto swap = storageHelper.getSwapHelper().loadSwap(mCloseSwap.swapID);
    if (!swap)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::SWAP;
        return false;
    }

    auto swapEntry = swap->getSwapEntry();

    auto destinationBalance = storageHelper.getBalanceHelper().mustLoadBalance(
        swapEntry.destinationBalance);

    auto asset = storageHelper.getAssetHelper().mustLoadAsset(
        destinationBalance->getAsset());

    SignerRuleResource resource(LedgerEntryType::SWAP);
    resource.swap().assetType = asset->getType();
    resource.swap().assetCode = asset->getCode();

    result.emplace_back(resource, SignerRuleAction::EXCHANGE);

    return true;
}

bool
CloseSwapOpFrame::secretValid(SwapFrame::pointer swapFrame)
{
    auto hash = sha256(*mCloseSwap.secret);

    return hash == swapFrame->mEntry.data.swap().secretHash;
}

bool
CloseSwapOpFrame::doApply(Application& app, StorageHelper& sh,
                          LedgerManager& lm)
{
    auto swap = sh.getSwapHelper().mustLoadSwap(mCloseSwap.swapID);

    if (!isAuthorized(sh, lm, app.getAdminID(), swap))
    {
        innerResult().code(CloseSwapResultCode::NOT_AUTHORIZED);
        return false;
    }

    if (!mCloseSwap.secret)
    {
        return cancelSwap(app, sh, lm, swap);
    }

    if (!secretValid(swap))
    {
        innerResult().code(CloseSwapResultCode::INVALID_SECRET);
        return false;
    }

    return processSwap(app, sh, lm, swap);
}

bool
CloseSwapOpFrame::doCheckValid(Application& app)
{
    return true;
}

bool
CloseSwapOpFrame::cancelSwap(Application& app, StorageHelper& sh,
                             LedgerManager& lm, SwapFrame::pointer swap)
{
    auto& balanceHelper = sh.getBalanceHelper();
    auto swapEntry = swap->getSwapEntry();

    auto sourceBalance = balanceHelper.mustLoadBalance(swapEntry.sourceBalance);

    auto totalAmount = swapEntry.amount + swapEntry.fee;

    auto result = sourceBalance->unlock(totalAmount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to unlock total amount on swap "
               "cancel, swap_id: "
            << swapEntry.id;
        throw std::runtime_error(
            "Unexpected state: failed to unlock total amount on swap cancel");
    }

    auto& swapHelper = sh.getSwapHelper();

    balanceHelper.storeChange(sourceBalance->mEntry);
    swapHelper.storeDelete(swap->getKey());

    innerResult().code(CloseSwapResultCode::SUCCESS);
    innerResult().success().effect = CloseSwapEffect::CANCELLED;
    return true;
}

bool
CloseSwapOpFrame::processSwap(Application& app, StorageHelper& sh,
                              LedgerManager& lm, SwapFrame::pointer swap)
{
    auto swapEntry = swap->getSwapEntry();
    if (swapEntry.lockTime <= lm.getCloseTime())
    {
        innerResult().code(CloseSwapResultCode::SWAP_EXPIRED);
        return false;
    }

    auto& db = sh.getDatabase();
    auto& delta = sh.mustGetLedgerDelta();
    AccountManager accountManager(app, db, delta, lm);

    auto& balanceHelper = sh.getBalanceHelper();
    auto sourceBalance = balanceHelper.mustLoadBalance(swapEntry.sourceBalance);

    accountManager.transferFee(sourceBalance->getAsset(), swapEntry.fee);

    auto totalAmount = swapEntry.amount + swapEntry.fee;

    auto result = sourceBalance->tryChargeFromLocked(totalAmount);
    if (result != BalanceFrame::Result::SUCCESS)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to charge total amount from source "
               "balance on swap close, swap_id: "
            << swapEntry.id;
        throw std::runtime_error(
            "Unexpected state: failed to charge total amount from source "
            "balance on swap close");
    }
    balanceHelper.storeChange(sourceBalance->mEntry);

    auto destinationBalance =
        balanceHelper.mustLoadBalance(swapEntry.destinationBalance);

    result = destinationBalance->tryFundAccount(swapEntry.amount);
    switch (result)
    {
    case BalanceFrame::Result::SUCCESS:
        break;
    case BalanceFrame::Result::LINE_FULL:
        innerResult().code(CloseSwapResultCode::LINE_FULL);
        return false;
    default:
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to fund destination on swap close, "
               "swap_id: "
            << swapEntry.id;
        throw std::runtime_error(
            "Unexpected state: failed to fund destination on swap close ");
    }

    balanceHelper.storeChange(destinationBalance->mEntry);
    auto& swapHelper = sh.getSwapHelper();
    swapHelper.storeDelete(swap->getKey());

    innerResult().code(CloseSwapResultCode::SUCCESS);
    innerResult().success().effect = CloseSwapEffect::CLOSED;
    return true;
}

bool
CloseSwapOpFrame::isAuthorized(StorageHelper& sh, LedgerManager& lm,
                               AccountID adminID, SwapFrame::pointer swap)
{
    auto swapEntry = swap->getSwapEntry();
    auto destinationBalance =
        sh.getBalanceHelper().mustLoadBalance(swapEntry.destinationBalance);
    auto sourceBalance =
        sh.getBalanceHelper().mustLoadBalance(swapEntry.sourceBalance);

    auto swapSource = sourceBalance->getAccountID();
    auto swapDestination = destinationBalance->getAccountID();

    if (getSourceID() == swapDestination && mCloseSwap.secret)
    {
        return true;
    }
    if (mCloseSwap.secret)
    {
        return false;
    }

    if (getSourceID() == swapSource && swapEntry.lockTime <= lm.getCloseTime())
    {
        return true;
    }

    if (getSourceID() == adminID && swapEntry.lockTime <= lm.getCloseTime())
    {
        return true;
    }

    return false;
}
}
