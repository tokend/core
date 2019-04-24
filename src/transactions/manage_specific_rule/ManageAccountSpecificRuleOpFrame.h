#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManageAccountSpecificRuleOpFrame : protected OperationFrame
{
protected:
    ManageAccountSpecificRuleOp const& mManageAccountSpecificRule;

    ManageAccountSpecificRuleResult&
    innerResult()
    {
        return mResult.tr().manageAccountSpecificRuleResult();
    }

public:
    ManageAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);

    static std::shared_ptr<ManageAccountSpecificRuleOpFrame>
    makeHelper(Operation const& op, OperationResult& res, TransactionFrame& tx);

    static ManageCreatePollRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageCreatePollRequestResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageAccountSpecificRuleResultCode>::enum_name(innerResult().code());
    }

};
}
