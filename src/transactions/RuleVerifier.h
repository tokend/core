#pragma once

#include <string>
#include <vector>

namespace stellar
{

class RuleVerifier {
protected:
    bool
    isActionMatches(std::string const &a, std::string const &b) const;

    bool
    isStringMatches(std::string const& a, std::string const& b) const;

    bool
    isAssetTypeMatches(uint64_t const expectedType, uint64_t const actualType) const;
};

} // namespace stellar
