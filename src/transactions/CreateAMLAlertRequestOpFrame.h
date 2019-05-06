#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {
    class CreateAMLAlertRequestOpFrame : public OperationFrame {
        CreateAMLAlertRequestResult &innerResult() {
            return mResult.tr().createAMLAlertRequestResult();
        }

        CreateAMLAlertRequestOp const &mCreateAMLAlertRequest;

        const std::map<CreateAMLAlertRequestResultCode, CreateAMLAlertRequestResultCode> mOldCodes = {
            {CreateAMLAlertRequestResultCode::BALANCE_NOT_EXIST, CreateAMLAlertRequestResultCode::OLD_BALANCE_NOT_EXIST},
            {CreateAMLAlertRequestResultCode::INVALID_CREATOR_DETAILS, CreateAMLAlertRequestResultCode::OLD_INVALID_CREATOR_DETAILS},
            {CreateAMLAlertRequestResultCode::INCORRECT_PRECISION, CreateAMLAlertRequestResultCode::OLD_INCORRECT_PRECISION},
            {CreateAMLAlertRequestResultCode::INVALID_AMOUNT, CreateAMLAlertRequestResultCode::OLD_INVALID_AMOUNT},
            {CreateAMLAlertRequestResultCode::REFERENCE_DUPLICATION, CreateAMLAlertRequestResultCode::OLD_REFERENCE_DUPLICATION},
            {CreateAMLAlertRequestResultCode::UNDERFUNDED, CreateAMLAlertRequestResultCode::OLD_UNDERFUNDED}
        };

        void
        pickResultCode(LedgerManager& lm, CreateAMLAlertRequestResultCode code);

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

        std::vector<longstring> makeTasksKeyVector(StorageHelper &storageHelper) override;
    };
}
