#pragma once

#include "transactions/OperationFrame.h"

namespace stellar 
{
class CreatePaymentRequestOpFrame : public OperationFrame 
{
    CreatePaymentRequestOp const& mCreatePaymentRequest;

    bool
    doApply(Application& app, StorageHelper& sh, LedgerManager& lm) override;

    bool 
    doCheckValid(Application& app) override;

    bool
    tryGetOperationConditions(StorageHelper& sh, std::vector<OperationCondition>& result) const override;

    bool
    tryGetSignerRequirements(StorageHelper& sh, std::vector<SignerRequirement>& result) const override;

public:
    CreatePaymentRequestOpFrame(Operation const& op, OperationResult& res, TransactionFrame& tx);
};
}