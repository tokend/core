#include "PaymentOpFrame.h"
#include "ledger/LedgerDelta.h"
#include "ledger/StorageHelper.h"
#include "main/Application.h"
#include <ledger/AccountHelperLegacy.h>
#include <ledger/AssetHelperLegacy.h>
#include <ledger/AssetPairHelper.h>
#include <ledger/BalanceHelperLegacy.h>
#include <ledger/FeeHelper.h>
#include <ledger/LedgerHeaderFrame.h>
#include <ledger/ReferenceHelper.h>
#include <ledger/BalanceHelper.h>
#include <ledger/AssetHelper.h>
#include <ledger/AccountHelper.h>

namespace stellar
{
using namespace std;
using xdr::operator==;

PaymentOpFrame::PaymentOpFrame(const stellar::Operation &op, OperationResult &res,
                               TransactionFrame &parentTx)
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
PaymentOpFrame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                    std::vector<SignerRequirement> &result) const
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
PaymentOpFrame::tryLoadDestinationAccount(StorageHelper &storageHelper) const
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
            throw std::runtime_error("Unexpected destination type on payment v2 when load account");
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

    bool PaymentOpFrame::processTransfer(AccountManager &accountManager, AccountFrame::pointer payer,
                                           BalanceFrame::pointer from, BalanceFrame::pointer to, uint64_t amount,
                                           uint64_t &universalAmount, Database &db) {
        auto transferResult = accountManager.processTransferV2(payer, from, to, amount);
        if (transferResult.result != AccountManager::Result::SUCCESS) {
            setErrorCode(transferResult.result);
            return false;
        }

        if (!safeSum(universalAmount, transferResult.universalAmount, universalAmount)) {
            innerResult().code(PaymentResultCode::STATS_OVERFLOW);
            return false;
        }

        return true;
    }

    bool PaymentOpFrame::processTransferFee(AccountManager &accountManager, AccountFrame::pointer payer,
                                              BalanceFrame::pointer chargeFrom, Fee expectedFee,
                                              Fee actualFee, AccountID const &commissionID,
                                              Database &db, LedgerDelta &delta, bool ignoreStats,
                                              uint64_t &universalAmount) {
        if (actualFee.fixed == 0 && actualFee.percent == 0) {
            return true;
        }

        if (expectedFee.fixed < actualFee.fixed || expectedFee.percent < actualFee.percent) {
            innerResult().code(PaymentResultCode::INSUFFICIENT_FEE_AMOUNT);
            return false;
        }

        uint64_t totalFee;
        if (!safeSum(actualFee.fixed, actualFee.percent, totalFee)) {
            CLOG(ERROR, Logging::OPERATION_LOGGER)
                    << "Unexpected state: failed to calculate total sum of fees to be charged - overflow";
            throw std::runtime_error("Total sum of fees to be charged overflows");
        }

        // load commission balance
        auto commissionBalance = AccountManager::loadOrCreateBalanceFrameForAsset(commissionID, chargeFrom->getAsset(), db,
                                                                                  delta);
        if (!commissionBalance) {
            CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. Expected commission balance to exist";
            throw std::runtime_error("Unexpected state. Expected commission balance to exist");
        }

        return processTransfer(accountManager, payer, chargeFrom, commissionBalance, totalFee, universalAmount, db);
    }

    void PaymentOpFrame::setErrorCode(AccountManager::Result transferResult) {
        switch (transferResult) {
            case AccountManager::Result::UNDERFUNDED: {
                innerResult().code(PaymentResultCode::UNDERFUNDED);
                return;
            }
            case AccountManager::Result::STATS_OVERFLOW: {
                innerResult().code(PaymentResultCode::STATS_OVERFLOW);
                return;
            }
            case AccountManager::Result::LIMITS_EXCEEDED: {
                innerResult().code(PaymentResultCode::LIMITS_EXCEEDED);
                return;
            }
            case AccountManager::Result::LINE_FULL: {
                innerResult().code(PaymentResultCode::LINE_FULL);
                return;
            }
            case AccountManager::Result::INCORRECT_PRECISION: {
                innerResult().code(PaymentResultCode::INCORRECT_AMOUNT_PRECISION);
                return;
            }
            default: {
                CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected result code from process transfer v2: "
                                                       << transferResult;
                throw std::runtime_error("Unexpected result code from process transfer v2");
            }
        }
    }

    BalanceFrame::pointer
    PaymentOpFrame::tryLoadDestinationBalance(AssetCode asset, StorageHelper& storageHelper)
    {
        switch (mPayment.destination.type())
        {
            case PaymentDestinationType::BALANCE:
            {
                auto dest = storageHelper.getBalanceHelper().loadBalance(mPayment.destination.balanceID());
                if (!dest) {
                    innerResult().code(PaymentResultCode::DESTINATION_BALANCE_NOT_FOUND);
                    return nullptr;
                }

                if (dest->getAsset() != asset) {
                    innerResult().code(PaymentResultCode::BALANCE_ASSETS_MISMATCHED);
                    return nullptr;
                }

                return dest;
            }
            case PaymentDestinationType::ACCOUNT: {
                if (!storageHelper.getAccountHelper().exists(mPayment.destination.accountID())) {
                    innerResult().code(PaymentResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
                    return nullptr;
                }

                auto dest = AccountManager::loadOrCreateBalanceFrameForAsset(
                        mPayment.destination.accountID(), asset, storageHelper.getDatabase(),
                        storageHelper.mustGetLedgerDelta());
                if (!dest) {
                    CLOG(ERROR, Logging::OPERATION_LOGGER)
                            << "Unexpected state: expected destination balance to exist, account id: "
                            << PubKeyUtils::toStrKey(mPayment.destination.accountID());
                    throw runtime_error("Unexpected state: expected destination balance to exist");
                }

                return dest;
            }
            default:
                throw std::runtime_error("Unexpected destination type on payment v2");
        }
    }

    bool PaymentOpFrame::isTransferAllowed(BalanceFrame::pointer from, BalanceFrame::pointer to, Database &db) {
        if (from->getAsset() != to->getAsset())
        {
            innerResult().code(PaymentResultCode::BALANCE_ASSETS_MISMATCHED);
            return false;
        }

        // is transfer allowed by asset policy
        auto asset = AssetHelperLegacy::Instance()->mustLoadAsset(from->getAsset(), db);
        if (!asset->isPolicySet(AssetPolicy::TRANSFERABLE)) {
            innerResult().code(PaymentResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
            return false;
        }

        return true;
    }

    Fee
    PaymentOpFrame::getActualFee(AccountFrame::pointer accountFrame, AssetCode const &transferAsset, uint64_t amount,
                                   PaymentFeeType feeType, Database &db, LedgerManager& lm) {
        Fee actualFee;
        actualFee.percent = 0;
        actualFee.fixed = 0;
        auto feeFrame = FeeHelper::Instance()->loadForAccount(FeeType::PAYMENT_FEE, transferAsset,
                                                              static_cast<int64_t>(feeType),
                                                              accountFrame, amount, db);
        // if we do not have any fee frame - any fee is valid
        if (!feeFrame) {
            return actualFee;
        }

        const uint64_t feeMinimumAmount = AssetHelperLegacy::Instance()->mustLoadAsset(transferAsset, db)->getMinimumAmount();
        if (!feeFrame->calculatePercentFee(amount, actualFee.percent, ROUND_UP, feeMinimumAmount)) {
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
        Database& db = storageHelper.getDatabase();
        LedgerDelta& delta = storageHelper.mustGetLedgerDelta();
        auto sourceBalance = BalanceHelperLegacy::Instance()->loadBalance(
            getSourceID(), mPayment.sourceBalanceID, db, &delta);
        if (!sourceBalance)
        {
            innerResult().code(PaymentResultCode::SRC_BALANCE_NOT_FOUND);
            return false;
        }

        auto destBalance = tryLoadDestinationBalance(sourceBalance->getAsset(), storageHelper);
        if (!destBalance) {
            return false;
        }

        BalanceID destBalanceID = destBalance->getBalanceID();

        if (isSendToSelf(ledgerManager, mPayment.sourceBalanceID, destBalanceID))
        {
            innerResult().code(PaymentResultCode::MALFORMED);
            return false;
        }

        if (!isTransferAllowed(sourceBalance, destBalance, db)) {
            return false;
        }

        uint64_t sourceSentUniversal = 0;

        AccountManager accountManager(app, db, delta, app.getLedgerManager());

        if (!processTransfer(accountManager, mSourceAccount, sourceBalance, destBalance, mPayment.amount, sourceSentUniversal, db)) {
            return false;
        }

        auto sourceFee = getActualFee(mSourceAccount, sourceBalance->getAsset(), mPayment.amount,
                                      PaymentFeeType::OUTGOING, db, ledgerManager);

        if (!processTransferFee(accountManager, mSourceAccount, sourceBalance, mPayment.feeData.sourceFee, sourceFee,
                                app.getAdminID(), db, delta, false, sourceSentUniversal)) {
            return false;
        }

        auto destAccount = AccountHelperLegacy::Instance()->mustLoadAccount(destBalance->getAccountID(), db);
        auto destFee = getActualFee(destAccount, destBalance->getAsset(), mPayment.amount, PaymentFeeType::INCOMING,
                                    db, ledgerManager);

        if (!(app.getAdminID() == getSourceID())) {
            auto destFeePayer = destAccount;
            auto destFeePayerBalance = destBalance;
            if (mPayment.feeData.sourcePaysForDest) {
                destFeePayer = mSourceAccount;
                destFeePayerBalance = sourceBalance;
            }

            uint64_t destFeeUniversalAmount = 0;

            if (!processTransferFee(accountManager, destFeePayer, destFeePayerBalance, mPayment.feeData.destinationFee,
                                    destFee, app.getAdminID(), db, delta, true, destFeeUniversalAmount)) {
                return false;
            }

            if (mPayment.feeData.sourcePaysForDest)
                sourceSentUniversal += destFeeUniversalAmount;
        }

        uint64 paymentID = delta.getHeaderFrame().generateID(LedgerEntryType::PAYMENT_REQUEST);

        if (!mPayment.reference.empty()) {
            AccountID sourceAccountID = mSourceAccount->getID();

            if (ReferenceHelper::Instance()->exists(db, mPayment.reference, sourceAccountID)) {
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

    bool PaymentOpFrame::isDestinationFeeValid() {
        uint64_t totalDestinationFee;
        if (!safeSum(mPayment.feeData.destinationFee.fixed, mPayment.feeData.destinationFee.percent,
                     totalDestinationFee)) {
            innerResult().code(PaymentResultCode::INVALID_DESTINATION_FEE);
            return false;
        }

        if (mPayment.feeData.sourcePaysForDest)
            return true;

        if (mPayment.amount < totalDestinationFee) {
            innerResult().code(PaymentResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
            return false;
        }

        return true;
    }

    bool PaymentOpFrame::doCheckValid(Application &app) {
        if (mPayment.reference.length() > 64) {
            innerResult().code(PaymentResultCode::MALFORMED);
            return false;
        }

        if (!isDestinationFeeValid()) {
            return false;
        }

        if (mPayment.destination.type() != PaymentDestinationType::BALANCE) {
            return true;
        }

        if (mPayment.sourceBalanceID == mPayment.destination.balanceID()) {
            innerResult().code(PaymentResultCode::MALFORMED);
            return false;
        }

        return true;
    }
}
