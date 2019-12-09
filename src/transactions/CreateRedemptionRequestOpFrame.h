#pragma once

#include "transactions/OperationFrame.h"
#include <vector>

namespace stellar {
    class CreateRedemptionRequestOpFrame : public OperationFrame {
        CreateRedemptionRequestResult &innerResult() {
            return mResult.tr().createRedemptionRequestResult();
        }

        CreateRedemptionRequestOp const &mCreateRedemptionRequest;

        void
        pickResultCode(CreateRedemptionRequestResultCode code);

        std::vector<std::string>
        makeTasksKeyVector(AssetCode const& code);

        bool
        tryGetOperationConditions(StorageHelper& storageHelper,
                                  std::vector<OperationCondition>& result,
                                  LedgerManager& ledgerManager) const override;

        bool
        tryGetSignerRequirements(StorageHelper& storageHelper,
                                 std::vector<SignerRequirement>& result) const override;

    public:

        CreateRedemptionRequestOpFrame(Operation const &op, OperationResult &res,
                                       TransactionFrame &parentTx);

        bool doApply(Application &app, StorageHelper &storageHelper,
                     LedgerManager &ledgerManager) override;

        bool doCheckValid(Application &app) override;

        static CreateRedemptionRequestResultCode getInnerCode(
                OperationResult const &res) {
            return res.tr().createRedemptionRequestResult().code();
        }

        std::string getInnerResultCodeAsStr() override {
            return xdr::xdr_traits<CreateRedemptionRequestResultCode >::enum_name(innerResult().code());
        }
    };
}


