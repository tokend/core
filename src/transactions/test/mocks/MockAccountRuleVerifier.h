#pragma once

#include "transactions/rule_verifing/AccountRuleVerifier.h"

namespace stellar
{

class MockAccountRuleVerifier : public AccountRuleVerifier
{
public:
    MOCK_METHOD2(isAllowed,
                 bool(OperationCondition& operationCondition, StorageHelper& storageHelper));
};

}  // namespace stellar
