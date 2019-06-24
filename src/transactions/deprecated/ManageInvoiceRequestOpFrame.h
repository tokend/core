#pragma once

#include <xdr/operation-manage-invoice-request.h>
#include "transactions/OperationFrame.h"

namespace stellar
{
class ManageInvoiceRequestOpFrame : public OperationFrame
{
    bool
    isSupported(LedgerManager& lm) const override
    {
        return false;
    }

    ManageInvoiceRequestResult&
    innerResult()
    {
        return mResult.tr().manageInvoiceRequestResult();
    }

    bool
    tryGetOperationConditions(
        StorageHelper& sh,
        std::vector<OperationCondition>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    bool
    tryGetSignerRequirements(
        StorageHelper& storageHelper,
        std::vector<SignerRequirement>& result) const override
    {
        throw std::runtime_error("Unexecpted call. Operation is deprecated");
    }

    ManageInvoiceRequestOp const& mManageInvoiceRequest;

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

};
}
