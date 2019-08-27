#pragma once 

#include "ManageOfferOpFrame.h"

namespace stellar 
{
class OfferValidator
{
    ManageOfferOpFrame* mManageOfferOpFrame;

public:
    ManageOfferResultCode 
    validate(Application& app) const
    {
        mManageOfferOpFrame->doCheckValid(app);
        return mManageOfferOpFrame->getInnerCode();
    }

    OfferValidator(ManageOfferOp const& manageOfferOp, TransactionFrame& tx) 
    {
        OperationResult res;
        Operation op;
        op.body.type(OperationType::MANAGE_OFFER);
        op.body.manageOfferOp() = manageOfferOp;
        mManageOfferOpFrame = ManageOfferOpFrame::make(op, res, tx);
    }
};
}