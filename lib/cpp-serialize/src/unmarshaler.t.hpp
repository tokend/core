
#include "unmarshaler.h"

namespace xdr
{

template<typename T, uint32_t bytesNum>
bool
unmarshaler::from_bytes(xdr::xarray<T, bytesNum>& value)
{
    for (auto& elem : value)
    {
        if (!from_bytes(elem))
        {
            error << "failed to fill array elem ";
            return false;
        }
    }

    return true;
}

template<uint32_t bytesNum>
bool
unmarshaler::from_bytes(xdr::xarray<uint8_t, bytesNum>& value)
{
    if (bytesNum == 0)
    {
        return true;
    }

    uint32_t extraBytes = (4 - (bytesNum % 4)) % 4;
    uint32_t totalBytes = bytesNum + extraBytes;

    if (totalBytes > INT32_MAX)
    {
        error << "total bytes overflow ";
        return false;
    }

    if (totalBytes > (end - current))
    {
        error << "not enough bytes ";
        return false;
    }

    for (uint8_t& elem : value)
    {
        elem = *current;
        current++;
    }

    for (int i = 0; i < extraBytes; i++)
    {
        if (extraBytes != 0x00)
        {
            error << "non zero extra byte ";
            return false;
        }

        current++;
    }

    return true;
}

template<typename T>
bool
unmarshaler::from_bytes(std::vector<T>& value)
{
    uint32_t dataLen;
    if (!from_bytes(dataLen))
    {
        error << "failed to fill vector length ";
        return false;
    }

    if (dataLen > INT32_MAX)
    {
        error << "data length overflow ";
        return false;
    }

    value.clear();

    for (uint32_t i = 0; i < dataLen; i++)
    {
        T elem;
        if (!from_bytes(elem))
        {
            error << "failed to fill vector elem ";
            return false;
        }

        value.emplace_back(elem);
    }

    return true;
}




template<typename T>
bool
unmarshaler::from_bytes(std::unique_ptr<T>& value)
{
    bool present;
    if (!from_bytes(present))
    {
        error << "failed to fill bool ";
        return false;
    }

    if (!present)
    {
        return true;
    }

    T innerValue;
    if (!from_bytes(innerValue))
    {
        error << "failed to fill inner value";
        return false;
    }

    value = std::make_unique<T>(innerValue);

    return true;
}
}