#pragma once

#include <xdr/Stellar-operation-manage-invoice-request.h>
#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageContractRequestOpFrame : public OperationFrame
{

    ManageContractRequestResult&
    innerResult()
    {
        return mResult.tr().manageContractRequestResult();
    }

    ManageContractRequestOp const& mManageContractRequest;

    std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(Database& db,
                                                                              LedgerDelta* delta) const override;
    SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                          int32_t ledgerVersion) const override;

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
