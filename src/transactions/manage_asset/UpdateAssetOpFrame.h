#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ManageAssetOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{

class UpdateAssetOpFrame : public ManageAssetOpFrame
{
	AssetUpdateRequest const& mAssetUpdateRequest;

    // Returns update already existing request from db or creates new one.
	// if fails to load request, returns nullptr
	ReviewableRequestFrame::pointer getUpdatedOrCreateReviewableRequest(Application& app, Database& db, LedgerDelta& delta);

	bool
	tryGetOperationConditions(StorageHelper& storageHelper,
							  std::vector<OperationCondition>& result) const override;

	bool
	tryGetSignerRequirements(StorageHelper& storageHelper,
							 std::vector<SignerRequirement>& result) const override;

public:
    
	UpdateAssetOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;

protected:
    std::string getAssetCode() const override;
	void updateRequest(ReviewableRequestEntry &requestEntry);
	bool ensureUpdateRequestValid(ReviewableRequestFrame::pointer request);


};
}
