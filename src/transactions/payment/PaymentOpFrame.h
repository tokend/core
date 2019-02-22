#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{
class PaymentOpFrame : public OperationFrame
{
    PaymentResult &innerResult() {
        return mResult.tr().paymentResult();
    }

    PaymentOp const &mPayment;

    bool isDestinationFeeValid();

    BalanceFrame::pointer
    tryLoadDestinationBalance(AssetCode asset, StorageHelper& storageHelper);

    bool isTransferAllowed(BalanceFrame::pointer from, BalanceFrame::pointer to, Database &db);

    Fee getActualFee(AccountFrame::pointer accountFrame, AssetCode const &transferAsset, uint64_t amount,
                           PaymentFeeType feeType, Database &db, LedgerManager& lm);

    bool processTransfer(AccountManager &accountManager, AccountFrame::pointer payer, BalanceFrame::pointer from, BalanceFrame::pointer to,
                         uint64_t amount, uint64_t& universalAmount, Database &db);

    bool processTransferFee(AccountManager &accountManager, AccountFrame::pointer payer,
                            BalanceFrame::pointer candidateToCharge, Fee expectedFee, Fee actualFee,
                            AccountID const &commissionID, Database &db, LedgerDelta &delta, bool ignoreStats,
                            uint64_t& universalAmount);

    void setErrorCode(AccountManager::Result transferResult);

    bool isSendToSelf(LedgerManager& lm, BalanceID sourceBalanceID, BalanceID destBalanceID);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    AccountFrame::pointer
    tryLoadDestinationAccount(StorageHelper& storageHelper) const;

public:
    PaymentOpFrame(Operation const &op, OperationResult &res, TransactionFrame &parentTx);

    bool doApply(Application &app, StorageHelper& storageHelper, LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static PaymentResultCode getInnerCode(OperationResult const &res) {
        return res.tr().paymentResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<PaymentResultCode>::enum_name(innerResult().code());
    }
};
}