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
    uint8_t * bytes;
    uint8_t * end;
    std::ostringstream error;
    size_t pos{0};

public:
    marshaler() = default;

    marshaler(uint8_t * start, uint8_t * end);
    marshaler(char * start, char * end);

    std::string
    get_error();

    void
    done();

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

    template<uint32_t N = XDR_MAX_LEN>
    bool
    to_bytes(xdr::xvector<uint8_t, N> const& value);

    bool
    to_bytes(std::string const& value);

    template<typename T>
    bool
    to_bytes(std::unique_ptr<T> const& value);
};

}
