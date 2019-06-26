#include "types.h"
#include "../src/unmarshaler.h"
#include "../src/unmarshaler.t.hpp"

namespace xdr
{
bool
PublicKey::to_bytes(xdr::marshaler& m)
{
    return true;
}

bool
PublicKey::from_bytes(xdr::unmarshaler& u)
{
    u.from_bytes(type_);

    switch (CryptoKeyType(type_))
    {
        case CryptoKeyType::KEY_TYPE_ED25519:
            u.from_bytes(ed25519_);
            break;
        default:
            throw std::runtime_error("gg");
    }

    return true;
}

bool
EmptyExt::to_bytes(xdr::marshaler& m)
{
    return true;
}

bool
EmptyExt::from_bytes(xdr::unmarshaler& u)
{
    u.from_bytes(type);

    switch (LedgerVersion(type))
    {
        case LedgerVersion::EMPTY_VERSION:
            break;
        default:
            throw std::runtime_error("gg");
    }

    return true;
}

}
