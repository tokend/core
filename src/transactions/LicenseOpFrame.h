#pragma once

#include <xdr/Stellar-operation-license.h>
#include "transactions/OperationFrame.h"

namespace stellar
{

class LicenseOpFrame : public OperationFrame
{
    LicenseResult&
    innerResult()
    {
        return mResult.tr().licenseResult();
    }
    LicenseOp const& mLicense;

    std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;
    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                          int32_t ledgerVersion) const override;

    bool isSignatureValid(Application& app, LedgerManager& lm);
public:
    LicenseOpFrame(Operation const& op, OperationResult& res,
                                       TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static LicenseResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().licenseResult().code();
    }

    std::string getInnerResultCodeAsStr() override {
        return xdr::xdr_traits<LicenseResultCode >::enum_name(innerResult().code());
    }
};
}