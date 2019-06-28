#include "measurer.h"

namespace xdr
{
measurer::measurer() : current(0)
{
}

void
measurer::count_size(uint64_t v)
{
    current += 8;
}

void
measurer::count_size(int64_t v)
{
    current += 8;
}

void
measurer::count_size(uint32_t v)
{
    current += 4;
}

void
measurer::count_size(int32_t v)
{
    current += 4;
}

void
measurer::count_size(bool v)
{
    current += 4;
}

void
measurer::count_size(const xdr::xdr_abstract &v)
{
    v.count_size(*this);
}

void
measurer::count_size(std::string const& value)
{
    size_t actualSize = value.size();
    uint32_t extraSize = (4 - (actualSize % 4)) % 4;

    current += actualSize + extraSize + 4;
}

void
measurer::count_size(std::vector<uint8_t> const& value)
{
    size_t actualSize = value.size();
    uint32_t extraSize = (4 - (actualSize % 4)) % 4;

    current += actualSize + extraSize + 4;
}
}
