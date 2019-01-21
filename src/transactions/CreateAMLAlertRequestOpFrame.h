//
// Created by Roman on 02.03.18.
//

#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"
#include "ledger/ReviewableRequestFrame.h"

namespace stellar {
    class CreateAMLAlertRequestOpFrame : public OperationFrame {
        CreateAMLAlertRequestResult &innerResult() {
            return mResult.tr().createAMLAlertRequestResult();
        }

        CreateAMLAlertRequestOp const &mCreateAMLAlertRequest;

        bool
        tryGetOperationConditions(StorageHelper& storageHelper,
                                  std::vector<OperationCondition>& result) const override;

    public:

        CreateAMLAlertRequestOpFrame(Operation const &op, OperationResult &res,
                                     TransactionFrame &parentTx);

        bool doApply(Application &app, StorageHelper &storageHelper,
                     LedgerManager &ledgerManager) override;

        bool doCheckValid(Application &app) override;

        static CreateAMLAlertRequestResultCode getInnerCode(
                OperationResult const &res) {
            return res.tr().createAMLAlertRequestResult().code();
        }

        std::string getInnerResultCodeAsStr() override {
            return xdr::xdr_traits<CreateAMLAlertRequestResultCode>::enum_name(innerResult().code());
        }

        std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;
    };
}
