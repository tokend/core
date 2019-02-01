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
RuleVerifier::isAssetMatches(AssetFields expectedAsset, AssetFields actualAsset) const
{
    return isTypeMatches(expectedAsset.type, actualAsset.type) &&
           isStringMatches(expectedAsset.code, actualAsset.code);
}

bool
RuleVerifier::isTasksMatch(uint32_t const expectedTasks, uint32_t const actualTasks) const
{
    return (expectedTasks | actualTasks) == expectedTasks;
}

} // namespace stellar