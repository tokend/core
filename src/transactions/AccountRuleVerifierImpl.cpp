#include <ledger/AccountRoleFrame.h>
#include <ledger/AccountRoleHelper.h>
#include <ledger/AccountRuleFrame.h>
#include <ledger/AccountRuleHelper.h>
#include "AccountRuleVerifierImpl.h"
#include "ledger/StorageHelper.h"

namespace stellar
{

AccountRuleVerifierImpl::AccountRuleVerifierImpl(StorageHelper &storageHelper)
        : mStorageHelper(storageHelper)
{
}

bool
AccountRuleVerifierImpl::isAllowed(OperationCondition& condition)
{
    auto& accountRoleHelper = mStorageHelper.getAccountRoleHelper();
    auto& accountRuleHelper = mStorageHelper.getAccountRuleHelper();

    if (!condition.account->getAccountRole())
    {
        return false; // accounts with no role assigned will fail the check
    }

    auto accountRoleFrame = accountRoleHelper.loadAccountRole(*condition.account->getAccountRole());
    if (!accountRoleFrame)
    {
        CLOG(ERROR, Logging::OPERATION_LOGGER) << "Unexpected state. "
                     << "Expected account role entry to exists. AccountRoleID: "
                     << *condition.account->getAccountRole();
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
            if (conditionResource.asset().assetType != actualResource.asset().assetType)
            {
                return false;
            }

            return isStringMatches(conditionResource.asset().assetCode,
                                   actualResource.asset().assetCode);
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID:
        case LedgerEntryType::EXTERNAL_SYSTEM_ACCOUNT_ID_POOL_ENTRY:
        case LedgerEntryType::KEY_VALUE:
            return true;
        default:
            return false;
    }

}

}