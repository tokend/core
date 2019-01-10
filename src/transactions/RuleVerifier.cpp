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
RuleVerifier::isAssetTypeMatches(uint64_t const expectedType,
                                 uint64_t const actualType) const
{
    return (expectedType == actualType) || (actualType == UINT64_MAX);
}

} // namespace stellar