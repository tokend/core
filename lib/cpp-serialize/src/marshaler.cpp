
#include "marshaler.h"
#include "xdr_abstract.h"

namespace xdr
{

marshaler::marshaler(const uint8_t * start, const uint8_t * end)
{
    bytes.assign(start, end);
}

marshaler::marshaler(char *start, char *end)
        : marshaler((const uint8_t*)start, (const uint8_t*)end)
{
}

std::string
marshaler::get_error()
{
    return error.str();
}

bool
marshaler::to_bytes(uint64_t const value)
{
    uint8_t buf[8];
    buf[0] = value >> 56;
    buf[1] = value >> 48;
    buf[2] = value >> 40;
    buf[3] = value >> 32;
    buf[4] = value >> 24;
    buf[5] = value >> 16;
    buf[6] = value >> 8;
    buf[7] = value;

    bytes.insert(bytes.end(), buf, buf + 8);

    return true;
}

bool
marshaler::to_bytes(int64_t value)
{
    uint8_t buf[8];
    buf[0] = value >> 56;
    buf[1] = value >> 48;
    buf[2] = value >> 40;
    buf[3] = value >> 32;
    buf[4] = value >> 24;
    buf[5] = value >> 16;
    buf[6] = value >> 8;
    buf[7] = value;

    bytes.insert(bytes.end(), buf, buf + 8);

    return true;
}

bool
marshaler::to_bytes(uint32_t value)
{
    uint8_t buf[4];
    buf[0] = value >> 24;
    buf[1] = value >> 16;
    buf[2] = value >> 8;
    buf[3] = value;

    bytes.insert(bytes.end(), buf, buf + 4);

    return true;
}

bool
marshaler::to_bytes(int32_t value)
{
    uint8_t buf[4];
    buf[0] = value >> 24;
    buf[1] = value >> 16;
    buf[2] = value >> 8;
    buf[3] = value;

    bytes.insert(bytes.end(), buf, buf + 4);

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
    uint64_t bytesNum  = value.size();
    if (bytesNum > INT32_MAX)
    {
        error << "bytes vector length overflow ";
        return false;
    }

    if (!to_bytes(uint32_t(bytesNum)))
    {
        return false;
    }

    bytes.insert(bytes.end(), value.begin(), value.end());

    uint32_t extraBytes = (4 - (bytesNum % 4)) % 4;

    for (uint32_t i = 0; i < extraBytes; i++)
    {
        bytes.emplace_back(0);
    }

    return true;
}


bool
marshaler::to_bytes(std::string const&value)
{
    bytes.insert(bytes.end(), value.begin(), value.end());

    return false;
}

}