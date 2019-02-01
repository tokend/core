#pragma once

#include <ledger/SignerFrame.h>
#include "SignerRuleVerifier.h"

namespace stellar
{

class SignerRuleVerifierImpl : public SignerRuleVerifier
{
private:
    bool
    isAllowed(SignerRequirement const& requirement, SignerFrame::pointer signer,
              StorageHelper& storageHelper) override;

    bool
    isResourceMatches(SignerRuleResource const requiredResource,
                      SignerRuleResource const actualResource);

public:
    SignerRuleVerifierImpl()
    {
    }

    ~SignerRuleVerifierImpl()
    {
    }
};
}
