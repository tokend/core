#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageVoteOpFrame : public OperationFrame
{
public:
    ManageVoteOpFrame(Operation const& op, OperationResult& res,
                        TransactionFrame& parentTx);

    static ManageVoteOpFrame* make(Operation const& op,
                                               OperationResult& res,
                                               TransactionFrame& parentTx);

    static ManageVoteResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageVoteResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageVoteResultCode>::enum_name(innerResult().code());
    }

protected:
    ManageVoteOp const& mManageVote;

    ManageVoteResult&
    innerResult()
    {
        return mResult.tr().manageVoteResult();
    }
};


}
