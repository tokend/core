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

        if (!isSignerRuleActionMatches(requirement.action, signerRuleFrame->getAction()))
        {
            continue;
        }

        if (signerRuleFrame->forbids())
        {
            return false;
        }

        isAllowed = true;
    }

    return isAllowed;
}

bool
SignerRuleVerifierImpl::isSignerRuleActionMatches(
        SignerRuleAction const requiredAction,
        SignerRuleAction const actualAction) 
{
    return (requiredAction == actualAction) || (actualAction == SignerRuleAction::ANY);
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
            if (!isTasksMatch(requiredResource.reviewableRequest().tasksToAdd,
                              actualResource.reviewableRequest().tasksToAdd))
            {
                return false;
            }

            if (!isTasksMatch(requiredResource.reviewableRequest().tasksToRemove,
                              actualResource.reviewableRequest().tasksToRemove))
            {
                return false;
            }

            if (!isTasksMatch(requiredResource.reviewableRequest().allTasks,
                              actualResource.reviewableRequest().allTasks))
            {
                return false;
            }

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
                case ReviewableRequestType::CREATE_SALE:
                    return isTypeMatches(expectedDetails.createSale().type,
                                         actualDetails.createSale().type);
                case ReviewableRequestType::CREATE_POLL:
                    return isType32Matches(expectedDetails.createPoll().permissionType,
                                         actualDetails.createPoll().permissionType);
                case ReviewableRequestType::CREATE_ISSUANCE:
                    return isTypeMatches(expectedDetails.createIssuance().assetType,
                                         actualDetails.createIssuance().assetType) &&
                           isStringMatches(expectedDetails.createIssuance().assetCode,
                                           actualDetails.createIssuance().assetCode);
                case ReviewableRequestType::CREATE_WITHDRAW:
                    return isTypeMatches(expectedDetails.createWithdraw().assetType,
                                         actualDetails.createWithdraw().assetType) &&
                           isStringMatches(expectedDetails.createWithdraw().assetCode,
                                           actualDetails.createWithdraw().assetCode);
                default:
                    return true;
            }
        }
        case LedgerEntryType::OFFER_ENTRY:
        {
            if (!isBoolMatches(requiredResource.offer().isBuy,
                               actualResource.offer().isBuy))
            {
                return false;
            }

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
                   isIDMatches(requiredResource.sale().saleID,
                               actualResource.sale().saleID);
        case LedgerEntryType::SIGNER:
            return isIDMatches(requiredResource.signer().roleID,
                               actualResource.signer().roleID);
        case LedgerEntryType::SIGNER_ROLE:
            return isIDMatches(requiredResource.signerRole().roleID,
                               actualResource.signerRole().roleID);
        case LedgerEntryType::SIGNER_RULE:
            return isBoolMatches(requiredResource.signerRule().isDefault,
                                 actualResource.signerRule().isDefault);
        case LedgerEntryType::KEY_VALUE:
            return isStringMatches(requiredResource.keyValue().keyPrefix,
                                   actualResource.keyValue().keyPrefix);
        case LedgerEntryType::POLL:
            return isType32Matches(requiredResource.poll().permissionType,
                                 actualResource.poll().permissionType) &&
                   isIDMatches(requiredResource.poll().pollID,
                               actualResource.poll().pollID);
        case LedgerEntryType::VOTE:
            return isType32Matches(requiredResource.vote().permissionType,
                                 actualResource.vote().permissionType) &&
                   isIDMatches(requiredResource.vote().pollID,
                               actualResource.vote().pollID);
        case LedgerEntryType::INITIATE_KYC_RECOVERY:
            return isIDMatches(requiredResource.initiateKYCRecovery().roleID,
                                actualResource.initiateKYCRecovery().roleID);
        case LedgerEntryType::ACCOUNT_KYC:
        case LedgerEntryType::ACCOUNT:
        case LedgerEntryType::ACCOUNT_RULE:
        case LedgerEntryType::ACCOUNT_ROLE:
        case LedgerEntryType::BALANCE:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        case LedgerEntryType::FEE:
        case LedgerEntryType::LIMITS_V2:
        case LedgerEntryType::ASSET_PAIR:
        case LedgerEntryType::TRANSACTION:
        case LedgerEntryType::LICENSE:
        case LedgerEntryType::STAMP:
        case LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
            return true;
        default:
            return false;
    }

}
}
