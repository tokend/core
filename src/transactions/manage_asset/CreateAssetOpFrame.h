#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "ManageAssetOpFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{

class CreateAssetOpFrame : public ManageAssetOpFrame
{

	AssetCreationRequest const& mAssetCreationRequest;

	// Returns update already existing request from db
	// if fails to load request, returns nullptr
	ReviewableRequestFrame::pointer getUpdatedReviewableRequest(Application& app, Database& db, LedgerDelta& delta) const;
	//creates new reviewable request
	ReviewableRequestFrame::pointer getCreatedReviewableRequest(Application& app, Database& db, LedgerDelta& delta) const;

    bool handleCreateRequest(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager);
    bool handleUpdateRequest(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager);


    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                          int32_t ledgerVersion) const override;

public:
    CreateAssetOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;


	longstring makeTasksKey() override;
	bool loadTasks(StorageHelper &storageHelper, uint32_t &allTasks) override;

protected:
    std::string getAssetCode() const override;
};
}
