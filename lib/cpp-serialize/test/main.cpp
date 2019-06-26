#include <iostream>
#include <zconf.h>
#include "../src/unmarshaler.h"
#include "types.h"
#include "../src/types.h"
#include "CreateAccountOp.h"
#include "../src/types.h"
#include "../src/marshaler.h"
#include "../src/unmarshaler.t.hpp"

using namespace xdr;
//using ::operator==;

int main()
{
    std::string rawBytes = "0 0 0 0 247 116 26 171 105 15 163 34 134 165 251 114 136 60 198 78 62 35 10 233 249 254 99 32 245 220 206 176 251 20 236 107 0 0 0 1 0 0 0 0 29 193 182 70 212 64 28 216 140 163 181 116 238 18 232 132 205 92 119 223 245 89 78 20 138 38 133 93 68 183 91 114 0 0 0 0 0 0 0 4 0 0 0 2 0 0 0 0 247 116 26 171 105 15 163 34 134 165 251 114 136 60 198 78 62 35 10 233 249 254 99 32 245 220 206 176 251 20 236 107 0 0 0 0 0 0 0 1 0 0 3 232 0 0 0 123 0 0 0 16 123 100 97 116 97 32 58 32 123 97 32 58 32 52 125 125 0 0 0 0 0 0 0 0 29 193 182 70 212 64 28 216 140 163 181 116 238 18 232 132 205 92 119 223 245 89 78 20 138 38 133 93 68 183 91 114 0 0 0 0 0 0 0 2 0 0 3 232 0 0 0 124 0 0 0 16 123 100 97 116 97 32 58 32 123 97 32 58 32 53 125 125 0 0 0 0 0 0 0 0]";

    std::vector<uint8_t> vec;

    std::istringstream is( rawBytes );

    uint32_t x;
    while (is >> x)
    {
        //std::cout << x << std::endl;
        vec.emplace_back(uint8_t(x));
    }

    unmarshaler u(vec.data(), vec.data() + vec.size());

    CreateAccountOp actual;
    u.from_bytes(actual);

    u.done();

    CreateAccountOp expected;

/*
    if (::operator==(expected.referrer, actual.referrer))
    {
        std::cout << "yay0" << std::endl;
    }*/

    if (expected == actual)
    {
        std::cout << "yay" << std::endl;
    }

    if (actual.destination.type() != CryptoKeyType::KEY_TYPE_ED25519)
    {
        throw std::runtime_error("aaaa");
    }

    std::cout << actual.signersData[0].roleID << std::endl;

/*
    xdr::xarray<PublicKey, 2> arr;
    marshaler m;
    m.to_bytes(arr);*/

    return 0;
}

