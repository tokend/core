// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "util/types.h"
#include "lib/util/uint128_t.h"
#include <locale>
#include <algorithm>
#include "util/XDROperators.h"
#include <locale>
#include "lib/json/json.h"
#include "lib/util/format.h"

namespace stellar
{

bool
isZero(uint256 const& b)
{
    for (auto i : b)
        if (i != 0)
            return false;

    return true;
}

Hash&
operator^=(Hash& l, Hash const& r)
{
    std::transform(l.begin(), l.end(), r.begin(), l.begin(),
                   [](uint8_t a, uint8_t b) -> uint8_t { return a ^ b; });
    return l;
}

bool
lessThanXored(Hash const& l, Hash const& r, Hash const& x)
{
    Hash v1, v2;
    for (size_t i = 0; i < l.size(); i++)
    {
        v1[i] = x[i] ^ l[i];
        v2[i] = x[i] ^ r[i];
    }

    return v1 < v2;
}

bool
isString32Valid(std::string const& str)
{
    auto& loc = std::locale::classic();
    for (auto c : str)
    {
        if (c < 0 || std::iscntrl(c, loc))
        {
            return false;
        }
    }
    return true;
}

bool isAlNum(std::string const& str) {
	for (auto c : str) {
		if (c < 0 || !std::isalnum(c, std::locale::classic()))
			return false;
	}

	return true;
}

int32 getAnyAssetPolicy()
{
	auto allAssetPolicies = xdr::xdr_traits<AssetPolicy>::enum_values();
	int32 result = 0;
	for (auto assetPolicy : allAssetPolicies)
	{
		result |= assetPolicy;
	}

	return result;
}

int32 getAnyAssetPairPolicy()
{
	auto allAssetPairPolicies = xdr::xdr_traits<AssetPairPolicy>::enum_values();
	int32 result = 0;
	for (auto assetPairPolicy : allAssetPairPolicies)
	{
		result |= assetPairPolicy;
	}

	return result;
}

bool isValidManageAssetAction(ManageAssetAction action)
{
	auto all = xdr::xdr_traits<ManageAssetAction>::enum_values();
	for (auto validAction : all)
	{
		if (validAction == static_cast<int32_t >(action))
			return true;
	}

	return false;
}

bool isValidManageAssetPairAction(ManageAssetPairAction action)
{
	auto all = xdr::xdr_traits<ManageAssetPairAction>::enum_values();
	for (auto validAction : all)
	{
		if (validAction == static_cast<int32_t >(action))
			return true;
	}

	return false;
}

std::vector<FeeType> getAllFeeTypes()
{
	auto allFeeTypes = xdr::xdr_traits<FeeType>::enum_values();
	std::vector<FeeType> result;
	for (auto rawFeeType : allFeeTypes)
	{
		result.push_back(FeeType(rawFeeType));
	}

	return result;
}

bool isFeeTypeValid(FeeType feeType)
{
	auto allFeeTypes = xdr::xdr_traits<FeeType>::enum_values();
	for (auto rawFeeType : allFeeTypes)
	{
		if (rawFeeType == static_cast<int32_t>(feeType))
			return true;
	}

	return false;
}

int32_t
unsignedToSigned(uint32_t v)
{
    if (v > static_cast<uint32_t>(std::numeric_limits<int32_t>::max()))
        throw std::runtime_error("unsigned-to-signed overflow");
    return static_cast<int32_t>(v);
}

int64_t
unsignedToSigned(uint64_t v)
{
    if (v > static_cast<uint64_t>(std::numeric_limits<int64_t>::max()))
        throw std::runtime_error("unsigned-to-signed overflow");
    return static_cast<int64_t>(v);
}

std::string
formatSize(size_t size)
{
    const std::vector<std::string> suffixes = {"B", "KB", "MB", "GB"};
    double dsize = static_cast<double>(size);

    auto i = 0;
    while (dsize >= 1024 && i < suffixes.size() - 1)
    {
        dsize /= 1024;
        i++;
    }

    return fmt::format("{:.2f}{}", dsize, suffixes[i]);
}

// calculates A*B/C when A*B overflows 64bits, with optional rounding step
bool
bigDivide(int64_t& result, int64_t A, int64_t B, int64_t C,
          Rounding rounding, uint64_t roundingStep)
{
    bool res;
    assert((A >= 0) && (B >= 0) && (C > 0));
    uint64_t r2;
    res = bigDivide(r2, (uint64_t)A, (uint64_t)B, (uint64_t)C,
                    rounding, roundingStep);
    if (res)
    {
        res = r2 <= INT64_MAX;
        result = r2;
    }
    return res;
}

bool
bigDivide(uint64_t& result, uint64_t A, uint64_t B, uint64_t C,
          Rounding rounding, uint64_t roundingStep)
{
    // update when moving to (signed) int128
    uint128_t a(A);
    uint128_t b(B);
    uint128_t c(C);
    uint128_t x(0);
    uint128_t r(roundingStep);
    if (rounding == ROUND_DOWN)
	{
    	x = (a * b) / c;
    	x -= x % r;
	}
	else
	{
		x = (a * b + c - 1) / c;
		if (x % r != 0)
		{
			x += r - (x % r);
		}
	}

    result = (uint64_t)x;

    return (x <= UINT64_MAX);
}

bool safeSum(uint64_t a, uint64_t b, uint64_t& result)
{
	result = a + b;
	return result >= a && result >= b;
}

bool safeSum(uint64_t& result, std::vector<uint64_t> params)
{
    result = 0;
    for (auto a : params)
    {
        const uint64_t b = result;
        if (!safeSum(a, b, result))
        {
            return false;
        }
    }

    return true;
}

uint64_t safeDelta(uint64_t a, uint64_t b){
	uint64_t res;
	res = a > b ? a - b : b - a;
	return res;
}

int64_t
bigDivide(int64_t A, int64_t B, int64_t C, Rounding rounding, uint64_t roundingStep)
{
    int64_t res;
    if (!bigDivide(res, A, B, C, rounding, roundingStep))
    {
        throw std::overflow_error("overflow while performing bigDivide");
    }
    return res;
}

bool
iequals(std::string const& a, std::string const& b)
{
    size_t sz = a.size();
    if (b.size() != sz)
        return false;
    for (size_t i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

bool isValidJson(std::string strJson)
{
    // get parser with strict configuration
    Json::Features features = Json::Features::strictMode();
    Json::Reader reader(features);

    Json::Value root;
    if (!reader.parse(strJson, root, false))
        return false;

    return root.isObject();
}
}
