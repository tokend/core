#pragma once

#include "ManageExternalSystemAccountIDPoolEntryOpFrame.h"

namespace stellar
{

class CreateExternalSystemAccountIDPoolEntryOpFrame : public ManageExternalSystemAccountIdPoolEntryOpFrame {
    CreateExternalSystemAccountIdPoolEntryActionInput const& mInput;

public:
    CreateExternalSystemAccountIDPoolEntryOpFrame(Operation const& op, OperationResult& res,
                                                  TransactionFrame& parentTx);

    bool doApply(Application& app, StorageHelper& storageHelper, LedgerManager& ledgerManager) override;

    bool doCheckValid(Application& app) override;
};

}
