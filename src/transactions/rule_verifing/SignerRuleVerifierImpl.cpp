#include "SignerRuleVerifierImpl.h"
#include "ledger/SignerRoleHelper.h"
#include "ledger/SignerRuleHelper.h"
#include "ledger/StorageHelper.h"
#include <transactions/OperationFrame.h>

namespace stellar
{

bool
SignerRuleVerifierImpl::isAllowed(const SignerRequirement& requirement,
                                  SignerFrame::pointer signer,
                                  StorageHelper& storageHelper)
{
    if (!signer)
    {
        throw std::runtime_error(
            "Expected signer ro exists on signer rule verifying");
    }

    auto& signerRoleHelper = storageHelper.getSignerRoleHelper();

    auto signerRoleFrame = signerRoleHelper.loadSignerRole(signer->getRoleID());
    if (!signerRoleFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER)
            << "Unexpected state. "
            << "Expected signer role entry to exists. SignerRoleID: "
            << signer->getRoleID();
        throw std::runtime_error(
            "Unexpected state. Expected signer role to exists.");
    }

    auto& signerRuleHelper = storageHelper.getSignerRuleHelper();
    auto signerRuleFrames =
        signerRuleHelper.loadSignerRules(signerRoleFrame->getRuleIDs());

    bool isAllowed = false;

    for (auto signerRuleFrame : signerRuleFrames)
    {
        if (!isResourceMatches(requirement.resource,
                               signerRuleFrame->getResource()))
        {
            continue;
        }

        if (!isSignerRuleActionMatches(requirement.action,
                                       signerRuleFrame->getAction()))
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
    SignerRuleAction const requiredAction, SignerRuleAction const actualAction)
{
    return (requiredAction == actualAction) ||
           (actualAction == SignerRuleAction::ANY);
}

bool
SignerRuleVerifierImpl::isResourceMatches(
    SignerRuleResource const requiredResource,
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
    case LedgerEntryType::ATOMIC_SWAP_ASK:
        return isTypeMatches(requiredResource.atomicSwapAsk().assetType,
                             actualResource.atomicSwapAsk().assetType) &&
               isStringMatches(requiredResource.atomicSwapAsk().assetCode,
                               actualResource.atomicSwapAsk().assetCode);
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
        if (actualDetails.requestType() == ReviewableRequestType::ANY)
        {
            return true;
        }

        if (actualDetails.requestType() != expectedDetails.requestType())
        {
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
        case ReviewableRequestType::CREATE_ATOMIC_SWAP_BID:
        {
            auto expExt = expectedDetails.createAtomicSwapBidExt();
            auto actExt = actualDetails.createAtomicSwapBidExt();

            if (expExt.v() != actExt.v())
            {
                return false;
            }

            switch (expExt.v())
            {
            case LedgerVersion::EMPTY_VERSION:
                return true;
            case LedgerVersion::ATOMIC_SWAP_RETURNING:
                return isTypeMatches(expExt.createAtomicSwapBid().assetType,
                                     actExt.createAtomicSwapBid().assetType) &&
                       isStringMatches(expExt.createAtomicSwapBid().assetCode,
                                       actExt.createAtomicSwapBid().assetCode);
            default:
                throw new std::runtime_error(
                    "Unexpected ledger version "
                    "in create atomic swap bid rule ext");
            }
        }
        case ReviewableRequestType::CREATE_ATOMIC_SWAP_ASK:
        {
            auto expExt = expectedDetails.createAtomicSwapAskExt();
            auto actExt = actualDetails.createAtomicSwapAskExt();

            if (expExt.v() != actExt.v())
            {
                return false;
            }

            switch (expExt.v())
            {
            case LedgerVersion::EMPTY_VERSION:
                return true;
            case LedgerVersion::ATOMIC_SWAP_RETURNING:
                return isTypeMatches(expExt.createAtomicSwapAsk().assetType,
                                     actExt.createAtomicSwapAsk().assetType) &&
                       isStringMatches(expExt.createAtomicSwapAsk().assetCode,
                                       actExt.createAtomicSwapAsk().assetCode);
            default:
                throw new std::runtime_error(
                    "Unexpected ledger version "
                    "in create atomic swap ask rule ext");
            }
        }
        case ReviewableRequestType::MANAGE_OFFER:
        {
            auto expected = expectedDetails.manageOffer();
            auto actual = actualDetails.manageOffer();

            return isTypeMatches(expected.baseAssetType,
                                 actual.baseAssetType) &&
                   isStringMatches(expected.baseAssetCode,
                                   actual.baseAssetCode) &&
                   isTypeMatches(expected.quoteAssetType,
                                 actual.quoteAssetType) &&
                   isStringMatches(expected.quoteAssetCode,
                                   actual.quoteAssetCode) &&
                   isType32Matches(expected.manageAction,
                                   actual.manageAction) &&
                   isBoolMatches(expected.isBuy, actual.isBuy);
        }

        case ReviewableRequestType::CREATE_PAYMENT:
        {
            auto expected = expectedDetails.createPayment();
            auto actual = actualDetails.createPayment();

            return isTypeMatches(expected.assetType, actual.assetType) &&
                   isStringMatches(expected.assetCode, actual.assetCode);
        }
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
    case LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
    {
        switch (requiredResource.accountSpecificRuleExt().v())
        {
        case LedgerVersion::EMPTY_VERSION:
            return true;
        case LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
        {
            if (requiredResource.accountSpecificRuleExt().v() !=
                actualResource.accountSpecificRuleExt().v())
            {
                return false;
            }

            if (requiredResource.accountSpecificRuleExt()
                    .accountSpecificRule()
                    .ledgerKey.type() == LedgerEntryType::ANY)
            {
                return true;
            }

            if (requiredResource.accountSpecificRuleExt()
                    .accountSpecificRule()
                    .ledgerKey.type() != actualResource.accountSpecificRuleExt()
                                             .accountSpecificRule()
                                             .ledgerKey.type())
            {
                return false;
            }

            auto conditionLedgerKey = requiredResource.accountSpecificRuleExt()
                                          .accountSpecificRule()
                                          .ledgerKey;
            auto actualLedgerKey = actualResource.accountSpecificRuleExt()
                                       .accountSpecificRule()
                                       .ledgerKey;
            switch (conditionLedgerKey.type())
            {
            case LedgerEntryType::SALE:
                return isIDMatches(conditionLedgerKey.sale().saleID,
                                   actualLedgerKey.sale().saleID);
            default:
                return false;
            }
        }
        }
    }
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
        return true;
    default:
        return false;
    }
}
}
