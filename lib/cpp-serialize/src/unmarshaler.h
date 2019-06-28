#pragma once

#include <sstream>
#include <array>
#include <vector>
#include <memory>
#include "types.h"

namespace xdr
{
class xdr_abstract;

class unmarshaler
{
    const uint8_t* current;
    const uint8_t* const end;

    std::ostringstream error;

public:
    unmarshaler(const uint8_t* start, const uint8_t* end);
    unmarshaler(char* start, char* end);

    std::string
    get_error();

    void
    done();

    bool
    from_bytes(uint64_t& value);

    bool
    from_bytes(int64_t& value);

    bool
    from_bytes(uint32_t& value);

    bool
    from_bytes(int32_t& value);

    bool
    from_bytes(bool& values);

    bool
    from_bytes(xdr_abstract& value);

    template<typename T, uint32_t N>
    bool
    from_bytes(xdr::xarray<T, N>& value);

    template<uint32_t bytesNum>
    bool
    from_bytes(xdr::xarray<uint8_t, bytesNum>& value);

    template<typename T>
    bool
    from_bytes(std::vector<T>& value);

    bool
    from_bytes(std::vector<uint8_t>& value);

    bool
    from_bytes(std::string& value);

    template<typename T>
    bool
    from_bytes(std::unique_ptr<T>& value);

    template<class T,class=typename std::enable_if< std::is_enum<T>::value >::type>
    bool
    from_bytes(T& value)
    {
        int32_t raw;
        if (!from_bytes(raw))
        {
            error << "failed to fill int32_t";
            return false;
        }

        value = static_cast<T>(value);

        return true;
    }
};

}
