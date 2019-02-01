#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include <ledger/SignerFrame.h>
#include "transactions/SignatureValidator.h"

namespace stellar
{
class SignerRuleVerifier;

class SignatureValidatorImpl : public SignatureValidator
{
protected:
	std::vector<bool> mUsedSignatures;
	Hash mContentHash;
	xdr::xvector<DecoratedSignature, 20> mSignatures;

	std::vector<SignerFrame::pointer>
	getSigners(StorageHelper& storageHelper, AccountID const& accountID);

    Result
	checkSignature(StorageHelper& storageHelper,
				   AccountID const& accountID, SignerRuleVerifier& verifier,
				   std::vector<SignerRequirement> requirements);

    bool shouldSkipCheck(Application &app);

	bool
	checkSignerRules(StorageHelper& storageHelper, SignerRuleVerifier& verifier,
					 std::vector<SignerRequirement> requirements, SignerFrame::pointer signer);

public:
	SignatureValidatorImpl(Hash contentHash, xdr::xvector<DecoratedSignature, 20> signatures);

	Result
	check(Application& app, StorageHelper& storageHelper, AccountID const& accountID,
		  std::vector<SignerRequirement> requirements) override;

	Result check(std::vector<PublicKey> keys, int signaturesRequired, LedgerVersion ledgerVersion) override;
	bool checkAllSignaturesUsed() override;
	void resetSignatureTracker() override;
};
}
