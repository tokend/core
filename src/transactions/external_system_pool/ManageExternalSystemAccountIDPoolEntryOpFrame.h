#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManageExternalSystemAccountIdPoolEntryOpFrame : public OperationFrame
{
protected:
    ManageExternalSystemAccountIdPoolEntryResult&
    innerResult()
    {
        return mResult.tr().manageExternalSystemAccountIdPoolEntryResult();
    }
    ManageExternalSystemAccountIdPoolEntryOp const& mManageExternalSystemAccountIdPoolEntryOp;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:
    ManageExternalSystemAccountIdPoolEntryOpFrame(Operation const& op, OperationResult& res,
                                        TransactionFrame& parentTx);

    static ManageExternalSystemAccountIdPoolEntryResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().manageExternalSystemAccountIdPoolEntryResult().code();
    }

    static ManageExternalSystemAccountIdPoolEntryOpFrame* makeHelper(Operation const& op, OperationResult& res,
                                                                     TransactionFrame& parentTx);

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<ManageExternalSystemAccountIdPoolEntryResultCode>::enum_name(innerResult().code());
    }
};
}
