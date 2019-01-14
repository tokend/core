#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{

class BindExternalSystemAccountIdOpFrame : public OperationFrame
{
    BindExternalSystemAccountIdResult&
    innerResult()
    {
        return mResult.tr().bindExternalSystemAccountIdResult();
    }
    BindExternalSystemAccountIdOp const& mBindExternalSystemAccountId;
    int getExpiresAt(StorageHelper& storageHelper, LedgerManager &ledgerManager, int32 externalSystemType);

    bool
    tryGetOperationConditions(StorageHelper& sh,
                              std::vector<OperationCondition>& result) const override;

public:
    BindExternalSystemAccountIdOpFrame(Operation const& op, OperationResult& res,
                                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static BindExternalSystemAccountIdResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().bindExternalSystemAccountIdResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<BindExternalSystemAccountIdResultCode>::enum_name(innerResult().code());
    }

    static const uint64_t dayInSeconds = 24 * 60 * 60;
};
}