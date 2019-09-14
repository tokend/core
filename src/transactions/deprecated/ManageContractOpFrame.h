#pragma once

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"
#include "ledger/ContractFrame.h"

namespace stellar
{
class ManageContractOpFrame : public OperationFrame {
    bool
    isSupported(LedgerManager& lm) const override
    {
        return false;
    }

    ManageContractResult&
    innerResult()
    {
        return mResult.tr().manageContractResult();
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

    ManageContractOp const& mManageContract;

    bool ensureIsAllowed(std::vector<AccountID> validSources);

    bool tryAddContractDetails(ContractFrame::pointer contractFrame, Application& app,
                               StorageHelper& storageHelper);

    bool tryConfirmCompleted(ContractFrame::pointer contractFrame, StorageHelper& storageHelper);

    bool tryCompleted(ContractFrame::pointer contractFrame,
                      std::vector<ReviewableRequestFrame::pointer> invoiceRequests,
                      StorageHelper& storageHelper);

    bool checkIsInvoicesApproved(std::vector<ReviewableRequestFrame::pointer> invoiceRequests);

    bool tryStartDispute(ContractFrame::pointer contractFrame,
                         Application& app, StorageHelper& storageHelper);

    bool tryResolveDispute(ContractFrame::pointer contractFrame, StorageHelper& storageHelper);

    bool revertInvoicesAmounts(ContractFrame::pointer contractFrame, StorageHelper& storageHelper);

    void unlockApprovedInvoicesAmounts(ContractFrame::pointer contractFrame, StorageHelper& storageHelper);

public:

    static uint64_t obtainMaxContractDetailLength(Application& app, StorageHelper& storageHelper);

    ManageContractOpFrame(Operation const& op, OperationResult& res,
                          TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper,
                 LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;

    static ManageContractResultCode
    getInnerCode(OperationResult const& res)
    {
        return res.tr().manageContractResult().code();
    }

    std::string getInnerResultCodeAsStr() override;
};
}
