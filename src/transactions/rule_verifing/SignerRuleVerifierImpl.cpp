#include <transactions/OperationFrame.h>
#include "SignerRuleVerifierImpl.h"
#include "ledger/StorageHelper.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/SignerRuleHelper.h"

namespace stellar
{

bool
SignerRuleVerifierImpl::isAllowed(const SignerRequirement &requirement,
                                  SignerFrame::pointer signer,
                                  StorageHelper &storageHelper)
{
    if (!signer)
    {
        throw std::runtime_error("Expected signer ro exists on signer rule verifying");
    }

    auto& signerRoleHelper = storageHelper.getSignerRoleHelper();

    auto signerRoleFrame = signerRoleHelper.loadSignerRole(signer->getRoleID());
    if (!signerRoleFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. "
                       << "Expected signer role entry to exists. SignerRoleID: "
                       << signer->getRoleID();
        throw std::runtime_error("Unexpected state. Expected signer role to exists.");
    }

    auto& signerRuleHelper = storageHelper.getSignerRuleHelper();
    auto signerRuleFrames = signerRuleHelper.loadSignerRules(signerRoleFrame->getRuleIDs());

    bool isAllowed = false;

    for (auto signerRuleFrame : signerRuleFrames)
    {
        if (!isResourceMatches(requirement.resource, signerRuleFrame->getResource()))
        {
            continue;
        }

        if (!isActionMatches(requirement.action, signerRuleFrame->getAction()))
        {
            continue;
        }

        if (signerRuleFrame->isForbid())
        {
            return false;
        }

        isAllowed = true;
    }

    return isAllowed;
}

bool
SignerRuleVerifierImpl::isResourceMatches(SignerRuleResource const requiredResource,
                                          SignerRuleResource const actualResource)
{
    if (actualResource.type() == LedgerEntryType::ANY)
    {
        return true;
    }

    if (actualResource.type() != requiredResource.type())
    {
        return false;
    }

    switch (requiredResource.type())
    {
        case LedgerEntryType::ASSET:
            return isTypeMatches(requiredResource.asset().assetType,
                                 actualResource.asset().assetType) &&
                   isStringMatches(requiredResource.asset().assetCode,
                                   actualResource.asset().assetCode);
        case LedgerEntryType::ATOMIC_SWAP_BID:
            return isTypeMatches(requiredResource.atomicSwapBid().assetType,
                                 actualResource.atomicSwapBid().assetType) &&
                   isStringMatches(requiredResource.atomicSwapBid().assetCode,
                                   actualResource.atomicSwapBid().assetCode);
        case LedgerEntryType::REVIEWABLE_REQUEST:
        {
            auto expectedDetails = requiredResource.reviewableRequest().details;
            auto actualDetails = actualResource.reviewableRequest().details;
            if (actualDetails.requestType() == ReviewableRequestType::ANY) {
                return true;
            }

            if (actualDetails.requestType() != expectedDetails.requestType()) {
                return false;
            }

            switch (expectedDetails.requestType())
            {
                case ReviewableRequestType::SALE:
                    return isTypeMatches(expectedDetails.sale().type,
                                         actualDetails.sale().type);
                default:
                    return true;
            }
        }
        case LedgerEntryType::OFFER_ENTRY:
        {
            AssetFields expectedBase{requiredResource.offer().baseAssetCode,
                                     requiredResource.offer().baseAssetType};
            AssetFields expectedQuote{requiredResource.offer().quoteAssetCode,
                                      requiredResource.offer().quoteAssetType};
            AssetFields actualBase{actualResource.offer().baseAssetCode,
                                   actualResource.offer().baseAssetType};
            AssetFields actualQuote{actualResource.offer().quoteAssetCode,
                                    actualResource.offer().quoteAssetType};
            return (isAssetMatches(expectedBase, actualBase) &&
                    isAssetMatches(expectedQuote, actualQuote)) ||
                   (isAssetMatches(expectedBase, actualQuote) &&
                    isAssetMatches(expectedQuote, actualBase));
        }
        case LedgerEntryType::SALE:
            return isTypeMatches(requiredResource.sale().saleType,
                                 actualResource.sale().saleType) &&
                   isIDMatches(requiredResource.sale().saleType,
                               actualResource.sale().saleType);
        case LedgerEntryType::ACCOUNT_KYC:
        case LedgerEntryType::ACCOUNT:
        case LedgerEntryType::ACCOUNT_RULE:
        case LedgerEntryType::ACCOUNT_ROLE:
        case LedgerEntryType::BALANCE:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        case LedgerEntryType::KEY_VALUE:
        case LedgerEntryType::FEE:
        case LedgerEntryType::LIMITS_V2:
        case LedgerEntryType::ASSET_PAIR:
        case LedgerEntryType::TRANSACTION:
            return true;
        default:
            return false;
    }

}
}