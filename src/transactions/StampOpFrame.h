#pragma once

#include <xdr/Tokend-operation-stamp.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class StampOpFrame : public OperationFrame
{
    StampResult&
    innerResult()
    {
        return mResult.tr().stampResult();
    }
    StampOp const& mStamp;

    bool tryGetOperationConditions(StorageHelper& storageHelper, std::vector<OperationCondition>& result) const override;
    bool tryGetSignerRequirements(StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const override;

public:
    StampOpFrame(Operation const& op, OperationResult& res,
                                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static StampResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().stampResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<StampResultCode >::enum_name(innerResult().code());
    }
};
}
