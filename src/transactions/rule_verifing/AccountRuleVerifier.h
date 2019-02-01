#pragma once

#include "transactions/OperationFrame.h"
#include "RuleVerifier.h"

namespace stellar
{

class AccountRuleVerifier : public RuleVerifier
{
public:
    virtual bool isAllowed(OperationCondition& operationCondition,
                           StorageHelper& storageHelper) = 0;
};

} // namespace stellar
