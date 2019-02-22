#pragma once

// Copyright 2015 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "transactions/OperationFrame.h"

namespace stellar
{
class SignerRuleVerifier;

class SignatureValidator
{
public:
	enum Result { NOT_ENOUGH_WEIGHT, INVALID_ACCOUNT_TYPE, ACCOUNT_BLOCKED, SUCCESS, EXTRA };
	typedef std::shared_ptr<SignatureValidator> pointer;

	// checks if signature is valid.
	virtual Result check(Application& app, StorageHelper& storageHelper,
						 SignerRuleVerifier& signerRuleVerifier,
						 AccountID const& accountID,
						 std::vector<SignerRequirement> requirements) = 0;

	virtual Result check(std::vector<PublicKey> keys, int signaturesRequired, LedgerVersion ledgerVersion) = 0;
	virtual bool checkAllSignaturesUsed() = 0;
	virtual void resetSignatureTracker() = 0;
};
}
