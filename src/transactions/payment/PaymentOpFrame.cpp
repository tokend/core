#include "PaymentOpFrame.h"
#include "ledger/AccountHelper.h"
#include "ledger/AssetHelper.h"
#include "ledger/BalanceHelper.h"
#include "ledger/AssetPairHelper.h"
#include "ledger/BalanceFrame.h"
#include "ledger/BalanceHelper.h"
#include "ledger/FeeHelper.h"
#include "ledger/LedgerDelta.h"
#include "ledger/LedgerHeaderFrame.h"
#include "ledger/ReferenceHelper.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

PaymentOpFrame::PaymentOpFrame(const stellar::Operation& op, OperationResult& res,
                               TransactionFrame& parentTx)
    : OperationFrame(op, res, parentTx), mPayment(mOperation.body.paymentOp())
{
}

bool
PaymentOpFrame::tryGetOperationConditions(StorageHelper& storageHelper,
                                          std::vector<OperationCondition>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto senderBalanceFrame = balanceHelper.loadBalance(mPayment.sourceBalanceID);
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

    AccountRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();

    result.emplace_back(resource, AccountRuleAction::SEND, mSourceAccount);
    result.emplace_back(resource, AccountRuleAction::RECEIVE_PAYMENT, destinationAccountFrame);

    return true;
}

bool
PaymentOpFrame::tryGetSignerRequirements(StorageHelper& storageHelper,
                                         std::vector<SignerRequirement>& result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(balanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();

    result.emplace_back(resource, SignerRuleAction::SEND);

    return true;
}

AccountFrame::pointer
PaymentOpFrame::tryLoadDestinationAccount(StorageHelper& storageHelper) const
{
    AccountID accountID;
    switch (mPayment.destination.type())
    {
        case PaymentDestinationType::ACCOUNT:
        {
            accountID = mPayment.destination.accountID();
            break;
        }
        case PaymentDestinationType::BALANCE:
        {
            auto destinationBalanceFrame = storageHelper.getBalanceHelper().loadBalance(mPayment.destination.balanceID());
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
            throw std::runtime_error("Unexpected destination type on payment when load account");
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
PaymentOpFrame::processTransfer(BalanceManager& balanceManager, AccountFrame::pointer payer,
                                BalanceFrame::pointer from, BalanceFrame::pointer to,
                                uint64_t amount, uint64_t& universalAmount, LedgerManager& lm) {
    auto transferResult = balanceManager.transfer(payer, from, to, amount);
    if (transferResult != BalanceManager::Result::SUCCESS) {
        setErrorCode(transferResult);
        return false;
    }

    if (!lm.shouldUse(LedgerVersion::FIX_PAYMENT_STATS)) {
        if (!safeSum(universalAmount, balanceManager.getUniversalAmount(), universalAmount)) {
            innerResult().code(PaymentResultCode::STATS_OVERFLOW);
            return false;
        }
    }

    return true;
}

bool
PaymentOpFrame::processTransferFee(BalanceManager& balanceManager,
                                   AccountFrame::pointer payer,
                                   BalanceFrame::pointer chargeFrom,
                                   Fee expectedFee, Fee actualFee,
                                   uint64_t& universalAmount,
                                   LedgerManager& lm, StorageHelper& sh)
{
    if ((actualFee.fixed == 0) && (actualFee.percent == 0))
    {
        return true;
    }

    if ((expectedFee.fixed < actualFee.fixed) ||
        (expectedFee.percent < actualFee.percent))
    {
        innerResult().code(PaymentResultCode::INSUFFICIENT_FEE_AMOUNT);
        return false;
    }

    uint64_t totalFee;
    if (!safeSum(actualFee.fixed, actualFee.percent, totalFee))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state: failed to calculate total sum of fees to be charged - overflow";
        throw std::runtime_error("Total sum of fees to be charged overflows");
    }

    if (lm.shouldUse(LedgerVersion::DELETE_REDEMPTION_ZERO_TASKS_CHECKING))
    {
        auto result = chargeFrom->tryCharge(totalFee);
        if (result != BalanceFrame::Result::SUCCESS) {
            innerResult().code(result == BalanceFrame::Result::UNDERFUNDED ?
                                         PaymentResultCode::UNDERFUNDED:
                                         PaymentResultCode::INCORRECT_AMOUNT_PRECISION);
            return false;
        }
        sh.getBalanceHelper().storeChange(chargeFrom->mEntry);

        balanceManager.transferFee(chargeFrom->getAsset(), totalFee);

        return true;
    }

    auto adminBalance = balanceManager.loadOrCreateBalanceForAdmin(chargeFrom->getAsset());

    return processTransfer(balanceManager, payer, chargeFrom, adminBalance, totalFee, universalAmount, lm);
}

void
PaymentOpFrame::setErrorCode(BalanceManager::Result transferResult)
{
    switch (transferResult)
    {
        case BalanceManager::Result::UNDERFUNDED:
            innerResult().code(PaymentResultCode::UNDERFUNDED);
            return;
        case BalanceManager::Result::STATS_OVERFLOW:
            innerResult().code(PaymentResultCode::STATS_OVERFLOW);
            return;
        case BalanceManager::Result::LIMITS_EXCEEDED:
            innerResult().code(PaymentResultCode::LIMITS_EXCEEDED);
            return;
        case BalanceManager::Result::LINE_FULL:
            innerResult().code(PaymentResultCode::LINE_FULL);
            return;
        case BalanceManager::Result::INCORRECT_PRECISION:
            innerResult().code(PaymentResultCode::INCORRECT_AMOUNT_PRECISION);
            return;
        default:
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from transfer: "
                                                   << transferResult;
            throw std::runtime_error("Unexpected result code from balance manager transfer");
    }
}

BalanceFrame::pointer
PaymentOpFrame::tryLoadDestinationBalance(AssetCode asset,
                                          StorageHelper& storageHelper, Application& app)
{
    switch (mPayment.destination.type())
    {
        case PaymentDestinationType::BALANCE:
        {
            auto dest = storageHelper.getBalanceHelper().loadBalance(mPayment.destination.balanceID());
            if (!dest)
            {
                innerResult().code(PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND);
                return nullptr;
            }

            if (dest->getAsset() != asset)
            {
                innerResult().code(PaymentResultCode::BALANCE_ASSETS_MISMATCHED);
                return nullptr;
            }

            return dest;
        }
        case PaymentDestinationType::ACCOUNT:
        {
            if (!storageHelper.getAccountHelper().exists(mPayment.destination.accountID()))
            {
                innerResult().code(PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
                return nullptr;
            }

            BalanceManager balanceManager(app, storageHelper);
            return balanceManager.loadOrCreateBalance(mPayment.destination.accountID(), asset);
        }
        default:
            throw std::runtime_error("Unexpected destination type on payment");
    }
}

bool
PaymentOpFrame::isTransferAllowed(BalanceFrame::pointer from, BalanceFrame::pointer to, StorageHelper& storageHelper)
{
    if (from->getAsset() != to->getAsset())
    {
        innerResult().code(PaymentResultCode::BALANCE_ASSETS_MISMATCHED);
        return false;
    }

    // is transfer allowed by asset policy
    auto asset = storageHelper.
        getAssetHelper().
        mustLoadAsset(from->getAsset());
    if (!asset->isPolicySet(AssetPolicy::TRANSFERABLE))
    {
        innerResult().code(PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
        return false;
    }

    return true;
}

Fee
PaymentOpFrame::getActualFee(AccountFrame::pointer accountFrame, AssetCode const& transferAsset, uint64_t amount,
                             PaymentFeeType feeType, StorageHelper& storageHelper, LedgerManager& lm)
{
    Fee actualFee;
    actualFee.percent = 0;
    actualFee.fixed = 0;
    auto feeFrame = storageHelper.getFeeHelper().loadForAccount(FeeType::PAYMENT_FEE, transferAsset,
                                                          static_cast<int64_t>(feeType),
                                                          accountFrame, amount);
    // if we do not have any fee frame - any fee is valid
    if (!feeFrame)
    {
        return actualFee;
    }

    const uint64_t feeMinimumAmount = storageHelper.
            getAssetHelper().
            mustLoadAsset(transferAsset)
        ->getMinimumAmount();
    if (!feeFrame->calculatePercentFee(amount, actualFee.percent, ROUND_UP, feeMinimumAmount))
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Failed to calculate actual payment fee - overflow, asset code: "
                                               << feeFrame->getFeeAsset();
        throw std::runtime_error("Failed to calculate actual payment fee - overflow");
    }

    actualFee.fixed = static_cast<uint64>(feeFrame->getFee().fixedFee);
    return actualFee;
}

bool
PaymentOpFrame::isSendToSelf(LedgerManager& lm, BalanceID sourceBalanceID, BalanceID destBalanceID)
{
    return sourceBalanceID == destBalanceID;
}

bool
PaymentOpFrame::doApply(Application& app, StorageHelper& storageHelper,
                        LedgerManager& ledgerManager)
{
    LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto sourceBalance = balanceHelper.loadBalance(mPayment.sourceBalanceID, getSourceID());
    if (!sourceBalance)
    {
        innerResult().code(PaymentResultCode::SRC_BALANCE_NOT_FOUND);
        return false;
    }

    auto destBalance = tryLoadDestinationBalance(sourceBalance->getAsset(), storageHelper, app);
    if (!destBalance)
    {
        return false;
    }

    BalanceID destBalanceID = destBalance->getBalanceID();

    if (isSendToSelf(ledgerManager, mPayment.sourceBalanceID, destBalanceID))
    {
        innerResult().code(PaymentResultCode::MALFORMED);
        return false;
    }

    if (!isTransferAllowed(sourceBalance, destBalance, storageHelper))
    {
        return false;
    }

    uint64_t sourceSentUniversal = 0;

    BalanceManager balanceManager(app, storageHelper);

    if (!processTransfer(balanceManager, mSourceAccount, sourceBalance, destBalance,
                         mPayment.amount, sourceSentUniversal, ledgerManager))
    {
        return false;
    }

    auto sourceFee = getActualFee(mSourceAccount, sourceBalance->getAsset(), mPayment.amount,
                                  PaymentFeeType::OUTGOING, storageHelper, ledgerManager);

    if (!processTransferFee(balanceManager, mSourceAccount, sourceBalance,
                            mPayment.feeData.sourceFee, sourceFee, sourceSentUniversal, ledgerManager, storageHelper))
    {
        return false;
    }

    auto destAccount = storageHelper.getAccountHelper().mustLoadAccount(destBalance->getAccountID());
    auto destFee = getActualFee(destAccount, destBalance->getAsset(), mPayment.amount, PaymentFeeType::INCOMING,
                                storageHelper, ledgerManager);

    if (!(app.getAdminID() == getSourceID()))
    {
        auto destFeePayer = destAccount;
        auto destFeePayerBalance = destBalance;
        if (mPayment.feeData.sourcePaysForDest)
        {
            destFeePayer = mSourceAccount;
            destFeePayerBalance = sourceBalance;
        }

        uint64_t destFeeUniversalAmount = 0;

        if (!processTransferFee(balanceManager, destFeePayer, destFeePayerBalance,
                                mPayment.feeData.destinationFee, destFee, destFeeUniversalAmount, ledgerManager, storageHelper))
        {
            return false;
        }

        if (mPayment.feeData.sourcePaysForDest)
            sourceSentUniversal += destFeeUniversalAmount;
    }

    uint64 paymentID = delta.getHeaderFrame().generateID(LedgerEntryType::PAYMENT_REQUEST);

    if (!mPayment.reference.empty())
    {
        AccountID sourceAccountID = mSourceAccount->getID();

        if (storageHelper.getReferenceHelper().exists(mPayment.reference, sourceAccountID))
        {
            innerResult().code(PaymentResultCode::REFERENCE_DUPLICATION);
            return false;
        }
        createReferenceEntry(mPayment.reference, sourceAccountID, storageHelper);
    }

    innerResult().code(PaymentResultCode::SUCCESS);
    innerResult().paymentResponse().destination = destAccount->getID();
    innerResult().paymentResponse().destinationBalanceID = destBalance->getBalanceID();
    innerResult().paymentResponse().asset = destBalance->getAsset();
    innerResult().paymentResponse().sourceSentUniversal = sourceSentUniversal;
    innerResult().paymentResponse().paymentID = paymentID;
    innerResult().paymentResponse().actualSourcePaymentFee = sourceFee;
    innerResult().paymentResponse().actualDestinationPaymentFee = destFee;

    return true;
}

bool PaymentOpFrame::isDestinationFeeValid()
{
    uint64_t totalDestinationFee;
    if (!safeSum(mPayment.feeData.destinationFee.fixed, mPayment.feeData.destinationFee.percent,
                 totalDestinationFee))
    {
        innerResult().code(PaymentResultCode::INVALID_DESTINATION_FEE);
        return false;
    }

    if (mPayment.feeData.sourcePaysForDest)
        return true;

    if (mPayment.amount < totalDestinationFee)
    {
        innerResult().code(PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
        return false;
    }

    return true;
}

bool PaymentOpFrame::doCheckValid(Application& app)
{

    if (app.getLedgerManager().shouldUse(LedgerVersion::FIX_MAX_SUBJECT_SIZE)) {

        if (mPayment.subject.size() > app.getMaxSigns()) {
            innerResult().code(PaymentResultCode::INVALID_SUBJECT);
            return false;
        }
    }

    if (mPayment.reference.length() > 64)
    {
        innerResult().code(PaymentResultCode::MALFORMED);
        return false;
    }

    if (!isDestinationFeeValid())
    {
        return false;
    }

    if (mPayment.destination.type() != PaymentDestinationType::BALANCE)
    {
        return true;
    }

    if (mPayment.sourceBalanceID == mPayment.destination.balanceID())
    {
        innerResult().code(PaymentResultCode::MALFORMED);
        return false;
    }

    return true;
}
}