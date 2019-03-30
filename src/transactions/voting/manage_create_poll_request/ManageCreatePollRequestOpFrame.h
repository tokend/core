#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManageCreatePollRequestOpFrame : public OperationFrame
{
protected:
    ManageCreatePollRequestOp const& mManageCreatePollRequest;

    ManageCreatePollRequestResult&
    innerResult()
    {
        return mResult.tr().manageCreatePollRequestResult();
    }

public:
    ManageCreatePollRequestOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    static std::shared_ptr<ManageCreatePollRequestOpFrame>
    makeHelper(Operation const& op, OperationResult& res, TransactionFrame& tx);

    static ManageCreatePollRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageCreatePollRequestResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageCreatePollRequestResultCode>::enum_name(innerResult().code());
    }

};


}
