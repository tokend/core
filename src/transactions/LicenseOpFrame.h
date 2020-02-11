#pragma once

#include <xdr/operation-license.h>
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


    bool
    signaturesUnique(Application& app);

    bool tryGetOperationConditions(StorageHelper& storageHelper, std::vector<OperationCondition>& result) const override;
    bool tryGetSignerRequirements(StorageHelper& storageHelper, std::vector<SignerRequirement>& result) const override;
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
