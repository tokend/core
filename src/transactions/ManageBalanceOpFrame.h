#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"

namespace stellar
{

class ManageBalanceOpFrame : public OperationFrame {
    ManageBalanceResult&
    innerResult()
    {
        return mResult.tr().manageBalanceResult();
    }

    ManageBalanceOp const& mManageBalance;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

public:

    ManageBalanceOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static ManageBalanceResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageBalanceResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        const auto result = getResult();
        const auto code = getInnerCode(result);
        return xdr::xdr_traits<ManageBalanceResultCode>::enum_name(code);
    }
};
}
