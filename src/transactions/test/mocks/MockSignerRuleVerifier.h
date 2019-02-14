#pragma once

#include "transactions/rule_verifing/SignerRuleVerifier.h"

namespace stellar
{
class StorageHelper;
struct SignerRequirement;

class MockSignerRuleVerifier : public SignerRuleVerifier
{
public:
    MOCK_METHOD3(isAllowed, bool(SignerRequirement const& requirement,
                                 SignerFrame::pointer signer,
                                 StorageHelper& storageHelper));
};

}  // namespace stellar
