#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ManageAssetOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{

class ChangeAssetPreIssuerOpFrame : public ManageAssetOpFrame
{

	AssetChangePreissuedSigner const& mAssetChangePreissuedSigner;

	bool
	tryGetOperationConditions(StorageHelper& storageHelper,
							  std::vector<OperationCondition>& result) const override;
public:
    ChangeAssetPreIssuerOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
protected:
    std::string getAssetCode() const override;
};
}
