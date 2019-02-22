// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/asio.h"
#include <set>
#include <transactions/rule_verifing/SignerRuleVerifier.h>
#include <transactions/rule_verifing/SignerRuleVerifierImpl.h>
#include <ledger/SignerRuleFrame.h>
#include "ledger/StorageHelper.h"
#include "ledger/SignerHelper.h"
#include "transactions/SignatureValidatorImpl.h"
#include "transactions/TransactionFrame.h"
#include "main/Application.h"

namespace stellar
{
using namespace std;
using xdr::operator==;

SignatureValidatorImpl::SignatureValidatorImpl(Hash contentHash,
                                       xdr::xvector<DecoratedSignature, 20>
                                       signatures)
{
    mContentHash = contentHash;
    mSignatures = signatures;

    resetSignatureTracker();
}

bool SignatureValidatorImpl::checkAllSignaturesUsed()
{
    for (auto sigb : mUsedSignatures)
    {
        if (!sigb)
        {
            return false;
        }
    }
    return true;
}

void SignatureValidatorImpl::resetSignatureTracker()
{
    mUsedSignatures = vector<bool>(mSignatures.size());
}

vector<SignerFrame::pointer>
SignatureValidatorImpl::getSigners(StorageHelper& storageHelper,
                                   AccountID const& accountID)
{
    auto& signerHelper = storageHelper.getSignerHelper();

    auto result = signerHelper.loadSigners(accountID);
    if (result.empty())
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Expected signers to exist for account: "
                                               << PubKeyUtils::toStrKey(accountID);
        throw std::runtime_error("Expected signers to exist for account");
    }

    return result;
}

SignatureValidatorImpl::Result SignatureValidatorImpl::check(
    std::vector<PublicKey> keys, int signaturesRequired, LedgerVersion ledgerVersion)
{
    set<PublicKey> usedKeys;
    for (size_t i = 0; i < mSignatures.size(); i++)
    {
        auto const& sig = mSignatures[i];
        for (auto it = keys.begin(); it != keys.end(); ++it)
        {
            if (usedKeys.find(*it) != usedKeys.end())
                continue;
            if (PubKeyUtils::hasHint(*it, sig.hint) &&
                PubKeyUtils::verifySig(*it, sig.signature, mContentHash))
            {
                signaturesRequired--;
                mUsedSignatures[i] = true;

                if (signaturesRequired == 0)
                {
                    return SUCCESS;
                }

                usedKeys.insert(*it);
            }
        }
    }
    return NOT_ENOUGH_WEIGHT;
}

bool
SignatureValidatorImpl::checkSignerRules(StorageHelper& storageHelper,
                                         SignerRuleVerifier& verifier,
                                         std::vector<SignerRequirement> requirements,
                                         SignerFrame::pointer signer)
{
    for (auto requirement : requirements)
    {
        if (!verifier.isAllowed(requirement, signer, storageHelper))
        {
            return false;
        }
    }

    return true;
}

SignatureValidatorImpl::Result
SignatureValidatorImpl::checkSignature(StorageHelper& storageHelper,
        AccountID const& accountID, SignerRuleVerifier& verifier,
        std::vector<SignerRequirement> requirements)
{
    auto signers = getSigners(storageHelper, accountID);

    std::map<uint32_t, SignatureWeight> identityWeights;
    uint64_t totalWeight = 0;

    for (size_t i = 0; i < mSignatures.size(); i++)
    {
        auto const& sig = mSignatures[i];

        for (auto const& signerFrame : signers)
        {
            auto const& signer = signerFrame->getEntry();
            bool isSignatureValid = PubKeyUtils::hasHint(signer.pubKey,
                                                         sig.hint) &&
                                    PubKeyUtils::verifySig(signer.pubKey,
                                                           sig.signature,
                                                           mContentHash);
            if (!isSignatureValid)
                continue;

            if (!checkSignerRules(storageHelper, verifier, requirements, signerFrame))
            {
                break;
            }

            auto existingIdentity = identityWeights.find(signer.identity);
            if (existingIdentity != identityWeights.end())
            {
                // we don't need signature if there is another one which signer has bigger weight
                if (existingIdentity->second.weight < signer.weight)
                {
                    totalWeight += signer.weight - existingIdentity->second.weight;
                    existingIdentity->second = {i, signer.weight};

                    if (totalWeight >= SignerRuleFrame::threshold)
                    {
                        return handleSuccess(identityWeights);
                    }
                }
                break;
            }

            totalWeight += signer.weight;
            identityWeights.emplace(signer.identity, SignatureWeight{i, signer.weight});

            if (totalWeight >= SignerRuleFrame::threshold)
            {
                return handleSuccess(identityWeights);
            }
            break;
        }
    }

    return NOT_ENOUGH_WEIGHT;
}

SignatureValidatorImpl::Result
SignatureValidatorImpl::handleSuccess(std::map<uint32_t, SignatureWeight> identityWeights)
{
    for (auto& identityWeight : identityWeights)
    {
        mUsedSignatures[identityWeight.second.signatureIndex] = true;
    }

    return SUCCESS;
}

bool SignatureValidatorImpl::shouldSkipCheck(Application & app)
{
    string txIDString(binToHex(mContentHash));
    auto skipCheckFor = app.getConfig().TX_SKIP_SIG_CHECK;
    if (skipCheckFor.find(txIDString) == skipCheckFor.end()) {
        return false;
    }

    for (size_t i = 0; i < mUsedSignatures.size(); i++) {
        mUsedSignatures[i] = true;
    }

    return true;
}

SignatureValidatorImpl::Result
SignatureValidatorImpl::check(Application& app, StorageHelper& storageHelper,
                              SignerRuleVerifier& signerRuleVerifier, AccountID const& accountID,
                              std::vector<SignerRequirement> requirements)
{
    if (shouldSkipCheck(app))
    {
        return SUCCESS;
    }

    return checkSignature(storageHelper, accountID, signerRuleVerifier, requirements);
}
}
