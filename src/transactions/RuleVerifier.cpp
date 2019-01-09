#include "RuleVerifier.h"

bool
RuleVerifier::isActionAppropriate(const std::string &expectedAction,
                                  const std::string &actualAction) const
{
    return (expectedAction == actualAction) || (actualAction == "*");
}