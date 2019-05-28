#pragma once

#include <xdr/Tokend-operation-manage-invoice-request.h>
#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageContractRequestOpFrame : public OperationFrame
{
    bool
    isSupported() const override
    {
        return false;
    }

    ManageContractRequestResult&
    innerResult()
    {
        return mResult.tr().manageContractRequestResult();
    }

    bool tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    bool tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    ManageContractRequestOp const& mManageContractRequest;

    bool createManageContractRequest(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager);

    bool checkMaxContractsForContractor(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager);

    uint64_t obtainMaxContractsForContractor(Application& app, StorageHelper &storageHelper);

    bool checkMaxContractDetailLength(Application& app, KeyValueHelper &keyValueHelper);

    uint64_t obtainMaxContractInitialDetailLength(Application& app, KeyValueHelper &keyValueHelper);

public:
    ManageContractRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static ManageContractRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageContractRequestResult().code();
    }

    std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;
};
}
