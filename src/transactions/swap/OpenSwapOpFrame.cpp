#include "OpenSwapOpFrame.h"
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

OpenSwapOpFrame::OpenSwapOpFrame(const stellar::Operation& op,
                                 OperationResult& res,
                                 TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mOpenSwap(mOperation.body.openSwapOp())
{
}

bool
OpenSwapOpFrame::tryGetOperationConditions(
    StorageHelper& storageHelper, std::vector<OperationCondition>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame =
        balanceHelper.loadBalance(mOpenSwap.sourceBalance);
    if (!senderBalanceFrame)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::BALANCE;
        return false;
    }

    auto destinationAccountFrame = tryLoadDestinationAccount(storageHelper);
    if (!destinationAccountFrame)
    {
        return false;
    }

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(senderBalanceFrame->getAsset());

    AccountRuleResource resource(LedgerEntryType::SWAP);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();

    result.emplace_back(resource, AccountRuleAction::EXCHANGE, mSourceAccount);
    result.emplace_back(resource, AccountRuleAction::EXCHANGE,
                        destinationAccountFrame);

    return true;
}

bool
OpenSwapOpFrame::tryGetSignerRequirements(
    StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.mustLoadBalance(mOpenSwap.sourceBalance);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(balanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::SWAP);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();

    result.emplace_back(resource, SignerRuleAction::EXCHANGE);

    return true;
}

AccountFrame::pointer
OpenSwapOpFrame::tryLoadDestinationAccount(StorageHelper& storageHelper) const
{
    AccountID accountID;
    switch (mOpenSwap.destination.type())
    {
    case PaymentDestinationType::ACCOUNT:
    {
        accountID = mOpenSwap.destination.accountID();
        break;
    }
    case PaymentDestinationType::BALANCE:
    {
        auto destinationBalanceFrame =
            storageHelper.getBalanceHelper().loadBalance(
                mOpenSwap.destination.balanceID());
        if (!destinationBalanceFrame)
        {
            mResult.code(OperationResultCode::opNO_ENTRY);
            mResult.entryType() = LedgerEntryType::BALANCE;
            return nullptr;
        }

        accountID = destinationBalanceFrame->getAccountID();
        break;
    }
    default:
        throw std::runtime_error(
            "Unexpected destination type on open swap when loading account");
    }

    auto account = storageHelper.getAccountHelper().loadAccount(accountID);
    if (!account)
    {
        mResult.code(OperationResultCode::opNO_ENTRY);
        mResult.entryType() = LedgerEntryType::ACCOUNT;
        return nullptr;
    }

    return account;
}

bool
OpenSwapOpFrame::checkFee(AccountManager& accountManager,
                          AccountFrame::pointer payer,
                          BalanceFrame::pointer chargeFrom, Fee expectedFee,
                          Fee actualFee, AccountID const& commissionID,
                          StorageHelper& sh)
{
    if (actualFee.fixed == 0 && actualFee.percent == 0)
    {
        return true;
    }

    if (expectedFee.fixed < actualFee.fixed ||
        expectedFee.percent < actualFee.percent)
    {
        innerResult().code(OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT);
        return false;
    }

    uint64_t totalFee;
    if (!safeSum(actualFee.fixed, actualFee.percent, totalFee))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to calculate total sum of fees to be "
               "charged - overflow";
        throw std::runtime_error("Total sum of fees to be charged overflows");
    }

    auto& db = sh.getDatabase();
    auto& delta = sh.mustGetLedgerDelta();

    // load commission balance
    auto commissionBalance = AccountManager::loadOrCreateBalanceFrameForAsset(
        commissionID, chargeFrom->getAsset(), db, delta);
    if (!commissionBalance)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state. Expected commission balance to exist";
        throw std::runtime_error(
            "Unexpected state. Expected commission balance to exist");
    }

    return true;
}

BalanceFrame::pointer
OpenSwapOpFrame::tryLoadDestinationBalance(AssetCode asset,
                                           StorageHelper& storageHelper)
{
    switch (mOpenSwap.destination.type())
    {
    case PaymentDestinationType::BALANCE:
    {
        auto dest = storageHelper.getBalanceHelper().loadBalance(
            mOpenSwap.destination.balanceID());
        if (!dest)
        {
            innerResult().code(
                OpenSwapResultCode::DESTINATION_BALANCE_NOT_FOUND);
            return nullptr;
        }

        if (dest->getAsset() != asset)
        {
            innerResult().code(OpenSwapResultCode::BALANCE_ASSETS_MISMATCHED);
            return nullptr;
        }

        return dest;
    }
    case PaymentDestinationType::ACCOUNT:
    {
        if (!storageHelper.getAccountHelper().exists(
                mOpenSwap.destination.accountID()))
        {
            innerResult().code(
                OpenSwapResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
            return nullptr;
        }

        auto dest = AccountManager::loadOrCreateBalanceFrameForAsset(
            mOpenSwap.destination.accountID(), asset,
            storageHelper.getDatabase(), storageHelper.mustGetLedgerDelta());
        if (!dest)
        {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                << "Unexpected state: expected destination balance to exist, "
                   "account id: "
                << PubKeyUtils::toStrKey(mOpenSwap.destination.accountID());
            throw runtime_error(
                "Unexpected state: expected destination balance to exist");
        }

        return dest;
    }
    default:
        throw std::runtime_error("Unexpected destination type on openSwap v2");
    }
}

bool
OpenSwapOpFrame::isSwapAllowed(StorageHelper& sh, BalanceFrame::pointer from,
                               BalanceFrame::pointer to)
{
    if (from->getAsset() != to->getAsset())
    {
        innerResult().code(OpenSwapResultCode::BALANCE_ASSETS_MISMATCHED);
        return false;
    }

    // is transfer allowed by asset policy
    auto asset = sh.getAssetHelper().mustLoadAsset(from->getAsset());
    if (!asset->isPolicySet(AssetPolicy::SWAPPABLE))
    {
        innerResult().code(OpenSwapResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    return true;
}

Fee
OpenSwapOpFrame::getActualFee(AccountFrame::pointer accountFrame,
                              AssetCode const& transferAsset, uint64_t amount,
                              PaymentFeeType feeType, StorageHelper& sh,
                              LedgerManager& lm)
{
    Fee actualFee;
    actualFee.percent = 0;
    actualFee.fixed = 0;

    auto& db = sh.getDatabase();
    auto feeFrame = FeeHelper::Instance()->loadForAccount(
        FeeType::SWAP_FEE, transferAsset, static_cast<int64_t>(feeType),
        accountFrame, amount, db);
    // if we do not have any fee frame - any fee is valid
    if (!feeFrame)
    {
        return actualFee;
    }

    const uint64_t feeMinimumAmount =
        sh.getAssetHelper().mustLoadAsset(transferAsset)->getMinimumAmount();
    if (!feeFrame->calculatePercentFee(amount, actualFee.percent, ROUND_UP,
                                       feeMinimumAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate actual swap fee - overflow, asset "
               "code: "
            << feeFrame->getFeeAsset();
        throw std::runtime_error(
            "Failed to calculate actual swap fee - overflow");
    }

    actualFee.fixed = static_cast<uint64>(feeFrame->getFee().fixedFee);
    return actualFee;
}

bool
OpenSwapOpFrame::isSendToSelf(BalanceID sourceBalanceID,
                              BalanceID destBalanceID)
{
    return sourceBalanceID == destBalanceID;
}

bool
OpenSwapOpFrame::doApply(Application& app, StorageHelper& sh, LedgerManager& lm)
{
    Database& db = sh.getDatabase();
    auto& balanceHelper = sh.getBalanceHelper();
    auto& accountHelper = sh.getAccountHelper();
    auto sourceBalance =
        balanceHelper.loadBalance(getSourceID(), mOpenSwap.sourceBalance);
    if (!sourceBalance)
    {
        innerResult().code(OpenSwapResultCode::SRC_BALANCE_NOT_FOUND);
        return false;
    }

    auto destBalance = tryLoadDestinationBalance(sourceBalance->getAsset(), sh);
    if (!destBalance)
    {
        return false;
    }

    BalanceID destBalanceID = destBalance->getBalanceID();

    if (isSendToSelf(mOpenSwap.sourceBalance, destBalanceID))
    {
        innerResult().code(OpenSwapResultCode::MALFORMED);
        return false;
    }

    if (!isSwapAllowed(sh, sourceBalance, destBalance))
    {
        return false;
    }

    auto& delta = sh.mustGetLedgerDelta();

    AccountManager accountManager(app, db, delta, app.getLedgerManager());

    auto sourceFee =
        getActualFee(mSourceAccount, sourceBalance->getAsset(),
                     mOpenSwap.amount, PaymentFeeType::OUTGOING, sh, lm);

    if (!checkFee(accountManager, mSourceAccount, sourceBalance,
                  mOpenSwap.feeData.sourceFee, sourceFee, app.getAdminID(), sh))
    {
        innerResult().code(OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT);
        return false;
    }
    auto destAccount =
        accountHelper.mustLoadAccount(destBalance->getAccountID());
    auto destFee =
        getActualFee(destAccount, destBalance->getAsset(), mOpenSwap.amount,
                     PaymentFeeType::INCOMING, sh, lm);

    if (!checkFee(accountManager, mSourceAccount, sourceBalance,
                  mOpenSwap.feeData.sourceFee, sourceFee, app.getAdminID(), sh))
    {
        innerResult().code(OpenSwapResultCode::INSUFFICIENT_FEE_AMOUNT);
        return false;
    }

    // Fee was checked, we can be sure that no overflow can occur
    auto destinationTotalFee = destFee.percent + destFee.fixed;
    auto sourceTotalFee = sourceFee.percent + sourceFee.fixed;

    auto amount = mOpenSwap.feeData.sourcePaysForDest
                      ? mOpenSwap.amount
                      : mOpenSwap.amount - destinationTotalFee;

    uint64_t totalFee;
    if (!safeSum(sourceTotalFee, destinationTotalFee, totalFee))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate total fee - overflow";
        throw std::runtime_error("Failed to calculate total fee - overflow");
    }
    uint64_t totalAmount ;
    if (!safeSum(totalFee, amount, totalAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Failed to calculate total amount - overflow";
        throw std::runtime_error("Failed to calculate total amount - overflow");
    }

    if (!tryLock(sh, sourceBalance, totalAmount))
    {
        innerResult().code(OpenSwapResultCode::UNDERFUNDED);
        return false;
    }


    uint64 swapID = delta.getHeaderFrame().generateID(LedgerEntryType::SWAP);

    LedgerEntry entry;
    entry.data.type(LedgerEntryType::SWAP);
    SwapEntry swapEntry;
    swapEntry.swapID = swapID;
    swapEntry.secretHash = mOpenSwap.secretHash;
    swapEntry.sourceBalance = mOpenSwap.sourceBalance;
    swapEntry.destinationBalance = destBalance->getBalanceID();
    swapEntry.amount = amount;
    swapEntry.createdAt = lm.getCloseTime();
    swapEntry.lockTime = mOpenSwap.lockTime;
    swapEntry.fee = totalFee;
    entry.data.swap() = swapEntry;

    sh.getSwapHelper().storeAdd(entry);

    innerResult().code(OpenSwapResultCode::SUCCESS);
    innerResult().success().swapID = swapID;
    innerResult().success().destinationBalance = destBalance->getBalanceID();
    innerResult().success().destination = destAccount->getID();
    innerResult().success().actualDestinationFee = destFee;
    innerResult().success().actualSourceFee = sourceFee;
    return true;
}

bool
OpenSwapOpFrame::isDestinationFeeValid()
{
    uint64_t totalDestinationFee;
    if (!safeSum(mOpenSwap.feeData.destinationFee.fixed,
                 mOpenSwap.feeData.destinationFee.percent, totalDestinationFee))
    {
        innerResult().code(OpenSwapResultCode::INVALID_DESTINATION_FEE);
        return false;
    }

    if (mOpenSwap.feeData.sourcePaysForDest)
        return true;

    if (mOpenSwap.amount < totalDestinationFee)
    {
        innerResult().code(OpenSwapResultCode::AMOUNT_IS_LESS_THAN_DEST_FEE);
        return false;
    }

    return true;
}

bool
OpenSwapOpFrame::tryLock(StorageHelper& sh,
                         BalanceFrame::pointer balance,
                         uint64_t amount)
{
    auto result = balance->tryLock(amount);
    return result == BalanceFrame::Result::SUCCESS;
}

bool
OpenSwapOpFrame::doCheckValid(Application& app)
{
    if (!isValidJson(mOpenSwap.details))
    {
        innerResult().code(OpenSwapResultCode::INVALID_DETAILS);
        return false;
    }

    if (!isDestinationFeeValid())
    {
        return false;
    }

    if (mOpenSwap.destination.type() != PaymentDestinationType::BALANCE)
    {
        return true;
    }

    if (mOpenSwap.sourceBalance == mOpenSwap.destination.balanceID())
    {
        innerResult().code(OpenSwapResultCode::MALFORMED);
        return false;
    }

    return true;
}
}
