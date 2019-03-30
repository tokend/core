#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManagePollOpFrame : public OperationFrame
{
protected:
    ManagePollOp const& mManagePoll;

    ManagePollResult&
    innerResult()
    {
        return mResult.tr().managePollResult();
    }

public:
    ManagePollOpFrame(Operation const& op, OperationResult& res,
                                   TransactionFrame& parentTx);

    static std::shared_ptr<ManagePollOpFrame>
    makeHelper(Operation const& op, OperationResult& res, TransactionFrame& tx);

    static ManagePollResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().managePollResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManagePollResultCode>::enum_name(innerResult().code());
    }

};


}
