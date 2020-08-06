#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {
class CreateDataRequestOpFrame : public OperationFrame {

    CreateDataRequestOp const &mCreateDataRequestOp;

    CreateDataRequestResult &innerResult();
    void pickResultCode(CreateDataRequestResultCode code);

    bool doApply(Application &app, StorageHelper &storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

public:
    CreateDataRequestOpFrame(Operation const &op, OperationResult &res,
                                   TransactionFrame &parentTx);

};
}