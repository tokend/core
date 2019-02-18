#pragma once

#include "AccountRuleVerifier.h"

namespace stellar
{
class StorageHelper;

class AccountRuleVerifierImpl : public AccountRuleVerifier {
private:
    bool
    isAllowed(OperationCondition& operationCondition,
              StorageHelper& storageHelper) override;

    bool
    isResourceMatches(AccountRuleResource const conditionResource,
                      AccountRuleResource const actualResource);

public:
    AccountRuleVerifierImpl()
    {
    }

    virtual ~AccountRuleVerifierImpl()
    {
    }

};
}


