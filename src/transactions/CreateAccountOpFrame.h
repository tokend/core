#pragma once

#include "transactions/OperationFrame.h"

namespace stellar
{
class CreateAccountOpFrame : public OperationFrame
{
public:
    CreateAccountOpFrame(Operation const &op, OperationResult &res,
                         TransactionFrame &parentTx);

    bool
    doCheckValid(Application &app) override;

    bool
    doApply(Application &app, StorageHelper& storageHelper,
            LedgerManager &ledgerManager) override;

    static CreateAccountResultCode
    getInnerCode(OperationResult const &res)
    {
        return res.tr().createAccountResult().code();
    }

private:
    CreateAccountResult &innerResult()
    {
        return mResult.tr().createAccountResult();
    }

    void
    trySetReferrer(Application& app, StorageHelper& storageHelper,
                   AccountFrame::pointer accountFrame) const;

    bool
    createAccount(Application &app, StorageHelper& storageHelper);

    void
    createBalances(StorageHelper& storageHelper);

    bool
    createSigners(Application &app, StorageHelper& storageHelper);

    bool
    checkRoleExisting(StorageHelper& storageHelper);

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& storageHelper,
                             std::vector<SignerRequirement>& result) const override;

    CreateAccountOp const &mCreateAccount;
};
}
