#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "StatisticsV2Processor.h"
#include "ledger/KeyValueEntryFrame.h"

namespace stellar
{
class CreateWithdrawalRequestOpFrame : public OperationFrame
{
    CreateWithdrawalRequestResult& innerResult()
    {
        return mResult.tr().createWithdrawalRequestResult();
    }

    CreateWithdrawalRequestOp const& mCreateWithdrawalRequest;

    BalanceFrame::pointer tryLoadBalance(StorageHelper& storageHelper) const;

    bool isFeeMatches(AccountManager& accountManager, BalanceFrame::pointer balance) const;

    bool tryLockBalance(BalanceFrame::pointer balance);

    bool
    processStatistics(AccountManager& accountManager, Database& db, LedgerDelta& delta,
                      LedgerManager& ledgerManager, BalanceFrame::pointer balanceFrame,
                      const uint64_t amountToAdd, uint64_t& universalAmount, const uint64_t requestID);

    bool tryAddStatsV2(StatisticsV2Processor& statisticsV2Processor, const BalanceFrame::pointer balance,
                       const uint64_t amountToAdd, uint64_t& universalAmount, uint64_t requestID);

    bool exceedsLowerBound(Database &db, AssetCode& code);

    ReviewableRequestFrame::pointer
    tryCreateWithdrawalRequest(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager,
                               BalanceFrame::pointer balanceFrame,
                               AssetFrame::pointer assetFrame);

    void
    storeChangeRequest(LedgerDelta& delta, ReviewableRequestFrame::pointer request,
                       Database& db, const uint64_t universalAmount);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    CreateWithdrawalRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);
    bool doApply (Application& app, StorageHelper& storageHelper,
    LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    std::vector<std::string> makeTasksKeyVector(AssetCode const& code);

    static CreateWithdrawalRequestResultCode getInnerCode(
        OperationResult const& res)
    {
        return res.tr().createWithdrawalRequestResult().code();
    }

    static bool isExternalDetailsValid(Application &app, const std::string &externalDetails);

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<CreateWithdrawalRequestResultCode>::enum_name(innerResult().code());
    }
};
}
