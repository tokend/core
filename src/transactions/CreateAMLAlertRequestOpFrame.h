#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {
    class CreateAMLAlertRequestOpFrame : public OperationFrame {
        CreateAMLAlertRequestResult &innerResult() {
            return mResult.tr().createAMLAlertRequestResult();
        }

        CreateAMLAlertRequestOp const &mCreateAMLAlertRequest;

        bool
        tryGetOperationConditions(StorageHelper& storageHelper,
                                  std::vector<OperationCondition>& result) const override;

        bool
        tryGetSignerRequirements(StorageHelper& storageHelper,
                                 std::vector<SignerRequirement>& result) const override;

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
    };
}
