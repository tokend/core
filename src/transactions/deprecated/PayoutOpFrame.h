#pragma once

#include <ledger/AssetHelper.h>
#include <ledger/BalanceHelper.h>
#include "transactions/OperationFrame.h"

namespace stellar
{
class BalanceManager;
class StatisticsV2Processor;

class PayoutOpFrame : public OperationFrame
{
    bool
    isSupported(LedgerManager& lm) const override;

    PayoutResult &innerResult() {
        return mResult.tr().payoutResult();
    }

    PayoutOp const &mPayout;

    bool
    tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    bool
    tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    Fee
    getActualFee(StorageHelper& storageHelper, AssetCode const& asset, uint64_t amount, uint64_t precisionStep);

    bool
    isFeeAppropriate(Fee const& actualFee) const;

    bool
    tryProcessTransferFee(BalanceManager& accountManager,
                          Database& db, uint64_t actualTotalAmount,
                          BalanceFrame::pointer sourceBalance);

    std::vector<AccountID>
    getAccountIDs(std::map<AccountID, uint64_t>& assetHoldersAmounts);

    std::map<AccountID, uint64_t>
    obtainHoldersPayoutAmountsMap(Application& app, uint64_t& totalAmount,
                            std::vector<BalanceFrame::pointer> holders,
                            uint64_t assetHoldersAmount);

    void
    addPayoutResponse(AccountID const& accountID, uint64_t amount,
                      BalanceID const& balanceID);

    std::map<AccountID, BalanceFrame::pointer>
    obtainAccountIDBalanceMap(
            std::map<AccountID, uint64_t>& assetHoldersAmounts,
            AssetCode assetCode, BalanceHelper& balanceHelper);

    bool
    processTransfers(BalanceFrame::pointer sourceBalance, uint64_t totalAmount,
                     std::map<AccountID, uint64_t> assetHoldersAmounts,
                     StorageHelper& storageHelper);

    BalanceFrame::pointer
    obtainSourceBalance(BalanceHelper& balanceHelper, AssetHelper& assetHelper);

    std::vector<BalanceFrame::pointer>
    obtainAssetHoldersBalances(AssetFrame::pointer assetFrame,
                               BalanceHelper& balanceHelper);

    bool
    processStatistics(StatisticsV2Processor statisticsV2Processor,
                      BalanceFrame::pointer sourceBalance, uint64_t amount);

public:

    PayoutOpFrame(Operation const &op, OperationResult &res,
                  TransactionFrame &parentTx);

    bool doApply(Application &app, StorageHelper &storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    static PayoutResultCode
    getInnerCode(OperationResult const &res)
    {
        return res.tr().payoutResult().code();
    }

    std::string getInnerResultCodeAsStr() override;
};
}