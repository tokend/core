#pragma once

#include <ledger/SignerFrame.h>
#include "RuleVerifier.h"

namespace stellar
{
class StorageHelper;
struct SignerRequirement;


class SignerRuleVerifier : public RuleVerifier
{
public:
    virtual bool
    isAllowed(SignerRequirement const& requirement, SignerFrame::pointer signer,
              StorageHelper& storageHelper) = 0;
};
}
