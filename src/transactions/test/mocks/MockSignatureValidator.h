#pragma once

namespace stellar
{
class SignerRuleVerifier;
class StorageHelper;

class MockSignatureValidator : public SignatureValidator
{
public:
    MOCK_METHOD5(check, Result(Application& app, StorageHelper& storageHelper,
                               SignerRuleVerifier& signerRuleVerifier, AccountID const& accountID,
                               std::vector<SignerRequirement> requirements));
    MOCK_METHOD3(check,
                 Result(std::vector<PublicKey> keys, int signaturesRequired, LedgerVersion ledgerVersion));
    MOCK_METHOD0(checkAllSignaturesUsed,
                 bool());
    MOCK_METHOD0(resetSignatureTracker,
                 void());
};

}  // namespace stellar

