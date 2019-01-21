#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"

namespace stellar
{
class CheckLicenseStateOpFrame : public OperationFrame
{
    CheckLicenseStateResult& innerResult()
    {
        return mResult.tr().checkLicenseStateResult();
    }

    CheckLicenseStateOp const& mCheckLicenseState;

    std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(
        Database& db, LedgerDelta* delta) const override;

    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                              int32_t ledgerVersion) const override;

public:

    CheckLicenseStateOpFrame(Operation const& op, OperationResult& res,
                         TransactionFrame& parentTx);

    bool doCheckValid(Application& app) override;

    bool doApply(Application &app, StorageHelper &storageHelper, LedgerManager &ledgerManager) override;

    static CheckLicenseStateResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().checkLicenseStateResult().code();
    }

    std::string getInnerResultCodeAsStr() override;

};
}
