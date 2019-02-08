#include "PaymentOpV2Frame.h"
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

PaymentOpV2Frame::PaymentOpV2Frame(const stellar::Operation &op, OperationResult &res,
                                   TransactionFrame &parentTx)
        : OperationFrame(op, res, parentTx), mPayment(mOperation.body.paymentOpV2())
{
}

bool
PaymentOpV2Frame::tryGetOperationConditions(StorageHelper& storageHelper,
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

    result.emplace_back(resource, "send", mSourceAccount);
    result.emplace_back(resource, "receive_from_payment", destinationAccountFrame);

    return true;
}

bool
PaymentOpV2Frame::tryGetSignerRequirements(StorageHelper &storageHelper,
                                    std::vector<SignerRequirement> &result) const
{
    auto& balanceHelper = storageHelper.getBalanceHelper();
    auto balanceFrame = balanceHelper.mustLoadBalance(mPayment.sourceBalanceID);

    auto& assetHelper = storageHelper.getAssetHelper();
    auto assetFrame = assetHelper.mustLoadAsset(balanceFrame->getAsset());

    SignerRuleResource resource(LedgerEntryType::ASSET);
    resource.asset().assetType = assetFrame->getType();
    resource.asset().assetCode = assetFrame->getCode();

    result.emplace_back(resource, "send");

    return true;
}

AccountFrame::pointer
PaymentOpV2Frame::tryLoadDestinationAccount(StorageHelper &storageHelper) const
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

    bool PaymentOpV2Frame::processTransfer(AccountManager &accountManager, AccountFrame::pointer payer,
                                           BalanceFrame::pointer from, BalanceFrame::pointer to, uint64_t amount,
                                           uint64_t &universalAmount, Database &db) {
        auto transferResult = accountManager.processTransferV2(payer, from, to, amount);
        if (transferResult.result != AccountManager::Result::SUCCESS) {
            setErrorCode(transferResult.result);
            return false;
        }

        if (!safeSum(universalAmount, transferResult.universalAmount, universalAmount)) {
            innerResult().code(PaymentV2ResultCode::STATS_OVERFLOW);
            return false;
        }

        return true;
    }

    bool PaymentOpV2Frame::processTransferFee(AccountManager &accountManager, AccountFrame::pointer payer,
                                              BalanceFrame::pointer chargeFrom, Fee expectedFee,
                                              Fee actualFee, AccountID const &commissionID,
                                              Database &db, LedgerDelta &delta, bool ignoreStats,
                                              uint64_t &universalAmount) {
        if (actualFee.fixed == 0 && actualFee.percent == 0) {
            return true;
        }

        if (expectedFee.fixed < actualFee.fixed || expectedFee.percent < actualFee.percent) {
            innerResult().code(PaymentV2ResultCode::INSUFFICIENT_FEE_AMOUNT);
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

    void PaymentOpV2Frame::setErrorCode(AccountManager::Result transferResult) {
        switch (transferResult) {
            case AccountManager::Result::UNDERFUNDED: {
                innerResult().code(PaymentV2ResultCode::UNDERFUNDED);
                return;
            }
            case AccountManager::Result::STATS_OVERFLOW: {
                innerResult().code(PaymentV2ResultCode::STATS_OVERFLOW);
                return;
            }
            case AccountManager::Result::LIMITS_EXCEEDED: {
                innerResult().code(PaymentV2ResultCode::LIMITS_EXCEEDED);
                return;
            }
            case AccountManager::Result::LINE_FULL: {
                innerResult().code(PaymentV2ResultCode::LINE_FULL);
                return;
            }
            case AccountManager::Result::INCORRECT_PRECISION: {
                innerResult().code(PaymentV2ResultCode::INCORRECT_AMOUNT_PRECISION);
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
    PaymentOpV2Frame::tryLoadDestinationBalance(AssetCode asset, Database &db, LedgerDelta &delta, LedgerManager& lm) {
        switch (mPayment.destination.type()) {
            case PaymentDestinationType::BALANCE: {
                auto dest = BalanceHelperLegacy::Instance()->loadBalance(mPayment.destination.balanceID(), db,
                                                                   &delta);
                if (!dest) {
                    innerResult().code(PaymentV2ResultCode::DESTINATION_BALANCE_NOT_FOUND);
                    return nullptr;
                }

                if (dest->getAsset() != asset) {
                    innerResult().code(PaymentV2ResultCode::BALANCE_ASSETS_MISMATCHED);
                    return nullptr;
                }

                return dest;
            }
            case PaymentDestinationType::ACCOUNT: {
                if (!AccountHelperLegacy::Instance()->exists(mPayment.destination.accountID(), db)) {
                    innerResult().code(PaymentV2ResultCode::DESTINATION_ACCOUNT_NOT_FOUND);
                    return nullptr;
                }

                auto dest = AccountManager::loadOrCreateBalanceFrameForAsset(mPayment.destination.accountID(),
                                                                             asset, db,
                                                                             delta);
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

    bool PaymentOpV2Frame::isTransferAllowed(BalanceFrame::pointer from, BalanceFrame::pointer to, Database &db) {
        if (from->getAsset() != to->getAsset())
        {
            innerResult().code(PaymentV2ResultCode::BALANCE_ASSETS_MISMATCHED);
            return false;
        }

        // is transfer allowed by asset policy
        auto asset = AssetHelperLegacy::Instance()->mustLoadAsset(from->getAsset(), db);
        if (!asset->isPolicySet(AssetPolicy::TRANSFERABLE)) {
            innerResult().code(PaymentV2ResultCode::NOT_ALLOWED_BY_ASSET_POLICY);
            return false;
        }

        return true;
    }

    Fee
    PaymentOpV2Frame::getActualFee(AccountFrame::pointer accountFrame, AssetCode const &transferAsset, uint64_t amount,
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
    PaymentOpV2Frame::isSendToSelf(LedgerManager& lm, BalanceID sourceBalanceID, BalanceID destBalanceID)
    {
        return sourceBalanceID == destBalanceID;
    }

    bool
    PaymentOpV2Frame::doApply(Application& app, StorageHelper& storageHelper,
                            LedgerManager& ledgerManager)
    {
        Database& db = storageHelper.getDatabase();
        LedgerDelta& delta = *storageHelper.getLedgerDelta();
        auto sourceBalance = BalanceHelperLegacy::Instance()->loadBalance(
            getSourceID(), mPayment.sourceBalanceID, db, &delta);
        if (!sourceBalance)
        {
            innerResult().code(PaymentV2ResultCode::SRC_BALANCE_NOT_FOUND);
            return false;
        }

        auto destBalance = tryLoadDestinationBalance(sourceBalance->getAsset(), db, delta, ledgerManager);
        if (!destBalance) {
            return false;
        }

        BalanceID destBalanceID = destBalance->getBalanceID();

        if (isSendToSelf(ledgerManager, mPayment.sourceBalanceID, destBalanceID))
        {
            innerResult().code(PaymentV2ResultCode::MALFORMED);
            return false;
        }

        if (!isTransferAllowed(sourceBalance, destBalance, db)) {
            return false;
        }

        uint64_t sourceSentUniversal = 0;

        AccountManager accountManager(app, db, delta, app.getLedgerManager());
        // process transfer from source to dest
        auto sourceAccount = AccountHelperLegacy::Instance()->mustLoadAccount(getSourceID(), db);

        if (!processTransfer(accountManager, sourceAccount, sourceBalance, destBalance, mPayment.amount, sourceSentUniversal, db)) {
            return false;
        }

        auto sourceFee = getActualFee(sourceAccount, sourceBalance->getAsset(), mPayment.amount,
                                      PaymentFeeType::OUTGOING, db, ledgerManager);

        if (!processTransferFee(accountManager, sourceAccount, sourceBalance, mPayment.feeData.sourceFee, sourceFee,
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
                destFeePayer = sourceAccount;
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
                innerResult().code(PaymentV2ResultCode::REFERENCE_DUPLICATION);
                return false;
            }
        createReferenceEntry(mPayment.reference, storageHelper);
        }

        innerResult().code(PaymentV2ResultCode::SUCCESS);
        innerResult().paymentV2Response().destination = destAccount->getID();
        innerResult().paymentV2Response().destinationBalanceID = destBalance->getBalanceID();
        innerResult().paymentV2Response().asset = destBalance->getAsset();
        innerResult().paymentV2Response().sourceSentUniversal = sourceSentUniversal;
        innerResult().paymentV2Response().paymentID = paymentID;
        innerResult().paymentV2Response().actualSourcePaymentFee = sourceFee;
        innerResult().paymentV2Response().actualDestinationPaymentFee = destFee;

        return true;
    }

    bool PaymentOpV2Frame::isDestinationFeeValid() {
        uint64_t totalDestinationFee;
        if (!safeSum(mPayment.feeData.destinationFee.fixed, mPayment.feeData.destinationFee.percent,
                     totalDestinationFee)) {
            innerResult().code(PaymentV2ResultCode::INVALID_DESTINATION_FEE);
            return false;
        }

        if (mPayment.feeData.sourcePaysForDest)
            return true;

        if (mPayment.amount < totalDestinationFee) {
            innerResult().code(PaymentV2ResultCode::PAYMENT_AMOUNT_IS_LESS_THAN_DEST_FEE);
            return false;
        }

        return true;
    }

    bool PaymentOpV2Frame::doCheckValid(Application &app) {
        if (mPayment.reference.length() > 64) {
            innerResult().code(PaymentV2ResultCode::MALFORMED);
            return false;
        }

        if (!isDestinationFeeValid()) {
            return false;
        }

        if (mPayment.destination.type() != PaymentDestinationType::BALANCE) {
            return true;
        }

        if (mPayment.sourceBalanceID == mPayment.destination.balanceID()) {
            innerResult().code(PaymentV2ResultCode::MALFORMED);
            return false;
        }

        return true;
    }
}
