#pragma once

#include "types.h"

namespace xdr
{

class measurer
{
    size_t current;

public:
    measurer();

    void
    count_size(uint64_t v);

    void
    count_size(int64_t v);

    void
    count_size(uint32_t v);

    void
    count_size(int32_t v);

    void
    count_size(bool v);

    void
    count_size(xdr_abstract const& v);

    template<typename T>
    void
    count_size(std::unique_ptr<T> const& v);

    template<typename T, uint32_t N>
    void
    count_size(xdr::xarray<T, N> const& value);

    template<uint32_t N>
    void
    count_size(xdr::xarray<uint8_t , N> const& value);

    template<typename T, uint32_t N = XDR_MAX_LEN>
    void
    count_size(xdr::xvector<T, N> const& value);

    template<uint32_t N = XDR_MAX_LEN>
    void
    count_size(xdr::xvector<uint8_t, N> const& value);

    void
    count_size(std::string const& value);

    template <class T,class=typename std::enable_if< std::is_enum<T>::value >::type>
    void
    count_size(T const& value)
    {
        count_size(int32_t(value));
    }

    size_t
    get_size() const
    {
        return current;
    }
};


}
