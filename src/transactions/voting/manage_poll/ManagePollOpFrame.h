#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/PollFrame.h"

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
    bool doCheckValid(Application& app);

    bool
    isAuthorized (AccountID adminID, PollFrame::pointer poll);


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
