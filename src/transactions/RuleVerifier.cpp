#include "RuleVerifier.h"

namespace stellar
{

bool
RuleVerifier::isActionMatches(const std::string &expectedAction,
                              const std::string &actualAction) const
{
    if (isStringMatches(expectedAction, actualAction))
    {
        return true;
    }

    if (expectedAction == "*")
    {
        return false;
    }

    std::vector<std::string> possibleActions{"manage", "use"};

    for (auto& possibleAction : possibleActions)
    {
        if (actualAction == possibleAction)
        {
            return true;
        }

        if (expectedAction == possibleAction)
        {
            return false;
        }
    }

    return false;
}

bool
RuleVerifier::isStringMatches(std::string const &expectedStr,
                              std::string const &actualStr) const
{
    return (expectedStr == actualStr) || (actualStr == "*");
}

} // namespace stellar