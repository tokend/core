#pragma once

#include <transactions/OperationFrame.h>

namespace stellar
{
class OpenSwapOpFrame : public OperationFrame
{
    OpenSwapResult&
    innerResult()
    {
        return mResult.tr().openSwapResult();
    }

    OpenSwapOp const& mOpenSwap;

    bool isDestinationFeeValid();

    BalanceFrame::pointer
    mustLoadDestinationBalance(AssetCode asset, StorageHelper& storageHelper);

    bool isSwapAllowed(StorageHelper& sh, BalanceFrame::pointer from,
                       BalanceFrame::pointer to);

    Fee getActualFee(AccountFrame::pointer accountFrame,
                     AssetCode const& transferAsset, uint64_t amount,
                     PaymentFeeType feeType, StorageHelper& sh,
                     LedgerManager& lm);

    bool checkFee(AccountManager& accountManager, AccountFrame::pointer payer,
                  BalanceFrame::pointer chargeFrom, Fee expectedFee,
                  Fee actualFee, AccountID const& commissionID,
                  StorageHelper& sh);

    bool isSendToSelf(BalanceID sourceBalanceID, BalanceID destBalanceID);

    bool tryLock(StorageHelper& sh, BalanceFrame::pointer balance,
                 uint64_t amount);

    bool tryGetOperationConditions(
        StorageHelper& storageHelper,
        std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override;

    AccountFrame::pointer
    tryLoadDestinationAccount(StorageHelper& storageHelper) const;

  public:
    OpenSwapOpFrame(Operation const& op, OperationResult& res,
                    TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& sh,
                 LedgerManager& lm) override;

    bool doCheckValid(Application& app) override;

    static OpenSwapResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().openSwapResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<OpenSwapResultCode>::enum_name(
            innerResult().code());
    }
};
}