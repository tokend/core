#pragma once

#include <ledger/SignerFrame.h>
#include "SignerRuleVerifier.h"

namespace stellar
{

class SignerRuleVerifierImpl : public SignerRuleVerifier
{
private:
    const LedgerVersion currentLedgerVersion;

    bool
    isAllowed(SignerRequirement const& requirement, SignerFrame::pointer signer,
              StorageHelper& storageHelper) override;

    bool
    isResourceMatches(SignerRuleResource const requiredResource,
                      SignerRuleResource const actualResource);

    bool
    isSignerRuleActionMatches(SignerRuleAction const requiredAction,
                              SignerRuleAction const actualAction);

public:
    SignerRuleVerifierImpl(LedgerVersion const& currentLedgerVersion = LedgerVersion::EMPTY_VERSION)
    : currentLedgerVersion(currentLedgerVersion)
    {
    }

    ~SignerRuleVerifierImpl()
    {
    }
};
}
