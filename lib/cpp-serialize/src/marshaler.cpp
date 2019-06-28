
#include <iostream>
#include "marshaler.h"
#include "xdr_abstract.h"

namespace xdr
{

marshaler::marshaler(uint8_t * start, uint8_t * end) : bytes(start), end(end)
{
}

marshaler::marshaler(char *start, char *end)
        : marshaler((uint8_t*)start, (uint8_t*)end)
{
}

std::string
marshaler::get_error()
{
    return error.str();
}


void
marshaler::done()
{
    if (bytes != end)
    {
        throw std::runtime_error("Expected current to be equal end");
    }
}


bool
marshaler::to_bytes(uint64_t const value)
{
    //uint8_t buf[8];
    bytes[pos++] = value >> 56;
    bytes[pos++] = value >> 48;
    bytes[pos++] = value >> 40;
    bytes[pos++] = value >> 32;
    bytes[pos++] = value >> 24;
    bytes[pos++] = value >> 16;
    bytes[pos++] = value >> 8;
    bytes[pos++] = value;

    //bytes.insert(bytes.end(), buf, buf + 8);

    return true;
}

bool
marshaler::to_bytes(int64_t value)
{
    //uint8_t buf[8];
    bytes[pos++] = value >> 56;
    bytes[pos++] = value >> 48;
    bytes[pos++] = value >> 40;
    bytes[pos++] = value >> 32;
    bytes[pos++] = value >> 24;
    bytes[pos++] = value >> 16;
    bytes[pos++] = value >> 8;
    bytes[pos++] = value;

    //bytes.insert(bytes.end(), buf, buf + 8);

    return true;
}

bool
marshaler::to_bytes(uint32_t value)
{
    //uint8_t buf[4];
    bytes[pos++] = value >> 24;
    bytes[pos++] = value >> 16;
    bytes[pos++] = value >> 8;
    bytes[pos++] = value;

    //bytes.insert(bytes.end(), buf, buf + 4);

    return true;
}

bool
marshaler::to_bytes(int32_t value)
{
    //uint8_t buf[4];
    bytes[pos++] = value >> 24;
    bytes[pos++] = value >> 16;
    bytes[pos++] = value >> 8;
    bytes[pos++] = value;

    //bytes.insert(bytes.end(), buf, buf + 4);

    return true;
}

bool
marshaler::to_bytes(bool value)
{
    return to_bytes(int32_t(value));
}

bool
marshaler::to_bytes(xdr::xdr_abstract const& value)
{
    return value.to_bytes(*this);
}

bool
marshaler::to_bytes(std::vector<uint8_t> const& value)
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


bool
marshaler::to_bytes(std::string const&value)
{
    std::vector<uint8_t> vec(value.begin(), value.end());

    return to_bytes(vec);
}

}