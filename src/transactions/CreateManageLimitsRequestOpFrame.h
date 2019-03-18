#pragma once

#include "OperationFrame.h"

namespace stellar
{

class CreateManageLimitsRequestOpFrame : public OperationFrame
{
    CreateManageLimitsRequestResult& innerResult()
    {
        return mResult.tr().createManageLimitsRequestResult();
    }

    CreateManageLimitsRequestOp const& mCreateManageLimitsRequest;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    std::string getLimitsManageRequestDetailsReference(longstring const& details) const;

    bool ensureLimitsUpdateValid();


public:

    CreateManageLimitsRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool createManageLimitsRequest(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager);

    bool updateManageLimitsRequest(Application &app, StorageHelper &storageHelper, LedgerManager &lm);

    bool doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static CreateManageLimitsRequestResultCode getInnerCode(OperationResult const& res)
    {
        return res.tr().createManageLimitsRequestResult().code();
    }

    std::string getInnerResultCodeAsStr() override
    {
        return xdr::xdr_traits<CreateManageLimitsRequestResultCode>::enum_name(innerResult().code());
    }

    std::vector<longstring> makeTasksKeyVector(StorageHelper& storageHelper);
};

}