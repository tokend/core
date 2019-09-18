#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "OfferValidator.h"

namespace stellar 
{
class ManageOfferOpFrame;

enum class ManageOfferAction 
{
    CREATE = 0,
    REMOVE = 1,
    CREATE_PARTICIPATION = 2,
    REMOVE_PARTICIPATION = 3
};

class CreateManageOfferRequestOpFrame : public OperationFrame 
{
    CreateManageOfferRequestOp const& mCreateManageOfferRequest;
    ManageOfferOp const& mManageOffer;

    std::unique_ptr<OfferValidator> mValidator;   

    ManageOfferAction mManageAction;
    std::function<std::string(AssetCode const& base, AssetCode const& quote)> mKeyMaker;

    bool
    doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    bool 
    doCheckValid(Application& app) override;

    CreateManageOfferRequestResult& innerResult() const
    {
        return mResult.tr().createManageOfferRequestResult();
    }

    bool
    tryGetOperationConditions(StorageHelper& sh, std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& sh, std::vector<SignerRequirement>& result) const override;

    std::vector<std::string>
    makeTasksKeyVector(AssetCode const& base, AssetCode const& quote);

    bool
    tryAutoApprove(Application& app, StorageHelper& sh,
                   ReviewableRequestFrame::pointer request);

public:
    CreateManageOfferRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& tx);
};
}