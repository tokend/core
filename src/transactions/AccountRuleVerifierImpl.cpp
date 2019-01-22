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

        bool actionMatches = isActionMatches(condition.action, accountRuleFrame->getAction());

        if (!actionMatches)
        {
            continue;
        }

        if (accountRuleFrame->isForbid())
        {
            return false;
        }

        isAllowed = true;
    }

    return isAllowed;
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
                case ReviewableRequestType::SALE:
                    return isTypeMatches(expectedDetails.sale().type,
                                         actualDetails.sale().type);
                default:
                    return true;
            }
        }
        case LedgerEntryType::OFFER_ENTRY:
        {
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
                   isIDMatches(conditionResource.sale().saleType,
                               actualResource.sale().saleType);
        case LedgerEntryType::ACCOUNT_KYC:
        case LedgerEntryType::ACCOUNT:
        case LedgerEntryType::ACCOUNT_RULE:
        case LedgerEntryType::ACCOUNT_ROLE:
        case LedgerEntryType::BALANCE:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        case LedgerEntryType::KEY_VALUE:
            return true;
        default:
            return false;
    }

}

}