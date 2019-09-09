#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar
{
class CancelChangeRoleRequestOpFrame : public OperationFrame
{
    CancelChangeRoleRequestResult& innerResult()
    {
        return mResult.tr().cancelChangeRoleRequestResult();
    }

    CancelChangeRoleRequestOp const& mCancelChangeRoleRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    CancelChangeRoleRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, LedgerDelta& delta, LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CancelChangeRoleRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().cancelChangeRoleRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CancelChangeRoleRequestResultCode>::
        enum_name(innerResult().code());
    }
};
}
