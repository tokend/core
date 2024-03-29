#pragma once

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "lib/util/uint128_t.h"
#include "overlay/StellarXDR.h"
#include "xdrpp/message.h"
#include <type_traits>
#include <vector>

namespace stellar
{

const int64 ONE = 1000000LL;

enum Rounding
{
	ROUND_DOWN,
	ROUND_UP
};

typedef std::vector<unsigned char> Blob;

bool isZero(uint256 const& b);

Hash& operator^=(Hash& l, Hash const& r);

// returns the int32_t of a non-negative uint32_t if it fits,
// otherwise throws.
int32_t unsignedToSigned(uint32_t v);
// returns the int64_t of a non-negative uint64_t if it fits,
// otherwise throws.
int64_t unsignedToSigned(uint64_t v);
std::string formatSize(size_t size);

// returns true if ( l ^ x ) < ( r ^ x)
bool lessThanXored(Hash const& l, Hash const& r, Hash const& x);

// returns true if the passed string32 is valid
bool isString32Valid(std::string const& str);

bool isValidManageAssetPairAction(ManageAssetPairAction action);
bool isValidManageAssetAction(ManageAssetAction action);

int32 getAnyAssetPairPolicy();

std::vector<FeeType> getAllFeeTypes();
// returns true, if passed opType is valid operation type

bool isFeeTypeValid(FeeType feeType);

// Returns true, if flag value is valid. (Does not contains any values which do not belongs to FlagType)
template <typename FlagType>
bool isValidXDRFlag(int32 value)
{
	for (auto flagElem : xdr::xdr_traits<FlagType>::enum_values()) {
		value &= ~flagElem;
	}

	return value == 0;
}

// Returns true, if enum value valid
template <typename EnumType>
bool isValidEnumValue(EnumType value)
{
	auto enums = xdr::xdr_traits<EnumType>::enum_values();
	return std::find(std::begin(enums), std::end(enums), static_cast<int32_t>(value)) != std::end(enums);
}

template <typename EnumType>
bool isSetFlag(uint32 value, EnumType flag)
{
    uint32 flagValue = static_cast<uint32>(flag);
    return (flagValue & value) == flagValue;
}

// returns true if strJson is a valid json
bool isValidJson(std::string strJson);

// returns true if result is valid (no overflow)
bool safeSum(uint64_t a, uint64_t b, uint64_t& result);
bool safeSum(uint64_t& result, std::vector<uint64_t> params);

uint64_t safeDelta(uint64_t a, uint64_t b);

// calculates A*B/C when A*B overflows 64bits
int64_t bigDivide(int64_t A, int64_t B, int64_t C, Rounding rounding,
                  uint64_t roundingStep = 1);
// no throw version, returns true if result is valid
bool bigDivide(int64_t& result, int64_t A, int64_t B, int64_t C, Rounding rounding,
               uint64_t roundingStep = 1);

// no throw version, returns true if result is valid
bool bigDivide(uint64_t& result, uint64_t A, uint64_t B, uint64_t C, Rounding rounding,
               uint64_t roundingStep = 1);

bool iequals(std::string const& a, std::string const& b);
}
