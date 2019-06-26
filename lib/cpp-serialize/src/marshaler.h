#pragma once

#include <vector>
#include <array>
#include <sstream>
#include <memory>
#include "types.h"

namespace xdr
{
class xdr_abstract;

class marshaler
{
    std::vector<uint8_t> bytes;
    std::ostringstream error;

public:
    marshaler() = default;

    marshaler(const uint8_t * start, const uint8_t * end);
    marshaler(char * start, char * end);

    std::string
    get_error();

    bool
    to_bytes(uint64_t value);

    bool
    to_bytes(int64_t value);

    bool
    to_bytes(uint32_t value);

    bool
    to_bytes(int32_t value);

    bool
    to_bytes(bool value);

    bool
    to_bytes(xdr_abstract const& value);

    template <class T,class=typename std::enable_if< std::is_enum<T>::value >::type>
    bool
    to_bytes(T& value)
    {
        return to_bytes(int32_t(value));
    }

    template<typename T, uint32_t N>
    bool
    to_bytes(xdr::xarray<T, N> const& value);

    template<uint32_t N>
    bool
    to_bytes(xdr::xarray<uint8_t , N> const& value);

    template<typename T, uint32_t N = XDR_MAX_LEN>
    bool
    to_bytes(xdr::xvector<T, N> const& value);

    bool
    to_bytes(std::vector<uint8_t> const& value);

    bool
    to_bytes(std::string const& value);

    template<typename T>
    bool
    to_bytes(std::unique_ptr<T> const& value);
};

}
