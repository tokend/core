#pragma once

#include <string>
#include <vector>
#include <xdr/types.h>

namespace stellar
{

struct AssetFields
{
    AssetCode code;
    uint64_t  type;
};

class RuleVerifier {
protected:
    bool
    isActionMatches(std::string const &a, std::string const &b) const;

    bool
    isStringMatches(std::string const& a, std::string const& b) const;

    bool
    isTypeMatches(uint64_t const expectedType, uint64_t const actualType) const;

    bool
    isType32Matches(uint32_t const expectedType, uint32_t const actualType) const;

    bool
    isIDMatches(uint64_t const expectedID, uint64_t const actualID) const;

    bool
    isNumberMatches(uint64_t const expectedNum, uint64_t const actualNum) const;

    bool
    isNumber32Matches(uint32_t const expectedNum, uint32_t const actualNum) const;

    bool
    isAssetMatches(AssetFields expectedAsset, AssetFields actualAsset) const;

    bool
    isTasksMatch(uint64_t const expectedTasks, uint64_t const actualTasks) const;

    bool
    isBoolMatches(bool const expected, bool const actual) const;
};

} // namespace stellar
