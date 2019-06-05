#include <ledger/AccountRoleFrame.h>
#include <ledger/AccountRoleHelper.h>
#include <ledger/AccountRuleFrame.h>
#include <ledger/AccountRuleHelper.h>
#include "AccountRuleVerifierImpl.h"
#include "ledger/StorageHelper.h"

namespace stellar
{

bool
AccountRuleVerifierImpl::isAllowed(OperationCondition& condition,
                                   StorageHelper& storageHelper)
{
    if (!condition.account) 
    {
        throw std::runtime_error("Expected account ro exists on account rule verifying");
    }
    
    auto& accountRoleHelper = storageHelper.getAccountRoleHelper();
    auto& accountRuleHelper = storageHelper.getAccountRuleHelper();

    auto accountRoleFrame = accountRoleHelper.loadAccountRole(condition.account->getAccountRole());
    if (!accountRoleFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. "
                     << "Expected account role entry to exists. AccountRoleID: "
                     << condition.account->getAccountRole();
        throw std::runtime_error("Unexpected state. Expected account role entry to exists.");
    }

    auto accountRuleFrames = accountRuleHelper.loadAccountRules(
            accountRoleFrame->getRuleIDs());

    bool isAllowed = false;

    for (auto accountRuleFrame : accountRuleFrames)
    {
        bool resourceMatches = isResourceMatches(condition.resource, accountRuleFrame->getResource());

        if (!resourceMatches)
        {
            continue;
        }

        bool actionMatches = isAccountRuleActionMatches(condition.action, accountRuleFrame->getAction());

        if (!actionMatches)
        {
            continue;
        }

        if (accountRuleFrame->forbids())
        {
            return false;
        }

        isAllowed = true;
    }

    return isAllowed;
}

bool
AccountRuleVerifierImpl::isAccountRuleActionMatches(
        AccountRuleAction const conditionAction,
        AccountRuleAction const actualAction)
{
    return (conditionAction == actualAction) || (actualAction == AccountRuleAction::ANY);
}

bool
AccountRuleVerifierImpl::isResourceMatches(
        AccountRuleResource const conditionResource,
        AccountRuleResource const actualResource)
{
    if (actualResource.type() == LedgerEntryType::ANY)
    {
        return true;
    }

    if (actualResource.type() != conditionResource.type())
    {
        return false;
    }

    switch (conditionResource.type())
    {
        case LedgerEntryType::ASSET:
            return isTypeMatches(conditionResource.asset().assetType,
                                 actualResource.asset().assetType) &&
                   isStringMatches(conditionResource.asset().assetCode,
                                   actualResource.asset().assetCode);
        case LedgerEntryType::ATOMIC_SWAP_ASK:
            return isTypeMatches(conditionResource.atomicSwapAsk().assetType,
                                 actualResource.atomicSwapAsk().assetType) &&
                   isStringMatches(conditionResource.atomicSwapAsk().assetCode,
                                   actualResource.atomicSwapAsk().assetCode);
        case LedgerEntryType::REVIEWABLE_REQUEST:
        {
            auto expectedDetails = conditionResource.reviewableRequest().details;
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
                default:
                    return true;
            }
        }
        case LedgerEntryType::OFFER_ENTRY:
        {
            if (!isBoolMatches(conditionResource.offer().isBuy,
                               actualResource.offer().isBuy))
            {
                return false;
            }

            AssetFields expectedBase{conditionResource.offer().baseAssetCode,
                                     conditionResource.offer().baseAssetType};
            AssetFields expectedQuote{conditionResource.offer().quoteAssetCode,
                                      conditionResource.offer().quoteAssetType};
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
            return isTypeMatches(conditionResource.sale().saleType,
                                 actualResource.sale().saleType) &&
                   isIDMatches(conditionResource.sale().saleID,
                               actualResource.sale().saleID);
        case LedgerEntryType::KEY_VALUE:
            return isStringMatches(conditionResource.keyValue().keyPrefix,
                                   actualResource.keyValue().keyPrefix);
        case LedgerEntryType::POLL:
            return isType32Matches(conditionResource.poll().permissionType,
                                 actualResource.poll().permissionType) &&
                   isIDMatches(conditionResource.poll().pollID,
                               actualResource.poll().pollID);
        case LedgerEntryType::VOTE:
            return isType32Matches(conditionResource.vote().permissionType,
                                 actualResource.vote().permissionType) &&
                   isIDMatches(conditionResource.vote().pollID,
                               actualResource.vote().pollID);
        case LedgerEntryType::ACCOUNT_SPECIFIC_RULE:
        {
            switch (conditionResource.accountSpecificRuleExt().v())
            {
                case LedgerVersion::EMPTY_VERSION:
                    return true;
                case LedgerVersion::ADD_ACC_SPECIFIC_RULE_RESOURCE:
                {
                    if (conditionResource.accountSpecificRuleExt().v() != actualResource.accountSpecificRuleExt().v())
                    {
                        return false;
                    }

                    if (conditionResource.accountSpecificRuleExt().accountSpecificRule().ledgerKey.type() == LedgerEntryType::ANY)
                    {
                        return true;
                    }

                    if (conditionResource.accountSpecificRuleExt().accountSpecificRule().ledgerKey.type()
                        != actualResource.accountSpecificRuleExt().accountSpecificRule().ledgerKey.type())
                    {
                        return false;
                    }

                    auto conditionLedgerKey = conditionResource.accountSpecificRuleExt().accountSpecificRule().ledgerKey;
                    auto actualLedgerKey = actualResource.accountSpecificRuleExt().accountSpecificRule().ledgerKey;
                    switch (conditionLedgerKey.type())
                    {
                        case LedgerEntryType::SALE:
                            return isIDMatches(conditionLedgerKey.sale().saleID, actualLedgerKey.sale().saleID);
                        default:
                            return false;
                    }
                }
            }
        }
        case LedgerEntryType::ACCOUNT_KYC:
        case LedgerEntryType::ACCOUNT:
        case LedgerEntryType::ACCOUNT_RULE:
        case LedgerEntryType::ACCOUNT_ROLE:
        case LedgerEntryType::SIGNER:
        case LedgerEntryType::SIGNER_ROLE:
        case LedgerEntryType::SIGNER_RULE:
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
