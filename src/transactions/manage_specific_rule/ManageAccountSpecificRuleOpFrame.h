#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManageAccountSpecificRuleOpFrame : public OperationFrame
{
protected:
    ManageAccountSpecificRuleOp const& mManageAccountSpecificRule;

    ManageAccountSpecificRuleResult&
    innerResult()
    {
        return mResult.tr().manageAccountSpecificRuleResult();
    }

    bool const
    isAuthorized(AccountID const &saleOwner, AccountID const &admin) const;

public:
    ManageAccountSpecificRuleOpFrame(Operation const& op, OperationResult& res,
            TransactionFrame& parentTx);

    static std::shared_ptr<ManageAccountSpecificRuleOpFrame>
    makeHelper(Operation const& op, OperationResult& res, TransactionFrame& tx);

    static ManageAccountSpecificRuleResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageAccountSpecificRuleResult().code();
    }

    std::string
    getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<ManageAccountSpecificRuleResultCode>::enum_name(innerResult().code());
    }

};
}
