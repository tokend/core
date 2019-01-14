#pragma once

#include <string>
#include <vector>
#include <xdr/Stellar-types.h>

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
    isAssetTypeMatches(uint64_t const expectedType, uint64_t const actualType) const;

    bool
    isAssetMatches(AssetFields expectedAsset, AssetFields actualAsset) const;
};

} // namespace stellar
