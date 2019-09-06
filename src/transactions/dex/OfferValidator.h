#pragma once 

#include "ManageOfferOpFrame.h"

namespace stellar 
{
class OfferValidator
{
    std::shared_ptr<ManageOfferOpFrame> mManageOfferOpFrame;
    OperationResult mRes;
    Operation mOp;

public:
    ManageOfferResultCode 
    validate(Application& app)
    {
        mManageOfferOpFrame->doCheckValid(app);
        return mManageOfferOpFrame->getInnerCode();
    }

    OfferValidator(ManageOfferOp const& manageOfferOp, TransactionFrame& tx) 
    {
        mRes.code(OperationResultCode::opINNER);
        mRes.tr().type(OperationType::MANAGE_OFFER);

        
        mOp.body.type(OperationType::MANAGE_OFFER);
        mOp.body.manageOfferOp() = manageOfferOp;
        mManageOfferOpFrame = std::shared_ptr<ManageOfferOpFrame>(ManageOfferOpFrame::make(mOp, mRes, tx));
    }
};
}