
#include <iostream>
#include "marshaler.h"
#include "xdr_abstract.h"
#include "marshaler.t.hpp"

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
    if (bytes + pos != end)
    {
        throw std::runtime_error("Expected bytes to be equal end" + std::to_string(uint64_t(bytes+pos)) + std::to_string(uint64_t(end)));
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
marshaler::to_bytes(std::string const&value)
{
    xdr::xvector<uint8_t> vec(value.begin(), value.end());

    return to_bytes(vec);
}

}