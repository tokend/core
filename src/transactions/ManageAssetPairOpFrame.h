#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/AssetPairFrame.h"

namespace stellar
{

class ManageAssetPairOpFrame : public OperationFrame
{
    ManageAssetPairResult&
    innerResult()
    {
        return mResult.tr().manageAssetPairResult();
    }
    ManageAssetPairOp const& mManageAssetPair;

	std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;
	SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                              int32_t ledgerVersion) const override;

	bool createNewAssetPair(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager, AssetPairFrame::pointer assetPair);

	std::vector<OperationCondition>
    getOperationConditions(StorageHelper& storageHelper) const override;

  public:
    
    ManageAssetPairOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static ManageAssetPairResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageAssetPairResult().code();
    }
};
}
