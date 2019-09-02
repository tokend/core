#pragma once 

#include "ReviewRequestOpFrame.h"

namespace stellar 
{

class ReviewPaymentRequestOpFrame : public ReviewRequestOpFrame 
{
    bool
    tryGetSignerRequirements(StorageHelper& sh, std::vector<SignerRequirement>& result) const override;

    bool 
    handleApprove(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
					   ReviewableRequestFrame::pointer request) override;
	bool 
    handleReject(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager,
					  ReviewableRequestFrame::pointer request) override;

public:
    ReviewPaymentRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& tx);
};
}