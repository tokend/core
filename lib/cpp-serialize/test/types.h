#pragma once

#include <array>
#include "../src/xdr_abstract.h"

namespace xdr
{

using uint256 = std::array<uint8_t, 32>;
using uint64 = uint64_t;
using uint32 = uint32_t;
using longstring = std::string;

enum class CryptoKeyType : std::int32_t {
    KEY_TYPE_ED25519 = 0,
};

enum class PublicKeyType : std::int32_t {
    PUBLIC_KEY_TYPE_ED25519 = 0,
};

class PublicKey : public xdr_abstract
{
private:
    int32_t type_;
    union
    {
        uint256 ed25519_;
    };

    bool
    from_bytes(unmarshaler& u) override;

    bool
    to_bytes(marshaler& m) override;

public:
    CryptoKeyType type() const { return CryptoKeyType(type_); }
    uint256& ed25519() { return ed25519_; }

    bool
    operator==(xdr_abstract const& other) override { return  true; }
};

using AccountID = PublicKey;

enum class LedgerVersion : std::int32_t
{
    EMPTY_VERSION = 0
};

class EmptyExt : public xdr_abstract
{
private:
    int32_t type;
    union
    {
    };

    bool
    from_bytes(unmarshaler& u) override;

    bool
    to_bytes(marshaler& m) override;

public:

    bool
    operator==(xdr_abstract const& other) override { return  true; }
};

}