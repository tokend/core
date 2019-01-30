#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"

namespace stellar {
    class CreateAccountOpFrame : public OperationFrame {
    public:

        CreateAccountOpFrame(Operation const &op, OperationResult &res,
                             TransactionFrame &parentTx);

        bool doCheckValid(Application &app) override;
        bool doApply(Application &app, LedgerDelta &delta, LedgerManager &ledgerManager) override;

        static CreateAccountResultCode getInnerCode(OperationResult const &res) {
            return res.tr().createAccountResult().code();
        }

    private:
        CreateAccountResult &innerResult() {
            return mResult.tr().createAccountResult();
        }

        bool createAccount(Application &app, LedgerDelta &delta,
                           LedgerManager &ledgerManager);

        void createBalance(LedgerDelta& delta, Database &db);

        bool checkRoleExisting(StorageHelper& storageHelper);

        bool
        tryGetOperationConditions(StorageHelper& storageHelper,
                                  std::vector<OperationCondition>& result) const override;

        CreateAccountOp const &mCreateAccount;
    };
}
