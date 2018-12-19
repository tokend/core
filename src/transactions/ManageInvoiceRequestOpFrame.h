#pragma once

#include <xdr/Stellar-operation-manage-invoice-request.h>
#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageInvoiceRequestOpFrame : public OperationFrame
{

    ManageInvoiceRequestResult&
    innerResult()
    {
        return mResult.tr().manageInvoiceRequestResult();
    }

    ManageInvoiceRequestOp const& mManageInvoiceRequest;

	std::unordered_map<AccountID, CounterpartyDetails> getCounterpartyDetails(Database& db, LedgerDelta* delta) const override;
	SourceDetails getSourceAccountDetails(std::unordered_map<AccountID, CounterpartyDetails> counterpartiesDetails,
                                              int32_t ledgerVersion) const override;

    bool createManageInvoiceRequest(Application& app, StorageHelper &storageHelper, LedgerManager& ledgerManager);

    bool checkMaxInvoicesForReceiverAccount(Application& app, Database &db, KeyValueHelper &keyValueHelper);
    bool checkMaxInvoiceDetailsLength(Application& app, KeyValueHelper &keyValueHelper);
    int64_t obtainMaxInvoicesCount(Application& app, KeyValueHelper &keyValueHelper);
    uint64_t obtainMaxInvoiceDetailsLength(Application& app, KeyValueHelper &keyValueHelper);


public:
    ManageInvoiceRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper &storageHelper,
                 LedgerManager& ledgerManager) override;
    bool doCheckValid(Application& app) override;

    static ManageInvoiceRequestResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageInvoiceRequestResult().code();
    }

    std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;

};
}
