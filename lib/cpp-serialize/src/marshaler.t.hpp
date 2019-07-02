#include "marshaler.h"

namespace xdr 
{

template<typename T, uint32_t bytesNum>
bool
marshaler::to_bytes(xdr::xarray<T, bytesNum> const& value)
{
    for (auto& elem : value)
    {
        if (!to_bytes(elem))
        {
            return false;
        }
    }

    return true;
}

template<uint32_t bytesNum>
bool
marshaler::to_bytes(xdr::xarray<uint8_t, bytesNum> const& value)
{
    uint32_t extraBytes = (4 - (bytesNum % 4)) % 4;

    for (auto const byte : value)
    {
        bytes[pos++] = byte;
    }

    for (uint32_t i = 0; i < extraBytes; i++)
    {
        bytes[pos++] = 0;
    }

    return true;
}

template<uint32_t N>
bool
marshaler::to_bytes(xdr::xvector<uint8_t, N> const& value)
{
    uint64_t bytesNum = value.size();
    if (bytesNum > INT32_MAX)
    {
        error << "bytes vector length overflow ";
        return false;
    }

    if (!to_bytes(uint32_t(bytesNum)))
    {
        return false;
    }

    for (auto const byte : value)
    {
        bytes[pos++] = byte;
    }

    uint32_t extraBytes = (4 - (bytesNum % 4)) % 4;

    for (uint32_t i = 0; i < extraBytes; i++)
    {
        bytes[pos++] = 0;
    }

    return true;
}

template<typename T, uint32_t N>
bool
marshaler::to_bytes(xdr::xvector<T, N> const& value)
{
    uint64_t dataLen  = value.size();
    if (dataLen > INT32_MAX)
    {
        error << "vector length overflow ";
        return false;
    }

    if (!to_bytes(uint32_t(dataLen)))
    {
        return false;
    }

    for (auto& elem : value)
    {
        if (!to_bytes(elem))
        {
            return false;
        }
    }

    return true;
}

template<typename T>
bool
marshaler::to_bytes(std::unique_ptr<T> const& value)
{
    bool present = value != nullptr;
    if (!to_bytes(present))
    {
        return false;
    }

    if (!present)
    {
        return true;
    }

    if (!to_bytes(*value))
    {
        error << "failed to convert inner value to bytes ";
        return false;
    }

    return true;
}

}