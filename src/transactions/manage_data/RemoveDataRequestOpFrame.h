#pragma once

#include "transactions/OperationFrame.h"

namespace stellar {
class RemoveDataRequestOpFrame : public OperationFrame {

    RemoveDataRequestOp const &mRemoveDataRequestOp;

    RemoveDataRequestResult &innerResult();
    void pickResultCode(RemoveDataRequestResultCode code);

    bool doApply(Application &app, StorageHelper &storageHelper,
                 LedgerManager &ledgerManager) override;

    bool doCheckValid(Application &app) override;

    bool
    tryGetOperationConditions(StorageHelper& storageHelper,
                              std::vector<OperationCondition>& result) const override;

    bool tryGetSignerRequirements(stellar::StorageHelper &storageHelper,
                                  std::vector<SignerRequirement> &result) const override;

public:
    RemoveDataRequestOpFrame(Operation const &op, OperationResult &res,
                             TransactionFrame &parentTx);

};
}