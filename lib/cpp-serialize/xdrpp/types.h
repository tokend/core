#pragma once

#include "../src/types.h"

namespace xdr
{

#define xdr_strerror std::strerror

template<typename T> struct xdr_traits;

template<typename T, typename U> struct xdr_integral_base
{
    using type = T;
    using uint_type = U;

};



#if XDRPP_WORDS_BIGENDIAN
Constexpr const bool is_big_endian = true;
#else // !XDRPP_WORDS_BIGENDIAN
constexpr const bool is_big_endian = false;
#endif // !XDRPP_WORDS_BIGENDIAN

constexpr inline std::uint32_t
swap32(std::uint32_t v)
{
    return v << 24 | (v & 0xff00) << 8 | (v >> 8 & 0xff00) | v >> 24;
}
constexpr inline std::uint32_t
swap32le(std::uint32_t v)
{
    return xdr::is_big_endian ? v : swap32(v);
}
}