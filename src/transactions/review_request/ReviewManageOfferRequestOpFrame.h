#pragma once 

#include "ReviewRequestOpFrame.h"

namespace stellar 
{
enum class ManageOfferAction;

class ReviewManageOfferRequestOpFrame : public ReviewRequestOpFrame 
{
    bool
    tryGetSignerRequirements(StorageHelper& sh,
        std::vector<SignerRequirement>& result,
        LedgerManager& lm) const override;

    bool 
    handleApprove(Application& app, StorageHelper& sh, LedgerManager& ledgerManager,
					   ReviewableRequestFrame::pointer request) override;
	bool 
    handleReject(Application& app, StorageHelper& sh, LedgerManager& ledgerManager,
					  ReviewableRequestFrame::pointer request) override;

    ManageOfferAction
    getManageOfferAction(ManageOfferOp const& op) const;

public:
    ReviewManageOfferRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& tx);
};
}