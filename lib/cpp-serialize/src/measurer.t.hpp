#include "measurer.h"

namespace xdr
{
template <typename T>
void measurer::count_size(const std::unique_ptr<T> &v)
{
    current += 4;

    if (!v)
    {
        return;
    }

    count_size(*v);
}

template<typename T, uint32_t N>
void
measurer::count_size(xdr::xvector<T, N> const& value)
{
    current += 4;

    for (T const & elem : value)
    {
        count_size(elem);
    }
}

template <uint32_t N>
void
measurer::count_size(xdr::xarray<uint8_t, N> const& value)
{
    uint32_t extraBytes = (4 - (N % 4)) % 4;

    current += N + extraBytes;
}

template <typename T, uint32_t N>
void
measurer::count_size(xdr::xarray<T, N> const& value)
{
    for (T const & elem : value)
    {
        count_size(elem);
    }
}

template<uint32_t N>
void
measurer::count_size(xdr::xvector<uint8_t, N> const& value)
{
    size_t actualSize = value.size();
    uint32_t extraSize = (4 - (actualSize % 4)) % 4;

    current += actualSize + extraSize + 4;
}
}