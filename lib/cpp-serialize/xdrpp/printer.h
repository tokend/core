#pragma once

#include "marshal.h"
//#include "src/marshaler.t.hpp"


namespace xdr
{
template<typename T>
std::string
xdr_to_string(const T &t, const char *name = nullptr, int indent = 0)
{
    auto vec = xdr_to_opaque(t);

    std::string result(vec.begin(), vec.end());
    return result;
}

template <uint32_t N>
inline  std::ostream &
operator<<(std::ostream &os, const opaque_array<N> &t)
{
    return os << xdr_to_string(t);
}
}