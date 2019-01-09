#pragma once

#include "AccountRuleVerifier.h"

namespace stellar
{
class StorageHelper;

class AccountRuleVerifierImpl : public AccountRuleVerifier {
private:
    StorageHelper& mStorageHelper;

    bool
    isAllowed(OperationCondition& operationCondition) override;

    bool
    isResourceMatches(AccountRuleResource const conditionResource,
                      AccountRuleResource const actualResource);

public:
    AccountRuleVerifierImpl(StorageHelper& storageHelper);

    virtual ~AccountRuleVerifierImpl()
    {
    }

};
}


