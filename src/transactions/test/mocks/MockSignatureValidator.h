#pragma once

namespace stellar {

    class MockSignatureValidator : public SignatureValidator {
    public:
        MOCK_METHOD4(check,
                     Result(Application& app, StorageHelper& storageHelper,                                             AccountID const& accountID,                                             std::vector<SignerRequirement> requirements));
        MOCK_METHOD3(check,
                     Result(std::vector<PublicKey> keys, int signaturesRequired, LedgerVersion ledgerVersion));
        MOCK_METHOD0(checkAllSignaturesUsed,
                     bool());
        MOCK_METHOD0(resetSignatureTracker,
                     void());
    };

}  // namespace stellar
