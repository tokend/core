#include "RuleVerifier.h"

namespace stellar
{

bool
RuleVerifier::isActionMatches(const std::string &expectedAction,
                              const std::string &actualAction) const
{
    return isStringMatches(expectedAction, actualAction);
}

bool
RuleVerifier::isStringMatches(std::string const &expectedStr,
                              std::string const &actualStr) const
{
    return (expectedStr == actualStr) || (actualStr == "*");
}

bool
RuleVerifier::isTypeMatches(uint64_t const expectedType,
                            uint64_t const actualType) const
{
    return isNumberMatches(expectedType, actualType);
}

bool
RuleVerifier::isType32Matches(uint32_t const expectedType,
                              uint32_t const actualType) const
{
    return isNumber32Matches(expectedType, actualType);
}

bool
RuleVerifier::isIDMatches(uint64_t const expectedID,
                          uint64_t const actualID) const
{
    return isNumberMatches(expectedID, actualID);
}

bool
RuleVerifier::isNumberMatches(uint64_t const expectedNum,
                              uint64_t const actualNum) const
{
    return (expectedNum == actualNum) || (actualNum == UINT64_MAX);
}

bool
RuleVerifier::isNumber32Matches(uint32_t const expectedNum,
                                uint32_t const actualNum) const
{
    return (expectedNum == actualNum) || (actualNum == UINT32_MAX);
}

bool
RuleVerifier::isAssetMatches(AssetFields expectedAsset, AssetFields actualAsset) const
{
    return isTypeMatches(expectedAsset.type, actualAsset.type) &&
           isStringMatches(expectedAsset.code, actualAsset.code);
}

bool
RuleVerifier::isTasksMatch(uint64_t const expectedTasks, uint64_t const actualTasks,
                           LedgerVersion const& ledgerVersion) const
{
    if(ledgerVersion >= LedgerVersion::FIX_CHANGE_ROLE_REQUEST_REQUESTOR)
    {
        return (expectedTasks & actualTasks) == expectedTasks;
    }
    else
    {
        if (expectedTasks == 0)
        {
            return true;
        }

        return (expectedTasks | actualTasks) == expectedTasks;
    }
}

bool
RuleVerifier::isBoolMatches(bool const expected, bool const actual) const
{
    return actual == expected;
}

} // namespace stellar