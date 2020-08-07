#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {
class UpdateDataRequestOpFrame : public OperationFrame {

    UpdateDataRequestOp const &mUpdateDataRequestOp;

    UpdateDataRequestResult &innerResult();
    void pickResultCode(UpdateDataRequestResultCode code);

    bool doApply(Application &app, StorageHelper &storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                  std::vector<SignerRequirement> &result) const override;

public:
    UpdateDataRequestOpFrame(Operation const &op, OperationResult &res,
                             TransactionFrame &parentTx);

};
}