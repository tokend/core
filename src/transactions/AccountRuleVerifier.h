#pragma once

#include "OperationFrame.h"
#include "RuleVerifier.h"

namespace stellar
{

class AccountRuleVerifier : public RuleVerifier
{
public:
    virtual bool isAllowed(OperationCondition& operationCondition) = 0;
};

} // namespace stellar
