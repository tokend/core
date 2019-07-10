
#include "unmarshaler.h"
#include "xdr_abstract.h"

namespace xdr
{

unmarshaler::unmarshaler(const uint8_t *start, const uint8_t *end)
        : current(start), end(end)
{
}

unmarshaler::unmarshaler(char *start, char *end)
    : current((const uint8_t*)start), end((const uint8_t*)end)
{
}

std::string
unmarshaler::get_error()
{
    return error.str();
}

void
unmarshaler::done()
{
    if (current != end)
    {
        throw std::runtime_error("Expected current to be equal end");
    }
}

bool
unmarshaler::from_bytes(uint64_t& value)
{
    uint32_t bytesNum = 8;
    if (bytesNum > (end - current))
    {
        error << "not enough bytes ";
        return false;
    }

    value = uint64_t(current[0])<<56 | uint64_t(current[1])<<48 |
            uint64_t(current[2])<<40 | uint64_t(current[3])<<32 |
            uint64_t(current[4])<<24 | uint64_t(current[5])<<16 |
            uint64_t(current[6])<<8 | uint64_t(current[7]);

    current += 8;

    return true;
}

bool
unmarshaler::from_bytes(int64_t& value)
{
    uint32_t bytesNum = 8;
    if (bytesNum > (end - current))
    {
        error << "not enough bytes ";
        return false;
    }

    value = int64_t(current[0])<<56 | int64_t(current[1])<<48 |
            int64_t(current[2])<<40 | int64_t(current[3])<<32 |
            int64_t(current[4])<<24 | int64_t(current[5])<<16 |
            int64_t(current[6])<<8 | int64_t(current[7]);

    current += bytesNum;

    return true;
}

bool
unmarshaler::from_bytes(uint32_t& value)
{
    uint32_t bytesNum = 4;
    if (bytesNum > (end - current))
    {
        error << "not enough bytes ";
        return false;
    }

    value = uint32_t(current[0])<<24 | uint32_t(current[1])<<16 |
            uint32_t(current[2])<<8 | uint32_t(current[3]);


    current += bytesNum;

    return true;
}

bool
unmarshaler::from_bytes(int32_t& value)
{
    uint32_t bytesNum = 4;
    if (bytesNum > (end - current))
    {
        error << "not enough bytes ";
        return false;
    }

    value = int32_t(current[0])<<24 | int32_t(current[1])<<16 |
            int32_t(current[2])<<8 | int32_t(current[3]);


    current += bytesNum;

    return true;
}

bool
unmarshaler::from_bytes(bool& value)
{
    int32_t result;
    if (!from_bytes(result))
    {
        error << "failed to fill int32";
        return false;
    }

    switch (result)
    {
        case 0:
            value = false;
            return true;
        case 1:
            value = true;
            return true;
        default:
            error << "unexpected value from int32: " << result << " ";
            return false;
    }
}

bool
unmarshaler::from_bytes(xdr_abstract& value)
{
    if (!value.from_bytes(*this))
    {
        error << "failed to fill value " << typeid(value).name() << " : ";
        return false;
    }

    return true;
}


bool
unmarshaler::from_bytes(std::string &value)
{
    std::vector<uint8_t> result;
    if (!from_bytes(result))
    {
        error << "failed to fill vector ";
        return false;
    }

    value.assign(result.begin(), result.end());

    return true;
}

bool
unmarshaler::from_bytes(std::vector<uint8_t>& value)
{
    uint32_t bytesNum;
    if (!from_bytes(bytesNum))
    {
        error << "failed to fill bytes number ";
        return false;
    }

    if (bytesNum > INT32_MAX)
    {
        error << "bytes number overflow ";
        return false;
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

    value.clear();

    for (uint32_t i = 0; i < bytesNum; i++)
    {
        value.emplace_back(*current);
        current++;
    }

    for (uint32_t i = 0; i < extraBytes; i++)
    {
        if (*current != 0x00)
        {
            error << "non zero extra byte ";
            return false;
        }

        current++;
    }

    return true;
}

}