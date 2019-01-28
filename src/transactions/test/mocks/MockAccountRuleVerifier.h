#pragma once

namespace stellar
{

class MockAccountRuleVerifier : public AccountRuleVerifier
{
public:
    MOCK_METHOD2(isAllowed,
    bool(OperationCondition& operationCondition, StorageHelper& storageHelper));
};

}  // namespace stellar
